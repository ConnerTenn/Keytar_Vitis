################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Video/lvgl/tests/lv_test_fonts/font_1.c \
../src/Video/lvgl/tests/lv_test_fonts/font_2.c \
../src/Video/lvgl/tests/lv_test_fonts/font_3.c 

OBJS += \
./src/Video/lvgl/tests/lv_test_fonts/font_1.o \
./src/Video/lvgl/tests/lv_test_fonts/font_2.o \
./src/Video/lvgl/tests/lv_test_fonts/font_3.o 

C_DEPS += \
./src/Video/lvgl/tests/lv_test_fonts/font_1.d \
./src/Video/lvgl/tests/lv_test_fonts/font_2.d \
./src/Video/lvgl/tests/lv_test_fonts/font_3.d 


# Each subdirectory must supply rules for building sources it contributes
src/Video/lvgl/tests/lv_test_fonts/%.o: ../src/Video/lvgl/tests/lv_test_fonts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O3 -g3 -IZ:/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/core1/bspinclude/include -I"Z:\Projects\Keytar\VitisWorkspace\UIController\src\Video" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IZ:/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/core1/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


