//-----------------------------------------------


#define CMD_IDLE    0               //����ģʽ
#define CMD_READ    1               //IAP�ֽڶ�����
#define CMD_PROGRAM 2               //IAP�ֽڱ������
#define CMD_ERASE   3               //IAP������������

//#define ENABLE_IAP 0x80           //if SYSCLK<30MHz
//#define ENABLE_IAP 0x81           //if SYSCLK<24MHz
#define ENABLE_IAP  0x82            //if SYSCLK<20MHz
//#define ENABLE_IAP 0x83           //if SYSCLK<12MHz
//#define ENABLE_IAP 0x84           //if SYSCLK<6MHz
//#define ENABLE_IAP 0x85           //if SYSCLK<3MHz
//#define ENABLE_IAP 0x86           //if SYSCLK<2MHz
//#define ENABLE_IAP 0x87           //if SYSCLK<1MHz

//���Ե�ַ
#define IAP_ADDRESS 0x0300

void EEPDelay(unsigned char n);
void IapIdle();
unsigned char IapReadByte(unsigned int addr);
void IapProgramByte(unsigned int addr, unsigned char dat);
void IapEraseSector(unsigned int addr);

extern unsigned char EEPROM_Save_Water_Bound(unsigned char bound);
extern unsigned char AFWS_Read_EEP();