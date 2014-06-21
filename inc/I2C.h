#include "main.h"
#include "STC15F104E.H"
#include <intrins.h> 
 
#define _Nop() _nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_() /*定义空指令*/ 
 
sbit SDA=P3^4; /*模拟I2C数据传送位*/ 
sbit SCL=P3^5; /*模拟I2C时钟控制位*/ 

#define LM75A 0x90

void Start_I2c(); 
void Stop_I2c(); 
void SendByte(uchar c);
uchar RcvByte(); 
void Ack_I2c(bit a); 
bit ISendByte(uchar sla,uchar c); 
bit ISendStr(uchar sla,uchar suba,uchar *s,uchar no); 
bit IRcvByte(uchar sla,uchar *c); 
bit IRcvStr(uchar sla,uchar suba,uchar *s,uchar no); 
