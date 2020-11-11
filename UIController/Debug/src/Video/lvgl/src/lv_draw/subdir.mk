################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Video/lvgl/src/lv_draw/lv_draw_arc.c \
../src/Video/lvgl/src/lv_draw/lv_draw_blend.c \
../src/Video/lvgl/src/lv_draw/lv_draw_img.c \
../src/Video/lvgl/src/lv_draw/lv_draw_label.c \
../src/Video/lvgl/src/lv_draw/lv_draw_line.c \
../src/Video/lvgl/src/lv_draw/lv_draw_mask.c \
../src/Video/lvgl/src/lv_draw/lv_draw_rect.c \
../src/Video/lvgl/src/lv_draw/lv_draw_triangle.c \
../src/Video/lvgl/src/lv_draw/lv_img_buf.c \
../src/Video/lvgl/src/lv_draw/lv_img_cache.c \
../src/Video/lvgl/src/lv_draw/lv_img_decoder.c 

OBJS += \
./src/Video/lvgl/src/lv_draw/lv_draw_arc.o \
./src/Video/lvgl/src/lv_draw/lv_draw_blend.o \
./src/Video/lvgl/src/lv_draw/lv_draw_img.o \
./src/Video/lvgl/src/lv_draw/lv_draw_label.o \
./src/Video/lvgl/src/lv_draw/lv_draw_line.o \
./src/Video/lvgl/src/lv_draw/lv_draw_mask.o \
./src/Video/lvgl/src/lv_draw/lv_draw_rect.o \
./src/Video/lvgl/src/lv_draw/lv_draw_triangle.o \
./src/Video/lvgl/src/lv_draw/lv_img_buf.o \
./src/Video/lvgl/src/lv_draw/lv_img_cache.o \
./src/Video/lvgl/src/lv_draw/lv_img_decoder.o 

C_DEPS += \
./src/Video/lvgl/src/lv_draw/lv_draw_arc.d \
./src/Video/lvgl/src/lv_draw/lv_draw_blend.d \
./src/Video/lvgl/src/lv_draw/lv_draw_img.d \
./src/Video/lvgl/src/lv_draw/lv_draw_label.d \
./src/Video/lvgl/src/lv_draw/lv_draw_line.d \
./src/Video/lvgl/src/lv_draw/lv_draw_mask.d \
./src/Video/lvgl/src/lv_draw/lv_draw_rect.d \
./src/Video/lvgl/src/lv_draw/lv_draw_triangle.d \
./src/Video/lvgl/src/lv_draw/lv_img_buf.d \
./src/Video/lvgl/src/lv_draw/lv_img_cache.d \
./src/Video/lvgl/src/lv_draw/lv_img_decoder.d 


# Each subdirectory must supply rules for building sources it contributes
src/Video/lvgl/src/lv_draw/%.o: ../src/Video/lvgl/src/lv_draw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video" -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video/lvgl" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


