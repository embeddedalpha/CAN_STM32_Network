/*
 * CAN.h
 *
 *  Created on: 15-Jun-2022
 *      Author: Kunal
 */

#ifndef CAN_H_
#define CAN_H_

#include "main.h"
#include "GPIO.h"
#include "CAN_defines.h"

//#define Transmit_Mailbox_Empty	CAN_IER_TMEIE
//#define Fifo0_Message_Pending	CAN_IER_FMPIE0
//#define Fifo1_Message_Pending	CAN_IER_FMPIE1
//#define Fifo0_Full				CAN_IER_FFIE0
//#define Fifo1_Full				CAN_IER_FFIE1
//#define Fifo0_Overflow			CAN_IER_FOVIE0
//#define Fifo1_Overflow			CAN_IER_FOVIE1

typedef struct CAN_RX_Typedef
{
	int message_timestamp;
	int data_length;
	int data[8];
	int filter_index;
	int frame_type;
	int id_type;
	int32_t ID;
}CAN_RX_Typedef;

typedef struct CAN_Filter_TypeDef{
	int filter_id;
	int enable;
	int id_type;
	int frame_type;


	int type;
	int scale;
	int bank_id;
	uint32_t ID;
}CAN_Filter_TypeDef;

typedef struct CAN_TX_Typedef{
	int frame_type;
	int send_timestamp;
	int32_t ID;
	int data_length;
	int data[8];
}CAN_TX_Typedef;

typedef struct CAN_Config
{
	CAN_TypeDef *CAN_INSTANCE;
	uint8_t RX_Pin;
	uint8_t TX_Pin;
	uint32_t Baudrate;
	int timestamp_enable;
	int interrupt;
}CAN_Config;




int CAN_Init(CAN_Config *config);

int CAN_Set_Filter_Mask(CAN_Config *config, uint32_t id, uint32_t mask, uint8_t filterBank, uint8_t fifoAssignment);
int CAN_Set_Filter_List(CAN_Config *config,uint32_t id1, uint32_t id2, uint8_t filterBank, uint8_t fifoAssignment);

void CAN_Start(CAN_Config *config);
int CAN_Activate_Callback(CAN_Config *config, uint32_t CAN_Interrupt_ID);

uint8_t CAN_Send_Packet(CAN_Config *config, CAN_TX_Typedef *tx);

void CAN_Get_Packet(CAN_Config *config, CAN_RX_Typedef *rx);

#endif /* CAN_H_ */
