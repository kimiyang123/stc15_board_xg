//************************************
//STC_XGboard 51��Ƭ��ѧϰ��
//��Ŀ˵����beep����������
//author:Kimiyang
//
//20170109
//************************************


#include <STC15F2K60s2.h>

#define uint unsigned int 
#define uchar unsigned char

#define beep  P40  //�������ܽ�

//���տ��ָ�
uchar code SONG_TONE[]={212,212,190,212,159,169,212,212,190,212,142,159,
												212,212,106,126,159,169,190,119,119,126,159,142,159,0};
uchar code SONG_LONG[]={9,3,12,12,12,24,9,3,12,12,12,24,
												9,3,12,12,12,12,12,9,3,12,12,12,24,0};
//************************************
//*�������ƣ�delay
//*�������ܣ���ʱ����
//*��    ����Dtime����ʱʱ��mS
//*�� �� ֵ����
//************************************
void DelayMs(unsigned int Dtime)
{
	unsigned int i;
	for(;Dtime>0;Dtime--)
		for(i=0;i<1000;i++);
}

void delay1(unsigned int Dtime)
{
	unsigned int i;
	for(;Dtime>0;Dtime--)
		for(i=0;i<1000;i++);
}

void PlayMusic()
{
	uchar tmp =0;
	uint i=0,j,k;
	while(SONG_LONG[i]!=0||SONG_TONE[i]!=0)
	{ //���Ÿ���������song_longΪ���ӳ���
			for(j=0;j<SONG_LONG[i]*20;j++)
			{
					beep=~beep;
				  P55 = ~P55; //LED����������˸
				//SONG_TONE ��ʱ�����ÿ��������Ƶ��
					for(k=0;k<SONG_TONE[i]/3;k++)
					{
						for(tmp=0;tmp<24;tmp++);
					}
			}
			DelayMs(20);
			i++;
	}
	beep = 0;
}


int main(void)
{
	unsigned int i=0;
	unsigned char j=0;
	
	P4M0 = 0x01;
	P4M1 = 0x00;  //����P40��Ϊ�����������ǿ�������

  P55 = 1;
	DelayMs(3000);
	while(1)
	{
		for(i=0;i<1000;i++)
		{
			beep = ~beep; // P40 = ~P40
			//for(j=0;j<150;j++);
			DelayMs(1);
		}
		DelayMs(3000);
	  PlayMusic();
	}

}
