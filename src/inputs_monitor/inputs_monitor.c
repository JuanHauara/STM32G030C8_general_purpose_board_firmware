#include "inputs_monitor.h"

#include "board_gpio.h"
#include "time_utils.h"
#include "soft_timer.h"
#include "event_sys.h"


#define INPUT_PULSE_SIGNAL_TIMEOUT_MS           (1200U)
#define WAIT_COMPLEMENT_SIGNAL_TIMEOUT_MS       (150U)


/* Types */
typedef enum 
{
    STATE_CHECK_INPUTS = 0, 

    STATE_WAIT_R_SIGNAL, 
    STATE_WAIT_L_SIGNAL, 

    STATE_TURN_ON_R_ONLY, 
    STATE_TURN_ON_L_ONLY, 

    STATE_TURN_ON_BOTH, 
} inputs_monitor_sm_state_t;

/* Static variables */
static inputs_monitor_sm_state_t s_inputs_monitor_sm_state = STATE_CHECK_INPUTS;
static soft_timer_inst_t s_soft_timer_r;
static soft_timer_inst_t s_soft_timer_l;
static soft_timer_inst_t s_soft_timer_wait_sig;
static soft_timer_inst_t s_soft_timer_both;

/* Static functions */
static void inputs_monitor_sm_switch_to_state(inputs_monitor_sm_state_t state);
static bool rising_edge_r_signal(void);
static bool rising_edge_l_signal(void);
static void soft_timer_handler_r(void *data, int32_t int_data);
static void soft_timer_handler_l(void *data, int32_t int_data);
static void soft_timer_handler_both(void *data, int32_t int_data);


/* Global funtions */
void inputs_monitor_init(void)
{
    s_inputs_monitor_sm_state = STATE_CHECK_INPUTS;

    s_soft_timer_r.timeout_ms = INPUT_PULSE_SIGNAL_TIMEOUT_MS;
    s_soft_timer_r.mode = TIMER_MODE_ONE_SHOT;
    s_soft_timer_r.handler = soft_timer_handler_r;
    s_soft_timer_r.handler_data_ptr = NULL;
    s_soft_timer_r.handler_data_int = 0;
    soft_timer_add(&s_soft_timer_r);
    soft_timer_stop(&s_soft_timer_r);

    s_soft_timer_l.timeout_ms = INPUT_PULSE_SIGNAL_TIMEOUT_MS;
    s_soft_timer_l.mode = TIMER_MODE_ONE_SHOT;
    s_soft_timer_l.handler = soft_timer_handler_l;
    s_soft_timer_l.handler_data_ptr = NULL;
    s_soft_timer_l.handler_data_int = 0;
    soft_timer_add(&s_soft_timer_l);
    soft_timer_stop(&s_soft_timer_l);

    s_soft_timer_wait_sig.timeout_ms = WAIT_COMPLEMENT_SIGNAL_TIMEOUT_MS;
    s_soft_timer_wait_sig.mode = TIMER_MODE_ONE_SHOT;
    s_soft_timer_wait_sig.handler = NULL;
    s_soft_timer_wait_sig.handler_data_ptr = NULL;
    s_soft_timer_wait_sig.handler_data_int = 0;
    soft_timer_add(&s_soft_timer_wait_sig);
    soft_timer_stop(&s_soft_timer_wait_sig);

    s_soft_timer_both.timeout_ms = INPUT_PULSE_SIGNAL_TIMEOUT_MS;
    s_soft_timer_both.mode = TIMER_MODE_ONE_SHOT;
    s_soft_timer_both.handler = soft_timer_handler_both;
    s_soft_timer_both.handler_data_ptr = NULL;
    s_soft_timer_both.handler_data_int = 0;
    soft_timer_add(&s_soft_timer_both);
    soft_timer_stop(&s_soft_timer_both);
}

