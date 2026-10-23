################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/main_sm/main_sm.c 

OBJS += \
./src/main_sm/main_sm.o 

C_DEPS += \
./src/main_sm/main_sm.d 


# Each subdirectory must supply rules for building sources it contributes
src/main_sm/%.o src/main_sm/%.su src/main_sm/%.cyclo: ../src/main_sm/%.c src/main_sm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -DUSE_HAL_DRIVER -DSTM32G030xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I../libraries/board_gpio -I../libraries/time_utils -I../libraries/soft_timer -I../src/event_sys -I../src/inputs_monitor -I../src/main_sm -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src-2f-main_sm

clean-src-2f-main_sm:
	-$(RM) ./src/main_sm/main_sm.cyclo ./src/main_sm/main_sm.d ./src/main_sm/main_sm.o ./src/main_sm/main_sm.su

.PHONY: clean-src-2f-main_sm

