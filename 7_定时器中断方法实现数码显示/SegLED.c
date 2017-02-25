//************************************
//STC_XGboard 51��Ƭ��ѧϰ��
//��Ŀ˵����
//author:Kimiyang
//
//DATE:20170110
//************************************

#include "SegLED.h"


//����������
//code��ʾ�����洢��flash�У�
//һ�㳣��ʹ��Code�ؼ��֡�
unsigned char code SegTab[10] = {0x3f,0x06,0x5b,0x4f,0x66,
																0x6d,0x7d,0x07,0x7f,0x6f};
//8����ʾ������
unsigned char DispBuf[8];

//************************************
//*�������ƣ�SegLED_Init
//*�������ܣ�����ܶ˿ڳ�ʼ��
//*��    ����
//*�� �� ֵ��
//************************************
void SegLED_Init()
{
	unsigned char i=0;
	//����P0 P2 ��ǿ�������ģʽ
	P0M1 = 0x00;
	P0M0 = 0xFF;
	
	P2M1 = 0x00;
	P2M0 = 0xFF;
	
	for(i=0;i<8;i++)
	{
		DispBuf[i] = 0x00;//SegTab[0];
	}

}



void ScanSegLED()
{
	//static��̬�����ؼ��֣�
	//�˳��Ӻ�����̬������Ȼ����
	static unsigned char ScanCnt=0;
	SegOE = 1;
	SegLED_Data = DispBuf[7-ScanCnt];
	SegCom_CS = ~(1<<ScanCnt);
	SegOE = 0;  //��ʹ�ܿ�ʼ��ʾ
	if(ScanCnt++ > 7) ScanCnt = 0;
	//DelayMs(2);
}

unsigned long Pow10(unsigned char x)
{
	unsigned long rValue=10;
	if(x==0)
		return 1;
	for(;x>1;x--)
	{
		rValue *=10;
	}
	return rValue;
	
}


void LED_Show_int(unsigned int num,
									unsigned char StartBit,
									unsigned char ShowBit)
{
	unsigned char i;
	unsigned long temp=0;
	if(ShowBit > 5 || ShowBit==0) ShowBit = 5;
	for(i=0;i<ShowBit;i++)
	{
		temp = Pow10((ShowBit-1-i));
		temp = num/temp%10;
		DispBuf[StartBit+i] = SegTab[temp];
		if(StartBit+i >= 7) break;
	}
//	if(StartBit>=8) 
//	DispBuf[7-StartBit]
}
