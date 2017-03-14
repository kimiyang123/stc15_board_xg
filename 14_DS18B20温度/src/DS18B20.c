#include "DS18B20.h"

volatile unsigned char Rom[9];

void DS_Delay_us(unsigned char dt)		//@11.0592MHz
{
	 while (dt--)               //mov  2 dec 1 
    {													//mov 1  jz 2
        _nop_();              //NOP  1+1 
        _nop_();							//sjmp 2
		//_nop_();								// ------共 10xN * 0.0904us
    }
}


unsigned char  oneWire_Start()
{
	//unsigned char dat;
	
	unsigned char waitCnt=0;
	DQ = 1;
	DS_Delay_us(2);
	DQ = 0;			// 拉低总线
	DS_Delay_us(240);
	DS_Delay_us(240);
	DQ = 1; 	//拉高总线，准备读取
	//DS_Delay_us(30);
	while(DQ==1 && waitCnt<200)
	{
		waitCnt++;
	}

	if(waitCnt>=200)
	{
		return FALSE;
	}
	else
	{
		//检测到存在，等待芯片释放总线
		waitCnt = 0;
		while(DQ == 0 && waitCnt<100)
		{
			waitCnt ++;
		}
		if(waitCnt >=100) 
			return FALSE; 	//芯片未释放总线
		else
		{
			return TRUE;
		}

	} 

}


void oneWire_WriteBit(Bit dat )
{
	unsigned char waitCnt=0;
	DQ = 0;	//拉低总线
	DS_Delay_us(3);
	DQ = dat;

	DS_Delay_us(55);
	DQ = 1;		//拉高总线 准备下一个数据
}

Bit oneWrie_ReadBit()
{
	Bit dat = 0;
	DQ = 0;	//拉低总线
	DS_Delay_us(3);
	DQ = 1;		//拉高总线 准备读取
	DS_Delay_us(3);
	dat = DQ;
	DS_Delay_us(45);
	return dat;
}

void oneWire_WriteByte(unsigned char Bdat)
{
	unsigned char i=0;
	for (i = 0; i < 8; i++)
	{
		oneWire_WriteBit( (Bdat>>i)&0x01 );
	}
	DQ = 1; // 写入命令结束，拉高总线
}

unsigned char oneWire_ReadByte()
{
	unsigned char i=0,dat=0;
	for ( i = 0; i < 8; i++)
	{
		dat >>= 1;
		if(oneWrie_ReadBit() == 1)
		{
			dat |= 0x80;
		}
	}
	return dat;
}

signed int DS18B20_GetTempRom()
{
	unsigned char tempH,tempL;
	signed int temp=0;
	EA = 0;
	if(oneWire_Start())
	{
		 oneWire_WriteByte(0xcc);
		 oneWire_WriteByte(0x44);
		if(oneWire_Start())
		{
			oneWire_WriteByte(0xcc);
			oneWire_WriteByte(0xBE);
			tempL = oneWire_ReadByte();
			tempH = oneWire_ReadByte();
			temp = (tempH << 8) + tempL;
		}
	}
	EA = 1;
	//temp = temp * 0.625; //12bit精度位0.0625度,int型变量中保留小数位1位，所以乘0.625
	return temp;
}

float DS18G20_Calculate_Temp(signed int dat)
{
	return (float)(dat * 0.0625);
}

//批量读取DS18B20的9个ROM数据，第九位为CRC
void DS18B20_ReadRom()
{
	unsigned char i=0;
	if(oneWire_Start())
	{
		oneWire_WriteByte(0xcc);
		oneWire_WriteByte(0xBE);
		for(i=0;i<9;i++)
		{
			Rom[i] = oneWire_ReadByte();
		}

	}
}

void DS18B20_WriteRom(unsigned char TH,unsigned char TL,
					unsigned char config)
{
	unsigned char i=0;
	if(oneWire_Start())
	{
		oneWire_WriteByte(0xCC);
		oneWire_WriteByte(0x4E);

		oneWire_WriteByte(TH);
		oneWire_WriteByte(TL);
		oneWire_WriteByte(config);

		//DS18B20_ReadRom();

		oneWire_Start();
		oneWire_WriteByte(0xCC);
		oneWire_WriteByte(0x48); //copy to eeprom

		//等待10ms 写入Eprom
		for(i=0;i<40;i++)
		{
			DS_Delay_us(250);
		}
		
		oneWire_Start();
	}
}

// /**************************************
// 从DS18B20读1字节数据
// **************************************/
// unsigned char DS18B20_ReadByte()
// {
//     unsigned char i;
//     unsigned char dat = 0;
// 	// DQ = 1;
// 	// DS_Delay_us(1);
//     for (i=0; i<8; i++)             //8位计数器
//     {
//         dat >>= 1;
//         DQ = 0;                     //开始时间片
//         DS_Delay_us(3);             //延时等待9us
//         DQ = 1;                     //准备接收
//         DS_Delay_us(3);                //接收延时
//         if (DQ) dat |= 0x80;        //读取数据
//         DS_Delay_us(45);               //等待时间片结束
//     }

//     return dat;
// }

// /**************************************
// 向DS18B20写1字节数据
// **************************************/
// void DS18B20_WriteByte(unsigned char dat)
// {
//     unsigned char i;
//     for (i=0; i<8; i++)             //8位计数器
//     {
//         DQ = 0;                     //开始时间片
//         DS_Delay_us(3);             //延时等待10us
//         //dat >>= 1;                //送出数据
// 		if(dat&0x01 == 1) DQ = 1;
//         //DQ = CY;
//         DS_Delay_us(60);            //等待时间片结束
//         DQ = 1;                     //恢复数据线
// 		dat >>=1;
//         DS_Delay_us(1);             //恢复延时
//     }
// }
