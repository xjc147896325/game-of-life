/**
  ******************************************************************************
  * @file    LifeGame.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-04-18
  * @brief   make a try
	
  ******************************************************************************
  */
	
#ifndef __LIFEGAME_H
#define __LIFEGAME_H

#include "stm32f4xx.h"
#include "bsp_oled.h"
#include "main.h"

#define LIFEGAME_WIDTH  128
#define LIFEGAME_HEIGHT 64
#define ALIVE  1
#define DEAD  0

/*  beginner  */
void InitBeginner(void);
void UpdateBeginner(void);
void DrawBeginner(void);
/*  game  */
void InitGame(void);
void UpdateGame(void);
void DrawGame(void);

/*  Global Variables  */
void LifeGame(void);

#endif
