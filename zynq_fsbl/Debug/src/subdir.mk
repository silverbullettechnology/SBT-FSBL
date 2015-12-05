################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ddr_init.c \
../src/ff.c \
../src/fsbl_hooks.c \
../src/image_mover.c \
../src/main.c \
../src/md5.c \
../src/mmc.c \
../src/nand.c \
../src/nor.c \
../src/pcap.c \
E:/Silver-Bullet/sdrdc/SBT-FSBL/sdrdc_2chan_viv20142_12_03_2015_1247/sdrdc_2chan/sdrdc/sdrdc_2chan_sdrdc.sdk/system_top_hw_platform_1/ps7_init.c \
../src/qspi.c \
../src/rsa.c \
../src/sd.c 

LD_SRCS += \
../src/lscript.ld 

S_UPPER_SRCS += \
../src/fsbl_handoff.S 

OBJS += \
./src/ddr_init.o \
./src/ff.o \
./src/fsbl_handoff.o \
./src/fsbl_hooks.o \
./src/image_mover.o \
./src/main.o \
./src/md5.o \
./src/mmc.o \
./src/nand.o \
./src/nor.o \
./src/pcap.o \
./src/ps7_init.o \
./src/qspi.o \
./src/rsa.o \
./src/sd.o 

C_DEPS += \
./src/ddr_init.d \
./src/ff.d \
./src/fsbl_hooks.d \
./src/image_mover.d \
./src/main.d \
./src/md5.d \
./src/mmc.d \
./src/nand.d \
./src/nor.d \
./src/pcap.d \
./src/ps7_init.d \
./src/qspi.d \
./src/rsa.d \
./src/sd.d 

S_UPPER_DEPS += \
./src/fsbl_handoff.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"E:\Silver-Bullet\sdrdc\SBT-FSBL\sdrdc_2chan_viv20142_12_03_2015_1247\sdrdc_2chan\sdrdc\sdrdc_2chan_sdrdc.sdk\system_top_hw_platform_1" -c -fmessage-length=0 -I../../standalone_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"E:\Silver-Bullet\sdrdc\SBT-FSBL\sdrdc_2chan_viv20142_12_03_2015_1247\sdrdc_2chan\sdrdc\sdrdc_2chan_sdrdc.sdk\system_top_hw_platform_1" -c -fmessage-length=0 -I../../standalone_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/ps7_init.o: E:/Silver-Bullet/sdrdc/SBT-FSBL/sdrdc_2chan_viv20142_12_03_2015_1247/sdrdc_2chan/sdrdc/sdrdc_2chan_sdrdc.sdk/system_top_hw_platform_1/ps7_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"E:\Silver-Bullet\sdrdc\SBT-FSBL\sdrdc_2chan_viv20142_12_03_2015_1247\sdrdc_2chan\sdrdc\sdrdc_2chan_sdrdc.sdk\system_top_hw_platform_1" -c -fmessage-length=0 -I../../standalone_bsp_0/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


