#include "delay.h"
#include "main.h"
#include <intrins.h>

void delay_ms(uint count)
{
	uint i,j;
	for(i=count;i>0;i--)
		for(j=660;j>0;j--);
}


