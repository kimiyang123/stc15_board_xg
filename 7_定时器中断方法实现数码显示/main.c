//************************************
//STC_XGboard 51单片机学习板
//项目说明：使用函数方法实现数码管显示数值
//author:Kimiyang
//
//20170110
//************************************

//#include <STC15Fxxxx.H>
#include <STC15f2K60S2.h>
#include <intrins.h>
#include "SegLED.h"  //  自定义数码管显示函数库


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
  
	SegLED_Init(); //数码管端口等初始化
	
	LED_Show_int(hour,0,2); //显示56
				//显示数据,显示位置,显示位数
	LED_Show_int(min,3,2); //显示26
	LED_Show_int(sec,6,2); //显示59
	DispBuf[2] = 0x40;
	DispBuf[5] = 0x40;
	
	P40 = 0;
	
	Timer0Init();
	EA = 1;
	while(1)
	{
		LED_Show_int(hour,0,2); 
		LED_Show_int(min,3,2); 
		LED_Show_int(sec,6,2); 
		DelayMs(1000);
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
