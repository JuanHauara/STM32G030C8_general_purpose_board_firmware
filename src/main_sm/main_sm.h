#ifndef MAIN_SM_H
#define MAIN_SM_H


#include <stdint.h>

#include "event_sys.h"


void main_sm_init(void);
void main_sm_run(event_type_t evt, void *ptr_data, int32_t int_data);


#endif  // MAIN_SM_H