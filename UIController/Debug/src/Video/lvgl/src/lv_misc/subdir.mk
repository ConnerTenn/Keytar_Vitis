################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Video/lvgl/src/lv_misc/lv_anim.c \
../src/Video/lvgl/src/lv_misc/lv_area.c \
../src/Video/lvgl/src/lv_misc/lv_async.c \
../src/Video/lvgl/src/lv_misc/lv_bidi.c \
../src/Video/lvgl/src/lv_misc/lv_color.c \
../src/Video/lvgl/src/lv_misc/lv_debug.c \
../src/Video/lvgl/src/lv_misc/lv_fs.c \
../src/Video/lvgl/src/lv_misc/lv_gc.c \
../src/Video/lvgl/src/lv_misc/lv_ll.c \
../src/Video/lvgl/src/lv_misc/lv_log.c \
../src/Video/lvgl/src/lv_misc/lv_math.c \
../src/Video/lvgl/src/lv_misc/lv_mem.c \
../src/Video/lvgl/src/lv_misc/lv_printf.c \
../src/Video/lvgl/src/lv_misc/lv_task.c \
../src/Video/lvgl/src/lv_misc/lv_templ.c \
../src/Video/lvgl/src/lv_misc/lv_txt.c \
../src/Video/lvgl/src/lv_misc/lv_txt_ap.c \
../src/Video/lvgl/src/lv_misc/lv_utils.c 

OBJS += \
./src/Video/lvgl/src/lv_misc/lv_anim.o \
./src/Video/lvgl/src/lv_misc/lv_area.o \
./src/Video/lvgl/src/lv_misc/lv_async.o \
./src/Video/lvgl/src/lv_misc/lv_bidi.o \
./src/Video/lvgl/src/lv_misc/lv_color.o \
./src/Video/lvgl/src/lv_misc/lv_debug.o \
./src/Video/lvgl/src/lv_misc/lv_fs.o \
./src/Video/lvgl/src/lv_misc/lv_gc.o \
./src/Video/lvgl/src/lv_misc/lv_ll.o \
./src/Video/lvgl/src/lv_misc/lv_log.o \
./src/Video/lvgl/src/lv_misc/lv_math.o \
./src/Video/lvgl/src/lv_misc/lv_mem.o \
./src/Video/lvgl/src/lv_misc/lv_printf.o \
./src/Video/lvgl/src/lv_misc/lv_task.o \
./src/Video/lvgl/src/lv_misc/lv_templ.o \
./src/Video/lvgl/src/lv_misc/lv_txt.o \
./src/Video/lvgl/src/lv_misc/lv_txt_ap.o \
./src/Video/lvgl/src/lv_misc/lv_utils.o 

C_DEPS += \
./src/Video/lvgl/src/lv_misc/lv_anim.d \
./src/Video/lvgl/src/lv_misc/lv_area.d \
./src/Video/lvgl/src/lv_misc/lv_async.d \
./src/Video/lvgl/src/lv_misc/lv_bidi.d \
./src/Video/lvgl/src/lv_misc/lv_color.d \
./src/Video/lvgl/src/lv_misc/lv_debug.d \
./src/Video/lvgl/src/lv_misc/lv_fs.d \
./src/Video/lvgl/src/lv_misc/lv_gc.d \
./src/Video/lvgl/src/lv_misc/lv_ll.d \
./src/Video/lvgl/src/lv_misc/lv_log.d \
./src/Video/lvgl/src/lv_misc/lv_math.d \
./src/Video/lvgl/src/lv_misc/lv_mem.d \
./src/Video/lvgl/src/lv_misc/lv_printf.d \
./src/Video/lvgl/src/lv_misc/lv_task.d \
./src/Video/lvgl/src/lv_misc/lv_templ.d \
./src/Video/lvgl/src/lv_misc/lv_txt.d \
./src/Video/lvgl/src/lv_misc/lv_txt_ap.d \
./src/Video/lvgl/src/lv_misc/lv_utils.d 


# Each subdirectory must supply rules for building sources it contributes
src/Video/lvgl/src/lv_misc/%.o: ../src/Video/lvgl/src/lv_misc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video" -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video/lvgl" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


