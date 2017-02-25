#include "Uart.h"


void UartInit(void)		//115200bps@11.0592MHz
{
	SCON = 0x50;		//8 λ�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc ��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//��ʱ��1 ѡ��Ϊ16λ�Զ����ط�ʽ
	TL1 = 0xE8;		//
	TH1 = 0xFF;		//
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
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