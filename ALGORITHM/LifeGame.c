/**
  ******************************************************************************
  * @file    LifeGame.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-04-18
  * @brief   make a try
	
  ******************************************************************************
  */

#include "LifeGame.h"

uint8_t Display_Temp[LIFEGAME_WIDTH][LIFEGAME_HEIGHT];

static uint8_t toDraw;

/**
  * @brief     num of alive cells
  * @param     (x,y)
  * @retval    uint8_t count
  */
uint8_t NeighborCount( uint16_t x, uint16_t y)//判断当前细胞周围存活个数 非全局函数
{
  int i;       
  int j;       
  int count = 0;
  
	if ( x >= (LIFEGAME_WIDTH-1)||y >= (LIFEGAME_HEIGHT-1)||x <=0||y <=0)//边界处理
  {
	return 0xff;
  }
	
  for (i = x-1; i <= x+1; i++)
	{
		for (j = y-1; j <= y+1; j++)
		if (OLED_GetPixel(i,j) == ALIVE)
		{
			count++;
		}
	}
	
	if (OLED_GetPixel(x,y) == ALIVE)  //上面统计包括本身共9点
	{
		count --;
	}
	
  return count;
}

/**
  * @brief     updata buff to gram
  * @param     none
  * @retval    none
  */
void UpDate(void)
{
	int i,j;
	for(i=0;i<LIFEGAME_WIDTH;i++)
	{
		for(j=0;j<LIFEGAME_HEIGHT;j++)
		{
			if(Display_Temp[i][j]==ALIVE)
			{
			OLED_DrawPixel(i,j,ALIVE);
			}
			else
			{
			OLED_DrawPixel(i,j,DEAD);
			}
		}
	}
}

/**
  * @brief     就是清屏
  * @param     none
  * @retval    none
  */
void InitGame(void)
{
	int i,j;
	for(i=0;i<LIFEGAME_WIDTH;i++)
	{
		for(j=0;j<LIFEGAME_HEIGHT;j++)
		{
		Display_Temp[i][j]=0;
		}
	}
}

/**
  * @brief     更新数据
  * @param     none
  * @retval    none
  */
void UpdateGame(void)
{
	int i = 0, j = 0;
	toDraw = true;
	for(i=0;i<LIFEGAME_WIDTH;i++)
	{
		for(j=0;j<LIFEGAME_HEIGHT;j++)
		{
			if (OLED_GetPixel(i,j) == ALIVE)
			{
				switch(NeighborCount(i,j))
				{
					 case 0:
						 Display_Temp[i][j]=DEAD;
					 break;
		
					 case 1:
						 Display_Temp[i][j]=DEAD;
					 break;
						
					 case 2:
						 Display_Temp[i][j]=ALIVE;
					 break;
							
					 case 3:
						 Display_Temp[i][j]=ALIVE;
					 break;
							
					 case 4:
							Display_Temp[i][j]=DEAD;
					 break;
					 
					 case 5:
							Display_Temp[i][j]=DEAD;
					 break;
					 
					 case 6:
							Display_Temp[i][j]=DEAD;
					 break;
					 
					 case 7:
							Display_Temp[i][j]=DEAD;
					 break;
					 
					 case 8:
							Display_Temp[i][j]=DEAD;
					 break;
					 
					 default:
						Display_Temp[i][j]=DEAD; 
					 break;
					 
				}
			}
			else
			{
				switch(NeighborCount(i,j))
				{
				 case 0:
					 Display_Temp[i][j]=DEAD;
				 break;
				 
				 case 1:
					 Display_Temp[i][j]=DEAD;
				 break;
					
				 case 2:
					 Display_Temp[i][j]=DEAD;
				 break;
						
				 case 3:
					 Display_Temp[i][j]=ALIVE;
				 break;
						
				 case 4:
						Display_Temp[i][j]=DEAD;
				 break;
				 
				 case 5:
						Display_Temp[i][j]=DEAD;
				 break;
				 
				 case 6:
						Display_Temp[i][j]=DEAD;
				 break;
				 
				 case 7:
						Display_Temp[i][j]=DEAD;
				 break;
				 
				 case 8:
						Display_Temp[i][j]=DEAD;
				 break;
				 
				 default:
					 Display_Temp[i][j]=DEAD; 
				 break;
				}
			}
		}
	}
}

/**
  * @brief     updata
  * @param     none
  * @retval    none
  */
void DrawGame(void)
{
	if(toDraw)
	{
		UpDate();
		toDraw=false;
	}
}
