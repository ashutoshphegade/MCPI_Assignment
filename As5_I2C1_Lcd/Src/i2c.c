/*
 * i2c.c
 *
 *  Created on: Sep 25, 2024
 *      Author: sunbeam
 */


#include "i2c.h"

void I2C_Init(void)
{
	//PB6, PB7 GPIO Initialization------MODER, AFRL, PUPDR, CLKEN
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	GPIOB->MODER |= (BV(SDA_PIN*2+1) | BV(SCL_PIN*2+1));
	GPIOB->MODER &= ~(BV(SDA_PIN*2) | BV(SCL_PIN*2));
	GPIOB->PUPDR &= ~(BV(SDA_PIN*2) | BV(SCL_PIN*2));
	GPIOB->PUPDR &= ~(BV(SDA_PIN*2+1) | BV(SCL_PIN*2+1));
	GPIOB->AFR[0] |= (BV(26) | BV(30));
	GPIOB->AFR[0] &= ~(BV(24) | BV(25) | BV(27) | BV(28) | BV(29) | BV(31));

	//I2C1 Initialisation
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	//Enable I2C at last otherwise we will not be able to set I2C by enabling CCR
	//reset and clear register
	I2C1->CR1 = I2C_CR1_SWRST;
	I2C1->CR1 = 0;
	//set pclk in CR2
	I2C1->CR2 |= 16;
	//set i2c bitrate to 100KHZ
	I2C1->CCR &= ~I2C_CCR_FS;
	I2C1->CCR |= 80;
	//standard mode max time reise = 1000ns
	//set Trise = max_Trise/Tpclk = 1000/62.5 = 17
	I2C1->TRISE |= 17;
	//enable acknowledment
	I2C1->CR1 |= I2C_CR1_ACK;
	//enable I2C
	I2C1->CR1 |= I2C_CR1_PE;
}

void I2C_Start(void)
{
	//CR1 ----- send start bit
	I2C1->CR1 |= I2C_CR1_START;
	//SR1 ----- poll(wait) for SB (Start Bit sent)
	while(!(I2C1->SR1 & I2C_SR1_SB));

}
void I2C_RepeatStart(void)
{
	I2C_Start();
}

void I2C_Stop(void)
{
	// send stop bit
	I2C1->CR1 |= I2C_CR1_STOP;
	// SR2 ----- poll (wait) for bus to be released
	while(!(I2C1->SR2 & I2C_SR2_BUSY));

}

void I2C_SendSlaveAddress(uint8_t SlaveAddr)
{
	//DR----write slave address in data register
	I2C1->DR = SlaveAddr;
	//SR1 ----- poll(wait) for address is transferred
	while(!(I2C1->SR1 & I2C_SR1_ADDR));

	//dummy read to clear flgs
	(void)I2C1->SR1;
	(void)I2C1->SR2;
}

void I2C_SendData(uint8_t data)
{
	//SR1 ---- wait while previous data is not transferred
	while(!(I2C1->SR1 & I2C_SR1_TXE));

	//DR ----- write data into data register
	I2C1->DR = data;
	//SR1 ---- poll(wait) for BTF is transferred
	while(!(I2C1->SR1 & I2C_SR1_BTF));

}
uint16_t I2C_RecvData(void)
{
	I2C1->CR1 |= I2C_CR1_ACK | I2C_CR1_POS;
	//wait until receive buffer is not empty
	while(!(I2C1->SR1 & I2C_SR1_RXNE));

	//read content and clear flags
	uint16_t val = I2C1->DR;
	return val;
}
uint16_t I2C_RecvDataNAck(void)
{
	I2C1->CR1 &= ~(I2C_CR1_ACK | I2C_CR1_POS);
	//wait until receive buffer is not empty
	while(!(I2C1->SR1 & I2C_SR1_RXNE));

	//read content and clear flags
	uint16_t val = I2C1->DR;
	return val;

}
int I2C_IsDeviceReady(uint8_t SlaveAddr)
{
	//DR----write slave address in data register
	I2C1->DR = SlaveAddr;
	//SR1 ----- poll(wait) for address is transferred
	while(!(I2C1->SR1 & I2C_SR1_ADDR));

	//dummy read to clear flags
	(void)I2C1->SR1;
	(void)I2C1->SR2;
	return 1;

}
