//************************************
//STC_XGboard 51单片机学习板
//项目说明：8个数码管动态扫描显示76543210
//author:Kimiyang
//
//20170110
//************************************

// 数码管显示端口 P0
// 数码管位选端口 P2
// 数码管显示使能 P1.5

#include <STC15F2K60S2.H>

#define SegLED_Data P0
#define SegCom_CS		P2
#define SegOE				P15

//数码管译码表
//code表示变量存储于flash中，
//一般常量使用Code关键字。
unsigned char code SegTab[10] = {0x3f,0x06,0x5b,0x4f,0x66,
																0x6d,0x7d,0x07,0x7f,0x6f};
//8个显示缓存区
unsigned char DispBuf[8];

void DelayMs(unsigned int Dtime)
{
	unsigned int i=0;
	for(;Dtime>0;Dtime--)
		for(i=0;i<1000;i++);
}


void ScanSegLED()
{
	//static静态变量关键字，
	//退出子函数静态变量任然存在
  static unsigned char ScanCnt=0;
	//SegOE = 1;
	SegCom_CS = 0xff;  //LED 全灭
	SegLED_Data = DispBuf[ScanCnt];
	SegCom_CS = ~(1<<ScanCnt);///显示到哪个数码管
	//SegOE = 0;  //打开使能开始显示
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

	//设置P0 P2 口强上拉输出模式
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
