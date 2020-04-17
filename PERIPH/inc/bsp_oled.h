/**
  ******************************************************************************
  * @file    bsp_oled.h
  * @author  jOKERII
  * @version v1.0
  * @date    20-04-17
  * @brief   header of oled
  ******************************************************************************
  */
	
#ifndef __BSP_OLED_H
#define __BSP_OLED_H

#include "stm32f4xx.h"
#include "oled_font.h"
#include "drv_systick.h"
#include "drv_i2c.h"
#include "stdio.h"
#include "main.h"

#define OLED_WIDTH  128
#define OLED_HEIGHT 64

#define WHITE 1 
#define BLACK 0 

#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))
#define ABS(x) (((x) > 0) ? (x) : -(x))
#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_dword(addr) (*(const unsigned long *)(addr))	

void OLED_Init(void);

void OLED_Refresh_Gram(void);//更新OLED显存
void OLED_FillScreen(u8 color);//OLED整屏填充
void OLED_DrawPixel(u8 x, u8 y, u8 color);//画点
u8 OLED_GetPixel(u8 x, u8 y);//读点
void OLED_DrawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color);//画圆
void OLED_ClearDisplay(void);//OLED清屏
void OLED_DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color);//OLED画图
void DrawChar(int16_t x, int16_t y, unsigned char c, uint8_t color, uint8_t bg, uint8_t size);//画字符
void FillRect2(int16_t x, int16_t y, uint8_t w, int8_t h, uint8_t color);////画实心矩形 带输入参数保护
void OLED_ShowString(u8 x,u8 y,char *chr);//OLED显示字符串
void DrawRect(int16_t x, int16_t y, uint8_t w, int8_t h, uint8_t color);//画空心矩形
void FillPatternedRect(int16_t x, int16_t y, uint8_t w, int8_t h, const uint8_t *ptn);
void OLED_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);//画线
void OLED_DrawFastVLine(int16_t x, int16_t y, int8_t h, uint8_t color);//画垂直线
void OLED_DrawFastHLine(int16_t x, int16_t y, uint8_t w, uint8_t color);//画水平线
void SetCursor(int16_t x, int16_t y);//设置坐标
void OLED_PrintChar( char *chr);//打印字符串
void OLED_PrintNum(u16 num);//打印数字
int  OLED_PrintCharEx(int16_t x, int16_t y,char *chr);////带坐标打印字符串

#endif

