
extern void SPI_Init(void);
extern uchar SPI_RW(uchar byte);
extern uchar SPI_RW_Reg(uchar reg,uchar value);
extern uchar SPI_Read(uchar reg);
extern uchar SPI_Read_Buf(uchar reg,uchar *pBuf,uchar bytes);
extern uchar SPI_Write_Buf(uchar reg,uchar *pBuf,uchar bytes);
extern uchar SPI_Write_Buf_2(uchar reg,uchar *pBuf,uchar bytes);