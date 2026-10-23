#ifndef BOARD_PINOUT_H
#define BOARD_PINOUT_H


#include "stm32g0xx_hal.h"


/*---------------------------------------------------------------*/
/*-- Board GP input pins                                      -- */
/*---------------------------------------------------------------*/
#define BOARD_GPIO_PORT_DI0		GPIOB
#define BOARD_GPIO_PIN_DI0		GPIO_PIN_11

#define BOARD_GPIO_PORT_DI1		GPIOB
#define BOARD_GPIO_PIN_DI1		GPIO_PIN_12

#define BOARD_GPIO_PORT_DI2		GPIOB
#define BOARD_GPIO_PIN_DI2		GPIO_PIN_13

#define BOARD_GPIO_PORT_DI3		GPIOB
#define BOARD_GPIO_PIN_DI3		GPIO_PIN_14

#define BOARD_GPIO_PORT_DI4		GPIOB
#define BOARD_GPIO_PIN_DI4		GPIO_PIN_15


/*---------------------------------------------------------------*/
/*-- Board GP output pins                                     -- */
/*---------------------------------------------------------------*/
#define BOARD_GPIO_PORT_DO0		GPIOA
#define BOARD_GPIO_PIN_DO0		GPIO_PIN_8

#define BOARD_GPIO_PORT_DO1		GPIOA
#define BOARD_GPIO_PIN_DO1		GPIO_PIN_9

#define BOARD_GPIO_PORT_DO2		GPIOC
#define BOARD_GPIO_PIN_DO2		GPIO_PIN_6

#define BOARD_GPIO_PORT_DO3		GPIOC
#define BOARD_GPIO_PIN_DO3		GPIO_PIN_7

#define BOARD_GPIO_PORT_DO4		GPIOA
#define BOARD_GPIO_PIN_DO4		GPIO_PIN_10


/*---------------------------------------------------------------*/
/*-- Board internal pins                                      -- */
/*---------------------------------------------------------------*/
#define BOARD_GPIO_PORT_DO_STATUS_LED       GPIOA
#define BOARD_GPIO_PIN_DO_STATUS_LED        GPIO_PIN_15

// GPIO pins
#define BOARD_GPIO_PORT_0       GPIOB
#define BOARD_GPIO_PIN_0        GPIO_PIN_3

#define BOARD_GPIO_PORT_1       GPIOD
#define BOARD_GPIO_PIN_1        GPIO_PIN_3

#define BOARD_GPIO_PORT_2       GPIOD
#define BOARD_GPIO_PIN_2        GPIO_PIN_2

#define BOARD_GPIO_PORT_3       GPIOD
#define BOARD_GPIO_PIN_3        GPIO_PIN_1

#define BOARD_GPIO_PORT_4       GPIOD
#define BOARD_GPIO_PIN_4        GPIO_PIN_0


#endif  // BOARD_PINOUT_H