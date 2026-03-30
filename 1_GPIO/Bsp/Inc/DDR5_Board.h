#ifndef DDR5_BOARD_H
#define DDR5_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32h5xx.h"
#include "stm32h5xx_ll_bus.h"
#include "stm32h5xx_ll_gpio.h"
#include "stm32h5xx_ll_exti.h"
#include "stm32h5xx_ll_system.h"

/* =========================================================
   Board identification
   ========================================================= */

#define BOARD_NAME "DDR5_TEST_PLATFORM\r\n"

#define ENABLE 			1
#define DISABLE 		0
#define PLL1_CLK_SEL 	1
#define HSI_CLK_SEL 	2

#define BUTTON_PRESSED 	0U
#define BUTTON_RELEASED 1U

#define DDR5_UART_OK            0
#define DDR5_UART_ERR_PARAM    -1
#define DDR5_UART_ERR_TIMEOUT  -2

/* =========================================================
   I3C bus (DDR5 sideband)
   ========================================================= */

#define I3C1_SCL_PORT GPIOB
#define I3C1_SCL_PIN  LL_GPIO_PIN_8

#define I3C1_SDA_PORT GPIOB
#define I3C1_SDA_PIN  LL_GPIO_PIN_9

/* =========================================================
   I2C LCD
   ========================================================= */

#define LCD_I2C_SCL_PORT GPIOB
#define LCD_I2C_SCL_PIN  LL_GPIO_PIN_6

#define LCD_I2C_SDA_PORT GPIOB
#define LCD_I2C_SDA_PIN  LL_GPIO_PIN_7

/* =========================================================
   Menu buttons
   Active LOW (internal pull-up)
   ========================================================= */

#define BTN_UP_PORT GPIOC
#define BTN_UP_PIN  LL_GPIO_PIN_0

#define BTN_DOWN_PORT GPIOC
#define BTN_DOWN_PIN  LL_GPIO_PIN_2

#define BTN_LEFT_PORT GPIOC
#define BTN_LEFT_PIN  LL_GPIO_PIN_3

#define BTN_RIGHT_PORT GPIOC
#define BTN_RIGHT_PIN  LL_GPIO_PIN_4

#define BTN_OK_PORT GPIOC
#define BTN_OK_PIN  LL_GPIO_PIN_5

#define BTN_CANCEL_PORT GPIOC
#define BTN_CANCEL_PIN  LL_GPIO_PIN_6

/* =========================================================
   Trigger signals
   ========================================================= */

#define TRIGGER_IN_PORT GPIOB
#define TRIGGER_IN_PIN  LL_GPIO_PIN_1

#define TRIGGER_OUT_PORT GPIOB
#define TRIGGER_OUT_PIN  LL_GPIO_PIN_2

/* =========================================================
   Power enable outputs (RDIMM)
   ========================================================= */

#define EN_0_PORT GPIOD
#define EN_0_PIN  LL_GPIO_PIN_0

#define EN_1_PORT GPIOD
#define EN_1_PIN  LL_GPIO_PIN_1

#define EN_2_PORT GPIOD
#define EN_2_PIN  LL_GPIO_PIN_2

#define EN_3_PORT GPIOD
#define EN_3_PIN  LL_GPIO_PIN_3

#define EN_4_PORT GPIOD
#define EN_4_PIN  LL_GPIO_PIN_4

#define EN_5_PORT GPIOD
#define EN_5_PIN  LL_GPIO_PIN_5

#define EN_6_PORT GPIOC
#define EN_6_PIN  LL_GPIO_PIN_7

#define EN_7_PORT GPIOC
#define EN_7_PIN  LL_GPIO_PIN_8

/* =========================================================
   Power good inputs (RDIMM)
   ========================================================= */

#define GOOD_0_PORT GPIOE
#define GOOD_0_PIN  LL_GPIO_PIN_8

#define GOOD_1_PORT GPIOE
#define GOOD_1_PIN  LL_GPIO_PIN_9

#define GOOD_2_PORT GPIOE
#define GOOD_2_PIN  LL_GPIO_PIN_10

#define GOOD_3_PORT GPIOE
#define GOOD_3_PIN  LL_GPIO_PIN_11

#define GOOD_4_PORT GPIOE
#define GOOD_4_PIN  LL_GPIO_PIN_12

