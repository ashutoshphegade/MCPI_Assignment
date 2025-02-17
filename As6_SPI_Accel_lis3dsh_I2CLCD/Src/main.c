/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "accel.h"
#include "i2c.h"
#include "i2c_lcd.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void) {
	char str1[32];
	char str2[32];
	int ret;
	LIS_Data val;
	SystemInit();
	ret = Lcd_Init();
	LIS_Init(); //initialize accel
	if (ret)
	{
		if(LIS_IsDataAvail()) // check if new data avail
		{
			val = LIS_GetData(); // get the new data
			// print value
			sprintf(str1, "X=%d, Y=%d\r\n", val.x, val.y);
			sprintf(str2, "Z=%d\r\n", val.z);
			Lcd_Puts(LCD_LINE1, str1);
			Lcd_Puts(LCD_LINE2, str2);
		}
		DelayMs(1000);

	}
	return 0;
}
