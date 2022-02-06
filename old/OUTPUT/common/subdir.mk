################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../common/list.c \
../common/log.c \
../common/mempool.c \
../common/mmem.c \
../common/printf.c \
../common/qsort.c \
../common/selection_sort.c \
../common/string.c \
../common/timer_event.c \
../common/tn_list.c \
../common/tn_mm.c \
../common/utility.c 

OBJS += \
./common/list.o \
./common/log.o \
./common/mempool.o \
./common/mmem.o \
./common/printf.o \
./common/qsort.o \
./common/selection_sort.o \
./common/string.o \
./common/timer_event.o \
./common/tn_list.o \
./common/tn_mm.o \
./common/utility.o 


# Each subdirectory must supply rules for building sources it contributes
common/%.o: ../common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"C:\Users\Damian\Documents\GitHub\HanshowESL\Firmware" -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


