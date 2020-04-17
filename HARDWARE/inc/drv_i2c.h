/**
  ******************************************************************************
  * @file    drv_i2c.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-04-17
  * @brief   header for i2c
  ******************************************************************************
  */
	
#ifndef __DRV_I2C_H
#define __DRV_I2C_H

#include "stm32f4xx.h"
#include "drv_systick.h"

#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78

// I2C2_SCL B10
// I2C2_SDA B11

void I2C_Configuration(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);


#endif
