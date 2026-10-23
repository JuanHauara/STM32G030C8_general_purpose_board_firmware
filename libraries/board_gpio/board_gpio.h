#ifndef BOARD_GPIO_H
#define BOARD_GPIO_H


#include <stdint.h>
#include <stdbool.h>

#include "board_pinout.h"


typedef enum 
{
	DI0 = 0,
	DI1, 
	DI2, 
	DI3, 
	DI4, 
} board_gpio_di_pin_t;

typedef enum 
{
	/* Board GP output pins */
	DO0 = 0,
	DO1, 
	DO2, 
	DO3, 
	DO4, 
} board_gpio_do_pin_t;

typedef enum 
{
	AI0 = 0,
	AI1, 
	AI2, 
} board_gpio_ai_pin_t;

typedef enum 
{
	GPIO0 = 0, 
	GPIO1, 
	GPIO2,
	GPIO3, 
	GPIO4, 

	STATUS_LED, 
} board_gpio_pin_t;


// Digital pins
bool board_gpio_read_di(board_gpio_di_pin_t pin);
bool board_gpio_read_do(board_gpio_do_pin_t pin);
void board_gpio_write_do(board_gpio_do_pin_t pin, bool pin_state);
void board_gpio_toggle_do(board_gpio_do_pin_t pin);

// Analog pins
uint16_t board_gpio_read_ai(board_gpio_ai_pin_t pin);

// GPIO pins
bool board_gpio_read(board_gpio_pin_t pin);
void board_gpio_write(board_gpio_pin_t pin, bool pin_state);
void board_gpio_toggle(board_gpio_pin_t pin);


#endif  // BOARD_GPIO_H