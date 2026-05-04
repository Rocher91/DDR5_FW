/*
 * DDR5_Time.h
 *
 *  Created on: Apr 29, 2026
 *      Author: Xavi
 */

#ifndef INC_DDR5_TIME_H_
#define INC_DDR5_TIME_H_

#include <stdint.h>

void DDR5_Time_IncTick(void);
uint32_t DDR5_GetTick(void);
void DDR5_Delay_ms(uint32_t ms);

typedef struct
{
    uint32_t start;
    uint32_t timeout_ms;
} DDR5_Timeout_t;

void DDR5_Timeout_Start(DDR5_Timeout_t *t, uint32_t timeout_ms);
uint8_t DDR5_Timeout_Expired(const DDR5_Timeout_t *t);

#endif /* INC_DDR5_TIME_H_ */
