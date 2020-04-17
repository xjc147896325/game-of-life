/**
  ******************************************************************************
  * @file    key.c
  * @author  xjc
  * @version v1.0
  * @date    19-10-18
  * @brief   keyscan
  ******************************************************************************
  */
	
#include "key.h"

void Key_Init(void)
{
	//GPIO_Init
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
void Key_Scan(void)
{	 
	static u8 key_up=1;//按键按松开标志
	if(0)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)
		{
			LED2 = ~LED2;
		}
		else 
		{
			if(KEY1==0)
			{
				LED3 = ~LED3;
				Beep_Change();
			}
		}
	}
	else 
	{
		if(KEY0==1&&KEY1==1)
		{
			key_up=1; 	
		}
	}		
}
