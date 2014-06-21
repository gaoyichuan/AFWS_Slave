#include "main.h"
#include "STC15F104E.H"

sbit CSN=		P1^3;
sbit MOSI=		P1^4;
sbit MISO=		P1^5;
sbit SCK=		P1^6;
sbit CE=		P1^7;
sbit IRQ=		P3^2;


#define		TX_ADR_WIDTH		5		//5字节宽度的发送/接收地址
#define		TX_PLOAD_WIDTH		32		//数据通道有效数据宽度


#define		READ_REG		0x00
#define 	WRITE_REG		0x20
#define 	RD_RX_PLOAD		0x61
#define		WR_TX_PLOAD		0xA0
#define 	FLUSH_TX		0xe1
#define		FLUSH_RX		0xe2
#define		REUSR_TX_PL		0xe3
#define 	NOP				0xff

#define		CONFIG			0x00
#define		EN_AA			0x01
#define		EN_RXADDR		0x02
#define		SETUP_AW		0x03
#define		SETUP_RETR		0x04
#define		RF_CH			0x05
#define		RF_SETUP		0x06
#define		STATUS			0x07
#define		OBSERVE_TX		0x08
#define		CD				0x09
#define		RX_ADDR_P0		0x0a
#define		RX_ADDR_P1		0x0b
#define		RX_ADDR_P2		0x0c
#define		RX_ADDR_P3		0x0d
#define		RX_ADDR_P4		0x0e
#define		RX_ADDR_P5		0x0f
#define		TX_ADDR			0x10
#define		RX_PW_P0		0x11
#define		RX_PW_P1		0x12
#define		RX_PW_P2		0x13
#define		RX_PW_P3		0x14
#define		RX_PW_P4		0x15
#define		RX_PW_P5		0x16
#define		FIFO_SATUS		0x17

extern void RX_Mode();
extern void TX_Mode(uchar *BUF);
extern void TX_Mode_2(uchar *BUF);
extern void NRF24L01_Send_Data();
extern void NRF24L01_Send_Data_2();

extern uchar Check_ACK(bit clear);
extern uchar	RX_BUF[TX_PLOAD_WIDTH];
extern void nRF24L01_FlushRX();
		