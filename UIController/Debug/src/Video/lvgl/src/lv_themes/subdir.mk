################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Video/lvgl/src/lv_themes/lv_theme.c \
../src/Video/lvgl/src/lv_themes/lv_theme_empty.c \
../src/Video/lvgl/src/lv_themes/lv_theme_material.c \
../src/Video/lvgl/src/lv_themes/lv_theme_mono.c \
../src/Video/lvgl/src/lv_themes/lv_theme_template.c 

OBJS += \
./src/Video/lvgl/src/lv_themes/lv_theme.o \
./src/Video/lvgl/src/lv_themes/lv_theme_empty.o \
./src/Video/lvgl/src/lv_themes/lv_theme_material.o \
./src/Video/lvgl/src/lv_themes/lv_theme_mono.o \
./src/Video/lvgl/src/lv_themes/lv_theme_template.o 

C_DEPS += \
./src/Video/lvgl/src/lv_themes/lv_theme.d \
./src/Video/lvgl/src/lv_themes/lv_theme_empty.d \
./src/Video/lvgl/src/lv_themes/lv_theme_material.d \
./src/Video/lvgl/src/lv_themes/lv_theme_mono.d \
./src/Video/lvgl/src/lv_themes/lv_theme_template.d 


# Each subdirectory must supply rules for building sources it contributes
src/Video/lvgl/src/lv_themes/%.o: ../src/Video/lvgl/src/lv_themes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video" -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video/lvgl" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


