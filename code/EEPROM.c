/*---------------------------------------------------------------------*/
/* --- STC MCU Limited ------------------------------------------------*/
/* --- STC15F4K60S4 ϵ�� �ڲ�EEPROM����--------------------------------*/
/* --- Mobile: (86)13922805190 ----------------------------------------*/
/* --- Fax: 86-755-82905966 -------------------------------------------*/
/* --- Tel: 86-755-82948412 -------------------------------------------*/
/* --- Web: www.STCMCU.com --------------------------------------------*/
/* ���Ҫ�ڳ�����ʹ�ô˴���,���ڳ�����ע��ʹ���˺꾧�Ƽ������ϼ�����   */
/* ���Ҫ��������Ӧ�ô˴���,����������ע��ʹ���˺꾧�Ƽ������ϼ�����   */
/*---------------------------------------------------------------------*/

//��ʾ����Keil������������ѡ��Intel��8058оƬ�ͺŽ��б���
//�ٶ�����оƬ�Ĺ���Ƶ��Ϊ18.432MHz

#include "STC15F104E.H"
#include "intrins.h"
#include "EEPROM.h"

unsigned char EEPROM_Save_Water_Bound(unsigned char bound)
{															  
    unsigned int i;

    //P1 = 0xfe;                      //1111,1110 ϵͳOK
    EEPDelay(10);                      //��ʱ
    IapEraseSector(IAP_ADDRESS);    //��������
    for (i=0; i<512; i++)           //����Ƿ�����ɹ�(ȫFF���)
    {
        if (IapReadByte(IAP_ADDRESS+i) != 0xff)
            goto Error;             //�������,���˳�
    }
    //P1 = 0xfc;                      //1111,1100 �����ɹ�
    EEPDelay(10);                      //��ʱ
    //for (i=0; i<512; i++)           //���512�ֽ�
    //{
        IapProgramByte(IAP_ADDRESS, (unsigned char)bound);
    //}
    //P1 = 0xf8;                      //1111,1000 ������
    EEPDelay(10);                      //��ʱ
    //for (i=0; i<512; i++)           //У��512�ֽ�
    //{
        if (IapReadByte(IAP_ADDRESS) != (unsigned char)bound)
            goto Error;             //���У�����,���˳�
    //}
    //P1 = 0xf0;                      //1111,0000 �������
    //while (1);
	return 0;
Error:
    //P1 &= 0x7f;                     //0xxx,xxxx IAP����ʧ��
    //while (1);
	return 1;
}

/*----------------------------
�����ʱ
----------------------------*/
void EEPDelay(unsigned char n)
{
    unsigned int x;

    while (n--)
    {
        x = 0;
        while (++x);
    }
}

/*----------------------------
�ر�IAP
----------------------------*/
void IapIdle()
{
    IAP_CONTR = 0;                  //�ر�IAP����
    IAP_CMD = 0;                    //�������Ĵ���
    IAP_TRIG = 0;                   //��������Ĵ���
    IAP_ADDRH = 0x80;               //����ַ���õ���IAP����
    IAP_ADDRL = 0;
}

/*----------------------------
��ISP/IAP/EEPROM�����ȡһ�ֽ�
----------------------------*/
unsigned char IapReadByte(unsigned int addr)
{
    unsigned char dat;                       //���ݻ�����

    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_READ;             //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    dat = IAP_DATA;                 //��ISP/IAP/EEPROM����
    IapIdle();                      //�ر�IAP����

    return dat;                     //����
}

/*----------------------------
дһ�ֽ����ݵ�ISP/IAP/EEPROM����
----------------------------*/
void IapProgramByte(unsigned int addr, unsigned char dat)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_PROGRAM;          //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_DATA = dat;                 //дISP/IAP/EEPROM����
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}

/*----------------------------
��������
----------------------------*/
void IapEraseSector(unsigned int addr)
{
    IAP_CONTR = ENABLE_IAP;         //ʹ��IAP
    IAP_CMD = CMD_ERASE;            //����IAP����
    IAP_ADDRL = addr;               //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;          //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                //д��������(0x5a)
    IAP_TRIG = 0xa5;                //д��������(0xa5)
    _nop_();                        //�ȴ�ISP/IAP/EEPROM�������
    IapIdle();
}

unsigned char AFWS_Read_EEP()
{
	return IapReadByte(IAP_ADDRESS);
}
