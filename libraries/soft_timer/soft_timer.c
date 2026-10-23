#include "soft_timer.h"

#include <string.h>
#include "time_utils.h"


/* 
==========================================================================================
||		Provide these function															||
==========================================================================================
*/
#define NUM_MAX_SOFT_TIMERS		20
#define SOFT_TIMER_GET_MS()		t_get_ms()


/* Static variables */
static soft_timer_inst_t *s_timer_list[NUM_MAX_SOFT_TIMERS];
static uint16_t s_num_timers;


/* Static functions */
static bool timer_has_expired(soft_timer_inst_t *soft_timer);


/* Global function definitions */
bool soft_timer_add(soft_timer_inst_t *in_out_timer_inst)
{
	/*
		Adds a new software timer and starts it immediately.

		Returns:
			true	Timer added successfully.
			false	Maximum number of timers (NUM_MAX_SOFT_TIMERS) reached.
	*/

	if (s_num_timers >= NUM_MAX_SOFT_TIMERS)
	{
		return false;
	}

	s_timer_list[s_num_timers] = in_out_timer_inst;

    in_out_timer_inst->timer_id = s_num_timers;
    in_out_timer_inst->first_time = true;
    in_out_timer_inst->is_stop = false;

    s_num_timers++;

    return true;
}

void soft_timer_check_timers(void)
{
	uint16_t idx = 0;

	while (idx < s_num_timers)
	{
		if (timer_has_expired(s_timer_list[idx]))
		{
			if (!s_timer_list[idx]->is_stop)
			{
				// Call the timer handler if it has one.
				if (s_timer_list[idx]->handler != NULL)
				{
					s_timer_list[idx]->handler(s_timer_list[idx]->handler_data_ptr, s_timer_list[idx]->handler_data_int);
				}

				if (s_timer_list[idx]->mode == TIMER_MODE_ONE_SHOT)
				{
					s_timer_list[idx]->is_stop = true;
				}
				else 
				{
					soft_timer_reset(s_timer_list[idx]);  // TIMER_MODE_PERIODIC
				}
			}
		}

		idx++;
	}
}

bool soft_timer_is_running(const soft_timer_inst_t *timer_inst)
{
	/*
		Determines whether the timer is still running.

		If the timer mode is TIMER_MODE_ONE_SHOT, this function returns false
		if it has timed out or was stopped using soft_timer_stop().

		If the timer mode is TIMER_MODE_PERIODIC, this function returns false
		only if it was stopped using soft_timer_stop().

		Returns:
			true	If the timer is still running.
			false	If the timer has timed out or was stopped using
					soft_timer_stop().
	*/

	if (timer_inst == NULL)
	{
		return false;
	}

	if (s_timer_list[timer_inst->timer_id]->is_stop)
	{
		return false;
	}

	return true;
}

void soft_timer_stop(soft_timer_inst_t *out_timer_inst)
{
	/*
		Stops the timer 'without' clearing its current count.
		The timer can be resumed later using soft_timer_resume().
		To restart the timer from its initial value, use soft_timer_reset().
	*/

	if (out_timer_inst == NULL)
	{
		return;
	}

	out_timer_inst->is_stop = true;
}

void soft_timer_resume(soft_timer_inst_t *out_timer_inst)
{
	/*
		Resumes the timer from the point where it was stopped using 
		soft_timer_stop().
	*/

	if (out_timer_inst == NULL)
	{
		return;
	}

	out_timer_inst->is_stop = false;
}

void soft_timer_reset(soft_timer_inst_t *out_timer_inst)
{
	/*
		Resets the timer so it starts counting immediately from 0.
		It does this by setting ti to the current ms value, so the timer
		measures the elapsed time (delta t) from that point onward.

		After resetting the timer count, it calls soft_timer_resume() so 
		the timer starts running immediately.
	*/

	if (out_timer_inst == NULL)
	{
		return;
	}

	out_timer_inst->ti = SOFT_TIMER_GET_MS();
	out_timer_inst->first_time = false;  // Ensures the timer keeps this ti initial value.

	soft_timer_resume(out_timer_inst);
}


/* Static function definitions */
static bool timer_has_expired(soft_timer_inst_t *soft_timer)
{
	if (soft_timer->first_time)
	{
		soft_timer->ti = SOFT_TIMER_GET_MS();
		soft_timer->first_time = false;

		return false;
	}

	if ( (SOFT_TIMER_GET_MS() - soft_timer->ti) >= soft_timer->timeout_ms )
	{
		return true;
	}

	return false;
}

