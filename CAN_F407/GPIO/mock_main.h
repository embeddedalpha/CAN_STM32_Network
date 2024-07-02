#ifndef MOCK_MAIN_H
#define MOCK_MAIN_H

#include <stdint.h>

// Mock definitions for GPIO_TypeDef
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_TypeDef;

// Mock definitions for RCC_TypeDef
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    volatile uint32_t AHB2RSTR;
    volatile uint32_t AHB3RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t AHB1ENR;
    volatile uint32_t AHB2ENR;
    volatile uint32_t AHB3ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t AHB3LPENR;
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
} RCC_TypeDef;

// Mock definitions for EXTI_TypeDef
typedef struct {
    volatile uint32_t IMR;
    volatile uint32_t EMR;
    volatile uint32_t RTSR;
    volatile uint32_t FTSR;
    volatile uint32_t SWIER;
    volatile uint32_t PR;
} EXTI_TypeDef;

// Mock definitions for NVIC_TypeDef
typedef struct {
    volatile uint32_t ISER[8];
    volatile uint32_t ICER[8];
    volatile uint32_t ISPR[8];
    volatile uint32_t ICPR[8];
    volatile uint32_t IABR[8];
    volatile uint8_t  IP[240];
    volatile uint32_t STIR;
} NVIC_TypeDef;

// Mocked register and function declarations
extern GPIO_TypeDef GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOH;
extern RCC_TypeDef RCC;
extern EXTI_TypeDef EXTI;
extern NVIC_TypeDef NVIC;

void GPIO_Clock_Enable(GPIO_TypeDef *PORT);
void GPIO_Clock_Disable(GPIO_TypeDef *PORT);
void NVIC_SetPriority(int IRQn, uint32_t priority);
void NVIC_EnableIRQ(int IRQn);

#endif // MOCK_MAIN_H
