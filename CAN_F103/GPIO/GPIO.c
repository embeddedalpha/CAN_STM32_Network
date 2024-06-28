
/**
 ************************************************************************************************
 * @file           : GPIO.c
 * @author         : Kunal Salvi
 * @brief          : Source File for GPIO Driver
 ***********************************************************************************************
 * This is the source file for the GPIO driver and contains all the functions that the user can
 * use to configure the physical pins of the MCU.
 ************************************************************************************************
 */


#include "GPIO.h"



void GPIO_Pin_Setup(GPIO_TypeDef *Port, uint8_t pin, uint8_t function)
{
	if(Port == GPIOA)
	{
		if((function == GPIO_Config.ALT_OPEN_DRAIN_OUTPUT) || (function == GPIO_Config.ALT_PUSH_PULL_OUTPUT))
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
		}
		else
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
		}

		if(pin < 8)
		{
			Port -> CRL |= function << (4*pin);
		}
		else
		{
			Port -> CRH |= function << (4*(pin - 8));
		}
	}


	if(Port == GPIOB)
	{
		if((function == GPIO_Config.ALT_OPEN_DRAIN_OUTPUT) || (function == GPIO_Config.ALT_PUSH_PULL_OUTPUT))
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
		}
		else
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
		}

		if(pin < 8)
		{
			Port -> CRL |= function << (4*pin);
		}
		else
		{
			Port -> CRH |= function << (4*(pin - 8));
		}
	}

	if(Port == GPIOC)
	{
		if((function == GPIO_Config.ALT_OPEN_DRAIN_OUTPUT) || (function == GPIO_Config.ALT_PUSH_PULL_OUTPUT))
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
		}
		else
		{
			RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
		}

		if(pin < 8)
		{
			Port -> CRL |= function << (4*pin);
		}
		else
		{
			Port -> CRH |= function << (4*(pin - 8));
		}
	}
}

void GPIO_Interrupt_Setup(int pin, int edge_select)
{
	EXTI ->IMR |= 1 << pin;
	switch (edge_select) {
		case 0:
			EXTI ->RTSR |= 1 << pin;
			break;
		case 1:
			EXTI ->FTSR |= 1 << pin;
			break;
		case 2:
			EXTI ->RTSR |= 1 << pin;
			EXTI ->FTSR |= 1 << pin;
			break;
	}

	if(pin == 0)
	{
		NVIC_SetPriority(EXTI0_IRQn,0);
		NVIC_EnableIRQ(EXTI0_IRQn);
	}
	else if(pin == 1)
	{
		NVIC_SetPriority(EXTI1_IRQn,0);
		NVIC_EnableIRQ(EXTI1_IRQn);
	}
	else if(pin == 2)
	{
		NVIC_SetPriority(EXTI2_IRQn,0);
		NVIC_EnableIRQ(EXTI2_IRQn);
	}
	else if(pin == 3)
	{
		NVIC_SetPriority(EXTI3_IRQn,0);
		NVIC_EnableIRQ(EXTI3_IRQn);
	}
	else if(pin == 4)
	{
		NVIC_SetPriority(EXTI4_IRQn,0);
		NVIC_EnableIRQ(EXTI4_IRQn);
	}
	else if(pin >= 5 && pin <= 9)
	{
		NVIC_SetPriority(EXTI9_5_IRQn,0);
		NVIC_EnableIRQ(EXTI9_5_IRQn);
	}
	else if(pin >= 10 && pin <= 15)
	{
		NVIC_SetPriority(EXTI15_10_IRQn,0);
		NVIC_EnableIRQ(EXTI15_10_IRQn);
	}



}
