//************************************
//STC_XGboard 51单片机学习板
//author:Kimiyang
//OneLEDFlash
//实现单个LED闪烁
//20170109
//************************************

// NAME    Pin
// LED		 P55

#include <STC15F2k60S2.H>
#include <intrins.h>

#define  LED P55  //定义LED管脚号

//************************************
//*函数名称：delay
//*函数功能：延时函数
//*参    数：Dtime：延时时间mS
//*返 回 值：无
//************************************
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

void delay_nMs(unsigned int Dtime)
{
	unsigned int i;  //255
	for(i=0;i<Dtime;i++)  // 10us
	{
		Delay1ms();  //1s
	}
}

int main(void)
{
	LED = 1;  //灯灭
	while(1)
	{
		LED = 0;  		//点亮LED
		delay_nMs(500);  	//延时约为0.5s
		LED = 1;			//熄灭LED
		delay_nMs(500);
	}

}