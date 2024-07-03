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
//    RCC -> APB1ENR &= ~(RCC_APB1ENR_CAN1EN | RCC_APB1ENR_CAN2EN);

    if(config->CAN_INSTANCE == CAN_Configuration.Instance._CAN1)
    {

    	RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
        if(config->RX_Pin == CAN_Configuration.Pin._CAN1.RX.PA11){
        	GPIO_Pin_Init(GPIOA, 11, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.CAN_1);
        }
        else if(config->RX_Pin == CAN_Configuration.Pin._CAN1.RX.PD0){
        	GPIO_Pin_Init(GPIOD, 0, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.CAN_1);
        }
        else if(config->RX_Pin == CAN_Configuration.Pin._CAN1.RX.PB8){
             GPIO_Pin_Init(GPIOB, 8, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.CAN_1);
        }

        if(config->TX_Pin == CAN_Configuration.Pin._CAN1.TX.PA12){
        	GPIO_Pin_Init(GPIOA, 12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.CAN_1);
        }
        else if(config->TX_Pin == CAN_Configuration.Pin._CAN1.TX.PD1){
        	GPIO_Pin_Init(GPIOD, 1, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.CAN_1);
        }
        else if(config->TX_Pin == CAN_Configuration.Pin._CAN1.TX.PB9){
        	GPIO_Pin_Init(GPIOB, 9, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.CAN_1);
        }
    }
    else if(config->CAN_INSTANCE == CAN_Configuration.Instance._CAN2)
    {
    	RCC->APB1ENR |= RCC_APB1ENR_CAN2EN;
        if(config->RX_Pin == CAN_Configuration.Pin._CAN2.RX.PB12){
        	GPIO_Pin_Init(GPIOB, 12, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.CAN_2);
        }
        else if(config->RX_Pin == CAN_Configuration.Pin._CAN2.RX.PB5){
        	GPIO_Pin_Init(GPIOB, 5, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.CAN_2);
        }

        if(config->TX_Pin == CAN_Configuration.Pin._CAN2.TX.PB13){
        	GPIO_Pin_Init(GPIOB, 13, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.CAN_2);
        }
        else if(config->TX_Pin == CAN_Configuration.Pin._CAN2.TX.PB6){
        	GPIO_Pin_Init(GPIOB, 6, MODE.Alternate_Function, Output_Type.Push_Pull, Speed.Very_High_Speed, Pull.No_Pull_Up_Down, Alternate_Functions.CAN_2);
        }
    }



    config -> CAN_INSTANCE -> MCR |=   CAN_MCR_RESET | CAN_MCR_SLEEP;
    while(!(config -> CAN_INSTANCE  -> MSR & CAN_MSR_SLAK)){}
    config -> CAN_INSTANCE -> MCR &= ~CAN_MCR_SLEEP;
    config -> CAN_INSTANCE -> MCR |= CAN_MCR_INRQ;
	while((config -> CAN_INSTANCE -> MSR & CAN_MSR_SLAK)){}
	while(!(config -> CAN_INSTANCE-> MSR & CAN_MSR_INAK)){}

	config -> CAN_INSTANCE -> BTR = config -> Baudrate;

	config -> CAN_INSTANCE -> FMR |= CAN_FMR_FINIT;
	config -> CAN_INSTANCE -> FMR &= 0xFFFFC0FF;
	config -> CAN_INSTANCE -> FMR |= 0x1C << 8;

	config -> CAN_INSTANCE -> FMR &= ~CAN_FMR_FINIT;
	config -> CAN_INSTANCE->MCR &= ~CAN_MCR_INRQ;
	config -> CAN_INSTANCE->MCR &= ~CAN_MCR_INRQ;
    while((config -> CAN_INSTANCE->MSR & CAN_MSR_INAK)){}
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
		if(filter -> id_type == CAN_Configuration.ID.Standard)
		{
			can_id = (filter->ID << 21) | 0;
		}
		else
		{
			can_id = (filter->ID << 3) | 4;
		}

		if(filter -> frame_type == CAN_Configuration.Frame.Remote_Frame)
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
	while((config -> CAN_INSTANCE -> MSR & CAN_MSR_SLAK)){}
	config -> CAN_INSTANCE -> MCR &= ~CAN_MCR_INRQ;
	while((config -> CAN_INSTANCE ->MSR & CAN_MSR_INAK));
}

