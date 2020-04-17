/**
  ******************************************************************************
  * @file    C620.h
  * @author  xjc
  * @version V1.0.0
  * @date    23-June-2018
  * @brief   This file contains the functions prototypes for the C620 ESC speed
  *          control and feedback infomation process.  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2018 Hex_AI</center></h2>
  *
  * Only use the function after connected the hardware and initialized the CAN bus
  *
  ******************************************************************************
  */
#include "can.h"

//CAN��ʼ��
//tsjw:����ͬ����Ծʱ�䵥Ԫ.��Χ:CAN_SJW_1tq~ CAN_SJW_4tq
//tbs2:ʱ���2��ʱ�䵥Ԫ.   ��Χ:CAN_BS2_1tq~CAN_BS2_8tq;
//tbs1:ʱ���1��ʱ�䵥Ԫ.   ��Χ:CAN_BS1_1tq ~CAN_BS1_16tq
//brp :�����ʷ�Ƶ��.��Χ:1~1024; tq=(brp)*tpclk1
//������=Fpclk1/((tbs1+1+tbs2+1+1)*brp);
//mode:CAN_Mode_Normal,��ͨģʽ;CAN_Mode_LoopBack,�ػ�ģʽ;
//Fpclk1��ʱ���ڳ�ʼ����ʱ������Ϊ42M,�������CAN1_Mode_Init(CAN_SJW_1tq,CAN_BS2_6tq,CAN_BS1_7tq,6,CAN_Mode_LoopBack);
//������Ϊ:42M/((6+7+1)*6)=500Kbps
//����ֵ:0,��ʼ��OK;
//    ����,��ʼ��ʧ��; 


void CAN1_Init()
{

  	GPIO_InitTypeDef       GPIO_InitStructure; 
	  CAN_InitTypeDef        CAN_InitStructure;
  	CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    NVIC_InitTypeDef       NVIC_InitStructure;
	
		//ʹ�����ʱ��
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��PORTAʱ��	                   											 

  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);//ʹ��CAN1ʱ��	
	
    //��ʼ��GPIO
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��PA11,PA12
	
	  //���Ÿ���ӳ������
	  GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_CAN1); //GPIOA11����ΪCAN1
	  GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_CAN1); //GPIOA12����ΪCAN1
	  
  	//CAN��Ԫ����
   	CAN_InitStructure.CAN_TTCM = DISABLE;	//��ʱ�䴥��ͨ��ģʽ   
  	CAN_InitStructure.CAN_ABOM = DISABLE;	//����Զ����߹���	  
  	CAN_InitStructure.CAN_AWUM = DISABLE;//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
  	CAN_InitStructure.CAN_NART = DISABLE;	//��ֹ�����Զ����� 
  	CAN_InitStructure.CAN_RFLM = DISABLE;	//���Ĳ�����,�µĸ��Ǿɵ�  
  	CAN_InitStructure.CAN_TXFP = ENABLE;	//���ȼ��ɱ��ı�ʶ������ 
  	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;	 //ģʽ���� 
  	CAN_InitStructure.CAN_SJW  = CAN_SJW_1tq;	//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ CAN_SJW_1tq~CAN_SJW_4tq
  	CAN_InitStructure.CAN_BS1  = CAN_BS1_9tq; //Tbs1��ΧCAN_BS1_1tq ~CAN_BS1_16tq
  	CAN_InitStructure.CAN_BS2  = CAN_BS2_4tq;//Tbs2��ΧCAN_BS2_1tq ~	CAN_BS2_8tq
  	CAN_InitStructure.CAN_Prescaler = 3;  //��Ƶϵ��(Fdiv)Ϊbrp+1	
  	CAN_Init(CAN1, &CAN_InitStructure);   // ��ʼ��CAN1 
    
		//���ù�����
 	  CAN_FilterInitStructure.CAN_FilterNumber         = 0;	  //������0
  	CAN_FilterInitStructure.CAN_FilterMode           = CAN_FilterMode_IdMask; 
  	CAN_FilterInitStructure.CAN_FilterScale          = CAN_FilterScale_32bit; //32λ 
  	CAN_FilterInitStructure.CAN_FilterIdHigh         = 0x0000;////32λID
  	CAN_FilterInitStructure.CAN_FilterIdLow          = 0x0000;
  	CAN_FilterInitStructure.CAN_FilterMaskIdHigh     = 0x0000;//32λMASK
  	CAN_FilterInitStructure.CAN_FilterMaskIdLow      = 0x0000;
   	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;//������0������FIFO0
  	CAN_FilterInitStructure.CAN_FilterActivation     = ENABLE; //���������0
  	CAN_FilterInit(&CAN_FilterInitStructure);//�˲�����ʼ��
		
		NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	
		NVIC_InitStructure.NVIC_IRQChannel = CAN1_TX_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);   

		CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
		CAN_ITConfig(CAN1,CAN_IT_TME ,ENABLE);
}

//exploer no can2 ic

void CAN1_TX_IRQHandler(void)
{
	if (CAN_GetITStatus(CAN1,CAN_IT_TME) != RESET)
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_TME);
	}
}

void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMsg;
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0) != RESET)
	{
		CAN_ClearITPendingBit(CAN1,CAN_IT_FF0);
		CAN_ClearFlag (CAN1, CAN_IT_FF0);
		CAN_Receive (CAN1, CAN_FIFO0 ,&RxMsg);
		C620_GetMotorInfo(&RxMsg);
	}
}









