#include "init.h"
#include "STC15F104E.H"

void Interrupt0_Init(void)
{
	EA=1;
	EX0=1;
	IT0=1;
}

void Interrupt1_Init(void)
{
	EA=1;
	EX1=1;
	IT1=1;
}

/*----------------------------
ADC�����ʱ
----------------------------*/
extern void Delay(WORD n)
{
    WORD x;

    while (n--)
    {
        x = 5000;
        while (x--);
    }
}

/*----------------------------
��ʼ��ADC
----------------------------*/
void InitADC(void)
{
	P10 = 0;
	//P1M0 = 0x01;
	//P1M1 = 0x01;
	P1ASF = 0x01;                   //����P1��ΪAD��
    ADC_RES = 0;                    //�������Ĵ���
    ADC_CONTR = ADC_POWER | ADC_SPEEDLL;
    Delay(2);                       //ADC�ϵ粢��ʱ
}

