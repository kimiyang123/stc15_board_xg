//************************************
//STC_XGboard 51单片机学习板
//项目说明：使用函数方法实现数码管显示数值
//author:Kimiyang
//
//20170110
//************************************

#include <STC15F2K60S2.H>
#include "SegLED.h"  //  自定义数码管显示函数库


void DelayMs(unsigned int Dtime)
{
	unsigned int i=0;
	for(;Dtime>0;Dtime--)
		for(i=0;i<1000;i++);
}


int main()
{

	SegLED_Init(); //数码管端口等初始化
	
	LED_Show_int(06,0,2); //显示56
				//显示数据,显示位置,显示位数
	LED_Show_int(26,3,2); //显示26
	LED_Show_int(59,6,2); //显示59
	DispBuf[2] = 0x40;
	DispBuf[5] = 0x40;
	while(1)
	{
		ScanSegLED();  //必须至少每隔2.5ms执行一次
		//LED_Show_int(i++,0,5);
	}
}
