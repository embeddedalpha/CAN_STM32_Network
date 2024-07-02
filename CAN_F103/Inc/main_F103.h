/*
 * main.h
 *
 *  Created on: Jun 26, 2024
 *      Author: kunal
 */

#ifndef MAIN_F103_H_
#define MAIN_F103_H_

#include "stm32f103x6.h"
#include "stm32f1xx.h"
#include <stdio.h>
#include "math.h"
#include "inttypes.h"
#include "string.h"
#include "stdlib.h"
#include "stdarg.h"
#include "stdbool.h"
#include "stdint.h"
#include "system_stm32f1xx.h"


extern uint32_t APB1CLK_SPEED;
extern uint32_t APB2CLK_SPEED;

__STATIC_INLINE int32_t SystemAPB1_Clock_Speed(void)
{
	return (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1)>> RCC_CFGR_PPRE1_Pos]);
}

__STATIC_INLINE int32_t SystemAPB2_Clock_Speed(void)
{
	return (SystemCoreClock >> APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2)>> RCC_CFGR_PPRE2_Pos]);
}


__STATIC_INLINE void MCU_Clock_Setup()
{
	RCC->CR |= RCC_CR_HSEON ;
	while(!(RCC->CR & RCC_CR_HSERDY));
	FLASH->ACR |= FLASH_ACR_PRFTBE|FLASH_ACR_LATENCY_1;
	RCC->CFGR |= (RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE_HSE | RCC_CFGR_PLLMULL9 | RCC_CFGR_PPRE1_DIV2);
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while(!(RCC->CFGR & RCC_CFGR_SWS_PLL));
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/72);
}


__STATIC_INLINE void separateFractionAndIntegral(double number, double *fractionalPart, double *integralPart) {
    *integralPart = (double)((int64_t)number);
    *fractionalPart = number - *integralPart;
}

__STATIC_INLINE uint32_t Delay_Config(void)
{

	SysTick->CTRL = 0;
	SysTick->LOAD = 0x00FFFFFF;
	SysTick->VAL = 0;
	SysTick->CTRL |= 5;
	return (0UL);                                                     /* Function successful */
}

__STATIC_INLINE uint32_t Delay_ns500(void)
{

	SysTick->LOAD = 192;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
	return (0UL);                                                     /* Function successful */
}


__STATIC_INLINE uint32_t Delay_us(float us)
{

	SysTick->LOAD = (SystemCoreClock / 1000000) * us;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
	return (0UL);                                                     /* Function successful */
}

__STATIC_INLINE uint32_t Delay_ms(unsigned long ms)
{
	unsigned long x = (SystemCoreClock / 1000) * (ms);
	SysTick->LOAD = x ;
	SysTick->VAL = 0;
	while((SysTick->CTRL & 0x00010000) == 0);
	return (0UL);                                                     /* Function successful */
}


__STATIC_INLINE uint32_t Delay_s(unsigned long s)
{
	s = s * 1000;
	for (; s>0; s--)
	{
		Delay_ms(1);
	}
	return (0UL);
}

#endif /* MAIN_F103_H_ */
