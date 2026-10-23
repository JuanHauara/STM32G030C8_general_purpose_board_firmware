################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/time_utils/time_utils.c 

OBJS += \
./libraries/time_utils/time_utils.o 

C_DEPS += \
./libraries/time_utils/time_utils.d 


# Each subdirectory must supply rules for building sources it contributes
libraries/time_utils/%.o libraries/time_utils/%.su libraries/time_utils/%.cyclo: ../libraries/time_utils/%.c libraries/time_utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../libraries/board_gpio -I../libraries/time_utils -I../libraries/soft_timer -I../src/event_sys -I../src/inputs_monitor -I../src/main_sm -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-libraries-2f-time_utils

clean-libraries-2f-time_utils:
	-$(RM) ./libraries/time_utils/time_utils.cyclo ./libraries/time_utils/time_utils.d ./libraries/time_utils/time_utils.o ./libraries/time_utils/time_utils.su

.PHONY: clean-libraries-2f-time_utils

