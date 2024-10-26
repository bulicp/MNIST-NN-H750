################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../X-CUBE-AI/App/aiSystemPerformance.c \
../X-CUBE-AI/App/aiTestHelper.c \
../X-CUBE-AI/App/aiTestUtility.c \
../X-CUBE-AI/App/ai_device_adaptor.c \
../X-CUBE-AI/App/app_x-cube-ai.c \
../X-CUBE-AI/App/lc_print.c \
../X-CUBE-AI/App/network.c \
../X-CUBE-AI/App/network_data.c \
../X-CUBE-AI/App/network_data_params.c \
../X-CUBE-AI/App/syscalls.c 

OBJS += \
./X-CUBE-AI/App/aiSystemPerformance.o \
./X-CUBE-AI/App/aiTestHelper.o \
./X-CUBE-AI/App/aiTestUtility.o \
./X-CUBE-AI/App/ai_device_adaptor.o \
./X-CUBE-AI/App/app_x-cube-ai.o \
./X-CUBE-AI/App/lc_print.o \
./X-CUBE-AI/App/network.o \
./X-CUBE-AI/App/network_data.o \
./X-CUBE-AI/App/network_data_params.o \
./X-CUBE-AI/App/syscalls.o 

C_DEPS += \
./X-CUBE-AI/App/aiSystemPerformance.d \
./X-CUBE-AI/App/aiTestHelper.d \
./X-CUBE-AI/App/aiTestUtility.d \
./X-CUBE-AI/App/ai_device_adaptor.d \
./X-CUBE-AI/App/app_x-cube-ai.d \
./X-CUBE-AI/App/lc_print.d \
./X-CUBE-AI/App/network.d \
./X-CUBE-AI/App/network_data.d \
./X-CUBE-AI/App/network_data_params.d \
./X-CUBE-AI/App/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
X-CUBE-AI/App/%.o X-CUBE-AI/App/%.su X-CUBE-AI/App/%.cyclo: ../X-CUBE-AI/App/%.c X-CUBE-AI/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../X-CUBE-AI/App -I../X-CUBE-AI -I../X-CUBE-AI/Target -I../Core/Inc -I../Middlewares/ST/AI/Inc -I../Drivers/BSP/Components/mt25tl01g -I../Drivers/BSP/STM32H750B-DK -I../Drivers/BSP/Components/mt48lc4m32b2 -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-X-2d-CUBE-2d-AI-2f-App

clean-X-2d-CUBE-2d-AI-2f-App:
	-$(RM) ./X-CUBE-AI/App/aiSystemPerformance.cyclo ./X-CUBE-AI/App/aiSystemPerformance.d ./X-CUBE-AI/App/aiSystemPerformance.o ./X-CUBE-AI/App/aiSystemPerformance.su ./X-CUBE-AI/App/aiTestHelper.cyclo ./X-CUBE-AI/App/aiTestHelper.d ./X-CUBE-AI/App/aiTestHelper.o ./X-CUBE-AI/App/aiTestHelper.su ./X-CUBE-AI/App/aiTestUtility.cyclo ./X-CUBE-AI/App/aiTestUtility.d ./X-CUBE-AI/App/aiTestUtility.o ./X-CUBE-AI/App/aiTestUtility.su ./X-CUBE-AI/App/ai_device_adaptor.cyclo ./X-CUBE-AI/App/ai_device_adaptor.d ./X-CUBE-AI/App/ai_device_adaptor.o ./X-CUBE-AI/App/ai_device_adaptor.su ./X-CUBE-AI/App/app_x-cube-ai.cyclo ./X-CUBE-AI/App/app_x-cube-ai.d ./X-CUBE-AI/App/app_x-cube-ai.o ./X-CUBE-AI/App/app_x-cube-ai.su ./X-CUBE-AI/App/lc_print.cyclo ./X-CUBE-AI/App/lc_print.d ./X-CUBE-AI/App/lc_print.o ./X-CUBE-AI/App/lc_print.su ./X-CUBE-AI/App/network.cyclo ./X-CUBE-AI/App/network.d ./X-CUBE-AI/App/network.o ./X-CUBE-AI/App/network.su ./X-CUBE-AI/App/network_data.cyclo ./X-CUBE-AI/App/network_data.d ./X-CUBE-AI/App/network_data.o ./X-CUBE-AI/App/network_data.su ./X-CUBE-AI/App/network_data_params.cyclo ./X-CUBE-AI/App/network_data_params.d ./X-CUBE-AI/App/network_data_params.o ./X-CUBE-AI/App/network_data_params.su ./X-CUBE-AI/App/syscalls.cyclo ./X-CUBE-AI/App/syscalls.d ./X-CUBE-AI/App/syscalls.o ./X-CUBE-AI/App/syscalls.su

.PHONY: clean-X-2d-CUBE-2d-AI-2f-App

