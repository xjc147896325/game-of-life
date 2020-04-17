/**
  ******************************************************************************
  * @file    drv_spi.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-02-23
  * @brief   deive for hardware spi
  ******************************************************************************
  */
	
#include "drv_spi.h"

#ifndef __USE_SOFT_SPI_INTERFACE__

/** Ӳ��SPI */
#define SPI_WAIT_TIMEOUT			((uint16_t)0xFFFF)

/**
  * @brief :SPI��ʼ��(Ӳ��)
  * @param :��
  * @note  :��
  * @retval:��
  */ 
void drv_spi_init( void )
{
	GPIO_InitTypeDef	GPIO_InitStructure;
	SPI_InitTypeDef		SpiInitStructer;
	
	/** SPI�������� */
	RCC_AHB1PeriphClockCmd( SPI_CLK_GPIO_CLK | SPI_MISO_GPIO_CLK | SPI_MOSI_GPIO_CLK | SPI_NSS_GPIO_CLK, ENABLE );	//�򿪶˿�ʱ��
	
	//SCK MOSI MISO ����Ϊ����
  GPIO_InitStructure.GPIO_Pin          = GPIO_PinSource5|GPIO_PinSource6|GPIO_PinSource7;//PA5~7���ù������	
	GPIO_InitStructure.GPIO_Speed        = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode         = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType        = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd         = GPIO_PuPd_UP;
	GPIO_Init( SPI_CLK_GPIO_PORT, &GPIO_InitStructure );		//��ʼ��SCK
	

	GPIO_PinAFConfig(SPI_CLK_GPIO_PORT,GPIO_PinSource5,GPIO_AF_SPI1); //PB3����Ϊ SPI1
	
	GPIO_PinAFConfig(SPI_MOSI_GPIO_PORT,GPIO_PinSource7,GPIO_AF_SPI1); //PB4����Ϊ SPI1

	GPIO_PinAFConfig(SPI_MISO_GPIO_PORT,GPIO_PinSource6,GPIO_AF_SPI1); //PB5����Ϊ SPI1

	GPIO_SetBits( SPI_MISO_GPIO_PORT, SPI_MISO_GPIO_PIN );
	
	//NSS����Ϊ�������
	GPIO_InitStructure.GPIO_Mode         = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin          = SPI_NSS_GPIO_PIN;
	GPIO_InitStructure.GPIO_OType        = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd         = GPIO_PuPd_UP;
	GPIO_Init( SPI_NSS_GPIO_PORT, &GPIO_InitStructure );		//��ʼ��NSS
	GPIO_SetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN );		//�ø�

	/** SPI���� */
	SPI_I2S_DeInit( SPI_PORT );			//��λSPI
	
	if( SPI1 == SPI_PORT | SPI4 == SPI_PORT | SPI5 == SPI_PORT | SPI6 == SPI_PORT )				
	{
		RCC_APB2PeriphClockCmd( SPI_PORT_CLK, ENABLE );			//SPI1��APB2�ϣ�����ӦSPIʱ��
	}
	else
	{
		RCC_APB1PeriphClockCmd( SPI_PORT_CLK, ENABLE );			//SPI2 3��APB1��
	}
	
	SPI_Cmd( SPI_PORT, DISABLE );		//�ر�SPI���裬����ǰ�ر�
	
	SpiInitStructer.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;	//˫��ȫ˫��
	SpiInitStructer.SPI_Mode              = SPI_Mode_Master;				        	//����ģʽ
	SpiInitStructer.SPI_CPOL              = SPI_CPOL_Low;						        	//����״̬Ϊ�͵�ƽ 
	SpiInitStructer.SPI_CPHA              = SPI_CPHA_1Edge;					        	//��һ�����زɼ�����
	SpiInitStructer.SPI_DataSize          = SPI_DataSize_8b;			        		//8λ����
	SpiInitStructer.SPI_NSS               = SPI_NSS_Soft;				  	        	//�ӻ��������
	SpiInitStructer.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;	        //64��Ƶ
	SpiInitStructer.SPI_FirstBit          = SPI_FirstBit_MSB;					        //���λ�ȷ���
	SpiInitStructer.SPI_CRCPolynomial     = 7;							                	//CRC����ʽ,Ĭ�ϲ�ʹ��SPI�Դ�CRC	 
	
	SPI_Init( SPI_PORT, &SpiInitStructer );
	SPI_Cmd( SPI_PORT, ENABLE );
}

/**
  * @brief :SPI�շ�һ���ֽ�
  * @param :
  *			@TxByte: ���͵������ֽ�
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:���յ����ֽ�
  */
uint8_t drv_spi_read_write_byte( uint8_t TxByte )
{
	uint8_t l_Data = 0;
	uint16_t l_WaitTime = 0;
	
	while( RESET == SPI_I2S_GetFlagStatus( SPI_PORT, SPI_I2S_FLAG_TXE ) )		//�ȴ����ͻ�����Ϊ��
	{
		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
		{
			break;			//����ȴ���ʱ���˳�
		}
	}
	l_WaitTime = SPI_WAIT_TIMEOUT / 2;		//�������ý��յȴ�ʱ��(��ΪSPI���ٶȺܿ죬����������ڷ������֮��������յ����ݣ��ȴ�ʱ�䲻��Ҫ����)
	SPI_PORT->DR = TxByte;	//��������
	
	while( RESET == SPI_I2S_GetFlagStatus( SPI_PORT, SPI_I2S_FLAG_RXNE ) )		//�ȴ����ջ������ǿ�
	{
		if( SPI_WAIT_TIMEOUT == ++l_WaitTime )
		{
			break;			//����ȴ���ʱ���˳�
		}
	}
	
	l_Data = (uint8_t)SPI_PORT->DR;		//��ȡ��������
	
	return l_Data;		//����
}

/**
  * @brief :SPI�շ��ַ���
  * @param :
  *			@ReadBuffer: �������ݻ�������ַ
  *			@WriteBuffer:�����ֽڻ�������ַ
  *			@Length:�ֽڳ���
  * @note  :�Ƕ���ʽ��һ���ȴ���ʱ���������Զ��˳�
  * @retval:��
  */
void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length )
{
	GPIO_ResetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);	  		//����Ƭѡ
	while( Length-- )
	{
		*ReadBuffer = drv_spi_read_write_byte( *WriteBuffer );		//�շ�����
		ReadBuffer++;
		WriteBuffer++;			                                    	//��д��ַ��1
	}
	GPIO_SetBits( SPI_NSS_GPIO_PORT, SPI_NSS_GPIO_PIN);				  //����Ƭѡ
}

/** Ӳ��SPI */
#endif



