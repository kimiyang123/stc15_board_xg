//************************************
//STC_XGboard 51单片机学习板
//项目说明：学习4X4按键扫描程序
//author:Kimiyang
//
//20170118
//************************************

#include <STC15f2K60S2.h>
#include <intrins.h>
#include "SegLED.h"  //  自定义数码管显示函数库
#include "keypad.h"
#include "UART.h"
#include "STC_ADC.h"


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



unsigned char hour,min,sec;
int main()
{
  unsigned int ADC_Value;
	P40 = 0; //beep关闭
	SegLED_Init(); //数码管端口等初始化
	UartInit();
	DelayMs(500);
	
	InitADC();  //初始化ADC
	
	Timer0Init();
	EA = 1;

	while(1)
	{
		ADC_Value = get_ADC(4);
		Uart_SendData(ADC_Value);
		LED_Show_int(ADC_Value,0,4);
		
		if(ADC_Value > 200)
		{
			P55 = 0;
		}
		else
		{
			P55 = 1;
		}
		DelayMs(200);
		
	}
}


void Timer0_Rountine(void) interrupt 1
{
	static unsigned long Tcnt=0;
	TR0 = 0;
	Tcnt++;
	if(Tcnt%2 == 0)
	{
		ScanSegLED();
	}
	
	if(Tcnt%1000UL == 0)
	{
		if(sec++>59)
		{
			sec = 0;
			if(min++>59)
			{
				min = 0;
				if(hour++>59)
				{
					hour=0;
				}
			}
		}
	}
	//TMOD &= 0xF0;		//???????
	//TMOD |= 0x01;		//???????
	TR0 = 1;
}


void Timer0Init(void)		//100??@11.0592MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TL0 = 0xCD;		//??????
	TH0 = 0xD4;		//??????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
	ET0 = 1;
}
