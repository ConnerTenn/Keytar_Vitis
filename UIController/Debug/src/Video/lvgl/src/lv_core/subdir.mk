################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Video/lvgl/src/lv_core/lv_disp.c \
../src/Video/lvgl/src/lv_core/lv_group.c \
../src/Video/lvgl/src/lv_core/lv_indev.c \
../src/Video/lvgl/src/lv_core/lv_obj.c \
../src/Video/lvgl/src/lv_core/lv_refr.c \
../src/Video/lvgl/src/lv_core/lv_style.c 

OBJS += \
./src/Video/lvgl/src/lv_core/lv_disp.o \
./src/Video/lvgl/src/lv_core/lv_group.o \
./src/Video/lvgl/src/lv_core/lv_indev.o \
./src/Video/lvgl/src/lv_core/lv_obj.o \
./src/Video/lvgl/src/lv_core/lv_refr.o \
./src/Video/lvgl/src/lv_core/lv_style.o 

C_DEPS += \
./src/Video/lvgl/src/lv_core/lv_disp.d \
./src/Video/lvgl/src/lv_core/lv_group.d \
./src/Video/lvgl/src/lv_core/lv_indev.d \
./src/Video/lvgl/src/lv_core/lv_obj.d \
./src/Video/lvgl/src/lv_core/lv_refr.d \
./src/Video/lvgl/src/lv_core/lv_style.d 


# Each subdirectory must supply rules for building sources it contributes
src/Video/lvgl/src/lv_core/%.o: ../src/Video/lvgl/src/lv_core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O3 -g3 -IZ:/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/core1/bspinclude/include -I"Z:\Projects\Keytar\VitisWorkspace\UIController\src\Video" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -IZ:/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/core1/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


