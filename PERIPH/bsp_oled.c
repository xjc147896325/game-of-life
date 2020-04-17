
/**
  ******************************************************************************
  * @file    bsp_oled.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-04-17
  * @brief   oled bsp��copy��
  ******************************************************************************
  */
	
#include "bsp_oled.h"

  int16_t cursor_x;
  int16_t cursor_y;
  uint8_t textsize=1;
  uint8_t textcolor=1;
  uint8_t textbg=0;
//oled�Դ�ӳ��
u8 OLED_GRAM[OLED_WIDTH*OLED_HEIGHT/8];	

void OLED_Init(void)
{
	delay_ms(50); //�������ʱ����Ҫ
	
	WriteCmd(0xAE); //display off
	WriteCmd(0x20);	//Set Memory Addressing Mode	
	WriteCmd(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	WriteCmd(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	WriteCmd(0xc8);	//Set COM Output Scan Direction
	WriteCmd(0x00); //---set low column address
	WriteCmd(0x10); //---set high column address
	WriteCmd(0x40); //--set start line address
	WriteCmd(0x81); //--set contrast control register
	WriteCmd(0xff); //���ȵ��� 0x00~0xff
	WriteCmd(0xa1); //--set segment re-map 0 to 127
	WriteCmd(0xa6); //--set normal display
	WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
	WriteCmd(0x3F); //
	WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	WriteCmd(0xd3); //-set display offset
	WriteCmd(0x00); //-not offset
	WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
	WriteCmd(0xf0); //--set divide ratio
	WriteCmd(0xd9); //--set pre-charge period
	WriteCmd(0x22); //
	WriteCmd(0xda); //--set com pins hardware configuration
	WriteCmd(0x12);
	WriteCmd(0xdb); //--set vcomh
	WriteCmd(0x20); //0x20,0.77xVcc
	WriteCmd(0x8d); //--set DC-DC enable
	WriteCmd(0x14); //
	WriteCmd(0xaf); //--turn on oled panel
}

//�����Դ浽OLED
void OLED_Refresh_Gram(void)
{
  WriteCmd(0x20);
  WriteCmd(0);
	
  WriteCmd(0x21);
  WriteCmd(0);   // Column start address (0 = reset)
  WriteCmd(OLED_WIDTH-1); // Column end address (127 = reset)

  WriteCmd(0x22);
  WriteCmd(0); // Page start address (0 = reset)
  WriteCmd(7); // Page end address

  for(int i=0; i<OLED_WIDTH*OLED_HEIGHT/8; i++){
    WriteDat(OLED_GRAM[i]);
  } 
}
//OLED�������
void OLED_FillScreen(u8 color)
{
  if (color) color = 0xFF;  
  for(int16_t i=0; i<OLED_WIDTH*OLED_HEIGHT/8; i++)  
  { 
    OLED_GRAM[i] = color; 
  }
}
//OLED����
u8 OLED_GetPixel(u8 x, u8 y)
{
  uint8_t row = y / 8;
  uint8_t bit_position = y % 8;
  return (OLED_GRAM[(row*OLED_WIDTH) + (u8)x] & _BV(bit_position)) >> bit_position;
}
//OLED����
void OLED_DrawPixel(u8 x, u8 y, u8 color)
{
  if ( x > (OLED_WIDTH-1) ||  y > (OLED_HEIGHT-1))
  {
    return;
  }

  u8 row = (u8)y / 8;
  if (color)
  {
    OLED_GRAM[(row*OLED_WIDTH) + (u8)x] |=   _BV((u8)y % 8);
  }
  else
  {
    OLED_GRAM[(row*OLED_WIDTH) + (u8)x] &= ~ _BV((u8)y % 8);
  }
}
//��Բ
void OLED_DrawCircle(int16_t x0, int16_t y0, uint8_t r, uint8_t color)
{
  int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  OLED_DrawPixel(x0, y0+r, color);
  OLED_DrawPixel(x0, y0-r, color);
  OLED_DrawPixel(x0+r, y0, color);
  OLED_DrawPixel(x0-r, y0, color);

  while (x<y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }

    x++;
    ddF_x += 2;
    f += ddF_x;

    OLED_DrawPixel(x0 + x, y0 + y, color);
    OLED_DrawPixel(x0 - x, y0 + y, color);
    OLED_DrawPixel(x0 + x, y0 - y, color);
    OLED_DrawPixel(x0 - x, y0 - y, color);
    OLED_DrawPixel(x0 + y, y0 + x, color);
    OLED_DrawPixel(x0 - y, y0 + x, color);
    OLED_DrawPixel(x0 + y, y0 - x, color);
    OLED_DrawPixel(x0 - y, y0 - x, color);
  }
}
//����ֱ��
void OLED_DrawFastVLine(int16_t x, int16_t y, int8_t h, uint8_t color)
{
  int end = y+h;
	
    /*  Check parameters  */
    if (y < 0) {
        if (h <= -y) return;
        h += y;
        y = 0;
    }
    if (h <= 0 || y >= OLED_HEIGHT || x <= 0 || x >= OLED_WIDTH) return;
    if (y + h > OLED_HEIGHT) h = OLED_HEIGHT - y;
	
  for (int a = max(0,y); a < min(end,OLED_HEIGHT); a++)
  {
    OLED_DrawPixel(x,a,color);
  }
}
//��ˮƽ��
void OLED_DrawFastHLine(int16_t x, int16_t y, uint8_t w, uint8_t color)
{	
  int end = x+w;
    /*  Check parameters  */
    if (x < 0) {
        if (w <= -x) return;
        w += x;
        x = 0;
    }
    if (w <= 0 || x >= OLED_WIDTH || y <= 0 || y >= OLED_HEIGHT) return;
    if (x + w > OLED_WIDTH) w = OLED_WIDTH - x;
	
  for (int a = max(0,x); a < min(end,OLED_WIDTH); a++)
  {
    OLED_DrawPixel(a,y,color);
  }
}
//��ͼ
void OLED_DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t color)
{
 int yOffset = ABS(y) % 8;
 int sRow = y / 8;
 if (y < 0) {
   sRow--;
   yOffset = 8 - yOffset;
 }
 int rows = h/8;
 if (h%8!=0) rows++;
 for (int a = 0; a < rows; a++) {
   int bRow = sRow + a;
   if (bRow > (OLED_HEIGHT/8)-1) break;
   if (bRow > -2) {
     for (int iCol = 0; iCol<w; iCol++) {
       if (iCol + x > (OLED_WIDTH-1)) break;
       if (iCol + x >= 0) {
         if (bRow >= 0) {
           if      (color == WHITE) OLED_GRAM[ (bRow*OLED_WIDTH) + x + iCol ] |= (pgm_read_byte(bitmap+(a*w)+iCol) << yOffset);
           else if (color == BLACK) OLED_GRAM[ (bRow*OLED_WIDTH) + x + iCol ] &= (pgm_read_byte(bitmap+(a*w)+iCol) << yOffset);
           else                     OLED_GRAM[ (bRow*OLED_WIDTH) + x + iCol ] ^= pgm_read_byte(bitmap+(a*w)+iCol) << yOffset;
         }
         if (yOffset && bRow<(OLED_HEIGHT/8)-1 && bRow > -2) {
           if      (color == WHITE) OLED_GRAM[ ((bRow+1)*OLED_WIDTH) + x + iCol ] |= pgm_read_byte(bitmap+(a*w)+iCol) >> (8-yOffset);
           else if (color == BLACK) OLED_GRAM[ ((bRow+1)*OLED_WIDTH) + x + iCol ] &= ~(pgm_read_byte(bitmap+(a*w)+iCol) >> (8-yOffset));
           else                     OLED_GRAM[ ((bRow+1)*OLED_WIDTH) + x + iCol ] ^= pgm_read_byte(bitmap+(a*w)+iCol) >> (8-yOffset);
         }
       }
     }
   }
 }
}
//��ʵ�ľ���
void FillRect(int16_t x, int16_t y, uint8_t w, uint8_t h, uint8_t color)
{
  for (int16_t i=x; i<x+w; i++)
  {
    OLED_DrawFastVLine(i, y, h, color);
  }
}
//void FillBeltBlack(uint8_t *p, uint8_t d, uint8_t w)
//{
//    d = ~d;
//    for (; w > 0; w--) {
//        *p++ &= d;
//    }
//}
//void FillBeltWhite(uint8_t *p, uint8_t d, uint8_t w)
//{
//    for (; w > 0; w--) {
//        *p++ |= d;
//    }
//}
//��ʵ�ľ��� �������������
void FillRect2(int16_t x, int16_t y, uint8_t w, int8_t h, uint8_t color)
{
    /*  Check parameters  */
    if (x < 0) {
        if (w <= -x) return;
        w += x;
        x = 0;
    }
    if (y < 0) {
        if (h <= -y) return;
        h += y;
        y = 0;
    }
    if (w <= 0 || x >= OLED_WIDTH || h <= 0 || y >= OLED_HEIGHT) return;
    if (x + w > OLED_WIDTH) w = OLED_WIDTH - x;
    if (y + h > OLED_HEIGHT) h = OLED_HEIGHT - y;

    /*  Draw a filled rectangle  */
	  for (int16_t i=x; i<x+w; i++)
	  {
		OLED_DrawFastVLine(i, y, h, color);
	  }
//	/*  Draw a filled rectangle2  */
//    uint8_t yOdd = y & 7;
//    uint8_t d = 0xFF << yOdd;
//    y -= yOdd;
//    h += yOdd;
//    for (uint8_t *p = OLED_GRAM + x + (y / 8) * OLED_WIDTH; h > 0; h -= 8, p += OLED_WIDTH) {
//        if (h < 8) d &= 0xFF >> (8 - h);
//        if (color == BLACK) {
//            FillBeltBlack(p, d, w);
//        } else {
//            FillBeltWhite(p, d, w);
//        }
//        d = 0xFF;
//    }
}
void DrawChar(int16_t x, int16_t y, unsigned char c, uint8_t color, uint8_t bg, uint8_t size)
{
	  //color=1;
    u8 draw_bg = bg != color;

    if (x >= OLED_WIDTH || y >= OLED_HEIGHT || x + 5 * size < 0 || y + 6 * size < 0) return;
    uint32_t ptn = pgm_read_dword(imgFont + (c - ' '));
    if (size == 1) {
        for (int8_t i = 0; i < 6; i++) {
            for (int8_t j = 0; j < 6; j++) {
                u8 draw_fg = ptn & 0x1;
                if (draw_fg || draw_bg) {
                    OLED_DrawPixel(x + i, y + j, (draw_fg) ? color : bg);
                }
                ptn >>= 1;
            }
        }
    } else {
        for (int8_t i = 0; i < 6; i++) {
            for (int8_t j = 0; j < 6; j++) {
                u8 draw_fg = ptn & 0x1;
                if (draw_fg || draw_bg) {
                    FillRect(x + i * size, y + j * size, size, size, (draw_fg) ? color : bg);
                }
                ptn >>= 1;
            }
        }
    }
}
//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,char *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		DrawChar(x,y,chr[j],1,0,1);
			x+=8;
		if(x>(OLED_WIDTH-8)){x=0;y+=6;}
			j++;
	}
}
//�����ľ���
void DrawRect(int16_t x, int16_t y, uint8_t w, int8_t h, uint8_t color)
{
    OLED_DrawFastHLine(x, y, w, color);
    OLED_DrawFastHLine(x, y + h - 1, w, color);
    OLED_DrawFastVLine(x, y + 1, h - 2, color);
    OLED_DrawFastVLine(x + w - 1, y + 1, h - 2, color);
}
 void FillPatternedRect(int16_t x, int16_t y, uint8_t w, int8_t h, const uint8_t *ptn)
{
    /*  Check parameters  */
    if (x < 0) {
        if (w <= -x) return;
        w += x;
        x = 0;
    }
    if (y < 0) {
        if (h <= -y) return;
        h += y;
        y = 0;
    }
    if (w <= 0 || x >= OLED_WIDTH || h <= 0 || y >= OLED_HEIGHT) return;
    if (x + w > OLED_WIDTH) w = OLED_WIDTH - x;
    if (y + h > OLED_HEIGHT) h = OLED_HEIGHT - y;

    /*  Draw a patterned rectangle  */
    uint8_t yOdd = y & 7;
    uint8_t d = 0xFF << yOdd;
    y -= yOdd;
    h += yOdd;
    for (uint8_t *p = OLED_GRAM + x + (y / 8) * OLED_WIDTH; h > 0; h -= 8, p += OLED_WIDTH - w) {
        if (h < 8) d &= 0xFF >> (8 - h);
        for (uint8_t i = w; i > 0; i--, p++) {
            *p = (*p & ~d)|(pgm_read_byte(ptn + (int) p % 4) & d);
        }
        d = 0xFF;
    }
}
void swap(int16_t *a, int16_t *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}
//OLED����
void OLED_DrawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color)
{
  // bresenham's algorithm - thx wikpedia
  uint8_t steep = ABS(y1 - y0) > ABS(x1 - x0);
  if (steep) {
    swap(&x0, &y0);
    swap(&x1, &y1);
  }

  if (x0 > x1) {
    swap(&x0, &x1);
    swap(&y0, &y1);
  }

  int16_t dx, dy;
  dx = x1 - x0;
  dy = ABS(y1 - y0);

  int16_t err = dx / 2;
  int8_t ystep;

  if (y0 < y1)
  {
    ystep = 1;
  }
  else
  {
    ystep = -1;
  }

  for (; x0 <= x1; x0++)
  {
    if (steep)
    {
      OLED_DrawPixel(y0, x0, color);
    }
    else
    {
      OLED_DrawPixel(x0, y0, color);
    }

    err -= dy;
    if (err < 0)
    {
      y0 += ystep;
      err += dx;
    }
  }
}
void OLED_Write(uint8_t c)
{
    if (c == '\n') {
        cursor_y += textsize * 6;
        cursor_x = 0;
    } else if (c >= ' ' && c <= '_') {
        DrawChar(cursor_x, cursor_y, c, textcolor, textbg, textsize);
        cursor_x += textsize * 6;
        if ( (cursor_x > (OLED_WIDTH - textsize * 6))) OLED_Write('\n');
    }
  
}

