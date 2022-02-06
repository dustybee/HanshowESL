################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include static/subdir.mk
-include src/subdir.mk
-include out/static/subdir.mk
-include out/src/subdir.mk
-include out/drivers/SSD1680/subdir.mk
-include out/drivers/8359/subdir.mk
-include out/common/subdir.mk
-include out/boot/subdir.mk
-include drivers/SSD1680/subdir.mk
-include drivers/8359/subdir.mk
-include common/subdir.mk
-include boot/subdir.mk
-include objects.mk

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LST += \
OUTPUT.lst \

FLASH_IMAGE += \
OUTPUT.bin \

SIZEDUMMY += \
sizedummy \


# All Target
all: EPD_ESL.elf secondary-outputs

# Tool invocations
EPD_ESL.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: TC32 C Linker'
	tc32-elf-ld --gc-sections  -T ../boot.link -o"EPD_ESL.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

OUTPUT.lst: EPD_ESL.elf
	@echo 'Invoking: TC32 Create Extended Listing'
	tc32-elf-objdump -x -D -l -S EPD_ESL.elf  >"OUTPUT.lst"
	@echo 'Finished building: $@'
	@echo ' '

OUTPUT.bin: EPD_ESL.elf
	@echo 'Create Flash image (binary format)'
	tc32-elf-objcopy -O binary EPD_ESL.elf  "OUTPUT.bin"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: EPD_ESL.elf
	@echo 'Invoking: Print Size'
	tc32-elf-size -t EPD_ESL.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(LST)$(SIZEDUMMY) EPD_ESL.elf
	-@echo ' '

secondary-outputs: $(LST) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
