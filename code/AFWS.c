#include "main.h"
#include "nrf24l01.h"
#include "spi.h"
#include "delay.h"
#include "init.h"
#include "AFWS.h"
#include "ADC.h"
#include "receive.h"
#include "EEPROM.h"
#include "I2C.H"

uchar Water_Upper_Bond = 50;
uchar data MRD[2]={0x01,0x02}; //接收缓冲区 


//uchar AFWS_Get_Humidity()
//{
//	 uchar tmphum=0;
//	 tmphum = GetADCResult(Sensor_ADC_Channel);
//	 delay_ms(5);
//	 return tmphum;
//}
void nRF24L01_Send_Humidity()
{
//	 uchar tmph;
//	 tmph = AFWS_Get_Humidity();
     IRcvStr(LM75A,0x00,MRD,2); //读取LM75A当前温度值 	 delay_ms(10);
	 RX_BUF[3] = COMMAND_DATA;
	 RX_BUF[4] = SLAVE_CODE;
	 RX_BUF[5] = GetADCResult(Sensor_ADC_Channel);
	 RX_BUF[6] = MRD[0];
	 RX_BUF[7] = MRD[1];
	 NRF24L01_Send_Data();
     CLR_BUF();
	 delay_ms(5);
} 

void AFWS_Read_Water_Bound()
{
	Water_Upper_Bond = AFWS_Read_EEP();
}
void AFWS_Set_Hum_Bound()
{
	//L1 = 0;
	Water_Upper_Bond = GetADCResult(Sensor_ADC_Channel);
	if(EEPROM_Save_Water_Bound(Water_Upper_Bond) == 0)
	{
		L2 = 0;
		delay_ms(100);
		L2 = 1;
	}
	else
	{
		L1 = 0;
		delay_ms(100);
		L1 = 1;
	}
	//L1 = 1;
}
void AFWS_Water()
{		
	RX_BUF[3] = COMMAND_WATER;
	RX_BUF[4] = SLAVE_CODE;
	RX_BUF[5] = 0x00;
	NRF24L01_Send_Data();
	delay_ms(100);
	CLR_BUF();
}	
void AFWS_Water_test()
{
    unsigned char tmph = 0;
	while(1)
	{
		tmph = GetADCResult(Sensor_ADC_Channel);
		if(tmph >= Water_Upper_Bond)
		{
			RX_BUF[3] = COMMAND_STOP_WATER;
			RX_BUF[4] = SLAVE_CODE;
			RX_BUF[5] = 0x00;
			NRF24L01_Send_Data();
			delay_ms(100);
			nRF24L01_FlushRX();
			CLR_BUF();
			delay_ms(300);
			break;
		}
		L1 = ~ L1;
		delay_ms(100);
		CLR_BUF();
		tmph = 0;
		nRF24L01_FlushRX();	  
	}
	L1 = 1;
}

void AFWS_Man_Control_Water()
{
	RX_BUF[3] = COMMAND_MANWATER;
	RX_BUF[4] = SLAVE_CODE;
	NRF24L01_Send_Data_2();
	CLR_BUF();		
}

void AFWS_Is_Watering()
{
	//unsigned char Is_Watering = 1;
	unsigned char tmph = 0;
	L1 = 0;
	delay_ms(500);
	L1 = 1;
	tmph = GetADCResult(Sensor_ADC_Channel);
	if(tmph < Water_Upper_Bond)
		{
	//	Is_Watering = 0;
		L2 = 0;
		AFWS_Water();
		}
		else
		{
	 		RX_BUF[3] = COMMAND_STOP_WATER;
			RX_BUF[4] = SLAVE_CODE;
			RX_BUF[5] = 0x00;
			NRF24L01_Send_Data();
			delay_ms(100);
			nRF24L01_FlushRX();
			CLR_BUF();
			delay_ms(300);
	 	};
	delay_ms(10);
}
