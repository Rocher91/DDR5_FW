################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32h5xx.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32h5xx.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32h5xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32H563xx -c -I../Inc -I"C:/Users/Xavi/Documents/FW/DDR5_FW/1_GPIO/Bsp/Inc" -I"C:/Users/Xavi/Documents/FW/DDR5_FW/1_GPIO/Bsp/src" -I"C:/Users/Xavi/Documents/FW/DDR5_FW/Drivers/STM32H5xx_HAL_Driver/Inc" -I"C:/Users/Xavi/Documents/FW/DDR5_FW/Drivers/CMSIS/Include" -I"C:/Users/Xavi/Documents/FW/DDR5_FW/Drivers/CMSIS/Device/ST/STM32H5xx/Include" -I"C:/Users/Xavi/Documents/FW/DDR5_FW/Drivers/CMSIS/Device/ST/STM32H5xx/Source/Templates" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32h5xx.cyclo ./Src/system_stm32h5xx.d ./Src/system_stm32h5xx.o ./Src/system_stm32h5xx.su

.PHONY: clean-Src

