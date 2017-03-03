//************************************
//STC_XGboard 51单片机学习板
//项目说明：学习4X4按键扫描程序
//author:Kimiyang
//
//20170111
//************************************

#include <STC15f2K60S2.h>
#include <intrins.h>
#include "SegLED.h"  //  自定义数码管显示函数库
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
	P40 = 0; //beep关闭
	SegLED_Init(); //数码管端口等初始化
	
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
		//每隔60ms扫描按键并显示
		if(tickes % 60 == 0)
		{
			keyn = getKeypad();
			if(keyn != 0xff)
			{
				BeepOn(15);
				switch(keyn)
				{
					
					case 3: //3号键对num加
						num++;
					break;
					case 2://2号键对num减
						num--;
					break;
					//其他键的功能可仿照上面编写
				}
				//将计数值显示于数码管中间
				LED_Show_int(num,3,2);
				//将按键编码值显示于数码管前2位
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
	//Beep控制 beepEn变量大于1时蜂鸣器响
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
