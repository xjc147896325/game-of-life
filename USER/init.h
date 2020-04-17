/**
  ******************************************************************************
  * @file    init.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-03-30
  * @brief   Í·ÎÄ¼þ
						 

  ******************************************************************************
  */
	
#ifndef __INIT_H
#define __INIT_H

#include "stm32f4xx.h"
#include "drv_systick.h"
#include "drv_uart.h"
#include "drv_i2c.h"
#include "bsp_oled.h"
#include "LifeGame.h"

void System_Init(void);

#endif
