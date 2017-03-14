#include "sys_time.h"


volatile unsigned long ticks = 0;
volatile unsigned char beepEn=0;

void Beep_On(unsigned char beep_ms)
{
	beepEn = beep_ms;
}

void Timer0_Rountine(void) interrupt 1
{
	TR0 = 0;
	ticks++;

	//任务1 ：数码管扫描
    if(ticks % 1 == 0)
    {
       ScanSegLED();	
    }
	//任务2 ：按键扫描
	if(ticks % 50 == 0)
	{
		 Keypad_Loop();
		// KeyValue = getKeypad();
		// if(KeyValue!=KEY_NULL)
		// {
		// 	Beep_On(10);
		// }
	}

	//Beep控制 beepEn变量大于1时蜂鸣器响
	if(ticks%1 == 0 && beepEn>0)
	{
		 BeepPin = ~BeepPin;
		 if(beepEn-- == 0)
		 {
			 BeepPin = 0;
		 };
	}

	TR0 = 1;
}


void Timer0Init(void)		//1毫秒@24.000MHz
{
	AUXR |= 0x80;		//定时器时钟1T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0x40;		//设置定时初值
	TH0 = 0xA2;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	 ET0 = 1;    //开启定时器0中断使能
}




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
