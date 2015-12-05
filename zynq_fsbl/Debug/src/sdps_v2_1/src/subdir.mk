################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/sdps_v2_1/src/xsdps.c \
../src/sdps_v2_1/src/xsdps_g.c \
../src/sdps_v2_1/src/xsdps_options.c \
../src/sdps_v2_1/src/xsdps_sinit.c 

OBJS += \
./src/sdps_v2_1/src/xsdps.o \
./src/sdps_v2_1/src/xsdps_g.o \
./src/sdps_v2_1/src/xsdps_options.o \
./src/sdps_v2_1/src/xsdps_sinit.o 

C_DEPS += \
./src/sdps_v2_1/src/xsdps.d \
./src/sdps_v2_1/src/xsdps_g.d \
./src/sdps_v2_1/src/xsdps_options.d \
./src/sdps_v2_1/src/xsdps_sinit.d 


# Each subdirectory must supply rules for building sources it contributes
src/sdps_v2_1/src/%.o: ../src/sdps_v2_1/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"E:\Silver-Bullet\sdrdc\SBT-FSBL\sdrdc_2chan_viv20142_11_27_2015_1240\sdrdc_2chan\sdrdc\sdrdc_2chan_sdrdc.sdk\system_top_hw_platform_1" -I"E:\Silver-Bullet\sdrdc\SBT-FSBL\sdrdc_2chan_viv20142_11_27_2015_1240\sdrdc_2chan\sdrdc\sdrdc_2chan_sdrdc.sdk\zynq_fsbl\src\sdps_v2_1\src" -I"E:\Silver-Bullet\sdrdc\SBT-FSBL\sdrdc_2chan_viv20142_11_27_2015_1240\sdrdc_2chan\sdrdc\sdrdc_2chan_sdrdc.sdk\zynq_fsbl\src\xilffs_v2_1\src" -I"E:\Silver-Bullet\sdrdc\SBT-FSBL\sdrdc_2chan_viv20142_11_27_2015_1240\sdrdc_2chan\sdrdc\sdrdc_2chan_sdrdc.sdk\zynq_fsbl\src\xilffs_v2_1\src\include" -c -fmessage-length=0 -I../../standalone_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


