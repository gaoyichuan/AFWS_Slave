#include "STC15F104E.H"
#include <intrins.h>
#include "INIT.H"
#include "main.h"
#include "SPI.h"
#include "NRF24L01.h"
#include "delay.h"
#include "bit.h"
#include "receive.h"
#include "ADC.h"
#include "AFWS.h"
#include "EEPROM.h"
#include "I2C.H"

uchar nrf24l01_receive_flag=0;

void main()
{
	L1 = 0;		 
	Interrupt0_Init();
	Interrupt1_Init();
	SPI_Init();
	InitADC();
	RX_Mode();
	AFWS_Read_Water_Bound();
	P3M0 = 0x30;
	L1 = 1;
	
	while(1)
		{
        PCON = 0x02;            //MCU进入掉电模式
        _nop_();                //掉电模式被唤醒后,首先执行此语句,然后再进入中断服务程序
        _nop_();
		}
}

void Interrupt0() interrupt 0
{
	uchar temp;
	uchar bit_flag;
	temp=SPI_Read(STATUS);
	SPI_RW_Reg(WRITE_REG+STATUS,temp);//清中断
	bit_flag=check_bit(temp,6);
	L2=0;
//	delay_ms(100);
	if(bit_flag==1)
	{
		SPI_Read_Buf(RD_RX_PLOAD,RX_BUF,TX_PLOAD_WIDTH);
		if((RX_BUF[0]==0x55)&&(RX_BUF[1]==0xaa)&&(RX_BUF[2]==0xcc))
		{
			Command_Deal();
//			NRF24L01_On_Receive();
			nrf24l01_receive_flag=1;
			L2=1;
			CLR_BUF();
		}
	}
	L2 = 1;
	nRF24L01_FlushRX(); //清除接收缓冲区数据
	delay_ms(200);
	RX_Mode();
	//delay_ms(200);
}

void Interrupt1_Key_Deal() interrupt 2
{
	delay_ms(20);      //软件延时消抖
	if(butt == 0)
	{
		delay_ms(1000); //检测是否长按
		if(butt == 0)
		{
			AFWS_Man_Control_Water(); //手动浇灌
		}
		else
		{
			AFWS_Set_Hum_Bound(); //设置浇灌上限
		}
	}
}
			