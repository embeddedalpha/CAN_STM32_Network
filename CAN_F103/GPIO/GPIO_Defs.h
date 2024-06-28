/*
 * GPIO_Defs.h
 *
 *  Created on: Jun 27, 2024
 *      Author: kunal
 */

#ifndef GPIO_DEFS_H_
#define GPIO_DEFS_H_

static const struct GPIO_Config
{

uint8_t  GEN_PUSH_PULL_OUTPUT; //   0b0011
uint8_t  GEN_OPEN_DRAIN_OUTPUT; //  0b0111
uint8_t  ALT_PUSH_PULL_OUTPUT; //   0b1011
uint8_t  ALT_OPEN_DRAIN_OUTPUT; //  0b1111
uint8_t  ANALOG_INPUT; //           0b0000
uint8_t  FLOATING_INPUT; //         0b0100
uint8_t  PULL_DOWN_INPUT; //        0b1000
uint8_t  PULL_UP_INPUT; //          0b1000
uint8_t  INPUT_MODE;//             0b0100

}GPIO_Config = {
		.GEN_PUSH_PULL_OUTPUT = 0b0011,
		.GEN_OPEN_DRAIN_OUTPUT = 0b0111,
		.ALT_PUSH_PULL_OUTPUT = 0b1011,
		.ALT_OPEN_DRAIN_OUTPUT = 0b1111,
		.ANALOG_INPUT = 0b0000,
		.FLOATING_INPUT = 0b0100,
		.PULL_DOWN_INPUT = 0b1000,
		.INPUT_MODE = 0b0100,
};


#endif /* GPIO_DEFS_H_ */
