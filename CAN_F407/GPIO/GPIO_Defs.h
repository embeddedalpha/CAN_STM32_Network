/*
 * GPIO_Defs.h
 *
 *  Created on: Oct 13, 2023
 *      Author: Kunal
 */

#ifndef GPIO_DEFS_H_
#define GPIO_DEFS_H_

#include "main.h"

static const struct MODE
{
	uint8_t Input;
	uint8_t General_Purpose_Output;
	uint8_t Alternate_Function;
	uint8_t Analog;
}MODE = {0,1,2,3};

static const struct Output_Type
{
	uint8_t Push_Pull;
	uint8_t Open_Drain;
}Output_Type = {0,1};

static const struct Speed
{
	uint8_t Low_Speed;
	uint8_t Medium_Speed;
	uint8_t High_Speed;
	uint8_t Very_High_Speed;
}Speed = {0,1,2,3};

static const struct Pull
{
	uint8_t No_Pull_Up_Down;
	uint8_t Pull_Up;
	uint8_t Pull_Down;
}Pull = {0,1,2};

//static const struct Alternate_Functions
//{
//	uint8_t None;
//	uint8_t Analog;
//	uint8_t SYS;
//	uint8_t MCO1;
//	uint8_t MCO2;
//	uint8_t RTC_REFIN;
//	uint8_t TIM_1;
//	uint8_t TIM_2;
//	uint8_t TIM_3;
//	uint8_t TIM_4;
//	uint8_t TIM_5;
//	uint8_t TIM_8;
//	uint8_t TIM_9;
//	uint8_t TIM_10;
//	uint8_t TIM_11;
//	uint8_t I2C_1;
//	uint8_t I2C_2;
//	uint8_t I2C_3;
//	uint8_t SPI_1;
//	uint8_t SPI_2;
//	uint8_t I2S_2;
//	uint8_t I2S_2EXT;
//	uint8_t SPI_3;
//	uint8_t I2S_EXT;
//	uint8_t I2S_3;
//	uint8_t USART_1;
//	uint8_t USART_2;
//	uint8_t USART_3;
//	uint8_t I2S_3EXT;
//	uint8_t USART_4;
//	uint8_t UART_5;
//	uint8_t USART_6;
//	uint8_t CAN_1;
//	uint8_t CAN_2;
//	uint8_t TIM_12;
//	uint8_t TIM_13;
//	uint8_t TIM_14;
//	uint8_t OTG_FS_1;
//	uint8_t OYG_HS_1;
//	uint8_t ETH_1;
//	uint8_t FSMC_1;
//	uint8_t SDIO_1;
//	uint8_t OTG_FS_2;
//	uint8_t DCMI_1;
//	uint8_t EVENTOUT;
//}Alternate_Functions = {0,0,0,0,0,
//		               1,1,
//					   2,2,2,
//					   3,3,3,3,
//					   4,4,4,
//					   5,5,5,5,
//					   6,6,6,
//					   7,7,7,7,
//					   8,8,8,
//					   9,9,9,9,9,
//					   10,10,
//					   11,
//					   12,12,12,
//					   13,
//					   15};

static const struct Alternate_Functions
{
    uint8_t None;
    uint8_t Analog;
    uint8_t SYS;
    uint8_t MCO1;
    uint8_t MCO2;
    uint8_t RTC_REFIN;
    uint8_t TIM_1;
    uint8_t TIM_2;
    uint8_t TIM_3;
    uint8_t TIM_4;
    uint8_t TIM_5;
    uint8_t TIM_8;
    uint8_t TIM_9;
    uint8_t TIM_10;
    uint8_t TIM_11;
    uint8_t I2C_1;
    uint8_t I2C_2;
    uint8_t I2C_3;
    uint8_t SPI_1;
    uint8_t SPI_2;
    uint8_t I2S_2;
    uint8_t I2S_2EXT;
    uint8_t SPI_3;
    uint8_t I2S_EXT;
    uint8_t I2S_3;
    uint8_t USART_1;
    uint8_t USART_2;
    uint8_t USART_3;
    uint8_t I2S_3EXT;
    uint8_t USART_4;
    uint8_t UART_5;
    uint8_t USART_6;
    uint8_t CAN_1;
    uint8_t CAN_2;
    uint8_t TIM_12;
    uint8_t TIM_13;
    uint8_t TIM_14;
    uint8_t OTG_FS_1;
    uint8_t OYG_HS_1;
    uint8_t ETH_1;
    uint8_t FSMC_1;
    uint8_t SDIO_1;
    uint8_t OTG_FS_2;
    uint8_t DCMI_1;
    uint8_t EVENTOUT;
} Alternate_Functions = {
    .None = 0,
    .Analog = 0,
    .SYS = 0,
    .MCO1 = 0,
    .MCO2 = 0,
    .RTC_REFIN = 1,
    .TIM_1 = 1,
    .TIM_2 = 2,
    .TIM_3 = 2,
    .TIM_4 = 2,
    .TIM_5 = 2,
    .TIM_8 = 3,
    .TIM_9 = 3,
    .TIM_10 = 3,
    .TIM_11 = 3,
    .I2C_1 = 4,
    .I2C_2 = 4,
    .I2C_3 = 4,
    .SPI_1 = 5,
    .SPI_2 = 5,
    .I2S_2 = 5,
    .I2S_2EXT = 5,
    .SPI_3 = 6,
    .I2S_EXT = 6,
    .I2S_3 = 6,
    .USART_1 = 7,
    .USART_2 = 7,
    .USART_3 = 7,
    .I2S_3EXT = 7,
    .USART_4 = 8,
    .UART_5 = 8,
    .USART_6 = 8,
    .CAN_1 = 9,
    .CAN_2 = 9,
    .TIM_12 = 9,
    .TIM_13 = 9,
    .TIM_14 = 9,
    .OTG_FS_1 = 10,
    .OYG_HS_1 = 10,
    .ETH_1 = 11,
    .FSMC_1 = 12,
    .SDIO_1 = 12,
    .OTG_FS_2 = 12,
    .DCMI_1 = 13,
    .EVENTOUT = 15
};


static const struct Interrupt_Edge
{
	uint8_t RISING_EDGE;
	uint8_t FALLING_EDGE;
	uint8_t RISING_FALLING_EDGE;
}Interrupt_Edge = {0,1,2};


#endif /* GPIO_DEFS_H_ */
