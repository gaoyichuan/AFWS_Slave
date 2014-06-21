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

#define     URMD    0           //0:使用定时器2作为波特率发生器
                                //1:使用定时器1的模式0(16位自动重载模式)作为波特率发生器
                                //2:使用定时器1的模式2(8位自动重载模式)作为波特率发生器

#define ADC_POWER   0x80            //ADC电源控制位
#define ADC_FLAG    0x10            //ADC完成标志
#define ADC_START   0x08            //ADC起始控制位
#define ADC_SPEEDLL 0x00            //540个时钟
#define ADC_SPEEDL  0x20            //360个时钟
#define ADC_SPEEDH  0x40            //180个时钟
#define ADC_SPEEDHH 0x60            //90个时钟

sbit L1 = P3^6;
sbit L2 = P3^7;
sbit sensor = P1^0;
sbit butt = P3^3;

#endif