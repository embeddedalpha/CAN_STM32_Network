/**
 ************************************************************************************************
 * @file           : GPIO.h
 * @author         : Kunal Salvi
 * @brief          : Header File for GPIO Driver
 ***********************************************************************************************
 * This is the header file for the GPIO driver and is to be called when a physical pin of the MCU
 * is to be configured.
 ************************************************************************************************
 */



#ifndef _GPIO_H_
#define _GPIO_H_

#include "main_F103.h"
#include "GPIO_Defs.h"



#define Rising_Edge     1
#define Falling_Ege     2
#define Rise_n_Fall_Edge 3


void GPIO_Pin_Setup(GPIO_TypeDef *Port, uint8_t pin, uint8_t function);

void GPIO_Interrupt_Setup(int pin, int edge_select);

#endif
