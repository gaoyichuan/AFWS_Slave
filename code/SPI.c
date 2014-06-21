#include "main.h"
#include "STC15F104E.H"
#include "nRF24L01.h"
void SPI_Init(void)
{
	CE=0;					 //待机
	CSN=1;					 //SPI禁止
	SCK=0;					 //SPI时钟置低
	IRQ=1;					 //中断复位
}

uchar SPI_RW(uchar byte)	 //SPI通讯规定：上升沿发送、下降沿接收、高位先发送。
{
	uchar i;
	for(i=0;i<8;i++)		 //循环8次
	{
		MOSI=(byte&0x80);	 //byte最高位输出到MOSI
		byte<<=1;			 //低一位移位到最高位
		SCK=1;				 //拉高SCK，nRF24L01从MOSI读入1位数据，同时从MISO输出1位数据
		byte|=MISO;			 //读MISO到byte最低位
		SCK=0;				 //SCK置地
	}
	return(byte);			 //返回读出的一字节
}

uchar SPI_RW_Reg(uchar reg,uchar value)
{
	uchar status;
	CSN=0;					 //CSN置低，开始传输数据
	status=SPI_RW(reg);		 //选择寄存器，同时返回状态字
	SPI_RW(value);			 //然后写数据到该寄存器上
	CSN=1;					 //CSN拉高，结束数据传输
	return(status); 		 //返回状态寄存器
}

uchar SPI_Read(uchar reg)
{
	uchar reg_val;
	CSN=0;					 //CSN置低，开始传输数据
	SPI_RW(reg);		 	 //选择寄存器
	reg_val=SPI_RW(0);	     //然后从该寄存器上读数据
	CSN=1;					 //CSN拉高，结束数据传输
	return(reg_val); 	     //返回寄存器数据
}

uchar SPI_Read_Buf(uchar reg,uchar *pBuf,uchar bytes)
{
	uchar status,i;
	CSN=0;					 //CSN置低，开始传输数据
	status=SPI_RW(reg);		 //选择寄存器
	for(i=0;i<bytes;i++)
		pBuf[i]=SPI_RW(0);	 //逐字节从nRF24L01读出
	CSN=1;					 //CSN拉高，结束数据传输
	return(status);			 //返回状态寄存器
}

uchar SPI_Write_Buf(uchar reg,uchar *pBuf,uchar bytes)
{
	uchar status,i;
	CSN=0;					 //CSN置低，开始传输数据
	status=SPI_RW(reg);		 //选择寄存器，同时返回状态字
	for(i=0;i<bytes;i++)
		SPI_RW(pBuf[i]);	 //逐字节写入nRF24L01?
	CSN=1;					 //CSN拉高，结束数据传输
	return(status);			 //返回状态寄存器
}

uchar SPI_Write_Buf_2(uchar reg,uchar *pBuf,uchar bytes)
{
	uchar status,i;
	CSN=0;					 //CSN置低，开始传输数据
	status=SPI_RW(reg);		 //选择寄存器，同时返回状态字
	for(i=0;i<bytes;i++)
		SPI_RW(pBuf[i]);	 //逐字节写入nRF24L01?
	CSN=1;					 //CSN拉高，结束数据传输
	return(status);			 //返回状态寄存器
}
