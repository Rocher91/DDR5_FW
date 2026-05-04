################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Bsp/src/DDR5_Board.c \
../Bsp/src/DDR5_Board_Clock.c \
../Bsp/src/DDR5_Board_IRQ.c \
../Bsp/src/DDR5_Time.c \
../Bsp/src/nhd0420_i2c.c 

OBJS += \
./Bsp/src/DDR5_Board.o \
./Bsp/src/DDR5_Board_Clock.o \
./Bsp/src/DDR5_Board_IRQ.o \
./Bsp/src/DDR5_Time.o \
./Bsp/src/nhd0420_i2c.o 

C_DEPS += \
./Bsp/src/DDR5_Board.d \
./Bsp/src/DDR5_Board_Clock.d \
./Bsp/src/DDR5_Board_IRQ.d \
./Bsp/src/DDR5_Time.d \
./Bsp/src/nhd0420_i2c.d 


# Each subdirectory must supply rules for building sources it contributes
Bsp/src/%.o Bsp/src/%.su Bsp/src/%.cyclo: ../Bsp/src/%.c Bsp/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32H563xx -c -I"C:/Users/Xavi/Documents/FW/DDR5_FW/1_GPIO/Bsp/Inc" -I"C:/Users/Xavi/Documents/FW/DDR5_FW/1_GPIO/Drivers/CMSIS/Device/ST/STM32H5xx/Include" -I"C:/Users/Xavi/Documents/FW/DDR5_FW/1_GPIO/Drivers/CMSIS/Include" -I"C:/Users/Xavi/Documents/FW/DDR5_FW/1_GPIO/Drivers/CMSIS/Device/ST/STM32H5xx/Include/Templates" -I"C:/Users/Xavi/Documents/FW/DDR5_FW/1_GPIO/Drivers/STM32H5xx_HAL_Driver/Inc" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Bsp-2f-src

clean-Bsp-2f-src:
	-$(RM) ./Bsp/src/DDR5_Board.cyclo ./Bsp/src/DDR5_Board.d ./Bsp/src/DDR5_Board.o ./Bsp/src/DDR5_Board.su ./Bsp/src/DDR5_Board_Clock.cyclo ./Bsp/src/DDR5_Board_Clock.d ./Bsp/src/DDR5_Board_Clock.o ./Bsp/src/DDR5_Board_Clock.su ./Bsp/src/DDR5_Board_IRQ.cyclo ./Bsp/src/DDR5_Board_IRQ.d ./Bsp/src/DDR5_Board_IRQ.o ./Bsp/src/DDR5_Board_IRQ.su ./Bsp/src/DDR5_Time.cyclo ./Bsp/src/DDR5_Time.d ./Bsp/src/DDR5_Time.o ./Bsp/src/DDR5_Time.su ./Bsp/src/nhd0420_i2c.cyclo ./Bsp/src/nhd0420_i2c.d ./Bsp/src/nhd0420_i2c.o ./Bsp/src/nhd0420_i2c.su

.PHONY: clean-Bsp-2f-src

