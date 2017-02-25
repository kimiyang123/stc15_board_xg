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
#include "keypad.h"
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
  unsigned char keyn;
	unsigned char num=0;
	P40 = 0; //beep�ر�
	SegLED_Init(); //����ܶ˿ڵȳ�ʼ��
	
	Timer0Init();
	EA = 1;
	
	LED_Show_int(num,3,2);
	LED_Show_int(keyn,0,2);
	LED_Show_int(Time,6,2);
	
	while(1)
	{
		
		if(tickes % 500 == 0)
		{
			LED_Show_int(Time,6,2);
		}
		//ÿ��60msɨ�谴������ʾ
		if(tickes % 60 == 0)
		{
			keyn = getKeypad();
			if(keyn != 0xff)
			{
				BeepOn(15);
				switch(keyn)
				{
					
					case 3: //3�ż���num��
						num++;
					break;
					case 2://2�ż���num��
						num--;
					break;
					//�������Ĺ��ܿɷ��������д
				}
				//������ֵ��ʾ��������м�
				LED_Show_int(num,3,2);
				//����������ֵ��ʾ�������ǰ2λ
				LED_Show_int(keyn,0,2);
			}
		}
		
	}
	
	
	
}


void Timer0_Rountine(void) interrupt 1
{
	TR0 = 0;
	tickes++;

	if(tickes%2 == 0)
	{
		ScanSegLED();
	}
	
	if(tickes%1000 == 0)
	{
		P55 = ~P55;
		Time++;
	}
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
