################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/8359/adc.c \
../drivers/8359/aes.c \
../drivers/8359/analog.c \
../drivers/8359/audio.c \
../drivers/8359/bsp.c \
../drivers/8359/clock.c \
../drivers/8359/emi.c \
../drivers/8359/flash.c \
../drivers/8359/gpio_8258.c \
../drivers/8359/i2c.c \
../drivers/8359/printf.c \
../drivers/8359/random.c \
../drivers/8359/spi.c \
../drivers/8359/timer.c \
../drivers/8359/uart.c \
../drivers/8359/usb.c \
../drivers/8359/usb_desc.c \
../drivers/8359/usbhw.c \
../drivers/8359/watchdog.c 

OBJS += \
./drivers/8359/adc.o \
./drivers/8359/aes.o \
./drivers/8359/analog.o \
./drivers/8359/audio.o \
./drivers/8359/bsp.o \
./drivers/8359/clock.o \
./drivers/8359/emi.o \
./drivers/8359/flash.o \
./drivers/8359/gpio_8258.o \
./drivers/8359/i2c.o \
./drivers/8359/printf.o \
./drivers/8359/random.o \
./drivers/8359/spi.o \
./drivers/8359/timer.o \
./drivers/8359/uart.o \
./drivers/8359/usb.o \
./drivers/8359/usb_desc.o \
./drivers/8359/usbhw.o \
./drivers/8359/watchdog.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/8359/%.o: ../drivers/8359/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Users\Damian\Documents\GitHub\HanshowESL\Firmware" -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


