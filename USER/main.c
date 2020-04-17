/**
  ******************************************************************************
  * @file    main.c
  * @author  jOKERII
  * @version v1.0
  * @date    20-04-17
  * @brief   
  ******************************************************************************
  */
#include "main.h"

int main()
{
//	uint16_t i = 0;
	
	System_Init();
	
	I2C_Configuration();
	OLED_Init();
	
	OLED_FillScreen(BLACK);
//	OLED_DrawLine(10,10,100,10,WHITE);
	OLED_Refresh_Gram();
	
	while(1)
	{
		LifeGame();		

	}
}
