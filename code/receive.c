#include "main.h"
#include "receive.h"
#include "NRF24L01.h"
#include "INIT.H"
#include "delay.h"
#include "AFWS.h"

//void NRF24L01_On_Receive(void)
//{
//	uchar cmd,num,dat = 0;
//	cmd = RX_BUF[3];
//	num = RX_BUF[4];
//	dat = RX_BUF[5];
//	Command_Deal(cmd,num,dat);
//}
//
void CLR_BUF()
{
 	unsigned char n = 0;
	for(n=0;n<32;n++)
	{
		RX_BUF[n]=0x00;
	}
}

void Command_Deal()
{
	if(RX_BUF[4] == SLAVE_CODE)
	{
		switch(RX_BUF[3])
		{
			case COMMAND_GET: nRF24L01_Send_Humidity(); break;
			case COMMAND_ASK_IF_WATER: AFWS_Is_Watering(); break;
			case COMMAND_WATER_CONFIG: AFWS_Water_test();break;
		}
	}
	else
	{
		L1 = 0;
		delay_ms(200);
		L1 = 1;
	}
	CLR_BUF();
}

