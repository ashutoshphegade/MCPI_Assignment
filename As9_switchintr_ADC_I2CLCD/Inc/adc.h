/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Oct 2, 2024
*/

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx.h"

void ADC_Init(void);
uint16_t ADC_GetValue(void);

#endif /* ADC_H_ */
