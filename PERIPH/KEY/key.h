#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"
#include "systick.h"
#include "led.h"
#include "beep.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4) //PC4
#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5) //PC5
	
void Key_Init(void);
void Key_Scan(void);

#endif
