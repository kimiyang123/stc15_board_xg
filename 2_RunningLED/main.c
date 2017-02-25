//************************************
//STC_XGboard 51单片机学习板
//项目说明：单个LED灯闪烁
//author:Kimiyang
//LED流水灯实验
//20170109
//************************************

// NAME    		Pin
//  LEDoE   	P16
//	LEDport		P0

#include <STC15F2k60S2.H>

#define LED_oE		P16
#define LED_PORT	P0

//************************************
//*函数名称：delay
//*函数功能：延时函数
//*参    数：Dtime：延时时间mS
//*返 回 值：无
//************************************
void delay(unsigned int Dtime)
{
	unsigned int i;
	for(;Dtime>0;Dtime--)
		for(i=0;i<1000;i++);
}


int main()
{
	unsigned char i=0;
	LED_oE = 0; //使能LED的245芯片P16=0
	while(1)
	{
		//流水灯正向移动
		for(i=0;i<8;i++) // i= 0 1 2 3 4 5 6 7 
		{
			LED_PORT = ~(1<<i);
			delay(100);
		}
		// 1000 0000

		//流水灯反向移动
		// 0100 0000
		for(i=1;i<7;i++)
		{
			LED_PORT = ~(0x80>>i);
			delay(100);
		}
		
	}
}



