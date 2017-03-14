#ifndef _SEGLED_H_
#define _SEGLED_H_

	#include <STC15F2K60S2.H>

// 数码管显示端口 P0
// 数码管位选端口 P2
// 数码管显示使能 P1.5

#define SegLED_Data 	P0
#define SegCom_CS		P2
#define SegOE			P15

#define LED_NUM			8

#define LED_BIT0_MASK		(1<<0)
#define LED_BIT1_MASK		(1<<1)
#define LED_BIT2_MASK		(1<<2)
#define LED_BIT3_MASK		(1<<3)
#define LED_BIT4_MASK		(1<<4)
#define LED_BIT5_MASK		(1<<5)
#define LED_BIT6_MASK		(1<<6)
#define LED_BIT7_MASK		(1<<7)
#define LED_BIT_ALL			(0xff)


extern unsigned char DispBuf[LED_NUM];
extern unsigned char flashBit;

void SegLED_Init();
void ScanSegLED();

void LED_Show_int(unsigned int num,
					unsigned char StartBit,
					unsigned char ShowBit);
					
void LED_Show_Float(float fnum,
					unsigned char StartBit,
					unsigned char zsBit,
					unsigned char xsBit);
void LED_Show_Clear();

//LED 数码管位闪烁功能控制
void LED_Flash_Ctrl_ON(unsigned char ctrl_bit);
void LED_Flash_Ctrl_OFF(unsigned char ctrl_bit);
void LED_Flash_Clear();


#endif