//************************************
//STC_XGboard 51单片机学习板
//项目说明：
//author:Kimiyang
//
//DATE:20170215
//************************************

#include <STC15f2K60S2.h>
#include <SegLED.h>
#include <intrins.h>

unsigned char showNum = 0;

//外部中断0初始化程序
void INT0_Init()
{
//    INT0 = 1;
    IT0 = 1;      //设置INT0中断类型(1:下降沿 0:上升沿 )
    EX0 = 1;      
}

//外部中断1初始化程序
void INT1_Init()
{
    IT1 = 1;      //设置INT0中断类型(1:下降沿 0:上升沿 )
    EX1 = 1;      
}
//外部中断函数 INT0的中断向量为0(详见手册P544)
void ExInt0() interrupt 0
{
	P55 = !P55;
	showNum++;
	LED_Show_int(showNum,0,3);
}
//外部中断函数 INT1的中断向量为2
void ExInt1() interrupt 2
{
	P55 = !P55;
	showNum--;
	LED_Show_int(showNum,0,3);
}


void main()
{
	SegLED_Init();
	LED_Show_int(showNum,0,3);
	INT0_Init();
	INT1_Init();
	EA = 1;
	
	while(1)
	{
		ScanSegLED();
	}
	
}