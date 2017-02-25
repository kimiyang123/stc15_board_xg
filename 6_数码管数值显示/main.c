//************************************
//STC_XGboard 51��Ƭ��ѧϰ��
//��Ŀ˵����ʹ�ú�������ʵ���������ʾ��ֵ
//author:Kimiyang
//
//20170110
//************************************

#include <STC15F2K60S2.H>
#include "SegLED.h"  //  �Զ����������ʾ������


void DelayMs(unsigned int Dtime)
{
	unsigned int i=0;
	for(;Dtime>0;Dtime--)
		for(i=0;i<1000;i++);
}


int main()
{

	SegLED_Init(); //����ܶ˿ڵȳ�ʼ��
	
	LED_Show_int(06,0,2); //��ʾ56
				//��ʾ����,��ʾλ��,��ʾλ��
	LED_Show_int(26,3,2); //��ʾ26
	LED_Show_int(59,6,2); //��ʾ59
	DispBuf[2] = 0x40;
	DispBuf[5] = 0x40;
	while(1)
	{
		ScanSegLED();  //��������ÿ��2.5msִ��һ��
		//LED_Show_int(i++,0,5);
	}
}
