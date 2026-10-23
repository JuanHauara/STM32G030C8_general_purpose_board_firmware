/*
	The maximum number of timers that can be created is configured with NUM_MAX_SOFT_TIMERS.

	The following functions may be called from within a soft_timer_handler_t:
		bool soft_timer_is_running(const soft_timer_inst_t *timer)
		bool soft_timer_stop(const soft_timer_inst_t *timer)
		bool soft_timer_resume(const soft_timer_inst_t *timer)
		bool soft_timer_reset(const soft_timer_inst_t *timer)

	Ejemplo de uso:

	- Crear una instancia global soft_timer_inst_t:
		soft_timer_inst_t s_timer;

	- Añadir el timer para que comience a correr en alguna función init() del programa:

		g_timer.timeout_ms
*/

#ifndef SOFT_TIMER_H
#define SOFT_TIMER_H


#include <stdint.h>
#include <stdbool.h>


/* Types */
typedef void (*soft_timer_handler_t)(void *data, int32_t int_data);  // Function signature for Software Timers handlers.

typedef enum 
{
	TIMER_MODE_ONE_SHOT = 0, 
	TIMER_MODE_PERIODIC = 1, 
} soft_timer_mode_t;

typedef struct
{
	// Setting variables.
	uint32_t timeout_ms;
	soft_timer_mode_t mode;
	soft_timer_handler_t handler;
	void *handler_data_ptr;
	int32_t handler_data_int;
	
	// Internal variables.
	uint16_t timer_id;
	uint32_t ti;
	bool first_time;
	bool is_stop;
} soft_timer_inst_t;


/* Global functions */
void soft_timer_check_timers(void);
bool soft_timer_add(soft_timer_inst_t *in_out_timer_inst);

bool soft_timer_is_running(const soft_timer_inst_t *timer_inst);
void soft_timer_stop(soft_timer_inst_t *out_timer_inst);
void soft_timer_resume(soft_timer_inst_t *out_timer_inst);
void soft_timer_reset(soft_timer_inst_t *out_timer_inst);


#endif  // SOFT_TIMER_H