//************************************
//STC_XGboard 51��Ƭ��ѧϰ��
//��Ŀ˵����
//author:Kimiyang
//
//DATE:20170215
//************************************

#include <STC15f2K60S2.h>
#include <SegLED.h>
#include <intrins.h>

unsigned char showNum = 0;

//�ⲿ�ж�0��ʼ������
void INT0_Init()
{
//    INT0 = 1;
    IT0 = 1;      //����INT0�ж�����(1:�½��� 0:������ )
    EX0 = 1;      
}

//�ⲿ�ж�1��ʼ������
void INT1_Init()
{
    IT1 = 1;      //����INT0�ж�����(1:�½��� 0:������ )
    EX1 = 1;      
}
//�ⲿ�жϺ��� INT0���ж�����Ϊ0(����ֲ�P544)
void ExInt0() interrupt 0
{
	P55 = !P55;
	showNum++;
	LED_Show_int(showNum,0,3);
}
//�ⲿ�жϺ��� INT1���ж�����Ϊ2
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