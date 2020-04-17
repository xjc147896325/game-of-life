/**
  ******************************************************************************
  * @file    beginner.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-04-18
  * @brief   make a try
	
  ******************************************************************************
  */
	
#include "LifeGame.h"

static const u8 GliderGun_Map[]=//列行式，低位在前
{
0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x70,0x88,0x04,0x04,0x20,0x88,0x70,0x20,0x00,0x00,0x1C,0x1C,0x22,0x00,
0x63,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};

static uint8_t  state;
static char   toDraw;
static void draw_blinker(int16_t x0, int16_t y0);
static void draw_beehive(int16_t x0, int16_t y0);
static void draw_block(int16_t x0, int16_t y0);
static void draw_boat(int16_t x0, int16_t y0);
static void draw_toad(int16_t x0, int16_t y0);
static void draw_glider(int16_t x0, int16_t y0);
static void draw_spaceship(int16_t x0, int16_t y0);
static void draw_GliderGun(int16_t x0, int16_t y0);
//static void draw_TV(int16_t x0, int16_t y0);

/*---------------------------------------------------------------------------*/
/*                              Main Functions                               */
/*---------------------------------------------------------------------------*/

void InitBeginner(void)
{
   // state = 0;
	toDraw = true;
}

void UpdateBeginner(void)
{
	state = 4;
}

void DrawBeginner(void)
{
	if (toDraw) 
	{
		OLED_ClearDisplay();
		switch (state) 
		{
			case 0:
			{
				draw_blinker(62,30);
				draw_blinker(32,30);
				draw_blinker(92,30);
				draw_toad(62,15);
				draw_toad(32,15);
				draw_toad(92,15);
				break;
			}
			case 1:
			{
				draw_beehive(62,45);
				draw_beehive(32,45);
				draw_beehive(92,45);
				draw_block(62,30);
				draw_block(32,30);
				draw_block(92,30);
				draw_boat(62,15);
				draw_boat(32,15);
				draw_boat(92,15);
				break;
			}
			case 2:  
			{
				draw_glider(32,30);
				draw_glider(92,30);
				draw_glider(62,30);
				break;
			}
			case 3:
			{
				draw_spaceship(32,30);
				draw_spaceship(62,30);
				draw_spaceship(92,30);
				break;
			}
			case 4:
			{
				draw_GliderGun(30,30);
				break;
			}
			case 5:
			{
//				draw_TV(31,0);
				break;
			}
			default:
			{
				break;
			}
		}
		toDraw = false;
	}
}

/*---------------------------------------------------------------------------*/
/*                              Draw Functions                               */
/*---------------------------------------------------------------------------*/


static void draw_blinker(int16_t x0, int16_t y0)//闪光灯 3x1
{	
	OLED_DrawLine(x0,y0,x0+2,y0,1);
}
static void draw_beehive(int16_t x0, int16_t y0)//蜂窝 3x4
{	
	OLED_DrawPixel(x0,y0+1,1);	
	OLED_DrawPixel(x0,y0+2,1);
	OLED_DrawPixel(x0+1,y0,1);
	OLED_DrawPixel(x0+1,y0+3,1);
	OLED_DrawPixel(x0+2,y0+1,1);	
	OLED_DrawPixel(x0+2,y0+2,1);
}
static void draw_block(int16_t x0, int16_t y0)//小区 2x2
{	
	FillRect2(x0,y0,2,2,1);	
}
static void draw_boat(int16_t x0, int16_t y0)//小船 3x3
{	
	OLED_DrawPixel(x0,y0,1);	
	OLED_DrawPixel(x0,y0+1,1);
	OLED_DrawPixel(x0+1,y0,1);	
	OLED_DrawPixel(x0+2,y0+1,1);
	OLED_DrawPixel(x0+1,y0+2,1);	
}
static void draw_toad(int16_t x0, int16_t y0)//蛤蟆 4x2
{
	OLED_DrawLine(x0+1,y0,x0+3,y0,1);
	OLED_DrawLine(x0,y0+1,x0+2,y0+1,1);
}
static void draw_glider(int16_t x0, int16_t y0)//滑翔机 3x3
{
	OLED_DrawLine(x0,y0,x0+2,y0,1);
	OLED_DrawPixel(x0,y0+1,1);
	OLED_DrawPixel(x0+1,y0+2,1);
}
static void draw_spaceship(int16_t x0, int16_t y0)//太空船 5x4
{
	OLED_DrawLine(x0,y0+3,x0+3,y0+3,1);
		
	OLED_DrawPixel(x0,y0+1,1);
	OLED_DrawPixel(x0,y0+2,1);	
		
	OLED_DrawPixel(x0+1,y0,1);
	OLED_DrawPixel(x0+4,y0,1);
		
	OLED_DrawPixel(x0+4,y0+2,1);
}
static void draw_GliderGun(int16_t x0, int16_t y0)//滑翔机枪 36x9
{
	OLED_DrawBitmap(x0,y0,GliderGun_Map,36,9,1);
}
//static void draw_TV(int16_t x0, int16_t y0)//小电视 64x64
//{
//	OLED_DrawBitmap(x0,y0,BlibliTv_Map,64,64,1);
//}
