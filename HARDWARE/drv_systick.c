/**
  ******************************************************************************
  * @file    systick.c
  * @author  xjc
  * @version V2.0.0
  * @date    2019.11.12
  * @brief    
  ******************************************************************************
  */
#include "drv_systick.h"

uint32_t E_COUNTER;

/**
  * @brief    SysTick_Init(important) 
  * @param    none 
  * @retval   none
  */
void SysTick_Init(void)
{
	SysTick->LOAD  = (uint32_t)(SystemCoreClock/1000000 - 1UL);
	SysTick->VAL   = 0UL;
	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_TICKINT_Msk;
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief     delay fuc(imporatnt use systick)
  * @param  	 uint32_t time
  * @retval    none
  */
void delay_us(uint32_t time)
{
	if(time<=0)
		return;

	E_COUNTER = time;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(E_COUNTER!=0);
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief     delay fuc(imporatnt use systick)
  * @param  	 uint32_t time
  * @retval    none
  */
void delay_ms(uint32_t time)
{
	if(time<=0)
		return;

	E_COUNTER = time*1000;
	SysTick->VAL = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	while(E_COUNTER!=0);
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/*-----------------
      在it内
-----------------*/
////systick中断处理函数
//void SysTick_Handler(void)
//{
//	if(count!=0){
//		count--;
//	}
//}
