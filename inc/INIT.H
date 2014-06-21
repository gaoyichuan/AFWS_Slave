#include "STC15F104E.H"
#ifndef __INIT_H__
#define __INIT_H__

extern void Interrupt0_Init(void);
extern void Interrupt1_Init(void);
extern void InitADC(void);

#define FOSC    18432000L
#define BAUD    9600

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define     URMD    0           //0:ʹ�ö�ʱ��2��Ϊ�����ʷ�����
                                //1:ʹ�ö�ʱ��1��ģʽ0(16λ�Զ�����ģʽ)��Ϊ�����ʷ�����
                                //2:ʹ�ö�ʱ��1��ģʽ2(8λ�Զ�����ģʽ)��Ϊ�����ʷ�����

#define ADC_POWER   0x80            //ADC��Դ����λ
#define ADC_FLAG    0x10            //ADC��ɱ�־
#define ADC_START   0x08            //ADC��ʼ����λ
#define ADC_SPEEDLL 0x00            //540��ʱ��
#define ADC_SPEEDL  0x20            //360��ʱ��
#define ADC_SPEEDH  0x40            //180��ʱ��
#define ADC_SPEEDHH 0x60            //90��ʱ��

sbit L1 = P3^6;
sbit L2 = P3^7;
sbit sensor = P1^0;
sbit butt = P3^3;

#endif