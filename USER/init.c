/**
  ******************************************************************************
  * @file    init.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-03-30
  * @brief   System_Init(void);
						 

  ******************************************************************************
  */

#include "init.h"

/**
  * @brief  system init
  * @param  none
  * @retval нч
  */
void System_Init(void)
{
	char s[] = "heiheihei";
	
	SystemInit();
	NVIC_Priority_Init();
	SysTick_Init();
	
	USART1_Init(115200);
	
	Serial_Send(Serial1,"ready %s \r\n",&s);
	
	delay_ms(500);
	
}


