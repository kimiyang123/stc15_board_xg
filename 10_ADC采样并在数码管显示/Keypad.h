#ifndef _KEYPAD_C_
#define _KEYPAD_C_

	#include <STC15f2K60S2.h>

	//4X4 键盘管脚
	#define KeyPad_Port		P2

	unsigned char getKeypad(void);


	#define KEY_NUM0	13
	#define KEY_NUM1	0
	#define KEY_NUM2	1
	#define KEY_NUM3	2
	#define KEY_NUM4	4
	#define KEY_NUM5	5
	#define KEY_NUM6	6
	#define KEY_NUM7	8
	#define KEY_NUM8	9
	#define KEY_NUM9	10
	#define KEY_A		3
	#define KEY_B		7
	#define KEY_C		11
	#define KEY_D		15
	#define KEY_OK		14
	#define KEY_CANCLE	12



#endif