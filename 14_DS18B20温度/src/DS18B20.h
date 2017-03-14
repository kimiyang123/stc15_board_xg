#ifndef _DS18B20_H_
#define _DS18B20_H_

	#include <STC15F2K60S2.H>
	#include <intrins.h>

	#define DQ P44

	#define TRUE	1
	#define FALSE	0

	#define Bit		bit

	#define DS18B20_CONF_9BIT	(0<<5)
	#define DS18B20_CONF_10BIT	(1<<5)
	#define DS18B20_CONF_11BIT	(2<<5)
	#define DS18B20_CONF_12BIT	(3<<5)

	extern volatile unsigned char Rom[9];

	unsigned char  oneWire_Start();

	unsigned char oneWire_ReadByte();
	void oneWire_WriteByte(unsigned char Bdat);
	
	signed int DS18B20_GetTempRom();
	float DS18G20_Calculate_Temp(signed int dat);

	void DS18B20_WriteRom(unsigned char TH,unsigned char TL,
					unsigned char config);
	void DS18B20_ReadRom();


#endif