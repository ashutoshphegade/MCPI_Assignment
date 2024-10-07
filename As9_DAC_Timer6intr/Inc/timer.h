/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Sep 30, 2024
*/

#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"

#define TCLK	16000000UL
#define PR		32000

void Timer_Init(uint32_t ms);
void TIM6_DAC_IRQHandler(void);

extern volatile int timer_intr_flag;


#endif /* TIMER_H_ */