#define GOOD_5_PORT GPIOE
#define GOOD_5_PIN  LL_GPIO_PIN_13

#define GOOD_6_PORT GPIOE
#define GOOD_6_PIN  LL_GPIO_PIN_14

#define GOOD_7_PORT GPIOE
#define GOOD_7_PIN  LL_GPIO_PIN_15

/* =========================================================
   AUX GPIO
   ========================================================= */

#define AUX_0_PORT GPIOB
#define AUX_0_PIN  LL_GPIO_PIN_10

#define AUX_1_PORT GPIOB
#define AUX_1_PIN  LL_GPIO_PIN_12

/* =========================================================
   Shift register interface
   ========================================================= */

#define SRCLK_PORT GPIOF
#define SRCLK_PIN  LL_GPIO_PIN_2

#define SR_DATA_PORT GPIOF
#define SR_DATA_PIN  LL_GPIO_PIN_3

#define SR_RESET_PORT GPIOF
#define SR_RESET_PIN  LL_GPIO_PIN_5

#define SR_LATCH_PORT GPIOF
#define SR_LATCH_PIN  LL_GPIO_PIN_6

/* =========================================================
   UART VCP (ST-LINK)
   ========================================================= */

#define VCP_TX_PORT GPIOD
#define VCP_TX_PIN  LL_GPIO_PIN_8

#define VCP_RX_PORT GPIOD
#define VCP_RX_PIN  LL_GPIO_PIN_9

/* =========================================================
   Status LEDs
   ========================================================= */

#define LED_PASS_PORT GPIOC
#define LED_PASS_PIN  LL_GPIO_PIN_10

#define LED_FAIL_PORT GPIOC
#define LED_FAIL_PIN  LL_GPIO_PIN_11

#define LED_RUN_PORT GPIOC
#define LED_RUN_PIN  LL_GPIO_PIN_12

#define LED_STOP_PORT GPIOF
#define LED_STOP_PIN  LL_GPIO_PIN_7

/* =========================================================
   GPIO clock enable
   ========================================================= */

static inline void DDR5_GPIO_ClocksEnable(void)
{
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOD);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOE);
    LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOF);
}

/* =========================================================
   LED helpers
   ========================================================= */

#define LED_PASS_ON()  LL_GPIO_SetOutputPin(LED_PASS_PORT, LED_PASS_PIN)
#define LED_PASS_OFF() LL_GPIO_ResetOutputPin(LED_PASS_PORT, LED_PASS_PIN)

#define LED_FAIL_ON()  LL_GPIO_SetOutputPin(LED_FAIL_PORT, LED_FAIL_PIN)
#define LED_FAIL_OFF() LL_GPIO_ResetOutputPin(LED_FAIL_PORT, LED_FAIL_PIN)

#define LED_RUN_ON()  LL_GPIO_SetOutputPin(LED_RUN_PORT, LED_RUN_PIN)
#define LED_RUN_OFF() LL_GPIO_ResetOutputPin(LED_RUN_PORT, LED_RUN_PIN)

#define LED_STOP_ON()  LL_GPIO_SetOutputPin(LED_STOP_PORT, LED_STOP_PIN)
#define LED_STOP_OFF() LL_GPIO_ResetOutputPin(LED_STOP_PORT, LED_STOP_PIN)


#define PWR_ENABLE_0_ON()  LL_GPIO_SetOutputPin(EN_0_PORT, EN_0_PIN)
#define PWR_ENABLE_1_ON()  LL_GPIO_SetOutputPin(EN_1_PORT, EN_1_PIN)
#define PWR_ENABLE_2_ON()  LL_GPIO_SetOutputPin(EN_2_PORT, EN_2_PIN)
#define PWR_ENABLE_3_ON()  LL_GPIO_SetOutputPin(EN_3_PORT, EN_3_PIN)
#define PWR_ENABLE_4_ON()  LL_GPIO_SetOutputPin(EN_4_PORT, EN_4_PIN)
#define PWR_ENABLE_5_ON()  LL_GPIO_SetOutputPin(EN_5_PORT, EN_5_PIN)
#define PWR_ENABLE_6_ON()  LL_GPIO_SetOutputPin(EN_6_PORT, EN_6_PIN)
#define PWR_ENABLE_7_ON()  LL_GPIO_SetOutputPin(EN_7_PORT, EN_7_PIN)

