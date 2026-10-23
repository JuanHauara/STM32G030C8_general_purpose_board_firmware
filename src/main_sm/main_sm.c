#include "main_sm.h"

#include "board_gpio.h"
#include "time_utils.h"
#include "soft_timer.h"


/* Types */
typedef enum 
{
    STATE_INIT = 0, 
    STATE_IDLE, 

	STATE_TURN_ON_RIGHT_LIGHTS, 
	STATE_TURN_ON_LEFT_LIGHTS, 

	STATE_TURN_OFF_RIGHT_LIGHTS, 
	STATE_TURN_OFF_LEFT_LIGHTS, 

	STATE_TURN_ON_BOTH_LIGHTS, 
	STATE_TURN_OFF_BOTH_LIGHTS, 
} main_sm_state_t;

/* Static variables */
static main_sm_state_t s_main_sm_state = STATE_INIT;

/* Static functions */
static void main_sm_switch_to_state(main_sm_state_t state);


/* Global functions */
void main_sm_init(void)
{
    event_sys_config(main_sm_run);  // The event handler is the main state machine itself.
}

void main_sm_run(event_type_t evt, void *ptr_data, int32_t int_data)
{
    switch (s_main_sm_state)
    {
        case STATE_INIT:
        {
            board_gpio_write_do(DO0, false);
            board_gpio_write_do(DO1, false);

            // Transitions
            main_sm_switch_to_state(STATE_IDLE);
        }
        break;

        case STATE_IDLE:
        {
            // Transitions
            if (evt == TURN_ON_RIGHT_LIGHT_EVT)
            {
                main_sm_switch_to_state(STATE_TURN_ON_RIGHT_LIGHTS);
            }
            else if (evt == TURN_ON_LEFT_LIGHT_EVT)
            {
                main_sm_switch_to_state(STATE_TURN_ON_LEFT_LIGHTS);
            }
            else if (evt == TURN_OFF_RIGHT_LIGHT_EVT)
            {
                main_sm_switch_to_state(STATE_TURN_OFF_RIGHT_LIGHTS);
            }
            else if (evt == TURN_OFF_LEFT_LIGHT_EVT)
            {
                main_sm_switch_to_state(STATE_TURN_OFF_LEFT_LIGHTS);
            }
            else if (evt == TURN_ON_BOTH_LIGHTS_EVT)
            {
                main_sm_switch_to_state(STATE_TURN_ON_BOTH_LIGHTS);
            }
            else if (evt == TURN_OFF_BOTH_LIGHTS_EVT)
            {
                main_sm_switch_to_state(STATE_TURN_OFF_BOTH_LIGHTS);
            }
        }
        break;

        case STATE_TURN_ON_RIGHT_LIGHTS:
        {
            board_gpio_write_do(DO0, true);
            board_gpio_write_do(DO1, false);

            // Transitions
            main_sm_switch_to_state(STATE_IDLE);
        }
        break;

        case STATE_TURN_ON_LEFT_LIGHTS:
        {
            board_gpio_write_do(DO0, false);
            board_gpio_write_do(DO1, true);

            // Transitions
            main_sm_switch_to_state(STATE_IDLE);
        }
        break;

        case STATE_TURN_OFF_RIGHT_LIGHTS:
        {
            board_gpio_write_do(DO0, false);

            // Transitions
            main_sm_switch_to_state(STATE_IDLE);
        }
        break;

        case STATE_TURN_OFF_LEFT_LIGHTS:
        {
            board_gpio_write_do(DO1, false);

            // Transitions
            main_sm_switch_to_state(STATE_IDLE);
        }
        break;

        case STATE_TURN_ON_BOTH_LIGHTS:
        {
            board_gpio_write_do(DO0, true);
            board_gpio_write_do(DO1, true);

            // Transitions
            main_sm_switch_to_state(STATE_IDLE);
        }
        break;

        case STATE_TURN_OFF_BOTH_LIGHTS:
        {
            board_gpio_write_do(DO0, false);
            board_gpio_write_do(DO1, false);

            // Transitions
            main_sm_switch_to_state(STATE_IDLE);
        }
        break;
        
        default:
        {
            board_gpio_write_do(DO0, false);
            board_gpio_write_do(DO1, false);
        }
        break;
    }
}


/* Static functions */
static void main_sm_switch_to_state(main_sm_state_t state)
{
    s_main_sm_state = state;
}
