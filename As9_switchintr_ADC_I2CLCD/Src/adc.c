/*
Author: Nilesh Ghule <nilesh@sunbeaminfo.com>
Course: PG-DESD @ Sunbeam Infotech
Date: Oct 2, 2024
*/

#include "adc.h"

// Sensor --> Channel 0 i.e. PA.1

void ADC_Init(void) {
	//1. Enable GPIO peripheral clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//2. Configure GPIO pin as analog mode (MODER = 0b11).
	GPIOA->MODER |= BV(1*2) | BV(1*2+1);
	//3. Enable ADC peripheral clock
	RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	//4. Set ADC resolution as 12-bits (CR1 RES = 0b00).
	ADC2->CR1 &= ~(ADC_CR1_RES_0 | ADC_CR1_RES_1);
	//5. Enable single conversion (CR2 CONT = 0b0)
	ADC2->CR2 &= ~ADC_CR2_CONT;
	//6. Set number of conversions in a sequence (SQR1 L(3:0) = 0b0000 for 1 conversion)
	ADC2->SQR1 |= (0 << ADC_SQR1_L_Pos);
	//7. Set channel number for conversions in sequence (e.g. SQR3 (4:0) = 0b00000 for channel 0).
	ADC2->SQR3 |= (0 << ADC_SQR3_SQ1_Pos);
	//8. Enable ADC (CR2 ADON=0b1)
	ADC2->CR2 |= ADC_CR2_ADON;
}

uint16_t ADC_GetValue(void) {
	//1. Start the conversion (CR2 SWSTART)
	ADC2->CR2 |= ADC_CR2_SWSTART;
	//2. Wait for end of conversion (SR EOC bit)
	while(!(ADC2->SR & ADC_SR_EOC));
	//3. Read ADC data register (DR)
	uint16_t val = ADC2->DR;
	return val;
}

