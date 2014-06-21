#include "main.h"
#include "NRF24L01.h"
#include "SPI.h"
#include "delay.h"
#include "init.h"
/*
RX_BUF�����ݸ�ʽ��
0,1,2Ϊ����������ݿ��ֻ�е�������ȷʱ�Ż���������������
3Ϊ�������ֿ��ƣ�4Ϊ���������ٶȣ�5Ϊ�������ֿ��ƣ�6Ϊ���������ٶ�
7Ϊ�������ֿ��ƣ�8Ϊ���������ٶȣ�9Ϊ�������ֿ��ƣ�10Ϊ���������ٶ�
11-31û�ж��壬��Ϊ���ڵ���Ҫʹ��
*/
uchar code TX_ADDRESS[TX_ADR_WIDTH]={0x97,0xa0,0xd2,0xc8,0x2c};	  //����һ����̬���͵�ַ
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
	SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,TX_ADDRESS,TX_ADR_WIDTH);//�����豸����ͨ��0ʹ�úͷ����豸��ͬ�ķ��͵�ַ�����͵�ַĬ����5λ���ɲ鿴�����ֲ��е�SETUPE_AW�Ĵ���
	SPI_RW_Reg(WRITE_REG+EN_AA,0x01);			  //ʹ�ܽ���ͨ��0�Զ�Ӧ��
	SPI_RW_Reg(WRITE_REG+EN_RXADDR,0x01);	      //ʹ�ܽ���ͨ��0
	SPI_RW_Reg(WRITE_REG+RF_CH,40);				  //ѡ����Ƶͨ��0x40
    SPI_RW_Reg(WRITE_REG+RX_PW_P0,TX_PLOAD_WIDTH);//����ͨ��0ѡ��ͷ���ͨ����ͬ��Ч���ݿ��
	SPI_RW_Reg(WRITE_REG + RF_SETUP, 0x07);       //���ݴ�������1Mbps�����书��0dBm���������Ŵ�������
	SPI_RW_Reg(WRITE_REG+CONFIG,0x0f);			  //CRCʹ�ܣ�16λCRCУ��,�򿪽����жϣ������жϣ��ط����������ж�
	CE=1;										  //����CE���������豸
}

void TX_Mode(uchar *BUF)
{
	CE=0;
	SPI_Write_Buf(WRITE_REG+TX_ADDR,TX_ADDRESS,TX_ADR_WIDTH);
	SPI_Write_Buf(WRITE_REG+RX_ADDR_P0,TX_ADDRESS,TX_ADR_WIDTH);
	SPI_Write_Buf(WR_TX_PLOAD,BUF,TX_PLOAD_WIDTH);
	SPI_RW_Reg(WRITE_REG+EN_AA,0x01);
	SPI_RW_Reg(WRITE_REG+EN_RXADDR,0x01);
	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0xff);       //�Զ��ط�15�Σ����4000+86us	
	SPI_RW_Reg(WRITE_REG+RF_CH,40);
	SPI_RW_Reg(WRITE_REG+RF_SETUP,0x07);
	SPI_RW_Reg(WRITE_REG+CONFIG,0x0e);			//�򿪽����жϣ������жϣ��ط����������ж�
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
	SPI_RW_Reg(WRITE_REG + SETUP_RETR, 0xff);       //�Զ��ط�15�Σ����4000+86us	
	SPI_RW_Reg(WRITE_REG+RF_CH,40);
	SPI_RW_Reg(WRITE_REG+RF_SETUP,0x07);
	SPI_RW_Reg(WRITE_REG+CONFIG,0x0e);			//�򿪽����жϣ������жϣ��ط����������ж�
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
    SPI_RW_Reg(FLUSH_RX,0);             //��ϴ����������
    CE = 1; 
    delay_ms(1);
}