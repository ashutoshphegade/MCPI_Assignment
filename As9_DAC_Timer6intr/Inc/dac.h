/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Oct 2, 2024
*/

#ifndef DAC_H_
#define DAC_H_

#include "stm32f4xx.h"

void DAC_Init(void);
void DAC_SetValue(uint16_t val);

#endif /* DAC_H_ */
