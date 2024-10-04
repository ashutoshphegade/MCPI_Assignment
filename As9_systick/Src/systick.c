/*
 * systick.c
 *
 *  Created on: Oct 2, 2024
 *      Author: sunbeam
 */

#include "systick.h"

volatile uint32_t jiffies = 0;

void SysTick_Handler(void) {
	jiffies++;
	//GPIOD->ODR ^= BV(LED_RED_PIN); // ---> Oscilloscope/Analyzer
}


void SysTick_Delay(uint32_t ms) {
	uint32_t until = jiffies + ms;
	while(jiffies < until)
		;
}
