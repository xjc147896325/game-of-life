/**
  ******************************************************************************
  * @file   
  * @author  xjc
  * @version v1.0
  * @date    
  * @brief   
  ******************************************************************************
  */
#include "timer.h"

void TIM2_Init(void)
{
  u16 arr = 8399; //自动重装载值
  u16 psc = 9;    //预分频值
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef         NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //定时器2时钟使能
	
	/*定时器2初始化*/
  TIM_TimeBaseStructure.TIM_Period = arr;              //设置重载值
  TIM_TimeBaseStructure.TIM_Prescaler = psc;           //设置分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置分频因子
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //递增计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             //将结构参数用于初始化定时器2
	
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE );           //使能定时器2更新中断
	
	/*设置中断参数*/
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //定时器2中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //抢占优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         //响应优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //使能中断通道
  NVIC_Init(&NVIC_InitStructure);                            //初始化中断
	TIM_Cmd(TIM2, ENABLE);  //使能定时器
	
}

/**
* @brief 定时器2中断函数，检测按键的状态
* @param none
* @return none
*/	
void TIM2_IRQHandler(void)
{	
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)   //每隔1ms进入一次更新中断
  {	
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);      //清除标志位
	}
}
