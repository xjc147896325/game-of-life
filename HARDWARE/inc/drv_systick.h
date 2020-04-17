#ifndef __DRV_SYSTICK_H
#define __DRV_SYSTICK_H

#include "stm32f4xx.h"

extern uint32_t E_COUNTER;

void SysTick_Init(void);
void delay_us(uint32_t time);
void delay_ms(uint32_t time);


#endif

