################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Video/lvgl/tests/lv_test_core/lv_test_core.c \
../src/Video/lvgl/tests/lv_test_core/lv_test_font_loader.c \
../src/Video/lvgl/tests/lv_test_core/lv_test_obj.c \
../src/Video/lvgl/tests/lv_test_core/lv_test_style.c 

OBJS += \
./src/Video/lvgl/tests/lv_test_core/lv_test_core.o \
./src/Video/lvgl/tests/lv_test_core/lv_test_font_loader.o \
./src/Video/lvgl/tests/lv_test_core/lv_test_obj.o \
./src/Video/lvgl/tests/lv_test_core/lv_test_style.o 

C_DEPS += \
./src/Video/lvgl/tests/lv_test_core/lv_test_core.d \
./src/Video/lvgl/tests/lv_test_core/lv_test_font_loader.d \
./src/Video/lvgl/tests/lv_test_core/lv_test_obj.d \
./src/Video/lvgl/tests/lv_test_core/lv_test_style.d 


# Each subdirectory must supply rules for building sources it contributes
src/Video/lvgl/tests/lv_test_core/%.o: ../src/Video/lvgl/tests/lv_test_core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/USB" -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video" -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video/lvgl" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


