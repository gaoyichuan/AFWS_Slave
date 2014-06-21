#include "main.h"
#include "STC15F104E.H"
#include "nRF24L01.h"
void SPI_Init(void)
{
	CE=0;					 //����
	CSN=1;					 //SPI��ֹ
	SCK=0;					 //SPIʱ���õ�
	IRQ=1;					 //�жϸ�λ
}

uchar SPI_RW(uchar byte)	 //SPIͨѶ�涨�������ط��͡��½��ؽ��ա���λ�ȷ��͡�
{
	uchar i;
	for(i=0;i<8;i++)		 //ѭ��8��
	{
		MOSI=(byte&0x80);	 //byte���λ�����MOSI
		byte<<=1;			 //��һλ��λ�����λ
		SCK=1;				 //����SCK��nRF24L01��MOSI����1λ���ݣ�ͬʱ��MISO���1λ����
		byte|=MISO;			 //��MISO��byte���λ
		SCK=0;				 //SCK�õ�
	}
	return(byte);			 //���ض�����һ�ֽ�
}

uchar SPI_RW_Reg(uchar reg,uchar value)
{
	uchar status;
	CSN=0;					 //CSN�õͣ���ʼ��������
	status=SPI_RW(reg);		 //ѡ��Ĵ�����ͬʱ����״̬��
	SPI_RW(value);			 //Ȼ��д���ݵ��üĴ�����
	CSN=1;					 //CSN���ߣ��������ݴ���
	return(status); 		 //����״̬�Ĵ���
}

uchar SPI_Read(uchar reg)
{
	uchar reg_val;
	CSN=0;					 //CSN�õͣ���ʼ��������
	SPI_RW(reg);		 	 //ѡ��Ĵ���
	reg_val=SPI_RW(0);	     //Ȼ��ӸüĴ����϶�����
	CSN=1;					 //CSN���ߣ��������ݴ���
	return(reg_val); 	     //���ؼĴ�������
}

uchar SPI_Read_Buf(uchar reg,uchar *pBuf,uchar bytes)
{
	uchar status,i;
	CSN=0;					 //CSN�õͣ���ʼ��������
	status=SPI_RW(reg);		 //ѡ��Ĵ���
	for(i=0;i<bytes;i++)
		pBuf[i]=SPI_RW(0);	 //���ֽڴ�nRF24L01����
	CSN=1;					 //CSN���ߣ��������ݴ���
	return(status);			 //����״̬�Ĵ���
}

uchar SPI_Write_Buf(uchar reg,uchar *pBuf,uchar bytes)
{
	uchar status,i;
	CSN=0;					 //CSN�õͣ���ʼ��������
	status=SPI_RW(reg);		 //ѡ��Ĵ�����ͬʱ����״̬��
	for(i=0;i<bytes;i++)
		SPI_RW(pBuf[i]);	 //���ֽ�д��nRF24L01�
	CSN=1;					 //CSN���ߣ��������ݴ���
	return(status);			 //����״̬�Ĵ���
}

uchar SPI_Write_Buf_2(uchar reg,uchar *pBuf,uchar bytes)
{
	uchar status,i;
	CSN=0;					 //CSN�õͣ���ʼ��������
	status=SPI_RW(reg);		 //ѡ��Ĵ�����ͬʱ����״̬��
	for(i=0;i<bytes;i++)
		SPI_RW(pBuf[i]);	 //���ֽ�д��nRF24L01�
	CSN=1;					 //CSN���ߣ��������ݴ���
	return(status);			 //����״̬�Ĵ���
}
