#ifndef _SEGLED_H_
#define _SEGLED_H_

	#include <STC15F2K60S2.H>

// �������ʾ�˿� P0
// �����λѡ�˿� P2
// �������ʾʹ�� P1.5

#define SegLED_Data P0
#define SegCom_CS		P2
#define SegOE				P15


extern unsigned char DispBuf[8];

void SegLED_Init();
void ScanSegLED();

void LED_Show_int(unsigned int num,
									unsigned char StartBit,
									unsigned char ShowBit);


#endif