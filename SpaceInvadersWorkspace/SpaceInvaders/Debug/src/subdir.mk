################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/PITDriver.c \
../src/aliens.c \
../src/bullets.c \
../src/bunkers.c \
../src/counters.c \
../src/globals.c \
../src/platform.c \
../src/render.c \
../src/renderTest.c \
../src/saucer.c \
../src/sounds.c \
../src/spaceInvadersMain.c \
../src/xac97_l.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/PITDriver.o \
./src/aliens.o \
./src/bullets.o \
./src/bunkers.o \
./src/counters.o \
./src/globals.o \
./src/platform.o \
./src/render.o \
./src/renderTest.o \
./src/saucer.o \
./src/sounds.o \
./src/spaceInvadersMain.o \
./src/xac97_l.o 

C_DEPS += \
./src/PITDriver.d \
./src/aliens.d \
./src/bullets.d \
./src/bunkers.d \
./src/counters.d \
./src/globals.d \
./src/platform.d \
./src/render.d \
./src/renderTest.d \
./src/saucer.d \
./src/sounds.d \
./src/spaceInvadersMain.d \
./src/xac97_l.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_0/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


