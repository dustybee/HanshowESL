################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 

OBJS += \
$(OUT_PATH)/app.o \
$(OUT_PATH)/led.o \
$(OUT_PATH)/app_ble.o \
$(OUT_PATH)/app_uart.o \
$(OUT_PATH)/app_att.o \
$(OUT_PATH)/epd.o \
$(OUT_PATH)/epd_spi.o \
$(OUT_PATH)/main.o 

# Each subdirectory must supply rules for building sources it contributes
$(OUT_PATH)/%.o: ./%.c
	@echo 'Building file: $<'
	@tc32-elf-gcc $(GCC_FLAGS) $(INCLUDE_PATHS) -c -o"$@" "$<"