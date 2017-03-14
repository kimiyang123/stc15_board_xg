#include <STC15f2K60S2.h>
#include <intrins.h>
#include "src\sys_Time.h"
#include "src\DS18B20.h"


int temp=65500;

int main()
{
	float Ftmp = -25.362;
	P4M1 = 0x00;
	P4M0 = 0x00;
	P4 = 0xff;
	temp = Ftmp;
	Ftmp = Ftmp- temp;
	SegLED_Init();
	Timer0Init();
	//LED_Show_int(15,0,2);
	
	EA = 1;
	while(1)
	{
		//获取DS18B20温度寄存器的值
		temp = DS18B20_GetTempRom();
		//计算温度数值
		Ftmp = DS18G20_Calculate_Temp(temp);
		//在数码管上显示温度
		LED_Show_Float(Ftmp,0,2,2);

		DelayMs(500);
	
	}
	

}
