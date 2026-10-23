################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/board_gpio/board_gpio.c 

OBJS += \
./libraries/board_gpio/board_gpio.o 

C_DEPS += \
./libraries/board_gpio/board_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/board_gpio/%.o libraries/board_gpio/%.su libraries/board_gpio/%.cyclo: ../libraries/board_gpio/%.c libraries/board_gpio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../libraries/board_gpio -I../libraries/time_utils -I../libraries/soft_timer -I../src/event_sys -I../src/inputs_monitor -I../src/main_sm -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libraries-2f-board_gpio

clean-libraries-2f-board_gpio:
	-$(RM) ./libraries/board_gpio/board_gpio.cyclo ./libraries/board_gpio/board_gpio.d ./libraries/board_gpio/board_gpio.o ./libraries/board_gpio/board_gpio.su

.PHONY: clean-libraries-2f-board_gpio