//��������
void SetCursor(int16_t x, int16_t y)
{
  cursor_x = x;
  cursor_y = y;
}
//�����ַ���С
void SetTextSize(uint8_t s)
{
  textsize = max(1,s); 
}

void OLED_PrintChar( char *chr)
{
	unsigned char j=0;
	while (chr[j]!='\0')
	{		
		OLED_Write(chr[j]);
		j++;
	}
}
void OLED_PrintNum(u16 num)
{
	unsigned char j=0;
	char chr[6];
	sprintf(chr, "%d", num); 
	while (chr[j]!='\0')
	{		
		OLED_Write(chr[j]);
		j++;
	}
}
//�������ӡ�ַ���
int OLED_PrintCharEx(int16_t x, int16_t y,char *chr)
{
	//size_t n = 0;
	SetCursor(x,y);
	unsigned char j=0;
	while (chr[j]!='\0')
	{		
		OLED_Write(chr[j]);
		j++;
	}
	return j;
}

//OLED����
void OLED_ClearDisplay(void) 
{
  OLED_FillScreen(BLACK);
}
//����OLED��ʾ    
void OLED_Display_On(void)
{
	WriteCmd(0X8D);  //SET DCDC����
	WriteCmd(0X14);  //DCDC ON
	WriteCmd(0XAF);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	WriteCmd(0X8D);  //SET DCDC����
	WriteCmd(0X10);  //DCDC OFF
	WriteCmd(0XAE);  //DISPLAY OFF
} 

