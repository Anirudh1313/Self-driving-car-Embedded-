################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../L1_FreeRTOS/hooks/hooks.c 

OBJS += \
./L1_FreeRTOS/hooks/hooks.o 

C_DEPS += \
./L1_FreeRTOS/hooks/hooks.d 


# Each subdirectory must supply rules for building sources it contributes
L1_FreeRTOS/hooks/%.o: ../L1_FreeRTOS/hooks/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\newlib" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L0_LowLevel" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L1_FreeRTOS" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L1_FreeRTOS\include" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L1_FreeRTOS\portable\no_mpu" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L2_Drivers" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L2_Drivers\base" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L3_Utils" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L3_Utils\tlm" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L4_IO" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L4_IO\fat" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L4_IO\wireless" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_Master_Module\L5_Application" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


