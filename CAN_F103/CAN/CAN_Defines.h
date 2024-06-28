/*
 * CAN_Defines.h
 *
 *  Created on: 18-May-2022
 *      Author: Kunal
 */

#ifndef CAN_DEFINES_H_
#define CAN_DEFINES_H_

#include "main_F103.h"


static const struct CAN_Pin{

	struct RX
	{
		uint8_t PA11;
		uint8_t PB8;
	}RX;

	struct TX
	{
		uint8_t PA12;
		uint8_t PB9;
	}TX;

}CAN_Pin =
		{
			.RX = {
					.PA11 = 0x01,
					.PB8 = 0x02,
			},

			.TX = {
					.PA12 = 0x03,
					.PB9 = 0x04,
			},
		};


static const struct CAN_Baudrate{

uint32_t  CAN_BAUDRATE_1000_KBPS ;
uint32_t  CAN_BAUDRATE_750_KBPS;
uint32_t  CAN_BAUDRATE_500_KBPS;
uint32_t  CAN_BAUDRATE_250_KBPS;
uint32_t  CAN_BAUDRATE_200_KBPS;
uint32_t  CAN_BAUDRATE_150_KBPS;
uint32_t  CAN_BAUDRATE_125_KBPS;
uint32_t  CAN_BAUDRATE_100_KBPS;
uint32_t  CAN_BAUDRATE_75_KBPS;
uint32_t  CAN_BAUDRATE_50_KBPS;
uint32_t  CAN_BAUDRATE_25_KBPS;
uint32_t  CAN_BAUDRATE_10_KBPS;
uint32_t  CAN_BAUDRATE_5_KBPS;

}CAN_Baudrate = {

.CAN_BAUDRATE_1000_KBPS = 	0x001e0001,
.CAN_BAUDRATE_750_KBPS =    0x001c0002,
.CAN_BAUDRATE_500_KBPS =    0x001e0003,
.CAN_BAUDRATE_250_KBPS =    0x001e0007,
.CAN_BAUDRATE_200_KBPS =    0x001e0009,
.CAN_BAUDRATE_150_KBPS =    0x001c000e,
.CAN_BAUDRATE_125_KBPS =    0x001e000f,
.CAN_BAUDRATE_100_KBPS =    0x001e0013,
.CAN_BAUDRATE_75_KBPS =     0x001c001d,
.CAN_BAUDRATE_50_KBPS =     0x001e0027,
.CAN_BAUDRATE_25_KBPS =     0x001e004f,
.CAN_BAUDRATE_10_KBPS =     0x001e00c7,
.CAN_BAUDRATE_5_KBPS =      0x001e018f,

};

static const struct CAN_Frame{

	uint8_t Data_Frame;
	uint8_t Remote_Frame;

}CAN_Frame = {
		.Data_Frame = 0,
		.Remote_Frame = 10,
};

static const struct CAN_ID{
	uint8_t Standard;
	uint8_t Extended;
}CAN_ID = {
		.Standard = 1,
		.Extended = 2,
};


//#define CAN_ID_Standard 0
//#define CAN_ID_Extended 10

#define CAN_FILTER_MASK_MODE 0
#define CAN_FILTER_LIST_MODE 10

#define CAN_Timestamp_Enable 1
#define CAN_Timestamp_Disable 0


#define CAN_Initialization_Mode	    0x10
#define CAN_Sleep_Mode			    0xEF
#define CAN_Normal_Mode			    0x45

#define CAN_TX_Mailbox_0 0x00
#define CAN_TX_Mailbox_1 0xAA
#define CAN_TX_Mailbox_2 0xFF

#define CAN_Timestamp_Enable 1
#define CAN_Timestamp_Disable 0

#define CAN_Filter_Scale_16bit 0
#define CAN_Filter_Scale_32bit 1

#define CAN_Filter_Bank_FIFO0	0
#define CAN_Filter_Bank_FIFO1	1

#define CAN_TX_Buffer_0 1
#define CAN_TX_Buffer_1 2
#define CAN_TX_Buffer_2 3

#define CAN_RX_Buffer_1 4
#define CAN_RX_Buffer_2 5


#define CAN_TX_All_Buffers 10
#define CAN_RX_ALL_Buffers 20

static const struct CAN_Interrupt
{

	uint16_t Transmit_Mailbox_Empty	;
	uint16_t Fifo0_Message_Pending	;
	uint16_t Fifo1_Message_Pending	;
	uint16_t Fifo0_Full				;
	uint16_t Fifo1_Full				;
	uint16_t Fifo0_Overflow			;
	uint16_t Fifo1_Overflow			;

}CAN_Interrupt = {

		.Transmit_Mailbox_Empty	 = (0x01 << 0), //(0x01 << 0)
		.Fifo0_Message_Pending	= (0x01 << 1), //(0x01 << 1)
		.Fifo1_Message_Pending	= (0x01 << 4), //(0x01 << 4)
		.Fifo0_Full				= (0x01 << 2),  //(0x01 << 2)
		.Fifo1_Full				= (0x01 << 5),  //(0x01 << 5)
		.Fifo0_Overflow			= (0x01 << 3), //(0x01 << 3)
		.Fifo1_Overflow			= (0x01 << 6), //(0x01 << 6)
};



#endif /* CAN_DEFINES_H_ */
