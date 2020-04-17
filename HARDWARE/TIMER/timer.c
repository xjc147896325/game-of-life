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
  u16 arr = 8399; //�Զ���װ��ֵ
  u16 psc = 9;    //Ԥ��Ƶֵ
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef         NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //��ʱ��2ʱ��ʹ��
	
	/*��ʱ��2��ʼ��*/
  TIM_TimeBaseStructure.TIM_Period = arr;              //��������ֵ
  TIM_TimeBaseStructure.TIM_Prescaler = psc;           //���÷�Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //���÷�Ƶ����
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //��������ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             //���ṹ�������ڳ�ʼ����ʱ��2
	
	TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE );           //ʹ�ܶ�ʱ��2�����ж�
	
	/*�����жϲ���*/
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;            //��ʱ��2�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;  //��ռ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;         //��Ӧ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            //ʹ���ж�ͨ��
  NVIC_Init(&NVIC_InitStructure);                            //��ʼ���ж�
	TIM_Cmd(TIM2, ENABLE);  //ʹ�ܶ�ʱ��
	
}

/**
* @brief ��ʱ��2�жϺ�������ⰴ����״̬
* @param none
* @return none
*/	
void TIM2_IRQHandler(void)
{	
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)   //ÿ��1ms����һ�θ����ж�
  {	
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);      //�����־λ
	}
}
