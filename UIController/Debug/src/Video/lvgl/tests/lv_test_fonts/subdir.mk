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
	arm-none-eabi-gcc -Wall -O0 -g3 -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video" -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video/lvgl" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


