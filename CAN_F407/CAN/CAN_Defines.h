/*
 * CAN_Defines.h
 *
 *  Created on: 18-May-2022
 *      Author: Kunal
 */

#ifndef CAN_DEFINES_H_
#define CAN_DEFINES_H_

#include "main.h"


static const struct CAN_Configuration
{
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  Instance{
		CAN_TypeDef *_CAN1;
		CAN_TypeDef *_CAN2;
	} Instance;
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  Pin{
		struct _CAN1{
			struct RX{
				uint8_t PA11;
				uint8_t PD0;
				uint8_t PB8;
			}RX;
			struct TX{
				uint8_t PA12;
				uint8_t PD1;
				uint8_t PB9;
			}TX;
		}_CAN1;
		struct _CAN2{
			 struct{
				uint8_t PB12;
				uint8_t PB5;
			}RX;
			struct{
				uint8_t PB13;
				uint8_t PB6;
			}TX;
		}_CAN2;
	} Pin;
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  Baudrate{
	uint32_t  _1000_KBPS ;
	uint32_t   _750_KBPS;
	uint32_t   _500_KBPS;
	uint32_t   _250_KBPS;
	uint32_t   _200_KBPS;
	uint32_t   _150_KBPS;
	uint32_t   _125_KBPS;
	uint32_t   _100_KBPS;
	uint32_t   _75_KBPS;
	uint32_t   _50_KBPS;
	uint32_t   _25_KBPS;
	uint32_t   _10_KBPS;
	uint32_t   _5_KBPS;
	}Baudrate;
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  Frame{
		uint8_t Data_Frame;
		uint8_t Remote_Frame;
	} Frame;
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  ID{
		uint8_t Standard;
		uint8_t Extended;
	} ID;
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	struct  Interrupt
	{
		uint16_t Transmit_Mailbox_Empty	;
		uint16_t Fifo0_Message_Pending	;
		uint16_t Fifo1_Message_Pending	;
		uint16_t Fifo0_Full				;
		uint16_t Fifo1_Full				;
		uint16_t Fifo0_Overflow			;
		uint16_t Fifo1_Overflow			;
	} Interrupt;

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/


}CAN_Configuration = {
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		. Instance = {
				._CAN1 = CAN1,
				._CAN2 = CAN2,
		},
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		. Pin ={
				._CAN1 = {
						.RX = {
								.PA11 = 11,
								.PD0  = 4,
								.PB8 = 9,
							  },

						.TX = {
								.PA12 = 12,
								.PD1  = 5,
								.PB9 = 10,
						      },
					     },
				._CAN2 = {
						.RX = {
								.PB12 = 13,
								.PB5  = 6,
						      },

						.TX = {
								.PB13 = 16,
								.PB6  = 7,
						      },
				        },
		           },
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
	   . Baudrate = {
			   . _1000_KBPS = 	0x001a0002,
			   . _750_KBPS =    0x001a0003,
			   . _500_KBPS =    0x001a0005,
			   . _250_KBPS =    0x001a000b,
			   . _200_KBPS =    0x001b000d,
			   . _150_KBPS =    0x001a0013,
			   . _125_KBPS =    0x001c0014,
			   . _100_KBPS =    0x001b001b,
			   . _75_KBPS =     0x001c0022,
			   . _50_KBPS =     0x001b0037,
			   . _25_KBPS =     0x001c0068,
			   . _10_KBPS =     0x001b0117,
			   . _5_KBPS =      0x001c020c,
					},
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		. Frame = {
				.Data_Frame = 0,
				.Remote_Frame = 10,
		},
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		. ID = {
				.Standard = 1,
				.Extended = 2,
		},
/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
		. Interrupt = {

				.Transmit_Mailbox_Empty	 = (0x01 << 0), //(0x01 << 0)
				.Fifo0_Message_Pending	= (0x01 << 1), //(0x01 << 1)
				.Fifo1_Message_Pending	= (0x01 << 4), //(0x01 << 4)
				.Fifo0_Full				= (0x01 << 2),  //(0x01 << 2)
				.Fifo1_Full				= (0x01 << 5),  //(0x01 << 5)
				.Fifo0_Overflow			= (0x01 << 3), //(0x01 << 3)
				.Fifo1_Overflow			= (0x01 << 6), //(0x01 << 6)
		},
};







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

//static const struct CAN_Interrupt
//{
//
//	uint16_t Transmit_Mailbox_Empty	;
//	uint16_t Fifo0_Message_Pending	;
//	uint16_t Fifo1_Message_Pending	;
//	uint16_t Fifo0_Full				;
//	uint16_t Fifo1_Full				;
//	uint16_t Fifo0_Overflow			;
//	uint16_t Fifo1_Overflow			;
//
//}CAN_Interrupt = {
//
//		.Transmit_Mailbox_Empty	 = (0x01 << 0), //(0x01 << 0)
//		.Fifo0_Message_Pending	= (0x01 << 1), //(0x01 << 1)
//		.Fifo1_Message_Pending	= (0x01 << 4), //(0x01 << 4)
//		.Fifo0_Full				= (0x01 << 2),  //(0x01 << 2)
//		.Fifo1_Full				= (0x01 << 5),  //(0x01 << 5)
//		.Fifo0_Overflow			= (0x01 << 3), //(0x01 << 3)
//		.Fifo1_Overflow			= (0x01 << 6), //(0x01 << 6)
//};



#endif /* CAN_DEFINES_H_ */
