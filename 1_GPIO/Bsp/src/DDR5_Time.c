/*
 * DDR5_Time.c
 *
 *  Created on: Apr 29, 2026
 *      Author: Xavi
 */

#include "DDR5_Time.h"

static volatile uint32_t g_ms_ticks = 0;

void DDR5_Time_IncTick(void)
{
    g_ms_ticks++;
}

uint32_t DDR5_GetTick(void)
{
    return g_ms_ticks;
}

void DDR5_Delay_ms(uint32_t ms)
{
    uint32_t start = DDR5_GetTick();

    while ((DDR5_GetTick() - start) < ms)
    {
    }
}

void DDR5_Timeout_Start(DDR5_Timeout_t *t, uint32_t timeout_ms)
{
    if (t == 0)
        return;

    t->start = DDR5_GetTick();
    t->timeout_ms = timeout_ms;
}

uint8_t DDR5_Timeout_Expired(const DDR5_Timeout_t *t)
{
    if (t == 0)
        return 1U;

    return ((DDR5_GetTick() - t->start) >= t->timeout_ms) ? 1U : 0U;
}
