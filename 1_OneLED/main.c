//************************************
//STC_XGboard 51��Ƭ��ѧϰ��
//author:Kimiyang
//OneLEDFlash
//ʵ�ֵ���LED��˸
//20170109
//************************************

// NAME    Pin
// LED		 P55

#include <STC15F2k60S2.H>
#include <intrins.h>

#define  LED P55  //����LED�ܽź�

//************************************
//*�������ƣ�delay
//*�������ܣ���ʱ����
//*��    ����Dtime����ʱʱ��mS
//*�� �� ֵ����
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
	LED = 1;  //����
	while(1)
	{
		LED = 0;  		//����LED
		delay_nMs(500);  	//��ʱԼΪ0.5s
		LED = 1;			//Ϩ��LED
		delay_nMs(500);
	}

}