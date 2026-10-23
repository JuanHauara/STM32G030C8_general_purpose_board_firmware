/*
	Simple events management system
*/

#ifndef EVENT_SYS_H
#define EVENT_SYS_H


#include <stdint.h>
#include <stdbool.h>


// Events
typedef enum 
{
	NO_EVENT_EVT = 0, 

	TURN_ON_RIGHT_LIGHT_EVT, 
	TURN_ON_LEFT_LIGHT_EVT, 

	TURN_OFF_RIGHT_LIGHT_EVT, 
	TURN_OFF_LEFT_LIGHT_EVT, 

	TURN_ON_BOTH_LIGHTS_EVT, 
	TURN_OFF_BOTH_LIGHTS_EVT, 
} event_type_t;

// Event handler
typedef void (*event_handler_t)(event_type_t evt, void *ptr_data, int32_t int_data);


// Global functions.
void event_sys_config(event_handler_t _event_handler);
bool event_sys_queue_put(event_type_t evt, void *ptr_data, int32_t int_data);
void event_sys_loop(void);


#endif  // EVENT_SYS_H
