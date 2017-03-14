#include <STC15f2K60S2.h>
#include <intrins.h>
#include "src/DS1302.h"
#include "src/SegLED.h"

void DelayMs(unsigned int Dtime);


int main()
{
    unsigned char sec,min,hour;

    P4M0 = 0x00;
    P4M1 = 0x01;
    P40 = 0; //蜂鸣器关闭

    DelayMs(1000);

    P4M0 = 0x00;
    P4M1 = 0x00;

    Ds1302_Init();
    SegLED_Init();

		
		Ds_Write(DS1302_ADDR_SECONDS,0x00); // 设定时间秒为0，
										//bit7位=0，开启时钟
    Ds_Write(DS1302_ADDR_MINUTES,0x00); //00 分
    Ds_Write(DS1302_ADDR_HOUR,0x08);    //00 秒

    Ds_Write(DS1302_ADDR_YEAR,0x17);    //17年
    Ds_Write(DS1302_ADDR_MONTH,0x03);   //3月
    Ds_Write(DS1302_ADDR_DATE,0x15);    //15日

    while (1)
    {
        sec = Ds_Read(DS1302_ADDR_SECONDS);
        min = Ds_Read(DS1302_ADDR_MINUTES);
        hour = Ds_Read(DS1302_ADDR_HOUR);

        LED_Show_int(hour ,0,2);
        LED_Show_int(min,3,2);
        LED_Show_int(sec,6,2);

        DelayMs(1);
        ScanSegLED();
    }


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
