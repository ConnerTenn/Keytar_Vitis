################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Video/lvgl/tests/lv_test_assert.c \
../src/Video/lvgl/tests/lv_test_main.c 

OBJS += \
./src/Video/lvgl/tests/lv_test_assert.o \
./src/Video/lvgl/tests/lv_test_main.o 

C_DEPS += \
./src/Video/lvgl/tests/lv_test_assert.d \
./src/Video/lvgl/tests/lv_test_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/Video/lvgl/tests/%.o: ../src/Video/lvgl/tests/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O3 -g3 -IZ:/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/core1/bspinclude/include -I"Z:\Projects\Keytar\VitisWorkspace\UIController\src\Video" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


