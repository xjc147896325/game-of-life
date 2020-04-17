/**
  ******************************************************************************
  * @file    drv_spi.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-02-23
  * @brief   SPI .h file
						 �궨��__USE_SOFT_SPI_INTERFACE__�����Ƿ�ʹ�����spi�������ƣ�
						 
  ******************************************************************************
  */

#ifndef __DRV_SPI_H
#define __DRV_SPI_H

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "main.h"

//SPI���Ŷ���
#define SPI_CLK_GPIO_PORT			GPIOA
#define SPI_CLK_GPIO_CLK			RCC_AHB1Periph_GPIOA
#define SPI_CLK_GPIO_PIN			GPIO_Pin_5

#define SPI_MISO_GPIO_PORT		GPIOA
#define SPI_MISO_GPIO_CLK			RCC_AHB1Periph_GPIOA
#define SPI_MISO_GPIO_PIN			GPIO_Pin_6

#define SPI_MOSI_GPIO_PORT		GPIOA
#define SPI_MOSI_GPIO_CLK			RCC_AHB1Periph_GPIOA
#define SPI_MOSI_GPIO_PIN			GPIO_Pin_7

#define SPI_NSS_GPIO_PORT			GPIOA
#define SPI_NSS_GPIO_CLK			RCC_AHB1Periph_GPIOG
#define SPI_NSS_GPIO_PIN			GPIO_Pin_4


#define spi_set_nss_high( )			SPI_NSS_GPIO_PORT->ODR |= SPI_NSS_GPIO_PIN						            		//Ƭѡ�ø�
#define spi_set_nss_low( )			SPI_NSS_GPIO_PORT->ODR &= (uint32_t)( ~((uint32_t)SPI_NSS_GPIO_PIN ))	//Ƭѡ�õ�

	#ifdef __USE_SOFT_SPI_INTERFACE__			/** ֻ��ʹ�����SPI����Ҫ�ķ�װ */			

	#define spi_set_clk_high( )			SPI_CLK_GPIO_PORT->ODR |= SPI_CLK_GPIO_PIN								//ʱ���ø�
	#define spi_set_clk_low( )			SPI_CLK_GPIO_PORT->ODR &= (uint32_t)( ~((uint32_t)SPI_CLK_GPIO_PIN ))	//ʱ���õ�

	#define spi_set_mosi_hight( )		SPI_MOSI_GPIO_PORT->ODR |= SPI_MOSI_GPIO_PIN							//���ͽ��ø�
	#define spi_set_mosi_low( )			SPI_MOSI_GPIO_PORT->ODR &= (uint32_t)( ~((uint32_t)SPI_MOSI_GPIO_PIN ))	//���ͽ��õ�

	#define spi_get_miso( )				(( SPI_MISO_GPIO_PORT->IDR & (uint32_t)SPI_MISO_GPIO_PIN) != SPI_MISO_GPIO_PIN ) ? 0 : 1 // ����Ӧ����λΪ����õ�0����Ӧ����λΪ����õ�1


	void drv_spi_init( void );
	uint8_t drv_spi_read_write_byte( uint8_t TxByte );
	void drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length );


	#else								                	/** ֻ��ʹ��Ӳ��SPIʱ��ʹ�� */


	//SPI�ӿڶ���
	#define SPI_PORT				  	SPI1				        		//SPI�ӿ�
	#define SPI_PORT_CLK				RCC_APB2Periph_SPI1			//SPIʱ��


	void    drv_spi_init( void );
	uint8_t drv_spi_read_write_byte( uint8_t TxByte );
	void    drv_spi_read_write_string( uint8_t* ReadBuffer, uint8_t* WriteBuffer, uint16_t Length );

	#endif

#endif

