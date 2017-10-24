################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/Jigar/Desktop/Alpha243/cgreen/tests/api/core_api.c \
C:/Users/Jigar/Desktop/Alpha243/cgreen/tests/api/suites_with_context_api.c \
C:/Users/Jigar/Desktop/Alpha243/cgreen/tests/api/suites_without_context_api.c 

OBJS += \
./cgreen/tests/api/core_api.o \
./cgreen/tests/api/suites_with_context_api.o \
./cgreen/tests/api/suites_without_context_api.o 

C_DEPS += \
./cgreen/tests/api/core_api.d \
./cgreen/tests/api/suites_with_context_api.d \
./cgreen/tests/api/suites_without_context_api.d 


# Each subdirectory must supply rules for building sources it contributes
cgreen/tests/api/core_api.o: C:/Users/Jigar/Desktop/Alpha243/cgreen/tests/api/core_api.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\newlib" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L0_LowLevel" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L1_FreeRTOS" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L1_FreeRTOS\include" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L1_FreeRTOS\portable\no_mpu" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L2_Drivers" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L2_Drivers\base" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L3_Utils" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L3_Utils\tlm" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L4_IO" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L4_IO\fat" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L4_IO\wireless" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L5_Application" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cgreen/tests/api/suites_with_context_api.o: C:/Users/Jigar/Desktop/Alpha243/cgreen/tests/api/suites_with_context_api.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\newlib" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L0_LowLevel" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L1_FreeRTOS" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L1_FreeRTOS\include" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L1_FreeRTOS\portable\no_mpu" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L2_Drivers" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L2_Drivers\base" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L3_Utils" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L3_Utils\tlm" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L4_IO" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L4_IO\fat" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L4_IO\wireless" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L5_Application" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

cgreen/tests/api/suites_without_context_api.o: C:/Users/Jigar/Desktop/Alpha243/cgreen/tests/api/suites_without_context_api.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Os -fmessage-length=0 -ffunction-sections -fdata-sections -Wall -Wshadow -Wlogical-op -Wfloat-equal -DBUILD_CFG_MPU=0 -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\newlib" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L0_LowLevel" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L1_FreeRTOS" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L1_FreeRTOS\include" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L1_FreeRTOS\portable\no_mpu" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L2_Drivers" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L2_Drivers\base" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L3_Utils" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L3_Utils\tlm" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L4_IO" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L4_IO\fat" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L4_IO\wireless" -I"C:\Users\Jigar\Desktop\Alpha243\Alpha_243\Source_Code\lpc1758_freertos2_tx\L5_Application" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


