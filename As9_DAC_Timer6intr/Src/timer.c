/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Sep 30, 2024
*/


#include "timer.h"


void Timer_Init(uint32_t ms) {
	//* Enable Timer APB clock
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	//* Set Timer clock -- PCLK = TCLK = 16 MHz : * Set PR = 16000
	TIM6->PSC = (PR-1);
	//* Calculate number of clocks to count (CNT).
	uint32_t cnt = (TCLK / 1000) * ms / PR;
	//* Set CNT in ARR.
	TIM6->ARR = (cnt-1);
	//* Reset Timer Counter to 0.
	TIM6->CNT = 0;
	//* Enable Timer Interrupt in DIER.
	TIM6->DIER |= TIM_DIER_UIE;
	//* Enable Timer Interrupt in NVIC.
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
	//Update event to Trigger (CR2 = 0b010).
	TIM6->CR2 &= ~(TIM_CR2_MMS_0 | TIM_CR2_MMS_2);
	TIM6->CR2 |= TIM_CR2_MMS_1;
	//* Start Timer in CR1.
	TIM6->CR1 |= TIM_CR1_CEN;
}

volatile int timer_intr_flag = 0;

void TIM6_DAC_IRQHandler(void) {
	//* Check if UIF flag is set (in SR).
	if(TIM6->SR & TIM_SR_UIF) {
		//* Clear UIF in SR (Ack)
		TIM6->SR &= ~TIM_SR_UIF;
		//* Perform interrupt handling --
		timer_intr_flag = 1;
	}
}