void inputs_monitor_sm_run(void)
{
    switch (s_inputs_monitor_sm_state)
    {
        case STATE_CHECK_INPUTS:
        {
            bool rising_edge_r = rising_edge_r_signal();
            bool rising_edge_l = rising_edge_l_signal();

            // Transitions
            if (rising_edge_r && !rising_edge_l)
            {
                soft_timer_reset(&s_soft_timer_wait_sig);  // Start timer.
                inputs_monitor_sm_switch_to_state(STATE_WAIT_L_SIGNAL);
            }
            else if (!rising_edge_r && rising_edge_l)
            {
                soft_timer_reset(&s_soft_timer_wait_sig);  // Start timer.
                inputs_monitor_sm_switch_to_state(STATE_WAIT_R_SIGNAL);
            }
            else if (rising_edge_r && rising_edge_l)
            {
                inputs_monitor_sm_switch_to_state(STATE_TURN_ON_BOTH);
            }
        }
        break;

        case STATE_WAIT_L_SIGNAL:
        {
            // Wait for the left signal while the timer is running.
            bool rising_edge_in_both = false;
            bool time_out = false;
            if (soft_timer_is_running(&s_soft_timer_wait_sig))
            {
                if (rising_edge_l_signal())
                {
                    rising_edge_in_both = true;
                }
            }
            else 
            {
                time_out = true;
            }

            // Transitions
            if (time_out && !rising_edge_in_both)
            {
                inputs_monitor_sm_switch_to_state(STATE_TURN_ON_R_ONLY);
            }
            else if (!time_out && rising_edge_in_both)
            {
                inputs_monitor_sm_switch_to_state(STATE_TURN_ON_BOTH);
            }
        }
        break;

        case STATE_TURN_ON_R_ONLY:
        {
            event_sys_queue_put(TURN_ON_RIGHT_LIGHT_EVT, NULL, 0);
            soft_timer_reset(&s_soft_timer_r);

            // Transitions
            inputs_monitor_sm_switch_to_state(STATE_CHECK_INPUTS);
        }
        break;

        case STATE_WAIT_R_SIGNAL:
        {
            // Wait for the right signal while the timer is running.
            bool rising_edge_in_both = false;
            bool time_out = false;
            if (soft_timer_is_running(&s_soft_timer_wait_sig))
            {
                if (rising_edge_r_signal())
                {
                    rising_edge_in_both = true;
                }
            }
            else 
            {
                time_out = true;
            }

            // Transitions
            if (time_out && !rising_edge_in_both)
            {
                inputs_monitor_sm_switch_to_state(STATE_TURN_ON_L_ONLY);
            }
            else if (!time_out && rising_edge_in_both)
            {
                inputs_monitor_sm_switch_to_state(STATE_TURN_ON_BOTH);
            }
        }
        break;

        case STATE_TURN_ON_L_ONLY:
        {
            event_sys_queue_put(TURN_ON_LEFT_LIGHT_EVT, NULL, 0);
            soft_timer_reset(&s_soft_timer_l);

            // Transitions
            inputs_monitor_sm_switch_to_state(STATE_CHECK_INPUTS);
        }
        break;

        case STATE_TURN_ON_BOTH:
        {
            event_sys_queue_put(TURN_ON_BOTH_LIGHTS_EVT, NULL, 0);
            soft_timer_reset(&s_soft_timer_both);

            // Transitions
            inputs_monitor_sm_switch_to_state(STATE_CHECK_INPUTS);
        }
        break;
        
        default:
        break;
    }
}


/* Static functions */
static void inputs_monitor_sm_switch_to_state(inputs_monitor_sm_state_t state)
{
    s_inputs_monitor_sm_state = state;
}

static bool rising_edge_r_signal(void)
{
    static bool prev_value = false;

    bool current_value = board_gpio_read_di(DI0);
    if (!prev_value && current_value)
    {
        prev_value = true;

        return true;
    }

    prev_value = current_value;

    return false;
}

static bool rising_edge_l_signal(void)
{
    static bool prev_value = false;

    bool current_value = board_gpio_read_di(DI1);
    if (!prev_value && current_value)
    {
        prev_value = true;

        return true;
    }

    prev_value = current_value;

    return false;
}

static void soft_timer_handler_r(void *data, int32_t int_data)
{
    event_sys_queue_put(TURN_OFF_RIGHT_LIGHT_EVT, NULL, 0);
}

static void soft_timer_handler_l(void *data, int32_t int_data)
{
    event_sys_queue_put(TURN_OFF_LEFT_LIGHT_EVT, NULL, 0);
}

static void soft_timer_handler_both(void *data, int32_t int_data)
{
    event_sys_queue_put(TURN_OFF_BOTH_LIGHTS_EVT, NULL, 0);
}

