#include "time_utils.h"

#include "stm32g0xx_hal.h"


#define T_DELAY_US_MAX		60000


/* Global variables */
extern TIM_HandleTypeDef htim14;
extern IWDG_HandleTypeDef hiwdg;

static uint32_t wdt_timeout_ms;


/* --------- Implement these functions --------- */
void time_utils_init(void)
{
	/*
		Calculate the watchdog timeout:
		timeout = (reload_value + 1) × prescaler / frec_LSI

		frec_LSI = 32KHz
	*/

	uint32_t prescaler = 0;

	switch (hiwdg.Init.Prescaler)
	{
		case IWDG_PRESCALER_4:
			prescaler = 4;
			break;

		case IWDG_PRESCALER_8:
			prescaler = 8;
			break;

		case IWDG_PRESCALER_16:
			prescaler = 16;
			break;

		case IWDG_PRESCALER_32:
			prescaler = 32;
			break;

		case IWDG_PRESCALER_64:
			prescaler = 64;
			break;

		case IWDG_PRESCALER_128:
			prescaler = 128;
			break;

		case IWDG_PRESCALER_256:
			prescaler = 256;
			break;
		
		default:
			break;
	}

	if (prescaler > 0)
	{
		wdt_timeout_ms = ( (hiwdg.Init.Reload + 1) * prescaler ) / 32;
	}
}

void t_delay_ms(uint32_t ms)
{
	/*
		t_delay_ms() generates a blocking delay in milliseconds.

		The watchdog is handled internally by this function. The caller does not
		need to refresh the watchdog before calling it, after it returns, or during
		long delays, even when the requested delay is longer than the configured
		watchdog timeout.
	*/

	while (1)
	{
		HAL_IWDG_Refresh(&hiwdg);  // Reset watchdog.

		if ( ms <= (wdt_timeout_ms / 2) )
		{
			HAL_Delay(ms);
			HAL_IWDG_Refresh(&hiwdg);  // Reset watchdog.

			return;
		}
		else
		{
			HAL_Delay(wdt_timeout_ms / 2);
			ms -= (wdt_timeout_ms / 2);
		}
	}
}

void t_delay_us(uint16_t us)
{
	/*
		t_delay_us() generates a blocking delay in microseconds using TIM14.

		TIM14 is configured as a free-running 16-bit timer at 1 MHz
		(1 tick = 1 us). The function captures the current counter value
		and waits until the desired number of microseconds has elapsed.

		Overflow handling:
		TIM14 overflows every 65.536 ms. Elapsed time is calculated using
		16-bit unsigned arithmetic, so counter overflow is handled naturally
		through modulo-65536 subtraction.

		Watchdog handling:
		The watchdog is refreshed before and after the delay, and periodically
		during the delay. Therefore, the caller does not need to handle the
		watchdog, even when the watchdog timeout is shorter than the requested
		delay.
	*/

	if (us > T_DELAY_US_MAX)
	{
		us = T_DELAY_US_MAX;
	}

	// Refresh at half the configured watchdog timeout.
	uint32_t wdt_refresh_period_us = ((uint32_t)wdt_timeout_ms * 1000U) / 2U;

	if (wdt_refresh_period_us == 0U)
	{
		wdt_refresh_period_us = 1U;
	}

	HAL_IWDG_Refresh(&hiwdg);

	uint16_t ti = (uint16_t)__HAL_TIM_GET_COUNTER(&htim14);
	uint16_t last_wdt_refresh = ti;

	while (1)
	{
		uint16_t now = (uint16_t)__HAL_TIM_GET_COUNTER(&htim14);
		uint16_t elapsed = (uint16_t)(now - ti);

		if (elapsed >= us)
		{
			break;
		}

		if ((uint16_t)(now - last_wdt_refresh) >= wdt_refresh_period_us)
		{
			HAL_IWDG_Refresh(&hiwdg);
			last_wdt_refresh = now;
		}
	}

	HAL_IWDG_Refresh(&hiwdg);
}

uint32_t t_get_ms(void)
{
	return HAL_GetTick();
}


/* --------------------------------------------- */

