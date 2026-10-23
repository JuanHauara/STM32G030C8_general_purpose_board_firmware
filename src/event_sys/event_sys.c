#include "event_sys.h"

#include <stddef.h>


#define EVENT_QUEUE_SIZE	20


// Types
typedef struct
{
	event_type_t evt_type;
	void *ptr_data; 
	int32_t int_data;
} event_t;

// Static variables.
static event_handler_t event_handler;
static event_t s_event_queue[EVENT_QUEUE_SIZE];
static volatile uint8_t s_head_idx;
static volatile uint8_t s_tail_idx;

// Static functions.
static bool event_sys_queue_pop(event_t *event);


void event_sys_config(event_handler_t _event_handler)
{
	event_handler = _event_handler;
}

bool event_sys_queue_put(event_type_t evt, void *ptr_data, int32_t int_data)
{
	/*
		Save a new event in the circular buffer.
		Return true on succes or false if the buffer is full.
	*/

	uint8_t next = (s_head_idx + 1) % EVENT_QUEUE_SIZE;

	if (next == s_tail_idx) 
	{
		return false;  // Queue is full.
	}

	s_event_queue[s_head_idx] = (event_t){evt, ptr_data, int_data};
	s_head_idx = next;

	return true;
}

static bool event_sys_queue_pop(event_t *event)
{
	/*
		Get an event from the circular buffer.
		Return true on succes or false if the buffer is empty.
	*/

	if (s_head_idx == s_tail_idx) 
	{
		return false;  // Queue is empty.
	}

	*event = s_event_queue[s_tail_idx];
	s_tail_idx = (s_tail_idx + 1) % EVENT_QUEUE_SIZE;

	return true;
}

void event_sys_loop(void)
{
	event_t evt;

	while (event_sys_queue_pop(&evt))
	{
		if (event_handler != NULL) 
		{
			event_handler(evt.evt_type, evt.ptr_data, evt.int_data);
		}
	}
}