#define PWR_ENABLE_0_OFF()  LL_GPIO_ResetOutputPin(EN_0_PORT, EN_0_PIN)
#define PWR_ENABLE_1_OFF()  LL_GPIO_ResetOutputPin(EN_1_PORT, EN_1_PIN)
#define PWR_ENABLE_2_OFF()  LL_GPIO_ResetOutputPin(EN_2_PORT, EN_2_PIN)
#define PWR_ENABLE_3_OFF()  LL_GPIO_ResetOutputPin(EN_3_PORT, EN_3_PIN)
#define PWR_ENABLE_4_OFF()  LL_GPIO_ResetOutputPin(EN_4_PORT, EN_4_PIN)
#define PWR_ENABLE_5_OFF()  LL_GPIO_ResetOutputPin(EN_5_PORT, EN_5_PIN)
#define PWR_ENABLE_6_OFF()  LL_GPIO_ResetOutputPin(EN_6_PORT, EN_6_PIN)
#define PWR_ENABLE_7_OFF()  LL_GPIO_ResetOutputPin(EN_7_PORT, EN_7_PIN)

#define PWR_GOOD_0_ON()  LL_GPIO_SetOutputPin(GOOD_0_PORT, GOOD_0_PIN)
#define PWR_GOOD_1_ON()  LL_GPIO_SetOutputPin(GOOD_1_PORT, GOOD_1_PIN)
#define PWR_GOOD_2_ON()  LL_GPIO_SetOutputPin(GOOD_2_PORT, GOOD_2_PIN)
#define PWR_GOOD_3_ON()  LL_GPIO_SetOutputPin(GOOD_3_PORT, GOOD_3_PIN)
#define PWR_GOOD_4_ON()  LL_GPIO_SetOutputPin(GOOD_4_PORT, GOOD_4_PIN)
#define PWR_GOOD_5_ON()  LL_GPIO_SetOutputPin(GOOD_5_PORT, GOOD_5_PIN)
#define PWR_GOOD_6_ON()  LL_GPIO_SetOutputPin(GOOD_6_PORT, GOOD_6_PIN)
#define PWR_GOOD_7_ON()  LL_GPIO_SetOutputPin(GOOD_7_PORT, GOOD_7_PIN)

#define PWR_GOOD_0_OFF()  LL_GPIO_ResetOutputPin(GOOD_0_PORT, GOOD_0_PIN)
#define PWR_GOOD_1_OFF()  LL_GPIO_ResetOutputPin(GOOD_1_PORT, GOOD_1_PIN)
#define PWR_GOOD_2_OFF()  LL_GPIO_ResetOutputPin(GOOD_2_PORT, GOOD_2_PIN)
#define PWR_GOOD_3_OFF()  LL_GPIO_ResetOutputPin(GOOD_3_PORT, GOOD_3_PIN)
#define PWR_GOOD_4_OFF()  LL_GPIO_ResetOutputPin(GOOD_4_PORT, GOOD_4_PIN)
#define PWR_GOOD_5_OFF()  LL_GPIO_ResetOutputPin(GOOD_5_PORT, GOOD_5_PIN)
#define PWR_GOOD_6_OFF()  LL_GPIO_ResetOutputPin(GOOD_6_PORT, GOOD_6_PIN)
#define PWR_GOOD_7_OFF()  LL_GPIO_ResetOutputPin(GOOD_7_PORT, GOOD_7_PIN)

#define AUX_0_ON()  LL_GPIO_SetOutputPin(AUX_0_PORT, AUX_0_PIN)
#define AUX_1_ON()  LL_GPIO_SetOutputPin(AUX_1_PORT, AUX_1_PIN)

#define AUX_0_OFF()  LL_GPIO_ResetOutputPin(AUX_0_PORT, AUX_0_PIN)
#define AUX_1_OFF()  LL_GPIO_ResetOutputPin(AUX_1_PORT, AUX_1_PIN)

#define TRIG_IN_ON()   LL_GPIO_SetOutputPin(TRIGGER_IN_PORT, TRIGGER_IN_PIN)
#define TRIG_OUT_ON()  LL_GPIO_SetOutputPin(TRIGGER_OUT_PORT, TRIGGER_OUT_PIN)

