#include "Uart.h"


void UartInit(void)		//115200bps@11.0592MHz
{
	SCON = 0x50;		//8 位可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc 即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//定时器1 选择为16位自动重载方式
	TL1 = 0xE8;		//
	TH1 = 0xFF;		//
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	ES = 1;			
	EA = 1;

}


void Uart_SendData(unsigned char dat)
{
	SBUF = dat;
	while(!TI);
	TI = 0;
	 
}

void Uart_SendString(char *s)
{
	while(*s)
	{
		Uart_SendData(*s++);

	}
}