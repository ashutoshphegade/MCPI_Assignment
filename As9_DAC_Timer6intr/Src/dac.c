/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Oct 2, 2024
*/

#include "dac.h"
#include "timer.h"

void DAC_Init(void) {
	//1. Enable GPIOA peripheral. (DAC1_OUT=PA4)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//2. Set GPIO mode to Analog. (MODER = 0b11).
	GPIOA->MODER |= BV(4*2) | BV(4*2+1);
	//3. Enable DAC peripheral (APB1).
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;
	//4. Enable DAC channel, Output buffer, Enable trigger, and select TIM6 Trigger (Software=0b000) (CR).
	DAC1->CR = DAC_CR_EN1 | DAC_CR_TEN1;
	DAC1->CR &= ~(DAC_CR_TSEL1_0 | DAC_CR_TSEL1_1 | DAC_CR_TSEL1_2);
}

void DAC_SetValue(uint16_t val) {
	//1. Set value in DAC register. (DHRxR)
	DAC1->DHR12R1 = val;

}

