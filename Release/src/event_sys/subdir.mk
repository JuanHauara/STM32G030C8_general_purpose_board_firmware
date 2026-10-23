################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/event_sys/event_sys.c 

OBJS += \
./src/event_sys/event_sys.o 

C_DEPS += \
./src/event_sys/event_sys.d 


# Each subdirectory must supply rules for building sources it contributes
src/event_sys/%.o src/event_sys/%.su src/event_sys/%.cyclo: ../src/event_sys/%.c src/event_sys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../libraries/board_gpio -I../libraries/time_utils -I../libraries/soft_timer -I../src/event_sys -I../src/inputs_monitor -I../src/main_sm -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-event_sys

clean-src-2f-event_sys:
	-$(RM) ./src/event_sys/event_sys.cyclo ./src/event_sys/event_sys.d ./src/event_sys/event_sys.o ./src/event_sys/event_sys.su

.PHONY: clean-src-2f-event_sys

