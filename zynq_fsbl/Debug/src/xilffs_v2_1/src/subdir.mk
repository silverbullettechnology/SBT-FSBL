################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/xilffs_v2_1/src/ff.c \
../src/xilffs_v2_1/src/mmc.c 

OBJS += \
./src/xilffs_v2_1/src/ff.o \
./src/xilffs_v2_1/src/mmc.o 

C_DEPS += \
./src/xilffs_v2_1/src/ff.d \
./src/xilffs_v2_1/src/mmc.d 


# Each subdirectory must supply rules for building sources it contributes
src/xilffs_v2_1/src/%.o: ../src/xilffs_v2_1/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"E:\Silver-Bullet\sdrdc\SBT-FSBL\sdrdc_2chan_viv20142_11_27_2015_1240\sdrdc_2chan\sdrdc\sdrdc_2chan_sdrdc.sdk\system_top_hw_platform_1" -I"E:\Silver-Bullet\sdrdc\SBT-FSBL\sdrdc_2chan_viv20142_11_27_2015_1240\sdrdc_2chan\sdrdc\sdrdc_2chan_sdrdc.sdk\zynq_fsbl\src\xilffs_v2_1\src" -I"E:\Silver-Bullet\sdrdc\SBT-FSBL\sdrdc_2chan_viv20142_11_27_2015_1240\sdrdc_2chan\sdrdc\sdrdc_2chan_sdrdc.sdk\zynq_fsbl\src\xilffs_v2_1\src\include" -c -fmessage-length=0 -I../../standalone_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


