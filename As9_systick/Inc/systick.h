/*
 * systick.h
 *
 *  Created on: Oct 2, 2024
 *      Author: sunbeam
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "stm32f407xx.h"

extern volatile uint32_t jiffies;

void SysTick_Handler(void);
void SysTick_Delay(uint32_t ms);


#endif /* SYSTICK_H_ */
