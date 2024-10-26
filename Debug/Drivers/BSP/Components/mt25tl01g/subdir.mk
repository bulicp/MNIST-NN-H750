################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/mt25tl01g/mt25tl01g.c 

OBJS += \
./Drivers/BSP/Components/mt25tl01g/mt25tl01g.o 

C_DEPS += \
./Drivers/BSP/Components/mt25tl01g/mt25tl01g.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/mt25tl01g/%.o Drivers/BSP/Components/mt25tl01g/%.su Drivers/BSP/Components/mt25tl01g/%.cyclo: ../Drivers/BSP/Components/mt25tl01g/%.c Drivers/BSP/Components/mt25tl01g/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../X-CUBE-AI/App -I../X-CUBE-AI -I../X-CUBE-AI/Target -I../Core/Inc -I../Middlewares/ST/AI/Inc -I../Drivers/BSP/Components/mt25tl01g -I../Drivers/BSP/STM32H750B-DK -I../Drivers/BSP/Components/mt48lc4m32b2 -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-mt25tl01g

clean-Drivers-2f-BSP-2f-Components-2f-mt25tl01g:
	-$(RM) ./Drivers/BSP/Components/mt25tl01g/mt25tl01g.cyclo ./Drivers/BSP/Components/mt25tl01g/mt25tl01g.d ./Drivers/BSP/Components/mt25tl01g/mt25tl01g.o ./Drivers/BSP/Components/mt25tl01g/mt25tl01g.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-mt25tl01g

