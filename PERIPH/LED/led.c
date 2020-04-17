/**
  ******************************************************************************
  * @file    led.c
  * @author  jOKERII
  * @version v1.0
  * @date    19-09-24
  * @brief   LED_Change();
  ******************************************************************************
  */
	
#include "led.h"

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	LED0 = 0;
	LED1 = 0;
	LED2 = 1;
	LED3 = 1;
}

void LED_Test(void)
{
	static uint8_t i = 0;
	if(i >= 200)
	{
		LED0 = ~LED0;
		i    = 0;
	}
	i++;
}
