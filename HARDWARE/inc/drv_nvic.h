/**
  ******************************************************************************
  * @file    nvic.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-03-31
  * @brief   中断优先级管理
						 PreemptionPriority
						 SubPriority
  ******************************************************************************
  */
	
#ifndef __DRV_NVIC_H
#define __DRV_NVIC_H

/*-----------------
    NVIC_Init()
-----------------*/
#define NVIC_Priority_Init() NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2)


/*-----------------
      USART
-----------------*/

#define USART1_PreemptionPriority  1;
#define USART1_SubPriority         0;

#define USART2_PreemptionPriority  1;
#define USART2_SubPriority         1;

#define USART3_PreemptionPriority  1;
#define USART3_SubPriority         2;

#define USART6_PreemptionPriority  1;
#define USART6_SubPriority         3;


#endif