#define TRIG_IN_OFF()   LL_GPIO_ResetOutputPin(TRIGGER_IN_PORT, TRIGGER_IN_PIN)
#define TRIG_OUT_OFF()  LL_GPIO_ResetOutputPin(TRIGGER_OUT_PORT, TRIGGER_OUT_PIN)

/* =========================================================
   Shift register helpers
   ========================================================= */

#define SHIFTREG_RESET_ASSERT() \
    LL_GPIO_ResetOutputPin(SR_RESET_PORT, SR_RESET_PIN)

#define SHIFTREG_RESET_RELEASE() \
    LL_GPIO_SetOutputPin(SR_RESET_PORT, SR_RESET_PIN)

/* =========================================================
   Button helpers
   ========================================================= */

static inline uint8_t DDR5_ButtonPressed(GPIO_TypeDef *port, uint32_t pin)
{
    return (LL_GPIO_IsInputPinSet(port, pin) == BUTTON_PRESSED );
}

static inline uint8_t DDR5_UPButtonPressed(void)
{
    return DDR5_ButtonPressed(BTN_UP_PORT, BTN_UP_PIN);
}

static inline uint8_t DDR5_DOWNButtonPressed(void)
{
    return DDR5_ButtonPressed(BTN_DOWN_PORT, BTN_DOWN_PIN);
}

static inline uint8_t DDR5_LEFTButtonPressed(void)
{
    return DDR5_ButtonPressed(BTN_LEFT_PORT, BTN_LEFT_PIN);
}

static inline uint8_t DDR5_RIGHTButtonPressed(void)
{
    return DDR5_ButtonPressed(BTN_RIGHT_PORT, BTN_RIGHT_PIN);
}

static inline uint8_t DDR5_OKButtonPressed(void)
{
    return DDR5_ButtonPressed(BTN_OK_PORT, BTN_OK_PIN);
}

static inline uint8_t DDR5_CANCELButtonPressed(void)
{
    return DDR5_ButtonPressed(BTN_CANCEL_PORT, BTN_CANCEL_PIN);
}
void I2C_Scan(I2C_TypeDef *I2Cx);

/* =========================================================
   Board init functions
   ========================================================= */

void DDR5_GPIO_Init(void);
void DDR5_EXTI_Init(void);
void DDR5_IRQ_Init(void);
void DDR5_Clock_Init(void);
void Debug_Clocks_And_Flash(void);
void DDR5_Debug_Enable_MCO_PA8(uint8_t enable, uint8_t sel_clock);
void DDR5_I2C1_Init(void);
int8_t DDR5_I2C_Write(I2C_TypeDef *I2Cx,
                      uint8_t dev_addr,
                      uint8_t reg_addr,
                      uint8_t *data,
                      uint16_t size);

int8_t DDR5_I2C_Read(I2C_TypeDef *I2Cx,
                     uint8_t dev_addr,
                     uint8_t reg_addr,
                     uint8_t *data,
                     uint16_t size);
int DDR5_UART_Init_115200_8N1(USART_TypeDef *USARTx, uint32_t periph_clk_hz);

int DDR5_UART_WriteByte(USART_TypeDef *USARTx, uint8_t byte, uint32_t timeout);
int DDR5_UART_ReadByte(USART_TypeDef *USARTx, uint8_t *byte, uint32_t timeout);

int DDR5_UART_WriteBuffer(USART_TypeDef *USARTx,
                          const uint8_t *data,
                          size_t len,
                          uint32_t timeout_per_byte);

int DDR5_UART_WriteString(USART_TypeDef *USARTx,
                          const char *str,
                          uint32_t timeout_per_byte);
int DDR5_I2C_Ping(I2C_TypeDef *I2Cx, uint8_t addr_7bit);
void DDR5_I2C_Scan(I2C_TypeDef *I2Cx);
int8_t DDR5_I2C_WriteRaw(I2C_TypeDef *I2Cx,
                         uint8_t dev_addr,
                         const uint8_t *data,
                         uint16_t size);
void MX_I2C1_Init(void);
int I2C_WriteBytes(I2C_TypeDef *I2Cx, uint8_t addr, uint8_t *data, uint8_t size);

#ifdef __cplusplus
}
#endif

#endif
