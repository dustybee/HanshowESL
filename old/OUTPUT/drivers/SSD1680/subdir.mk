################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/SSD1680/epd.c \
../drivers/SSD1680/epd_GUI.c \
../drivers/SSD1680/epd_spi.c \
../drivers/SSD1680/font12.c \
../drivers/SSD1680/font16.c \
../drivers/SSD1680/font20.c \
../drivers/SSD1680/font24.c \
../drivers/SSD1680/font8.c 

OBJS += \
./drivers/SSD1680/epd.o \
./drivers/SSD1680/epd_GUI.o \
./drivers/SSD1680/epd_spi.o \
./drivers/SSD1680/font12.o \
./drivers/SSD1680/font16.o \
./drivers/SSD1680/font20.o \
./drivers/SSD1680/font24.o \
./drivers/SSD1680/font8.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/SSD1680/%.o: ../drivers/SSD1680/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Users\Damian\Documents\GitHub\HanshowESL\Firmware" -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


