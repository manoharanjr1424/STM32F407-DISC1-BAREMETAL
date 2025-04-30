################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../driver/flash.c \
../driver/gpio.c \
../driver/i2c.c \
../driver/interrupt.c \
../driver/mcu.c \
../driver/timer.c \
../driver/uart.c 

OBJS += \
./driver/flash.o \
./driver/gpio.o \
./driver/i2c.o \
./driver/interrupt.o \
./driver/mcu.o \
./driver/timer.o \
./driver/uart.o 

C_DEPS += \
./driver/flash.d \
./driver/gpio.d \
./driver/i2c.d \
./driver/interrupt.d \
./driver/mcu.d \
./driver/timer.d \
./driver/uart.d 


# Each subdirectory must supply rules for building sources it contributes
driver/%.o driver/%.su driver/%.cyclo: ../driver/%.c driver/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-driver

clean-driver:
	-$(RM) ./driver/flash.cyclo ./driver/flash.d ./driver/flash.o ./driver/flash.su ./driver/gpio.cyclo ./driver/gpio.d ./driver/gpio.o ./driver/gpio.su ./driver/i2c.cyclo ./driver/i2c.d ./driver/i2c.o ./driver/i2c.su ./driver/interrupt.cyclo ./driver/interrupt.d ./driver/interrupt.o ./driver/interrupt.su ./driver/mcu.cyclo ./driver/mcu.d ./driver/mcu.o ./driver/mcu.su ./driver/timer.cyclo ./driver/timer.d ./driver/timer.o ./driver/timer.su ./driver/uart.cyclo ./driver/uart.d ./driver/uart.o ./driver/uart.su

.PHONY: clean-driver

