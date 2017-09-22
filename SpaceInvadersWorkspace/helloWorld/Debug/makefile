################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
helloWorld.elf.size \


# All Target
all: helloWorld.elf secondary-outputs

# Tool invocations
helloWorld.elf: $(OBJS)  $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: ARM gcc linker
	arm-xilinx-eabi-gcc  -o"helloWorld.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

helloWorld.elf.size: helloWorld.elf
	@echo Invoking: ARM Print Size
	arm-xilinx-eabi-size helloWorld.elf  |tee "helloWorld.elf.size"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(S_UPPER_DEPS) helloWorld.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
