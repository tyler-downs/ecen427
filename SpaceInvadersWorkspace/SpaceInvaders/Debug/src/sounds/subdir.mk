################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/sounds/UFOHighPitchSound.c \
../src/sounds/UFOLowPitchSound.c \
../src/sounds/alienKilledSound.c \
../src/sounds/alienMoveSound1.c \
../src/sounds/alienMoveSound2.c \
../src/sounds/alienMoveSound3.c \
../src/sounds/alienMoveSound4.c \
../src/sounds/explosionSound.c \
../src/sounds/shootSound.c 

OBJS += \
./src/sounds/UFOHighPitchSound.o \
./src/sounds/UFOLowPitchSound.o \
./src/sounds/alienKilledSound.o \
./src/sounds/alienMoveSound1.o \
./src/sounds/alienMoveSound2.o \
./src/sounds/alienMoveSound3.o \
./src/sounds/alienMoveSound4.o \
./src/sounds/explosionSound.o \
./src/sounds/shootSound.o 

C_DEPS += \
./src/sounds/UFOHighPitchSound.d \
./src/sounds/UFOLowPitchSound.d \
./src/sounds/alienKilledSound.d \
./src/sounds/alienMoveSound1.d \
./src/sounds/alienMoveSound2.d \
./src/sounds/alienMoveSound3.d \
./src/sounds/alienMoveSound4.d \
./src/sounds/explosionSound.d \
./src/sounds/shootSound.d 


# Each subdirectory must supply rules for building sources it contributes
src/sounds/%.o: ../src/sounds/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../hello_world_bsp_2/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mxl-pattern-compare -mcpu=v8.20.b -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


