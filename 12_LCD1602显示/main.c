#include <STC15f2K60S2.h>
#include <intrins.h>
#include "LCM1602.h"

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

void delay_ms(unsigned int dtim)
{
	for(;dtim>0;dtim--)
		Delay1ms();
}

char author[]={"Author:Kimiyang"};

unsigned char num=0;
void main()
{
	LCM_BK = 0;//LCM背光关闭
	delay_ms(1500);
	
	LCM_Init();
	LCM_Display_Str(2,0,author);
	LCM_Display_Str(0,1,"YCL@SCSTPEA.COM");
	LCM_Display_Str(0,2,"QQ:520283769");
	LCM_Display_Str(0,3,"Hello world");

	
	
	P55 = 0;
	while(1)
	{
		//LCM_Write_Data('h');
		delay_ms(1500);
		LCM_Display_Num(17,3,num++);
	}
}