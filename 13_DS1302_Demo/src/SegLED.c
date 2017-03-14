//************************************
//STC_XGboard 51单片机学习板
//项目说明：
//author:Kimiyang
//
//DATE:20170110
//************************************

#include "SegLED.h"


//数码管译码表
//code表示变量存储于flash中，
//一般常量使用Code关键字。
unsigned char code SegTab[10] = {0x3f,0x06,0x5b,0x4f,0x66,
								0x6d,0x7d,0x07,0x7f,0x6f};
//8个显示缓存区
unsigned char DispBuf[LED_NUM];

//闪烁位定义
unsigned char flashBit = 0;

//************************************
//*函数名称：SegLED_Init
//*函数功能：数码管端口初始化
//*参    数：
//*返 回 值：
//************************************
void SegLED_Init()
{
	unsigned char i=0;
	//设置P0 P2 口强上拉输出模式
	P0M1 = 0x00;
	P0M0 = 0xFF;
	
	P2M1 = 0x00;
	P2M0 = 0xFF;
	
	for(i=0;i<8;i++)
	{
		DispBuf[i] = 0x00;//SegTab[0];
	}

}


unsigned char flashCtl = 0;
void ScanSegLED()
{
	//static静态变量关键字，
	//退出子函数静态变量任然存在
	static unsigned char ScanCnt=0;
	unsigned char bfP2M1,bfP2M0;
	static unsigned char flashCnt=0;

	bfP2M0 = P2M0;
	bfP2M1 = P2M1;

		P2M1 = 0x00;
		P2M0 = 0x00;
	SegOE = 1;
	SegLED_Data = DispBuf[7-ScanCnt];

	if(flashBit & (1<<ScanCnt))
	{
		if(flashCnt % 15 == 0)
		{
			flashCtl ^= (1<<ScanCnt);
			//if(flashCnt>=200) 
			flashCnt = 0;
		}
		if(flashCtl & (1<<ScanCnt))
		{
			SegLED_Data = 0x00;
		}
	
	}

		P2M1 = (1<<ScanCnt);
		P2M0 = (1<<ScanCnt); //芯片选中脚 开漏输出0
	SegCom_CS = ~(1<<ScanCnt);
	SegOE = 0;  //打开使能开始显示
	if(ScanCnt++ >= LED_NUM )
	{
		flashCnt++;
		ScanCnt = 0;
	} 
	
	P2M0 = bfP2M0;
	P2M1 = bfP2M1;
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

void LED_Show_Clear()
{
	unsigned char i=0;
	for ( i = 0; i < 8; i++)
	{
		DispBuf[i] = 0x00;
	}
}

void LED_Flash_Ctrl_ON(unsigned char ctrl_bit)
{
	flashBit |= ctrl_bit;
}

void LED_Flash_Ctrl_OFF(unsigned char ctrl_bit)
{
	flashBit &= ~(ctrl_bit);
	flashCtl &= ~(ctrl_bit); 
}

void LED_Flash_Clear()
{
	flashBit = 0x00;
	flashCtl = 0x00;
}