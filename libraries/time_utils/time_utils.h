#ifndef TIME_UTILS_H
#define TIME_UTILS_H


#include <stdint.h>
#include <stdbool.h>


void time_utils_init(void);

void t_delay_ms(uint32_t ms);
void t_delay_us(uint16_t us);
uint32_t t_get_ms(void);


#endif  // TIME_UTILS_H