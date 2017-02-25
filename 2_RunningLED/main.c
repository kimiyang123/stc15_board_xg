//************************************
//STC_XGboard 51��Ƭ��ѧϰ��
//��Ŀ˵��������LED����˸
//author:Kimiyang
//LED��ˮ��ʵ��
//20170109
//************************************

// NAME    		Pin
//  LEDoE   	P16
//	LEDport		P0

#include <STC15F2k60S2.H>

#define LED_oE		P16
#define LED_PORT	P0

//************************************
//*�������ƣ�delay
//*�������ܣ���ʱ����
//*��    ����Dtime����ʱʱ��mS
//*�� �� ֵ����
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
	LED_oE = 0; //ʹ��LED��245оƬP16=0
	while(1)
	{
		//��ˮ�������ƶ�
		for(i=0;i<8;i++) // i= 0 1 2 3 4 5 6 7 
		{
			LED_PORT = ~(1<<i);
			delay(100);
		}
		// 1000 0000

		//��ˮ�Ʒ����ƶ�
		// 0100 0000
		for(i=1;i<7;i++)
		{
			LED_PORT = ~(0x80>>i);
			delay(100);
		}
		
	}
}



