#include "board_gpio.h"

#include "stm32g0xx_hal.h"


// Digital pins
bool board_gpio_read_di(board_gpio_di_pin_t pin)
{
	switch (pin)
	{
		case DI0:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_DI0, BOARD_GPIO_PIN_DI0);
		case DI1:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_DI1, BOARD_GPIO_PIN_DI1);
		case DI2:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_DI2, BOARD_GPIO_PIN_DI2);
		case DI3:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_DI3, BOARD_GPIO_PIN_DI3);
		case DI4:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_DI4, BOARD_GPIO_PIN_DI4);

		default:
			return false;
	}
}

bool board_gpio_read_do(board_gpio_do_pin_t pin)
{
	switch (pin)
	{
		case DO0:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_DO0, BOARD_GPIO_PIN_DO0);
		case DO1:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_DO1, BOARD_GPIO_PIN_DO1);
		case DO2:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_DO2, BOARD_GPIO_PIN_DO2);
		case DO3:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_DO3, BOARD_GPIO_PIN_DO3);
		case DO4:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_DO4, BOARD_GPIO_PIN_DO4);

		default:
			return false;
	}
}

void board_gpio_write_do(board_gpio_do_pin_t pin, bool pin_state)
{
	switch (pin)
	{
		case DO0:	HAL_GPIO_WritePin(BOARD_GPIO_PORT_DO0, BOARD_GPIO_PIN_DO0, (GPIO_PinState)pin_state);		break;
		case DO1:	HAL_GPIO_WritePin(BOARD_GPIO_PORT_DO1, BOARD_GPIO_PIN_DO1, (GPIO_PinState)pin_state);		break;
		case DO2:	HAL_GPIO_WritePin(BOARD_GPIO_PORT_DO2, BOARD_GPIO_PIN_DO2, (GPIO_PinState)pin_state);		break;
		case DO3:	HAL_GPIO_WritePin(BOARD_GPIO_PORT_DO3, BOARD_GPIO_PIN_DO3, (GPIO_PinState)pin_state);		break;
		case DO4:	HAL_GPIO_WritePin(BOARD_GPIO_PORT_DO4, BOARD_GPIO_PIN_DO4, (GPIO_PinState)pin_state);		break;

		default:
		break;
	}
}

void board_gpio_toggle_do(board_gpio_do_pin_t pin)
{
	switch (pin)
	{
		case DO0:	HAL_GPIO_TogglePin(BOARD_GPIO_PORT_DO0, BOARD_GPIO_PIN_DO0);		break;
		case DO1:	HAL_GPIO_TogglePin(BOARD_GPIO_PORT_DO1, BOARD_GPIO_PIN_DO1);		break;
		case DO2:	HAL_GPIO_TogglePin(BOARD_GPIO_PORT_DO2, BOARD_GPIO_PIN_DO2);		break;
		case DO3:	HAL_GPIO_TogglePin(BOARD_GPIO_PORT_DO3, BOARD_GPIO_PIN_DO3);		break;
		case DO4:	HAL_GPIO_TogglePin(BOARD_GPIO_PORT_DO4, BOARD_GPIO_PIN_DO4);		break;
	
		default:
		break;
	}
}


// GPIO pins
bool board_gpio_read(board_gpio_pin_t pin)
{
	switch (pin)
	{
		case GPIO0:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_0, BOARD_GPIO_PIN_0);
		case GPIO1:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_1, BOARD_GPIO_PIN_1);
		case GPIO2:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_2, BOARD_GPIO_PIN_2);
		case GPIO3:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_3, BOARD_GPIO_PIN_3);
		case GPIO4:	return (bool)HAL_GPIO_ReadPin(BOARD_GPIO_PORT_4, BOARD_GPIO_PIN_4);

		default:
			return false;
	}
}

void board_gpio_write(board_gpio_pin_t pin, bool pin_state)
{
	switch (pin)
	{
		case GPIO0:	HAL_GPIO_WritePin(BOARD_GPIO_PORT_0, BOARD_GPIO_PIN_0, (GPIO_PinState)pin_state);		break;
		case GPIO1:	HAL_GPIO_WritePin(BOARD_GPIO_PORT_1, BOARD_GPIO_PIN_1, (GPIO_PinState)pin_state);		break;
		case GPIO2:	HAL_GPIO_WritePin(BOARD_GPIO_PORT_2, BOARD_GPIO_PIN_2, (GPIO_PinState)pin_state);		break;
		case GPIO3:	HAL_GPIO_WritePin(BOARD_GPIO_PORT_3, BOARD_GPIO_PIN_3, (GPIO_PinState)pin_state);		break;
		case GPIO4:	HAL_GPIO_WritePin(BOARD_GPIO_PORT_4, BOARD_GPIO_PIN_4, (GPIO_PinState)pin_state);		break;

		case STATUS_LED: HAL_GPIO_WritePin(BOARD_GPIO_PORT_DO_STATUS_LED, BOARD_GPIO_PIN_DO_STATUS_LED, (GPIO_PinState)pin_state);	break;

		default:
		break;
	}
}

void board_gpio_toggle(board_gpio_pin_t pin)
{
	switch (pin)
	{
		case GPIO0:	HAL_GPIO_TogglePin(BOARD_GPIO_PORT_0, BOARD_GPIO_PIN_0);		break;
		case GPIO1:	HAL_GPIO_TogglePin(BOARD_GPIO_PORT_1, BOARD_GPIO_PIN_1);		break;
		case GPIO2:	HAL_GPIO_TogglePin(BOARD_GPIO_PORT_2, BOARD_GPIO_PIN_2);		break;
		case GPIO3:	HAL_GPIO_TogglePin(BOARD_GPIO_PORT_3, BOARD_GPIO_PIN_3);		break;
		case GPIO4:	HAL_GPIO_TogglePin(BOARD_GPIO_PORT_4, BOARD_GPIO_PIN_4);		break;
	
		case STATUS_LED: HAL_GPIO_TogglePin(BOARD_GPIO_PORT_DO_STATUS_LED, BOARD_GPIO_PIN_DO_STATUS_LED);	break;

		default:
		break;
	}
}


// Analog pins
uint16_t board_gpio_read_ai(board_gpio_ai_pin_t pin)
{
	// TODO: Implementar esta función.
	return 0;
}

