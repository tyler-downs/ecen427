################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
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
hello_world_dma.elf.size \

ELFCHECK += \
hello_world_dma.elf.elfcheck \


# All Target
all: hello_world_dma.elf secondary-outputs

# Tool invocations
hello_world_dma.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo Building target: $@
	@echo Invoking: MicroBlaze gcc linker
	mb-gcc -Wl,-T -Wl,../src/lscript.ld -L../../hello_world_bsp_dma/microblaze_0/lib -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -o"hello_world_dma.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo Finished building target: $@
	@echo ' '

hello_world_dma.elf.size: hello_world_dma.elf
	@echo Invoking: MicroBlaze Print Size
	mb-size hello_world_dma.elf  |tee "hello_world_dma.elf.size"
	@echo Finished building: $@
	@echo ' '

hello_world_dma.elf.elfcheck: hello_world_dma.elf
	@echo Invoking: Xilinx ELF Check
	elfcheck hello_world_dma.elf -hw ../../SpaceInvaders_hw_platform/system.xml -pe microblaze_0  |tee "hello_world_dma.elf.elfcheck"
	@echo Finished building: $@
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES)$(ELFSIZE)$(ELFCHECK)$(S_UPPER_DEPS) hello_world_dma.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE) $(ELFCHECK)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
