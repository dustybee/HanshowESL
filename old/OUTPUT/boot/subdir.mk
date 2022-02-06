################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../boot/cstartup_8258.S 

OBJS += \
./boot/cstartup_8258.o 


# Each subdirectory must supply rules for building sources it contributes
boot/%.o: ../boot/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 CC/Assembler'
	tc32-elf-gcc  -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


