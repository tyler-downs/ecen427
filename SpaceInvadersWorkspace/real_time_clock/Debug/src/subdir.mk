################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PITDriver.c \
../src/platform.c \
../src/realtimeclock_main.c \
../src/setTimeSM.c \
../src/sharedGlobals.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/PITDriver.o \
./src/platform.o \
./src/realtimeclock_main.o \
./src/setTimeSM.o \
./src/sharedGlobals.o 

C_DEPS += \
./src/PITDriver.d \
./src/platform.d \
./src/realtimeclock_main.d \
./src/setTimeSM.d \
./src/sharedGlobals.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


