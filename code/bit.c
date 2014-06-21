#include "bit.h"
#include "main.h"

uchar check_bit(uchar data1,uchar num)
{
	uchar temp;
	temp=data1&(1<<num);
	if(temp!=0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

#if 0
void set_bit(uchar *data1,uchar num)
{
	*data1=*data1|(1<<num);	
}

void clr_bit(uchar *data1,uchar num)
{
	*data1=*data1&(~(1<<num));
}
	
#endif
