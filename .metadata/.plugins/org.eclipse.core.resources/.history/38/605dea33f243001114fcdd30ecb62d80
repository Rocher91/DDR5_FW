/*
 * DDR5_Board.c
 *
 *  Created on: Mar 8, 2026
 *      Author: Xavi
 */

#include "DDR5_Board.h"
#include <stdio.h>
#include "stm32h5xx_ll_bus.h"
#include "stm32h5xx_ll_gpio.h"
#include "stm32h5xx_ll_i2c.h"
#include "stm32h5xx_ll_usart.h"
#include "stm32h5xx_ll_exti.h"
#include "stm32h5xx_ll_system.h"

/* --------------------------------------------------------------------------
 * Local helpers
 * -------------------------------------------------------------------------- */
static void DDR5_GPIO_Init_Output(GPIO_TypeDef *port,
                                  uint32_t pin,
                                  uint32_t output_type,
                                  uint32_t speed,
                                  uint32_t pull)
{
    LL_GPIO_SetPinMode(port, pin, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinOutputType(port, pin, output_type);
    LL_GPIO_SetPinSpeed(port, pin, speed);
    LL_GPIO_SetPinPull(port, pin, pull);
}

static void DDR5_GPIO_Init_Input(GPIO_TypeDef *port,
                                 uint32_t pin,
                                 uint32_t pull)
{
    LL_GPIO_SetPinMode(port, pin, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinPull(port, pin, pull);
}

static uint32_t DDR5_GPIO_IsLowPin(uint32_t pin)
{
    return ((pin & 0x00FFU) != 0U);
}

static void DDR5_GPIO_Init_AF(GPIO_TypeDef *port,
                              uint32_t pin,
                              uint32_t af,
                              uint32_t output_type,
                              uint32_t speed,
                              uint32_t pull)
{
    LL_GPIO_SetPinMode(port, pin, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinOutputType(port, pin, output_type);
    LL_GPIO_SetPinSpeed(port, pin, speed);
    LL_GPIO_SetPinPull(port, pin, pull);

    if (DDR5_GPIO_IsLowPin(pin))
    {
        LL_GPIO_SetAFPin_0_7(port, pin, af);
    }
    else
    {
        LL_GPIO_SetAFPin_8_15(port, pin, af);
    }
}

/* --------------------------------------------------------------------------
 * Public GPIO init
 * -------------------------------------------------------------------------- */
void DDR5_GPIO_Init(void)
{
    /* Enable GPIO peripheral clocks */
    DDR5_GPIO_ClocksEnable();

    /* =========================================================
     * Safe output states BEFORE configuring pins as outputs
     * ========================================================= */

    /* EN_x default OFF */
    LL_GPIO_ResetOutputPin(EN_0_PORT, EN_0_PIN);
    LL_GPIO_ResetOutputPin(EN_1_PORT, EN_1_PIN);
    LL_GPIO_ResetOutputPin(EN_2_PORT, EN_2_PIN);
    LL_GPIO_ResetOutputPin(EN_3_PORT, EN_3_PIN);
    LL_GPIO_ResetOutputPin(EN_4_PORT, EN_4_PIN);
    LL_GPIO_ResetOutputPin(EN_5_PORT, EN_5_PIN);
    LL_GPIO_ResetOutputPin(EN_6_PORT, EN_6_PIN);
    LL_GPIO_ResetOutputPin(EN_7_PORT, EN_7_PIN);

    /* Trigger out idle low */
    LL_GPIO_ResetOutputPin(TRIGGER_OUT_PORT, TRIGGER_OUT_PIN);

    /* AUX default low */
    LL_GPIO_ResetOutputPin(AUX_0_PORT, AUX_0_PIN);
    LL_GPIO_ResetOutputPin(AUX_1_PORT, AUX_1_PIN);

    /* Shift register defaults */
    LL_GPIO_ResetOutputPin(SRCLK_PORT, SRCLK_PIN);
    LL_GPIO_ResetOutputPin(SR_DATA_PORT, SR_DATA_PIN);
    LL_GPIO_ResetOutputPin(SR_LATCH_PORT, SR_LATCH_PIN);
    SHIFTREG_RESET_RELEASE();   /* reset inactive (active low) */

    /* LEDs OFF */
    LED_PASS_OFF();
    LED_FAIL_OFF();
    LED_RUN_OFF();
    LED_STOP_OFF();

    /* =========================================================
     * I3C1 (PB8 / PB9)
     *
     * AF number must be checked against CubeMX / datasheet for
     * your exact STM32H563 package and LL headers.
     * Using AF4 here as a placeholder if your Cube project
     * resolves it that way; adjust if needed.
     * ========================================================= */
    /*
    DDR5_GPIO_Init_AF(I3C1_SCL_PORT, I3C1_SCL_PIN,
                      LL_GPIO_AF_6,
                      LL_GPIO_OUTPUT_OPENDRAIN,
                      LL_GPIO_SPEED_FREQ_VERY_HIGH,
                      LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_AF(I3C1_SDA_PORT, I3C1_SDA_PIN,
                      LL_GPIO_AF_6,
                      LL_GPIO_OUTPUT_OPENDRAIN,
                      LL_GPIO_SPEED_FREQ_VERY_HIGH,
                      LL_GPIO_PULL_NO);
	*/
    /* =========================================================
     * I2C LCD (PB6 / PB7)
     * Open-drain, external pull-ups required
     * ========================================================= */

    /*
    DDR5_GPIO_Init_AF(LCD_I2C_SCL_PORT, LCD_I2C_SCL_PIN,
                      LL_GPIO_AF_4,
                      LL_GPIO_OUTPUT_OPENDRAIN,
                      LL_GPIO_SPEED_FREQ_HIGH,
                      LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_AF(LCD_I2C_SDA_PORT, LCD_I2C_SDA_PIN,
                      LL_GPIO_AF_4,
                      LL_GPIO_OUTPUT_OPENDRAIN,
                      LL_GPIO_SPEED_FREQ_HIGH,
                      LL_GPIO_PULL_NO);

    */

    /* =========================================================
     * Menu buttons: input + pull-up
     * Active LOW
     * ========================================================= */
    DDR5_GPIO_Init_Input(BTN_UP_PORT,     BTN_UP_PIN,     LL_GPIO_PULL_NO); //LL_GPIO_PULL_UP
    DDR5_GPIO_Init_Input(BTN_DOWN_PORT,   BTN_DOWN_PIN,   LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(BTN_LEFT_PORT,   BTN_LEFT_PIN,   LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(BTN_RIGHT_PORT,  BTN_RIGHT_PIN,  LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(BTN_OK_PORT,     BTN_OK_PIN,     LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(BTN_CANCEL_PORT, BTN_CANCEL_PIN, LL_GPIO_PULL_NO);

    /* =========================================================
     * Trigger input / output
     * ========================================================= */
    //DDR5_GPIO_Init_Input(TRIGGER_IN_PORT, TRIGGER_IN_PIN, LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(TRIGGER_IN_PORT, TRIGGER_IN_PIN,
                              LL_GPIO_OUTPUT_PUSHPULL,
                              LL_GPIO_SPEED_FREQ_HIGH,
                              LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(TRIGGER_OUT_PORT, TRIGGER_OUT_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_HIGH,
                          LL_GPIO_PULL_NO);

    /* =========================================================
     * Power enable outputs
     * ========================================================= */
    DDR5_GPIO_Init_Output(EN_0_PORT, EN_0_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(EN_1_PORT, EN_1_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(EN_2_PORT, EN_2_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(EN_3_PORT, EN_3_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(EN_4_PORT, EN_4_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(EN_5_PORT, EN_5_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(EN_6_PORT, EN_6_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(EN_7_PORT, EN_7_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    /* =========================================================
     * GOOD_x inputs
     * ========================================================= */

    /*
    DDR5_GPIO_Init_Input(GOOD_0_PORT, GOOD_0_PIN, LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(GOOD_1_PORT, GOOD_1_PIN, LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(GOOD_2_PORT, GOOD_2_PIN, LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(GOOD_3_PORT, GOOD_3_PIN, LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(GOOD_4_PORT, GOOD_4_PIN, LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(GOOD_5_PORT, GOOD_5_PIN, LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(GOOD_6_PORT, GOOD_6_PIN, LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Input(GOOD_7_PORT, GOOD_7_PIN, LL_GPIO_PULL_NO);
	*/

    DDR5_GPIO_Init_Output(GOOD_0_PORT, GOOD_0_PIN,
                              LL_GPIO_OUTPUT_PUSHPULL,
                              LL_GPIO_SPEED_FREQ_LOW,
                              LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Output(GOOD_1_PORT, GOOD_1_PIN,
                                  LL_GPIO_OUTPUT_PUSHPULL,
                                  LL_GPIO_SPEED_FREQ_LOW,
                                  LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Output(GOOD_2_PORT, GOOD_2_PIN,
                                  LL_GPIO_OUTPUT_PUSHPULL,
                                  LL_GPIO_SPEED_FREQ_LOW,
                                  LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Output(GOOD_3_PORT, GOOD_3_PIN,
                                  LL_GPIO_OUTPUT_PUSHPULL,
                                  LL_GPIO_SPEED_FREQ_LOW,
                                  LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Output(GOOD_4_PORT, GOOD_4_PIN,
                                  LL_GPIO_OUTPUT_PUSHPULL,
                                  LL_GPIO_SPEED_FREQ_LOW,
                                  LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Output(GOOD_5_PORT, GOOD_5_PIN,
                                  LL_GPIO_OUTPUT_PUSHPULL,
                                  LL_GPIO_SPEED_FREQ_LOW,
                                  LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Output(GOOD_6_PORT, GOOD_6_PIN,
                                  LL_GPIO_OUTPUT_PUSHPULL,
                                  LL_GPIO_SPEED_FREQ_LOW,
                                  LL_GPIO_PULL_NO);
    DDR5_GPIO_Init_Output(GOOD_7_PORT, GOOD_7_PIN,
                                  LL_GPIO_OUTPUT_PUSHPULL,
                                  LL_GPIO_SPEED_FREQ_LOW,
                                  LL_GPIO_PULL_NO);

    /* =========================================================
     * AUX GPIO
     * Default as output, can be changed later if required
     * ========================================================= */
    DDR5_GPIO_Init_Output(AUX_0_PORT, AUX_0_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(AUX_1_PORT, AUX_1_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    /* =========================================================
     * Shift register signals
     * ========================================================= */
    DDR5_GPIO_Init_Output(SRCLK_PORT, SRCLK_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_HIGH,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(SR_DATA_PORT, SR_DATA_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_HIGH,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(SR_RESET_PORT, SR_RESET_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_HIGH,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(SR_LATCH_PORT, SR_LATCH_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_HIGH,
                          LL_GPIO_PULL_NO);

    /* =========================================================
     * USART3 VCP (PD8 / PD9)
     * AF7 is the typical USART3 mapping here
     * ========================================================= */
    DDR5_GPIO_Init_AF(VCP_TX_PORT, VCP_TX_PIN,
                      LL_GPIO_AF_7,
                      LL_GPIO_OUTPUT_PUSHPULL,
                      LL_GPIO_SPEED_FREQ_HIGH,
                      LL_GPIO_PULL_UP);

    DDR5_GPIO_Init_AF(VCP_RX_PORT, VCP_RX_PIN,
                      LL_GPIO_AF_7,
                      LL_GPIO_OUTPUT_PUSHPULL,
                      LL_GPIO_SPEED_FREQ_HIGH,
                      LL_GPIO_PULL_UP);

    /* =========================================================
     * Status LEDs
     * ========================================================= */
    DDR5_GPIO_Init_Output(LED_PASS_PORT, LED_PASS_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(LED_FAIL_PORT, LED_FAIL_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(LED_RUN_PORT, LED_RUN_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);

    DDR5_GPIO_Init_Output(LED_STOP_PORT, LED_STOP_PIN,
                          LL_GPIO_OUTPUT_PUSHPULL,
                          LL_GPIO_SPEED_FREQ_LOW,
                          LL_GPIO_PULL_NO);
}


#define DDR5_EXTI_PORT_A   0x00U
#define DDR5_EXTI_PORT_B   0x01U
#define DDR5_EXTI_PORT_C   0x02U
#define DDR5_EXTI_PORT_D   0x03U
#define DDR5_EXTI_PORT_E   0x04U
#define DDR5_EXTI_PORT_F   0x05U
#define DDR5_EXTI_PORT_G   0x06U
#define DDR5_EXTI_PORT_H   0x07U
#define DDR5_EXTI_PORT_I   0x08U

static void DDR5_EXTI_SelectPort(uint32_t line, uint32_t portsel)
{
    uint32_t index = line / 4U;
    uint32_t shift = (line % 4U) * 8U;

    EXTI->EXTICR[index] &= ~(0xFFUL << shift);
    EXTI->EXTICR[index] |= ((portsel & 0xFFUL) << shift);
}
int DDR5_I2C_Ping(I2C_TypeDef *I2Cx, uint8_t addr_7bit)
{
    uint32_t timeout;

    if (I2Cx == NULL)
        return -10;

    /* Limpiar flags previos */
    if (LL_I2C_IsActiveFlag_STOP(I2Cx))
        LL_I2C_ClearFlag_STOP(I2Cx);

    if (LL_I2C_IsActiveFlag_NACK(I2Cx))
        LL_I2C_ClearFlag_NACK(I2Cx);

    if (LL_I2C_IsActiveFlag_BERR(I2Cx))
        LL_I2C_ClearFlag_BERR(I2Cx);

    if (LL_I2C_IsActiveFlag_ARLO(I2Cx))
        LL_I2C_ClearFlag_ARLO(I2Cx);

    /* Esperar bus libre */
    timeout = 100000U;
    while (LL_I2C_IsActiveFlag_BUSY(I2Cx))
    {
        if (--timeout == 0U)
            return -1;
    }

    /* Solo dirección, sin datos */
    LL_I2C_HandleTransfer(I2Cx,
                          (uint32_t)(addr_7bit << 1),
                          LL_I2C_ADDRSLAVE_7BIT,
                          0,
                          LL_I2C_MODE_AUTOEND,
                          LL_I2C_GENERATE_START_WRITE);

    timeout = 100000U;

    while (!LL_I2C_IsActiveFlag_STOP(I2Cx))
    {
        if (LL_I2C_IsActiveFlag_NACK(I2Cx))
        {
            LL_I2C_ClearFlag_NACK(I2Cx);

            /* Esperar a que llegue STOP si hace falta */
            timeout = 100000U;
            while (!LL_I2C_IsActiveFlag_STOP(I2Cx))
            {
                if (--timeout == 0U)
                    return -2;
            }

            LL_I2C_ClearFlag_STOP(I2Cx);
            return -3;   /* NACK */
        }

        if (LL_I2C_IsActiveFlag_BERR(I2Cx))
        {
            LL_I2C_ClearFlag_BERR(I2Cx);
            return -5;
        }

        if (LL_I2C_IsActiveFlag_ARLO(I2Cx))
        {
            LL_I2C_ClearFlag_ARLO(I2Cx);
            return -6;
        }

        if (--timeout == 0U)
            return -4;   /* timeout esperando STOP */
    }

    LL_I2C_ClearFlag_STOP(I2Cx);

    /* Esperar realmente a que BUSY caiga */
    timeout = 100000U;
    while (LL_I2C_IsActiveFlag_BUSY(I2Cx))
    {
        if (--timeout == 0U)
            return -7;
    }

    return 0;
}

void DDR5_I2C_Scan(I2C_TypeDef *I2Cx)
{
    char msg[32];

    for (uint8_t addr = 0x08; addr < 0x78; addr++)
    {
        int rc = DDR5_I2C_Ping(I2Cx, addr);

        if (rc == 0)
        {
            snprintf(msg, sizeof(msg), "ACK 0x%02X\r\n", addr);
            DDR5_UART_WriteString(USART3, msg, 100000U);
        }

        /* pequeña pausa entre probes */
        for (volatile uint32_t i = 0; i < 5000U; i++)
        {
        }
    }

    DDR5_UART_WriteString(USART3, "Scan done\r\n", 100000U);
}

void MX_I2C1_Init(void)
{
    LL_I2C_InitTypeDef I2C_InitStruct = {0};
    LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Clock GPIOB */
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

    /* PB6 = SCL, PB7 = SDA */
    GPIO_InitStruct.Pin = LL_GPIO_PIN_6 | LL_GPIO_PIN_7;
    GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
    GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_OPENDRAIN;
    GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;   // importante si tienes pull-ups externos
    GPIO_InitStruct.Alternate = LL_GPIO_AF_4;
    LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Clock I2C */
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

    /* Reset */
    LL_I2C_Disable(I2C1);

    I2C_InitStruct.PeripheralMode = LL_I2C_MODE_I2C;
    I2C_InitStruct.Timing = 0x10B046E2; // 100kHz aprox (puedes ajustar luego)
    I2C_InitStruct.AnalogFilter = LL_I2C_ANALOGFILTER_ENABLE;
    I2C_InitStruct.DigitalFilter = 0;
    I2C_InitStruct.OwnAddress1 = 0;
    I2C_InitStruct.TypeAcknowledge = LL_I2C_ACK;
    I2C_InitStruct.OwnAddrSize = LL_I2C_OWNADDRESS1_7BIT;

    LL_I2C_Init(I2C1, &I2C_InitStruct);

    LL_I2C_EnableAutoEndMode(I2C1);
    LL_I2C_Enable(I2C1);
}
void DDR5_I2C4_Init(void)
{

    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
    LL_APB3_GRP1_EnableClock(LL_APB3_GRP1_PERIPH_I2C4);


    /* PB6 = SCL, PB7 = SDA */
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);

    LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_8, LL_GPIO_AF_6);
    LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_9, LL_GPIO_AF_6);

    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_OPENDRAIN);

    LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);
    LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_9, LL_GPIO_PULL_NO);

    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);

    LL_I2C_Disable(I2C4);

    LL_I2C_SetTiming(I2C4, 0x403032CA);

    LL_I2C_EnableAnalogFilter(I2C4);
    LL_I2C_SetDigitalFilter(I2C4, 0);

    LL_I2C_SetOwnAddress1(I2C4, 0x00, LL_I2C_OWNADDRESS1_7BIT);
    LL_I2C_DisableOwnAddress1(I2C4);
    LL_I2C_DisableOwnAddress2(I2C4);
    LL_I2C_DisableGeneralCall(I2C4);

    LL_I2C_SetMode(I2C4,LL_I2C_MODE_I2C);
    LL_I2C_AcknowledgeNextData(I2C4,LL_I2C_ACK);

    LL_I2C_EnableAutoEndMode(I2C4);
    LL_I2C_EnableClockStretching(I2C4);

    LL_I2C_Enable(I2C4);

}

void DDR5_I2C1_Init(void)
{

    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_I2C1);

    /* PB6 = SCL, PB7 = SDA */
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_6, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_7, LL_GPIO_MODE_ALTERNATE);

    LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_6, LL_GPIO_AF_4);
    LL_GPIO_SetAFPin_0_7(GPIOB, LL_GPIO_PIN_7, LL_GPIO_AF_4);

    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_6, LL_GPIO_OUTPUT_OPENDRAIN);
    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_7, LL_GPIO_OUTPUT_OPENDRAIN);

    LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_6, LL_GPIO_PULL_NO);
    LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_7, LL_GPIO_PULL_NO);

    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_6, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_7, LL_GPIO_SPEED_FREQ_HIGH);

    LL_I2C_Disable(I2C1);

    LL_I2C_SetTiming(I2C1, 0x403032CA);

    LL_I2C_EnableAnalogFilter(I2C1);
    LL_I2C_SetDigitalFilter(I2C1, 0);

    LL_I2C_SetOwnAddress1(I2C1, 0x00, LL_I2C_OWNADDRESS1_7BIT);
    LL_I2C_DisableOwnAddress1(I2C1);
    LL_I2C_DisableOwnAddress2(I2C1);
    LL_I2C_DisableGeneralCall(I2C1);

    LL_I2C_SetMode(I2C1,LL_I2C_MODE_I2C);
    LL_I2C_AcknowledgeNextData(I2C1,LL_I2C_ACK);

    LL_I2C_EnableAutoEndMode(I2C1);
    LL_I2C_EnableClockStretching(I2C1);

    LL_I2C_Enable(I2C1);

}

int I2C_WriteBytes(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t size)
{
    uint32_t timeout = 100000;

    /* Start + address */
    LL_I2C_HandleTransfer(I2Cx,
                          addr << 1,
                          LL_I2C_ADDRSLAVE_7BIT,
                          size,
                          LL_I2C_MODE_AUTOEND,
                          LL_I2C_GENERATE_START_WRITE);

    for (uint8_t i = 0; i < size; i++)
    {
        /* Esperar TXIS */
        while (!LL_I2C_IsActiveFlag_TXIS(I2Cx))
        {
            if (LL_I2C_IsActiveFlag_NACK(I2Cx))
                return -1;

            if (--timeout == 0)
                return -2;
        }

        LL_I2C_TransmitData8(I2Cx, data[i]);
    }

    /* Esperar STOP */
    timeout = 100000;
    while (!LL_I2C_IsActiveFlag_STOP(I2Cx))
    {
        if (--timeout == 0)
            return -3;
    }

    LL_I2C_ClearFlag_STOP(I2Cx);

    return 0;
}

int8_t DDR5_I2C_Write(I2C_TypeDef *I2Cx,
                      uint8_t dev_addr,
                      uint8_t reg_addr,
                      uint8_t *data,
                      uint16_t size)
{
    uint32_t timeout;

    if ((I2Cx == NULL) || ((data == NULL) && (size > 0U)))
        return -1;

    if (LL_I2C_IsActiveFlag_STOP(I2Cx)) LL_I2C_ClearFlag_STOP(I2Cx);
    if (LL_I2C_IsActiveFlag_NACK(I2Cx)) LL_I2C_ClearFlag_NACK(I2Cx);

    timeout = 100000U;
    while (LL_I2C_IsActiveFlag_BUSY(I2Cx))
    {
        if (--timeout == 0U) return -2;
    }

    LL_I2C_HandleTransfer(I2Cx,
                          (uint32_t)(dev_addr << 1),
                          LL_I2C_ADDRSLAVE_7BIT,
                          size + 1U,
                          LL_I2C_MODE_AUTOEND,
                          LL_I2C_GENERATE_START_WRITE);

    timeout = 100000U;
    while (!LL_I2C_IsActiveFlag_TXIS(I2Cx))
    {
        if (LL_I2C_IsActiveFlag_NACK(I2Cx))
        {
            LL_I2C_ClearFlag_NACK(I2Cx);
            if (LL_I2C_IsActiveFlag_STOP(I2Cx)) LL_I2C_ClearFlag_STOP(I2Cx);
            return -3;
        }
        if (--timeout == 0U) return -4;
    }
    LL_I2C_TransmitData8(I2Cx, reg_addr);

    for (uint16_t i = 0; i < size; i++)
    {
        timeout = 100000U;
        while (!LL_I2C_IsActiveFlag_TXIS(I2Cx))
        {
            if (LL_I2C_IsActiveFlag_NACK(I2Cx))
            {
                LL_I2C_ClearFlag_NACK(I2Cx);
                if (LL_I2C_IsActiveFlag_STOP(I2Cx)) LL_I2C_ClearFlag_STOP(I2Cx);
                return -5;
            }
            if (--timeout == 0U) return -6;
        }

        LL_I2C_TransmitData8(I2Cx, data[i]);
    }

    timeout = 100000U;
    while (!LL_I2C_IsActiveFlag_STOP(I2Cx))
    {
        if (--timeout == 0U) return -7;
    }

    LL_I2C_ClearFlag_STOP(I2Cx);
    return 0;
}

void DDR5_I2C_Scan_With_LCD(I2C_TypeDef *I2Cx, nhd0420_t *lcd, const char *bus_name)
{
    char msg[32]= {" "};
    char line[21] = {" "};
    uint8_t found = 0;

    if (lcd != NULL)
    {
        nhd0420_clear(lcd);
        snprintf(line, sizeof(line), "Scan %s", bus_name);
        nhd0420_write_line(lcd, 0, line);
        nhd0420_write_line(lcd, 1, "Scanning...");
        nhd0420_write_line(lcd, 2, " ");
        nhd0420_write_line(lcd, 3, " ");
        for (volatile uint32_t i = 0; i < 50000U; i++);

    }

    for (uint8_t addr = 0x08; addr < 0x78; addr++)
    {
        int rc = DDR5_I2C_Ping(I2Cx, addr);

        if (rc == 0)
        {
            found++;

            /* UART */
            snprintf(msg, sizeof(msg), "ACK 0x%X\r\n", addr);
            DDR5_UART_WriteString(USART3, msg, 100000U);

            /* LCD */
            if (lcd != NULL)
            {
            	for (uint32_t i = 0; i < 21; i++) line[i] = ' ';
                snprintf(line, sizeof(line), "-> ACK 0x%02X ", addr);

                if (found == 1)
                    nhd0420_write_line(lcd, 1, line);
                else if (found == 2)
                    nhd0420_write_line(lcd, 2, line);
                //else if (found == 3)
                  //  nhd0420_write_line(lcd, 3, line);
                else
                {
                    /* si hay más de 3, recicla líneas */
                    nhd0420_write_line(lcd, 1, "More devices...");
                    nhd0420_write_line(lcd, 2, line);
                }
            }
        }

        for (volatile uint32_t i = 0; i < 5000U; i++)
        {
        }
    }

    DDR5_UART_WriteString(USART3, "Scan done\r\n", 100000U);

    if (lcd != NULL)
    {
        if (found == 0)
        {
            nhd0420_write_line(lcd, 1, "No device found");
            nhd0420_write_line(lcd, 2, "");
            nhd0420_write_line(lcd, 3, "");
        }
        else
        {
            snprintf(line, sizeof(line), "Found: %u slaves", found);
            nhd0420_write_line(lcd, 0, line);
        }
    }
}

int8_t DDR5_I2C_WriteRaw(I2C_TypeDef *I2Cx,
                         uint8_t dev_addr,
                         const uint8_t *data,
                         uint16_t size)
{
    uint32_t timeout;

    if ((I2Cx == NULL) || (data == NULL) || (size == 0U))
        return -1;

    if (LL_I2C_IsActiveFlag_STOP(I2Cx)) LL_I2C_ClearFlag_STOP(I2Cx);
    if (LL_I2C_IsActiveFlag_NACK(I2Cx)) LL_I2C_ClearFlag_NACK(I2Cx);

    timeout = 100000U;
    while (LL_I2C_IsActiveFlag_BUSY(I2Cx))
    {
        if (--timeout == 0U) return -2;
    }

    LL_I2C_HandleTransfer(I2Cx,
                          (uint32_t)(dev_addr << 1),
                          LL_I2C_ADDRSLAVE_7BIT,
                          size,
                          LL_I2C_MODE_AUTOEND,
                          LL_I2C_GENERATE_START_WRITE);

    for (uint16_t i = 0; i < size; i++)
    {
        timeout = 100000U;
        while (!LL_I2C_IsActiveFlag_TXIS(I2Cx))
        {
            if (LL_I2C_IsActiveFlag_NACK(I2Cx))
            {
                LL_I2C_ClearFlag_NACK(I2Cx);
                if (LL_I2C_IsActiveFlag_STOP(I2Cx)) LL_I2C_ClearFlag_STOP(I2Cx);
                return -3;
            }
            if (--timeout == 0U) return -4;
        }

        LL_I2C_TransmitData8(I2Cx, data[i]);
    }

    timeout = 100000U;
    while (!LL_I2C_IsActiveFlag_STOP(I2Cx))
    {
        if (--timeout == 0U) return -5;
    }

    LL_I2C_ClearFlag_STOP(I2Cx);
    return 0;
}

int8_t DDR5_I2C_Read(I2C_TypeDef *I2Cx,
                     uint8_t dev_addr,
                     uint8_t reg_addr,
                     uint8_t *data,
                     uint16_t size)
{
    uint32_t timeout;

    if ((I2Cx == NULL) || (data == NULL) || (size == 0U))
        return -1;

    if (LL_I2C_IsActiveFlag_STOP(I2Cx)) LL_I2C_ClearFlag_STOP(I2Cx);
    if (LL_I2C_IsActiveFlag_NACK(I2Cx)) LL_I2C_ClearFlag_NACK(I2Cx);

    timeout = 100000U;
    while (LL_I2C_IsActiveFlag_BUSY(I2Cx))
    {
        if (--timeout == 0U) return -2;
    }

    LL_I2C_HandleTransfer(I2Cx,
                          (uint32_t)(dev_addr << 1),
                          LL_I2C_ADDRSLAVE_7BIT,
                          1,
                          LL_I2C_MODE_SOFTEND,
                          LL_I2C_GENERATE_START_WRITE);

    timeout = 100000U;
    while (!LL_I2C_IsActiveFlag_TXIS(I2Cx))
    {
        if (LL_I2C_IsActiveFlag_NACK(I2Cx))
        {
            LL_I2C_ClearFlag_NACK(I2Cx);
            if (LL_I2C_IsActiveFlag_STOP(I2Cx)) LL_I2C_ClearFlag_STOP(I2Cx);
            return -3;
        }
        if (--timeout == 0U) return -4;
    }

    LL_I2C_TransmitData8(I2Cx, reg_addr);

    timeout = 100000U;
    while (!LL_I2C_IsActiveFlag_TC(I2Cx))
    {
        if (--timeout == 0U) return -5;
    }

    LL_I2C_HandleTransfer(I2Cx,
                          (uint32_t)(dev_addr << 1),
                          LL_I2C_ADDRSLAVE_7BIT,
                          size,
                          LL_I2C_MODE_AUTOEND,
                          LL_I2C_GENERATE_START_READ);

    for (uint16_t i = 0; i < size; i++)
    {
        timeout = 100000U;
        while (!LL_I2C_IsActiveFlag_RXNE(I2Cx))
        {
            if (LL_I2C_IsActiveFlag_NACK(I2Cx))
            {
                LL_I2C_ClearFlag_NACK(I2Cx);
                if (LL_I2C_IsActiveFlag_STOP(I2Cx)) LL_I2C_ClearFlag_STOP(I2Cx);
                return -6;
            }
            if (--timeout == 0U) return -7;
        }

        data[i] = LL_I2C_ReceiveData8(I2Cx);
    }

    timeout = 100000U;
    while (!LL_I2C_IsActiveFlag_STOP(I2Cx))
    {
        if (--timeout == 0U) return -8;
    }

    LL_I2C_ClearFlag_STOP(I2Cx);
    return 0;
}

static int DDR5_UART_WaitFlagSet(volatile const uint32_t *reg,
                                 uint32_t mask,
                                 uint32_t timeout)
{
    while (((*reg) & mask) == 0U)
    {
        if (timeout == 0U)
        {
            return DDR5_UART_ERR_TIMEOUT;
        }
        timeout--;
    }

    return DDR5_UART_OK;
}

void DDR5_USART3_GPIO_Init(void)
{
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

    /* PB10 = TX, PB11 = RX, AF7 típico */
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_10, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetPinMode(GPIOB, LL_GPIO_PIN_11, LL_GPIO_MODE_ALTERNATE);

    LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_10, LL_GPIO_AF_7);
    LL_GPIO_SetAFPin_8_15(GPIOB, LL_GPIO_PIN_11, LL_GPIO_AF_7);

    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_10, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinSpeed(GPIOB, LL_GPIO_PIN_11, LL_GPIO_SPEED_FREQ_HIGH);

    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinOutputType(GPIOB, LL_GPIO_PIN_11, LL_GPIO_OUTPUT_PUSHPULL);

    LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_10, LL_GPIO_PULL_NO);
    LL_GPIO_SetPinPull(GPIOB, LL_GPIO_PIN_11, LL_GPIO_PULL_NO);
}

int DDR5_UART_Init_115200_8N1(USART_TypeDef *USARTx, uint32_t periph_clk_hz)
{
    if ((USARTx == NULL) || (periph_clk_hz == 0U))
    {
        return DDR5_UART_ERR_PARAM;
    }

    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

    LL_USART_Disable(USARTx);

    LL_USART_SetTransferDirection(USARTx, LL_USART_DIRECTION_TX_RX);
    LL_USART_ConfigCharacter(USARTx,
                             LL_USART_DATAWIDTH_8B,
                             LL_USART_PARITY_NONE,
                             LL_USART_STOPBITS_1);

    LL_USART_SetHWFlowCtrl(USARTx, LL_USART_HWCONTROL_NONE);
    LL_USART_SetOverSampling(USARTx, LL_USART_OVERSAMPLING_16);
    LL_USART_SetPrescaler(USARTx, LL_USART_PRESCALER_DIV1);

    LL_USART_SetBaudRate(USARTx,
                         periph_clk_hz,
                         LL_USART_PRESCALER_DIV1,
                         LL_USART_OVERSAMPLING_16,
                         115200U);

    LL_USART_Enable(USARTx);

    return DDR5_UART_OK;
}

int DDR5_UART_WriteByte(USART_TypeDef *USARTx, uint8_t byte, uint32_t timeout)
{
    int rc;

    if (USARTx == NULL)
    {
        return DDR5_UART_ERR_PARAM;
    }

    rc = DDR5_UART_WaitFlagSet(&USARTx->ISR, USART_ISR_TXE_TXFNF, timeout);
    if (rc != DDR5_UART_OK)
    {
        return rc;
    }

    LL_USART_TransmitData8(USARTx, byte);

    rc = DDR5_UART_WaitFlagSet(&USARTx->ISR, USART_ISR_TC, timeout);
    if (rc != DDR5_UART_OK)
    {
        return rc;
    }

    return DDR5_UART_OK;
}

int DDR5_UART_ReadByte(USART_TypeDef *USARTx, uint8_t *byte, uint32_t timeout)
{
    int rc;

    if ((USARTx == NULL) || (byte == NULL))
    {
        return DDR5_UART_ERR_PARAM;
    }

    rc = DDR5_UART_WaitFlagSet(&USARTx->ISR, USART_ISR_RXNE_RXFNE, timeout);
    if (rc != DDR5_UART_OK)
    {
        return rc;
    }

    *byte = LL_USART_ReceiveData8(USARTx);

    return DDR5_UART_OK;
}

int DDR5_UART_WriteBuffer(USART_TypeDef *USARTx,
                          const uint8_t *data,
                          size_t len,
                          uint32_t timeout_per_byte)
{
    if ((USARTx == NULL) || (data == NULL))
    {
        return DDR5_UART_ERR_PARAM;
    }

    for (size_t i = 0; i < len; i++)
    {
        int rc = DDR5_UART_WriteByte(USARTx, data[i], timeout_per_byte);
        if (rc != DDR5_UART_OK)
        {
            return rc;
        }
    }

    return DDR5_UART_OK;
}

int DDR5_UART_WriteString(USART_TypeDef *USARTx,
                          const char *str,
                          uint32_t timeout_per_byte)
{
    if ((USARTx == NULL) || (str == NULL))
    {
        return DDR5_UART_ERR_PARAM;
    }

    while (*str != '\0')
    {
        int rc = DDR5_UART_WriteByte(USARTx, (uint8_t)(*str), timeout_per_byte);
        if (rc != DDR5_UART_OK)
        {
            return rc;
        }
        str++;
    }

    return DDR5_UART_OK;
}

void DDR5_Debug_Enable_MCO_PA8(uint8_t enable, uint8_t sel_clock)
{
	if ( enable )
	{
		/* GPIOA clock */
		LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);

		/* PA8 -> AF0 (MCO1) */
		LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_ALTERNATE);
		LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_8, LL_GPIO_AF_0);
		LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_8, LL_GPIO_SPEED_FREQ_HIGH);
		LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_8, LL_GPIO_OUTPUT_PUSHPULL);
		LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_8, LL_GPIO_PULL_NO);

		/* MCO1 source = SYSCLK, prescaler = /8
		   Ajusta los valores si tu RM/header usan otra codificación. */
		RCC->CFGR1 &= ~(RCC_CFGR1_MCO1SEL | RCC_CFGR1_MCO1PRE);

		if ( sel_clock == PLL1_CLK_SEL )
		{
			/* PLL1 como fuente (011) */
			RCC->CFGR1 |= (0x03U << RCC_CFGR1_MCO1SEL_Pos);
		}
		else if ( sel_clock == HSI_CLK_SEL )
		{
			/* HSI como fuente (011) */
			RCC->CFGR1 |= (0x00U << RCC_CFGR1_MCO1SEL_Pos);
		}

		/* División por 8 */
		RCC->CFGR1 |= (0x8U << RCC_CFGR1_MCO1PRE_Pos);

		// Si la fuente es el PLL1 la frecuencia de salida es 16 Mhz.
		// Si la fuente es el HSI la frecuencia de salida es 8 Mhz.
	}
	else
	{
		/* Disable MCO output */

		/* Opción 1: poner PA8 como input (limpio) */
		LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_INPUT);

		/* Opción 2 (opcional): quitar clock MCO */
		RCC->CFGR1 &= ~(RCC_CFGR1_MCO1SEL | RCC_CFGR1_MCO1PRE);
	}
}

/* --------------------------------------------------------------------------
 * EXTI init
 * Buttons: falling edge (active low)
 * Trigger input: rising edge
 * -------------------------------------------------------------------------- */
void DDR5_EXTI_Init(void)
{

    /* Route EXTI lines to the correct ports */
    DDR5_EXTI_SelectPort(0U, DDR5_EXTI_PORT_C); /* BTN_UP     PC0 */
	DDR5_EXTI_SelectPort(2U, DDR5_EXTI_PORT_C); /* BTN_DOWN   PC2 */
	DDR5_EXTI_SelectPort(3U, DDR5_EXTI_PORT_C); /* BTN_LEFT   PC3 */
	DDR5_EXTI_SelectPort(4U, DDR5_EXTI_PORT_C); /* BTN_RIGHT  PC4 */
	DDR5_EXTI_SelectPort(5U, DDR5_EXTI_PORT_C); /* BTN_OK     PC5 */
	DDR5_EXTI_SelectPort(6U, DDR5_EXTI_PORT_C); /* BTN_CANCEL PC6 */

	DDR5_EXTI_SelectPort(1U, DDR5_EXTI_PORT_B); /* TRIGGER_IN PB1 */

    /* Enable interrupt lines */
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_1);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_2);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_3);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_4);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_5);
    LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_6);

    /* Buttons: falling edge */
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_0);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_2);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_3);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_4);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_5);
    LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_6);

    /* Trigger input: rising edge */
    LL_EXTI_EnableRisingTrig_0_31(LL_EXTI_LINE_1);

    /* Clear stale pending flags */
    LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_0);
    LL_EXTI_ClearRisingFlag_0_31(LL_EXTI_LINE_1);
    LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_2);
    LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_3);
    LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_4);
    LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_5);
    LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_6);
}
