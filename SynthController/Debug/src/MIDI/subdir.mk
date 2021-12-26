################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/MIDI/MIDI_Actions.c \
../src/MIDI/MIDI_Processor.c 

OBJS += \
./src/MIDI/MIDI_Actions.o \
./src/MIDI/MIDI_Processor.o 

C_DEPS += \
./src/MIDI/MIDI_Actions.d \
./src/MIDI/MIDI_Processor.d 


# Each subdirectory must supply rules for building sources it contributes
src/MIDI/%.o: ../src/MIDI/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/standalone_domain/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


