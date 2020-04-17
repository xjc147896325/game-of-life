/**
  ******************************************************************************
  * @file    GameControl.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-04-18
  * @brief   make a try
	
  ******************************************************************************
  */

#include "LifeGame.h"

enum MODE
{
	BEGINNER_MODE,
	GAME_MODE
};

typedef struct {
    void (*InitFunc)(void);
    void (*UpdateFunc)(void);
    void (*DrawFunc)(void);
} MODULE_FUNCS;

static const MODULE_FUNCS moduleBeginner[] = {
    { InitBeginner, UpdateBeginner, DrawBeginner },
    { InitGame,  UpdateGame,  DrawGame },
};

static enum MODE mode = BEGINNER_MODE;
char isDone = 0;

void LifeGame(void)
{
	if(!isDone)
	{
		moduleBeginner[BEGINNER_MODE].InitFunc();
		isDone = 1;
	}
	moduleBeginner[mode].UpdateFunc();
	moduleBeginner[mode].DrawFunc();
	OLED_Refresh_Gram();//¸üÐÂOLEDÏÔ´æ
	if (isDone == 1) 
	{
		mode = (mode == BEGINNER_MODE) ? GAME_MODE : BEGINNER_MODE;
		moduleBeginner[mode].InitFunc();
		isDone = 2;
	}
}
