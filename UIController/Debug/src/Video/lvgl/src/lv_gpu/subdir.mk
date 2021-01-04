################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Video/lvgl/src/lv_gpu/lv_gpu_nxp_pxp.c \
../src/Video/lvgl/src/lv_gpu/lv_gpu_nxp_pxp_osa.c \
../src/Video/lvgl/src/lv_gpu/lv_gpu_nxp_vglite.c \
../src/Video/lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.c 

OBJS += \
./src/Video/lvgl/src/lv_gpu/lv_gpu_nxp_pxp.o \
./src/Video/lvgl/src/lv_gpu/lv_gpu_nxp_pxp_osa.o \
./src/Video/lvgl/src/lv_gpu/lv_gpu_nxp_vglite.o \
./src/Video/lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.o 

C_DEPS += \
./src/Video/lvgl/src/lv_gpu/lv_gpu_nxp_pxp.d \
./src/Video/lvgl/src/lv_gpu/lv_gpu_nxp_pxp_osa.d \
./src/Video/lvgl/src/lv_gpu/lv_gpu_nxp_vglite.d \
./src/Video/lvgl/src/lv_gpu/lv_gpu_stm32_dma2d.d 


# Each subdirectory must supply rules for building sources it contributes
src/Video/lvgl/src/lv_gpu/%.o: ../src/Video/lvgl/src/lv_gpu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video" -I"/NetDrive/Personal/Projects/Keytar/VitisWorkspace/UIController/src/Video/lvgl" -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I/NetDrive/Personal/Projects/Keytar/VitisWorkspace/ZTurnPlatform/export/ZTurnPlatform/sw/ZTurnPlatform/ps7_cortexa9_1/bspinclude/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


