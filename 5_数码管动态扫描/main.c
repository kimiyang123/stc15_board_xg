//************************************
//STC_XGboard 51��Ƭ��ѧϰ��
//��Ŀ˵����8������ܶ�̬ɨ����ʾ76543210
//author:Kimiyang
//
//20170110
//************************************

// �������ʾ�˿� P0
// �����λѡ�˿� P2
// �������ʾʹ�� P1.5

#include <STC15F2K60S2.H>

#define SegLED_Data P0
#define SegCom_CS		P2
#define SegOE				P15

//����������
//code��ʾ�����洢��flash�У�
//һ�㳣��ʹ��Code�ؼ��֡�
unsigned char code SegTab[10] = {0x3f,0x06,0x5b,0x4f,0x66,
																0x6d,0x7d,0x07,0x7f,0x6f};
//8����ʾ������
unsigned char DispBuf[8];

void DelayMs(unsigned int Dtime)
{
	unsigned int i=0;
	for(;Dtime>0;Dtime--)
		for(i=0;i<1000;i++);
}


void ScanSegLED()
{
	//static��̬�����ؼ��֣�
	//�˳��Ӻ�����̬������Ȼ����
  static unsigned char ScanCnt=0;
	//SegOE = 1;
	SegCom_CS = 0xff;  //LED ȫ��
	SegLED_Data = DispBuf[ScanCnt];
	SegCom_CS = ~(1<<ScanCnt);///��ʾ���ĸ������
	//SegOE = 0;  //��ʹ�ܿ�ʼ��ʾ
	if(ScanCnt++ > 7) ScanCnt = 0;
	//DelayMs(2);
}

int main()
{
	unsigned char i=0;
	for(i=0;i<8;i++)
	{
		DispBuf[i] = SegTab[i];
	}

	//����P0 P2 ��ǿ�������ģʽ
	P0M1 = 0x00;
	P0M0 = 0xFF;
	
	P2M1 = 0x00;
	P2M0 = 0xFF;
	SegOE = 0;

	while(1)
	{
		ScanSegLED();
	}
}
