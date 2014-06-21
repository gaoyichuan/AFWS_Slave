#include "main.h"
#include "NRF24L01.h"
#include "SPI.h"
#include "delay.h"
#include "init.h"
/*
RX_BUF的数据格式：
0,1,2为传输接收数据口令，只有当口令正确时才会继续传输接收数据
3为副控左轮控制，4为副控左轮速度，5为副控右轮控制，6为副控右轮速度
7为主控左轮控制，8为主控左轮速度，9为主控右轮控制，10为主控右轮速度
11-31没有定义，作为后期的需要使用
*/
uchar code TX_ADDRESS[TX_ADR_WIDTH]={0x97,0xa0,0xd2,0xc8,0x2c};	  //定义一个静态发送地址
uchar RX_BUF[TX_PLOAD_WIDTH];
uchar 	flag;
uchar 	DATA=0x01;
uchar 	bdata sta;
sbit	RX_DR=sta^6;
sbit	TX_DS=sta^5;
sbit	MAX_RT=sta^4;



void RX_Mode()
{
	CE=0;
	SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,TX_ADDRESS,TX_ADR_WIDTH);//接收设备接收通道0使用和发送设备相同的发送地址，发送地址默认是5位，可查看数据手册中的SETUPE_AW寄存器
	SPI_RW_Reg(WRITE_REG+EN_AA,0x01);			  //使能接收通道0自动应答
	SPI_RW_Reg(WRITE_REG+EN_RXADDR,0x01);	      //使能接收通道0
	SPI_RW_Reg(WRITE_REG+RF_CH,40);				  //选择射频通道0x40
    SPI_RW_Reg(WRITE_REG+RX_PW_P0,TX_PLOAD_WIDTH);//接收通道0选择和发送通道相同有效数据宽度
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);       //数据传输速率1Mbps，发射功率0dBm，低噪声放大器增益
	SPI_RW_Reg(WRITE_REG+CONFIG,0x0f);			  //CRC使能，16位CRC校验,打开接收中断，发送中断，重发次数超出中断
	CE=1;										  //拉高CE启动接收设备
}

void TX_Mode(uchar *BUF)
{
	CE=0;
	SPI_Write_Buf(WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);
	SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,TX_ADDRESS,TX_ADR_WIDTH);
	SPI_Write_Buf(WR_TX_PLOAD,BUF,TX_PLOAD_WIDTH);
	SPI_RW_Reg(WRITE_REG+EN_AA,0x01);
	SPI_RW_Reg(WRITE_REG+EN_RXADDR,0x01);
	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0xff);       //自动重发15次，间隔4000+86us	
	SPI_RW_Reg(WRITE_REG+RF_CH,40);
	SPI_RW_Reg(WRITE_REG+RF_SETUP,0x07);
	SPI_RW_Reg(WRITE_REG+CONFIG,0x0e);			//打开接收中断，发送中断，重发次数超出中断
	CE=1;
}

void TX_Mode_2(uchar *BUF)
{
	CE=0;
	SPI_Write_Buf_2(WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);
	SPI_Write_Buf_2(WRITE_REG+RX_ADDR_P0,TX_ADDRESS,TX_ADR_WIDTH);
	SPI_Write_Buf_2(WR_TX_PLOAD,BUF,TX_PLOAD_WIDTH);
	SPI_RW_Reg(WRITE_REG+EN_AA,0x01);
	SPI_RW_Reg(WRITE_REG+EN_RXADDR,0x01);
	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0xff);       //自动重发15次，间隔4000+86us	
	SPI_RW_Reg(WRITE_REG+RF_CH,40);
	SPI_RW_Reg(WRITE_REG+RF_SETUP,0x07);
	SPI_RW_Reg(WRITE_REG+CONFIG,0x0e);			//打开接收中断，发送中断，重发次数超出中断
	CE=1;													   
}

void NRF24L01_Send_Data()
{
	RX_BUF[0]=0x55;
	RX_BUF[1]=0xaa;
	RX_BUF[2]=0xcc;
	//delay_ms(300);
	TX_Mode(&RX_BUF);
}

void NRF24L01_Send_Data_2()
{
	RX_BUF[0]=0x55;
	RX_BUF[1]=0xaa;
	RX_BUF[2]=0xcc;
	//delay_ms(300);
	TX_Mode_2(&RX_BUF);
}

#if 0
uchar Check_ACK(bit clear)
{
	while(IRQ);
	sta=SPI_RW(NOP);
	if(MAX_RT)
		if(clear)
			SPI_RW(FLUSH_TX);
	SPI_RW_Reg(WRITE_REG+STATUS,sta);
	IRQ=1;
	if(TX_DS)
		return(0x00);
	else
		return(0xff);
}
#endif
void nRF24L01_FlushRX()
{
    CE = 0;
    SPI_RW_Reg(FLUSH_RX,0);             //冲洗缓冲区数据
    CE = 1; 
    delay_ms(1);
}