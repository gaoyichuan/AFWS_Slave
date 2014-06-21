#include "init.h"
#include "main.h"
#include <intrins.h>


//#define ADC_POWER   0x80            //ADC电源控制位
//#define ADC_FLAG    0x10            //ADC完成标志
//#define ADC_START   0x08            //ADC起始控制位
//#define ADC_SPEEDLL 0x00            //540个时钟
//#define ADC_SPEEDL  0x20            //360个时钟
//#define ADC_SPEEDH  0x40            //180个时钟
//#define ADC_SPEEDHH 0x60            //90个时钟

//extern void InitUart();
extern void InitADC();
//extern void SendData(BYTE dat);
extern BYTE GetADCResult(BYTE ch);
extern void Delay(WORD n);
//extern void ShowResult(BYTE ch);
