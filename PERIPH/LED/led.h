#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"
#include "sys.h"

#define LED0  PCout(0)
#define LED1  PCout(1)
#define LED2  PCout(2)
#define LED3  PCout(3)

void LED_Init(void);
void LED_Test(void);

#endif

