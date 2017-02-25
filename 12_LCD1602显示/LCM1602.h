#ifndef _LCM1602_H_
#define _LCM1602_H_

#include <intrins.h>
#include <STC15f2K60S2.h>

	#define LCM_DATA	P0
	#define LCM_RS	P27
	#define LCM_RW	P26
	#define LCM_EN	P25
	#define LCM_BK	P24  //LCM背光控制


	#define LCM2004_ROW0	0
	#define LCM2004_ROW1	1
	#define LCM2004_ROW2	2
	#define LCM2004_ROW3	3
	#define LCM2004_ROW0_ADDRESS_START	(0x80)
	#define LCM2004_ROW1_ADDRESS_START	(0xC0)
	#define LCM2004_ROW2_ADDRESS_START	(0x80+20)
	#define LCM2004_ROW3_ADDRESS_START	(0xC0+20)



	void LCM_Init(void);
	void LCM_Pos(unsigned char x,unsigned char y);
	void LCM_Write_Data(unsigned char Data);

	void LCM_Display_Str(unsigned char x,
				unsigned char y,
				char* sdata);

	void LCM_Display_oneNum(unsigned char x,
					unsigned char y,
					unsigned char num);

	void LCM_Display_Num(unsigned char x,
					unsigned char y,
					unsigned char num);

#endif