uint8_t CAN_Send_Packet(CAN_Config *config, CAN_TX_Typedef *tx)
{

    // Check which mailbox is free
	uint8_t mailbox;
    if ((config -> CAN_INSTANCE -> TSR & CAN_TSR_TME0) == CAN_TSR_TME0) {
        mailbox = 0;
    } else if ((config -> CAN_INSTANCE -> TSR & CAN_TSR_TME1) == CAN_TSR_TME1) {
        mailbox = 1;
    } else if ((config -> CAN_INSTANCE -> TSR & CAN_TSR_TME2) == CAN_TSR_TME2) {
        mailbox = 2;
    } else {
        // No available mailbox
        return 0;
    }

	config -> CAN_INSTANCE -> sTxMailBox[mailbox].TDHR &= ~0xFFFFFFFF;
	config -> CAN_INSTANCE -> sTxMailBox[mailbox].TDLR &= ~0xFFFFFFFF;
	config -> CAN_INSTANCE -> sTxMailBox[mailbox].TDTR &= ~0xFFFFFFFF;
	config -> CAN_INSTANCE -> sTxMailBox[mailbox].TIR  &= ~0xFFFFFFFF;
//---------------------------------------------------------------------------------------------------------------------

	if(tx->ID < 0x7FF)
	{
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TIR  = tx->ID << 21;
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TIR  &= ~(CAN_TI0R_IDE);
	}
	else
	{
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TIR  = tx->ID << 3;
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TIR  |= CAN_TI0R_IDE;
	}

//---------------------------------------------------------------------------------------------------------------------
	if(tx->frame_type == CAN_Configuration.Frame.Data_Frame)
	{
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TIR  &= ~(1 << 1);
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TDTR = tx->data_length;
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TDTR &= ~CAN_TDT0R_TGT;
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TDHR = tx->data[7] << 24 | tx->data[6] << 16 | tx->data[5] << 8 | tx->data[4] << 0;
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TDLR = tx->data[3] << 24 | tx->data[2] << 16 | tx->data[1] << 8 | tx->data[0] << 0;
	}
	if(tx->frame_type == CAN_Configuration.Frame.Remote_Frame)
	{
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TIR  |= (1 << 1);
		config -> CAN_INSTANCE -> sTxMailBox[mailbox].TDTR = tx->data_length;
	}
//---------------------------------------------------------------------------------------------------------------------

	config -> CAN_INSTANCE -> sTxMailBox[mailbox].TIR  |= CAN_TI0R_TXRQ;
    while ((config -> CAN_INSTANCE ->TSR & (CAN_TSR_RQCP0 << mailbox)) == 0);

    // Clear the transmission complete flag
    config -> CAN_INSTANCE ->TSR |= (CAN_TSR_RQCP0 << mailbox);
    return 1;

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
		rx->id_type = CAN_Configuration.ID.Extended;
		rx->ID = (config -> CAN_INSTANCE -> sFIFOMailBox[0].RIR & CAN_RI0R_EXID_Msk) >> CAN_RI0R_EXID_Pos;
	}
	else
	{
		//Standard ID
		rx->id_type = CAN_Configuration.ID.Standard;
		rx->ID = (config -> CAN_INSTANCE -> sFIFOMailBox[0].RIR & CAN_RI0R_STID_Msk) >> CAN_RI0R_STID_Pos;
	}

	if(frame_type)
	{
		//RTR Frame
		rx->frame_type = CAN_Configuration.Frame.Remote_Frame;
		rx->data_length = (config -> CAN_INSTANCE -> sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC_Msk) >> CAN_RDT0R_DLC_Pos;
		config -> CAN_INSTANCE -> RF0R |= CAN_RF0R_RFOM0;
		while((config -> CAN_INSTANCE -> RF0R & CAN_RF0R_RFOM0)){}
	}
	else
	{
		//Data Frame
		rx->frame_type = CAN_Configuration.Frame.Data_Frame;
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
