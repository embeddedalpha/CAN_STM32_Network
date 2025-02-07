/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "main.h"
#include "CAN.h"

CAN_Config Master1;
CAN_Config Master2;
CAN_TX_Typedef Master_TX;





int main(void)
{
	MCU_Clock_Setup();
	Delay_Config();

	Master1.CAN_INSTANCE = CAN_Configuration.Instance._CAN1;
	Master1.Baudrate = CAN_Configuration.Baudrate._1000_KBPS;
	Master1.RX_Pin = CAN_Configuration.Pin._CAN1.RX.PD0;
	Master1.TX_Pin = CAN_Configuration.Pin._CAN1.TX.PD1;
	CAN_Init(&Master1);

//	Master2.CAN_INSTANCE = CAN_Configuration.Instance._CAN2;
//	Master2.Baudrate = CAN_Configuration.Baudrate._1000_KBPS;
//	Master2.RX_Pin = CAN_Configuration.Pin._CAN2.RX.PB12;
//	Master2.TX_Pin = CAN_Configuration.Pin._CAN2.TX.PB13;
//	CAN_Init(&Master2);
//	CAN_Set_Filter_List(&Master1, 0x200, 0x202, 0, 0);
	CAN_Set_Filter_List_Dummy(0x200, 0, 0, 0);
	CAN_Activate_Callback(&Master1, CAN_Configuration.Interrupt_ID.FIFO0_Full_Interrupt);

	CAN_Start(&Master1);








	for(;;)
	{
//		Master_TX.ID = 0x200;
//		Master_TX.frame_type = CAN_Configuration.Frame.Data_Frame;
//		Master_TX.data_length = 8;
//		Master_TX.data[0] = 0x01;
//		Master_TX.data[1] = 0x02;
//		Master_TX.data[2] = 0x03;
//		Master_TX.data[3] = 0x04;
//		Master_TX.data[4] = 0x05;
//		Master_TX.data[5] = 0x06;
//		Master_TX.data[6] = 0x07;
//		Master_TX.data[7] = 0x08;
//		CAN_Send_Packet(&Master1, &Master_TX);
//		Delay_s(1);
	}
}
