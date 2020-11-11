################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Video/lvgl/src/lv_hal/lv_hal_disp.c \
../src/Video/lvgl/src/lv_hal/lv_hal_indev.c \
../src/Video/lvgl/src/lv_hal/lv_hal_tick.c 

OBJS += \
./src/Video/lvgl/src/lv_hal/lv_hal_disp.o \
./src/Video/lvgl/src/lv_hal/lv_hal_indev.o \
./src/Video/lvgl/src/lv_hal/lv_hal_tick.o 

C_DEPS += \
./src/Video/lvgl/src/lv_hal/lv_hal_disp.d \
./src/Video/lvgl/src/lv_hal/lv_hal_indev.d \
./src/Video/lvgl/src/lv_hal/lv_hal_tick.d 


# Each subdirectory must supply rules for building sources it contributes
src/Video/lvgl/src/lv_hal/%.o: ../src/Video/lvgl/src/lv_hal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video" -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video/lvgl" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


