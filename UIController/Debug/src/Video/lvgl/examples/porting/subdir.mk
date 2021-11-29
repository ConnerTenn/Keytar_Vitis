################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Video/lvgl/examples/porting/lv_port_disp_template.c \
../src/Video/lvgl/examples/porting/lv_port_fs_template.c \
../src/Video/lvgl/examples/porting/lv_port_indev_template.c 

OBJS += \
./src/Video/lvgl/examples/porting/lv_port_disp_template.o \
./src/Video/lvgl/examples/porting/lv_port_fs_template.o \
./src/Video/lvgl/examples/porting/lv_port_indev_template.o 

C_DEPS += \
./src/Video/lvgl/examples/porting/lv_port_disp_template.d \
./src/Video/lvgl/examples/porting/lv_port_fs_template.d \
./src/Video/lvgl/examples/porting/lv_port_indev_template.d 


# Each subdirectory must supply rules for building sources it contributes
src/Video/lvgl/examples/porting/%.o: ../src/Video/lvgl/examples/porting/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/USB" -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video" -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video/lvgl" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


