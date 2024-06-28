/*
 * CAN.c
 *
 *  Created on: May 26, 2022
 *      Author: Kunal
 */



#include "CAN.h"


/*
 * @func 			:	CAN_Init
 * @rev				:	1
 * @Comment			:	None
 * @input param		:	mailbox
 * @output param	:	none
 * @operation		:	Configures the CAN controller as per the CAN_Config struct.
 *                      Take a look at the examples and the CAN_Config structure for
 *                      more information
 */
int CAN_Init(CAN_Config *config)
{
    RCC -> APB1ENR &= ~RCC_APB1ENR_CAN1EN;

    if(config->RX_Pin == CAN_Pin.RX.PA11) GPIO_Pin_Setup(GPIOA, 11, GPIO_Config.ALT_PUSH_PULL_OUTPUT);
    else if(config->RX_Pin == CAN_Pin.RX.PB8) GPIO_Pin_Setup(GPIOB, 8, GPIO_Config.ALT_PUSH_PULL_OUTPUT);

    if(config->TX_Pin == CAN_Pin.TX.PA12) GPIO_Pin_Setup(GPIOA, 12, GPIO_Config.ALT_PUSH_PULL_OUTPUT);
    else if(config->TX_Pin == CAN_Pin.TX.PB9) GPIO_Pin_Setup(GPIOB, 9, GPIO_Config.ALT_PUSH_PULL_OUTPUT);


//    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
//    GPIOA -> CRH |= GPIO_CRH_CNF12_1 | GPIO_CRH_MODE12;
//    GPIOA -> CRH &= ~GPIO_CRH_CNF12_0;

    RCC -> APB1ENR |= RCC_APB1ENR_CAN1EN;


	config -> CAN_INSTANCE -> MCR	|= CAN_MCR_INRQ;
	config -> CAN_INSTANCE -> MCR |= CAN_MCR_NART;
	config -> CAN_INSTANCE -> IER |= config -> interrupt;
	config -> CAN_INSTANCE -> BTR = config -> Baudrate;

	return 1;
}

int CAN_Filter_Init(CAN_Config *config, CAN_Filter_TypeDef *filter)
{
	uint32_t can_id = 0;
	config -> CAN_INSTANCE -> FMR |= CAN_FMR_FINIT;

	if(filter->filter_id > 13)
	{
		return -1;
	}
	else
	{
// ID INFORMATION
		if(filter -> id_type == CAN_ID.Standard)
		{
			can_id = (filter->ID << 21) | 0;
		}
		else
		{
			can_id = (filter->ID << 3) | 4;
		}

		if(filter -> frame_type == CAN_Frame.Remote_Frame)
		{
			can_id |= 2;
		}

		config -> CAN_INSTANCE -> FA1R &= ~(1 << filter -> filter_id);

		config -> CAN_INSTANCE -> FS1R |=  (1 << filter -> filter_id);

		config -> CAN_INSTANCE -> sFilterRegister[filter->filter_id].FR1 = can_id;
		config -> CAN_INSTANCE -> sFilterRegister[filter->filter_id].FR2 = can_id;

		config -> CAN_INSTANCE -> FFA1R &= ~(1 << filter->filter_id);
		config -> CAN_INSTANCE -> FA1R  |= (1 << filter->filter_id);

		config -> CAN_INSTANCE -> FMR &= ~CAN_FMR_FINIT;

	}
	return 1;
}

void CAN_Start(CAN_Config *config)
{
	config -> CAN_INSTANCE -> MCR &= ~CAN_MCR_SLEEP;
	config -> CAN_INSTANCE -> MCR &= ~CAN_MCR_INRQ;
	while((config -> CAN_INSTANCE -> MSR & CAN_MSR_SLAK)){}
	while((config -> CAN_INSTANCE ->MSR & CAN_MSR_INAK));
}

