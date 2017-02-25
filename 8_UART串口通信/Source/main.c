//************************************
//STC_XGboard 51��Ƭ��ѧϰ��
//��Ŀ˵����ѧϰ4X4����ɨ�����
//author:Kimiyang
//
//20170111
//************************************

#include <STC15f2K60S2.h>
#include <intrins.h>
#include "SegLED.h"  //  �Զ����������ʾ������

#include "UART.h"

volatile unsigned long tickes=0;

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}



void DelayMs(unsigned int Dtime)
{
	for(;Dtime>0;Dtime--)
		Delay1ms();
}

void Timer0Init(void);

volatile unsigned char beepEn=0;
void BeepOn(unsigned char ltime)
{
		beepEn = ltime;
}

unsigned char Time=0;

int main()
{
	unsigned char num=0;
	P40 = 0; //beep�ر�
	
	Timer0Init();
	UartInit(); //���ڳ�ʼ�� �����ʣ�115200bps
	
	EA = 1;
	Uart_SendString("Hello STC51\n");
	while(1)
	{
		
		
		
	}
	
	
}


void Timer0_Rountine(void) interrupt 1
{
	TR0 = 0;
	tickes++;
	
	//Beep���� beepEn��������1ʱ��������
	if(tickes%1 == 0 && beepEn>0)
	{
			P40 = ~P40;
		  beepEn --;
	}
	
	//TMOD &= 0xF0;		//???????
	//TMOD |= 0x01;		//???????
	TR0 = 1;
}

void Timer0Init(void)		//100??@11.0592MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TL0 = 0xCD;			//??????
	TH0 = 0xD4;			//??????
	TF0 = 0;				//??TF0??
	TR0 = 1;				//???0????
	ET0 = 1;
}
