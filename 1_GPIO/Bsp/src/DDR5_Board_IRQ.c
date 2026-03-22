/*
 * DDR5_Board_IRQ.c
 *
 *  Created on: Mar 8, 2026
 *      Author: Xavi
 */

#include "DDR5_Board.h"

#include "stm32h5xx_ll_exti.h"
#include "stm32h5xx_ll_cortex.h"

/*
 * Weak callbacks
 * Override them in your application if needed.
 */
__WEAK void DDR5_OnButtonIRQ(uint32_t pin)
{
    (void)pin;
}

__WEAK void DDR5_OnTriggerInIRQ(void)
{
}

void DDR5_IRQ_Init(void)
{
    /*
     * Priority grouping:
     * 4 bits preemption priority, 0 bits subpriority
     */
    NVIC_SetPriorityGrouping(3U);

    /*
     * One IRQ per EXTI line (common in H5, but verify startup file if needed)
     */
    NVIC_SetPriority(EXTI0_IRQn, NVIC_EncodePriority(3U, 5U, 0U));
    NVIC_EnableIRQ(EXTI0_IRQn);

    NVIC_SetPriority(EXTI1_IRQn, NVIC_EncodePriority(3U, 4U, 0U));
    NVIC_EnableIRQ(EXTI1_IRQn);

    NVIC_SetPriority(EXTI2_IRQn, NVIC_EncodePriority(3U, 5U, 0U));
    NVIC_EnableIRQ(EXTI2_IRQn);

    NVIC_SetPriority(EXTI3_IRQn, NVIC_EncodePriority(3U, 5U, 0U));
    NVIC_EnableIRQ(EXTI3_IRQn);

    NVIC_SetPriority(EXTI4_IRQn, NVIC_EncodePriority(3U, 5U, 0U));
    NVIC_EnableIRQ(EXTI4_IRQn);

    NVIC_SetPriority(EXTI5_IRQn, NVIC_EncodePriority(3U, 5U, 0U));
    NVIC_EnableIRQ(EXTI5_IRQn);

    NVIC_SetPriority(EXTI6_IRQn, NVIC_EncodePriority(3U, 5U, 0U));
    NVIC_EnableIRQ(EXTI6_IRQn);
}

/* --------------------------------------------------------------------------
 * IRQ handlers
 * -------------------------------------------------------------------------- */

void EXTI0_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_0) != 0U)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_0);
        DDR5_OnButtonIRQ(BTN_UP_PIN);
    }
}

void EXTI1_IRQHandler(void)
{
    if (LL_EXTI_IsActiveRisingFlag_0_31(LL_EXTI_LINE_1) != 0U)
    {
        LL_EXTI_ClearRisingFlag_0_31(LL_EXTI_LINE_1);
        DDR5_OnTriggerInIRQ();
    }
}

void EXTI2_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_2) != 0U)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_2);
        DDR5_OnButtonIRQ(BTN_DOWN_PIN);
    }
}

void EXTI3_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_3) != 0U)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_3);
        DDR5_OnButtonIRQ(BTN_LEFT_PIN);
    }
}

void EXTI4_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_4) != 0U)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_4);
        DDR5_OnButtonIRQ(BTN_RIGHT_PIN);
    }
}

void EXTI5_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_5) != 0U)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_5);
        DDR5_OnButtonIRQ(BTN_OK_PIN);
    }
}

void EXTI6_IRQHandler(void)
{
    if (LL_EXTI_IsActiveFallingFlag_0_31(LL_EXTI_LINE_6) != 0U)
    {
        LL_EXTI_ClearFallingFlag_0_31(LL_EXTI_LINE_6);
        DDR5_OnButtonIRQ(BTN_CANCEL_PIN);
    }
}
