
#include <LCM1602.h>

void _LCM_Delay100us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
}

void _LCM_DelayMs(unsigned int dt)
{
	unsigned char i=0;
	for(;dt>0;dt--)
	{
		for(i=0;i<10;i++)
		{
			_LCM_Delay100us();
		}
	}
}


//LCD1602写入命令函数
void LCM_Write_Com(unsigned char com)
{
	LCM_EN = 0;

	 LCM_RS	= 0;
	 LCM_RW	= 0;

	 LCM_DATA = com;
	_nop_();
	LCM_EN = 1;
	//_LCM_DelayMs(1);
	LCM_EN = 0;

	_LCM_DelayMs(1);
}

//LCD1602写入数据函数
void LCM_Write_Data(unsigned char Data)
{
	LCM_EN = 0;

	LCM_RS = 1;
	LCM_RW = 0;

	LCM_DATA = Data;
	_nop_();
	_LCM_DelayMs(1);
	LCM_EN = 1;
	//_LCM_DelayMs(1);
	LCM_EN = 0;
	
	_LCM_DelayMs(1);

}

//LCD1602清屏函数
void LCM_Clear(void)
{
	LCM_Write_Com(0x01);
	_LCM_DelayMs(5);

}

void LCM_Pos(unsigned char column,unsigned char row)
{
	if(row== LCM2004_ROW0 )
		LCM_Write_Com(LCM2004_ROW0_ADDRESS_START +column);
	else if(row == LCM2004_ROW1)
		LCM_Write_Com(LCM2004_ROW1_ADDRESS_START+column);
	else if(row == LCM2004_ROW2)
		LCM_Write_Com(LCM2004_ROW2_ADDRESS_START+column);
	else if(row == LCM2004_ROW3)
		LCM_Write_Com(LCM2004_ROW3_ADDRESS_START+column);
		
}

void LCM_Display_oneByte(unsigned char x,
						unsigned char y,
						unsigned char dat)
{
		LCM_Pos(x,y);
		LCM_Write_Data(dat);
}

void LCM_Display_Str(unsigned char x,
				unsigned char y,
				char* sdata)
{
	LCM_Pos(x,y);
	while(*sdata != '\0')
	{
		LCM_Write_Data(*sdata++);

	}
}

void LCM_Display_oneNum(unsigned char x,
					unsigned char y,
					unsigned char num)
{
	LCM_Pos(x,y);
	LCM_Write_Data((num%10)+'0');

}

void LCM_Display_Num(unsigned char x,
					unsigned char y,
					unsigned char num)
{
	LCM_Pos(x,y);
	LCM_Write_Data((num/100)+'0');
	LCM_Write_Data((num/10%10)+'0');
	LCM_Write_Data((num%10)+'0');

	
}


void LCM_Init(void)
{
	P2 = 0x00; //防止P2口复用的数码管对其影响
	LCM_BK = 1;//背光打开
	P15 = 0; //HC245使能
	
	
	LCM_Write_Com(0x38);  //设置显示模式
	_LCM_DelayMs(5);
	LCM_Write_Com(0x38);
	_LCM_DelayMs(5);
	LCM_Write_Com(0x38);
	_LCM_DelayMs(5);
	LCM_Write_Com(0x38);
	_LCM_DelayMs(5);

	LCM_Write_Com(0x08);	//显示关闭
	_LCM_DelayMs(5);
	
	LCM_Write_Com(0x0f);	//显示开及光标设置
	_LCM_DelayMs(5);
	LCM_Write_Com(0x0e);	//显示开及光标设置
	_LCM_DelayMs(5);

	LCM_Write_Com(0x01);	//显示清屏
	_LCM_DelayMs(5);

	//LCM_Write_Com(0X02);
	//_LCM_DelayMs(5);

	LCM_EN = 0;
}

