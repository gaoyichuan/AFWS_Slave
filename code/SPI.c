#include "main.h"
#include "STC15F104E.H"
#include "nRF24L01.h"
void SPI_Init(void)
{
	CE=0;					 //´ı»ú
	CSN=1;					 //SPI½ûÖ¹
	SCK=0;					 //SPIÊ±ÖÓÖÃµÍ
	IRQ=1;					 //ÖĞ¶Ï¸´Î»
}

uchar SPI_RW(uchar byte)	 //SPIÍ¨Ñ¶¹æ¶¨£ºÉÏÉıÑØ·¢ËÍ¡¢ÏÂ½µÑØ½ÓÊÕ¡¢¸ßÎ»ÏÈ·¢ËÍ¡£
{
	uchar i;
	for(i=0;i<8;i++)		 //Ñ­»·8´Î
	{
		MOSI=(byte&0x80);	 //byte×î¸ßÎ»Êä³öµ½MOSI
		byte<<=1;			 //µÍÒ»Î»ÒÆÎ»µ½×î¸ßÎ»
		SCK=1;				 //À­¸ßSCK£¬nRF24L01´ÓMOSI¶ÁÈë1Î»Êı¾İ£¬Í¬Ê±´ÓMISOÊä³ö1Î»Êı¾İ
		byte|=MISO;			 //¶ÁMISOµ½byte×îµÍÎ»
		SCK=0;				 //SCKÖÃµØ
	}
	return(byte);			 //·µ»Ø¶Á³öµÄÒ»×Ö½Ú
}

uchar SPI_RW_Reg(uchar reg,uchar value)
{
	uchar status;
	CSN=0;					 //CSNÖÃµÍ£¬¿ªÊ¼´«ÊäÊı¾İ
	status=SPI_RW(reg);		 //Ñ¡Ôñ¼Ä´æÆ÷£¬Í¬Ê±·µ»Ø×´Ì¬×Ö
	SPI_RW(value);			 //È»ºóĞ´Êı¾İµ½¸Ã¼Ä´æÆ÷ÉÏ
	CSN=1;					 //CSNÀ­¸ß£¬½áÊøÊı¾İ´«Êä
	return(status); 		 //·µ»Ø×´Ì¬¼Ä´æÆ÷
}

uchar SPI_Read(uchar reg)
{
	uchar reg_val;
	CSN=0;					 //CSNÖÃµÍ£¬¿ªÊ¼´«ÊäÊı¾İ
	SPI_RW(reg);		 	 //Ñ¡Ôñ¼Ä´æÆ÷
	reg_val=SPI_RW(0);	     //È»ºó´Ó¸Ã¼Ä´æÆ÷ÉÏ¶ÁÊı¾İ
	CSN=1;					 //CSNÀ­¸ß£¬½áÊøÊı¾İ´«Êä
	return(reg_val); 	     //·µ»Ø¼Ä´æÆ÷Êı¾İ
}

uchar SPI_Read_Buf(uchar reg,uchar *pBuf,uchar bytes)
{
	uchar status,i;
	CSN=0;					 //CSNÖÃµÍ£¬¿ªÊ¼´«ÊäÊı¾İ
	status=SPI_RW(reg);		 //Ñ¡Ôñ¼Ä´æÆ÷
	for(i=0;i<bytes;i++)
		pBuf[i]=SPI_RW(0);	 //Öğ×Ö½Ú´ÓnRF24L01¶Á³ö
	CSN=1;					 //CSNÀ­¸ß£¬½áÊøÊı¾İ´«Êä
	return(status);			 //·µ»Ø×´Ì¬¼Ä´æÆ÷
}

uchar SPI_Write_Buf(uchar reg,uchar *pBuf,uchar bytes)
{
	uchar status,i;
	CSN=0;					 //CSNÖÃµÍ£¬¿ªÊ¼´«ÊäÊı¾İ
	status=SPI_RW(reg);		 //Ñ¡Ôñ¼Ä´æÆ÷£¬Í¬Ê±·µ»Ø×´Ì¬×Ö
	for(i=0;i<bytes;i++)
		SPI_RW(pBuf[i]);	 //Öğ×Ö½ÚĞ´ÈënRF24L01ö
	CSN=1;					 //CSNÀ­¸ß£¬½áÊøÊı¾İ´«Êä
	return(status);			 //·µ»Ø×´Ì¬¼Ä´æÆ÷
}

uchar SPI_Write_Buf_2(uchar reg,uchar *pBuf,uchar bytes)
{
	uchar status,i;
	CSN=0;					 //CSNÖÃµÍ£¬¿ªÊ¼´«ÊäÊı¾İ
	status=SPI_RW(reg);		 //Ñ¡Ôñ¼Ä´æÆ÷£¬Í¬Ê±·µ»Ø×´Ì¬×Ö
	for(i=0;i<bytes;i++)
		SPI_RW(pBuf[i]);	 //Öğ×Ö½ÚĞ´ÈënRF24L01ö
	CSN=1;					 //CSNÀ­¸ß£¬½áÊøÊı¾İ´«Êä
	return(status);			 //·µ»Ø×´Ì¬¼Ä´æÆ÷
}
