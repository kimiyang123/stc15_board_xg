//************************************
//STC_XGboard 51��Ƭ��ѧϰ��
//��Ŀ˵������ʾ�����������ʾ
//author:Kimiyang
//
//20170109
//************************************

// �������ʾ�˿� P0
// �����λѡ�˿� P2
// �������ʾʹ�� P1.5

#include <STC15F2K60S2.H>

#define SegLED_Data P0
#define SegCom_CS		P2
#define SegOE				P15

unsigned char code SegTab[10] = {0x3f,0x06,0x5b,0x4f,0x66,
																0x6d,0x7d,0x07,0x7f,0x6f};

void DelayMs(unsigned int Dtime)
{
	unsigned int i=0;
	for(;Dtime>0;Dtime--)
		for(i=0;i<1000;i++);

}

int main()
{
	unsigned char i=0;
	SegOE = 0;		//�����ʹ��
	SegLED_Data = SegTab[6];
	SegCom_CS =  0x00;//~(1<<1); //��ʾ�ڵ�һ�������

	while(1)
	{
		for(i=0;i<10;i++)
		{
			SegLED_Data = SegTab[i];
			DelayMs(500);
		}
	}
	
}