void CAN_Send_Packet(CAN_Config *config, CAN_TX_Typedef *tx)
{
	config -> CAN_INSTANCE -> sTxMailBox[0].TDHR &= ~0xFFFFFFFF;
	config -> CAN_INSTANCE -> sTxMailBox[0].TDLR &= ~0xFFFFFFFF;
	config -> CAN_INSTANCE -> sTxMailBox[0].TDTR &= ~0xFFFFFFFF;
	config -> CAN_INSTANCE -> sTxMailBox[0].TIR  &= ~0xFFFFFFFF;
//---------------------------------------------------------------------------------------------------------------------

	if(tx->id_type == CAN_ID.Standard)
	{
		config -> CAN_INSTANCE -> sTxMailBox[0].TIR  = tx->ID << 21;
		config -> CAN_INSTANCE -> sTxMailBox[0].TIR  &= ~1 << 2;
	}
	else if(tx->id_type == CAN_ID.Extended)
	{
		config -> CAN_INSTANCE -> sTxMailBox[0].TIR  = tx->ID << 3;
		config -> CAN_INSTANCE -> sTxMailBox[0].TIR  |= 1 << 2;
	}

//---------------------------------------------------------------------------------------------------------------------
	if(tx->frame_type == CAN_Frame.Data_Frame)
	{
		config -> CAN_INSTANCE -> sTxMailBox[0].TIR  &= ~(1 << 1);
	}
	if(tx->frame_type == CAN_Frame.Remote_Frame)
	{
		config -> CAN_INSTANCE -> sTxMailBox[0].TIR  |= (1 << 1);
	}
//---------------------------------------------------------------------------------------------------------------------
	config -> CAN_INSTANCE -> sTxMailBox[0].TDTR = tx->data_length;
	config -> CAN_INSTANCE -> sTxMailBox[0].TDTR &= ~CAN_TDT0R_TGT;
	config -> CAN_INSTANCE -> sTxMailBox[0].TDHR = tx->data[7] << 24 | tx->data[6] << 16 | tx->data[5] << 8 | tx->data[4] << 0;
	config -> CAN_INSTANCE -> sTxMailBox[0].TDLR = tx->data[3] << 24 | tx->data[2] << 16 | tx->data[1] << 8 | tx->data[0] << 0;
	config -> CAN_INSTANCE -> sTxMailBox[0].TIR  |= (1 << 0);
	while(config -> CAN_INSTANCE -> sTxMailBox[0].TIR & (1 << 0)){}

}

void CAN_Get_Packet(CAN_Config *config, CAN_RX_Typedef *rx)
{
//	int fifo1_full, fifo2_full;
//	fifo1_full = (config -> CAN_INSTANCE -> RF0R & CAN_RF0R_FMP0_Msk) >> CAN_RF0R_FMP0_Pos;
//	fifo2_full = (config -> CAN_INSTANCE -> RF1R & CAN_RF1R_FMP1_Msk) >> CAN_RF1R_FMP1_Pos;

	int frame_type = 0;
	int id_type = 0;



	id_type =  (CAN1 -> sFIFOMailBox[0].RIR & CAN_RI0R_IDE_Msk) >> CAN_RI0R_IDE_Pos ;
	frame_type = (CAN1 -> sFIFOMailBox[0].RIR & CAN_RI0R_RTR_Msk) >> CAN_RI0R_RTR_Pos ;

	if(id_type)
	{
		//Extended ID
		rx->id_type = CAN_ID.Extended;
		rx->ID = (config -> CAN_INSTANCE -> sFIFOMailBox[0].RIR & CAN_RI0R_EXID_Msk) >> CAN_RI0R_EXID_Pos;
	}
	else
	{
		//Standard ID
		rx->id_type = CAN_ID.Standard;
		rx->ID = (config -> CAN_INSTANCE -> sFIFOMailBox[0].RIR & CAN_RI0R_STID_Msk) >> CAN_RI0R_STID_Pos;
	}

	if(frame_type)
	{
		//RTR Frame
		rx->frame_type = CAN_Frame.Remote_Frame;
		rx->data_length = (config -> CAN_INSTANCE -> sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC_Msk) >> CAN_RDT0R_DLC_Pos;
		config -> CAN_INSTANCE -> RF0R |= CAN_RF0R_RFOM0;
		while((config -> CAN_INSTANCE -> RF0R & CAN_RF0R_RFOM0)){}
	}
	else
	{
		//Data Frame
		rx->frame_type = CAN_Frame.Data_Frame;
		rx->data_length = (config -> CAN_INSTANCE -> sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC_Msk) >> CAN_RDT0R_DLC_Pos;
		for(int i = 0; i < rx->data_length; i++)
		{
			if(i < 4)
			{
				rx->data[i] =  (config -> CAN_INSTANCE -> sFIFOMailBox[0].RDLR & ( 0xFF << (8*i))) >> (8*i);
			}
			else
			{
				rx->data[i] =  (config -> CAN_INSTANCE -> sFIFOMailBox[0].RDHR & ( 0xFF << (8*(i-4)))) >> (8*(i-4));
			}
		}

		int x = (config -> CAN_INSTANCE -> RF0R & CAN_RF0R_FMP0_Msk);

		for(int i = 0; i < x; i++)
		{
			config -> CAN_INSTANCE -> RF0R |= CAN_RF0R_RFOM0;
		}


//		while((config -> CAN_INSTANCE -> RF0R & CAN_RF0R_RFOM0)){}
	}


}
