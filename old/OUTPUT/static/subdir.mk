################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../static/div_mod.S 

OBJS += \
./static/div_mod.o 


# Each subdirectory must supply rules for building sources it contributes
static/%.o: ../static/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 CC/Assembler'
	tc32-elf-gcc  -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


