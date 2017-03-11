#include "src/Keypad.h"
#include <intrins.h>

volatile unsigned char Global_KeyValue = KEY_NULL;


void KDelay1ms()		//@24.000MHz
{
	// unsigned char i, j;
	// i = 24;
	// j = 85;
	// do
	// {
	// 	while (--j);
	// } while (--i);
}


volatile  unsigned int KeyloopCnt = 0;


unsigned char GetKey()
{
	static unsigned char perKey = 0;
	unsigned char _getKey = KEY_NULL;

	static unsigned char Combo_mode_En = 0;

	_getKey = Global_KeyValue;
	if(_getKey == KEY_NULL) Combo_mode_En = 0;

	if(_getKey != perKey)
	{
		KeyloopCnt = 0;  //轮询计数清空
		perKey = _getKey;
	}
	else
	{
		if(_getKey != KEY_NULL && 
				KeyloopCnt > 40 && 
				Combo_mode_En == 0) //40*50Ms = 2S 长按保存2S进入连击事件
		{
			Combo_mode_En = 1;
		}

		if(Combo_mode_En && KeyloopCnt> 2 ) //连击事件频率 5*50ms
		{
			KeyloopCnt = 0;
		}
		else
		{
			_getKey = KEY_NULL;
		}
			
	}

	if(_getKey != KEY_NULL)
	{
		Beep_On(20);
	}
	
	return _getKey;
}


//此函数被定时器间断性调用。常规定义为50ms轮询一次
unsigned char Keypad_Loop(void)
{
	// static unsigned int loopCnt = 0;
	static unsigned char perKey = 0;
	unsigned char keyValue = KEY_NULL; //空按键值
	unsigned char keyRow,keyCol;
		/**以下为保存数码管状态**/
		unsigned char p0buf,p2buf;
		P15 = 1;
		p2buf = P2;
		p0buf = P0;
		P0 = 0x00;
		/**end**/
	
	//低四位开漏模式
	P2M1 = 0x0f;
	P2M0 = 0x0f;
	//高四位输出1，低四位输出0
	KeyPad_Port = 0xf0;
	//读取高四位管脚值，判断按键在哪行。
	KDelay1ms();
	keyRow =((~KeyPad_Port>>4) & 0x0f);
	if(keyRow != 0)
	{
		KDelay1ms();
		//按键扫描消抖
		if(keyRow == ((~KeyPad_Port>>4) & 0x0f)) 
		{
				//高四位设为开漏模式
				P2M1 = 0xf0;
				P2M0 = 0xf0;
				//高四位输出0，低四位输出1
				KeyPad_Port = 0x0f;
				KDelay1ms();
				keyCol = (~(KeyPad_Port) & 0x0f);
				if(keyCol != 0)
				{
					switch(keyCol){
						case 0x01:
							keyCol = 3;
						break;
						case 0x02:
							keyCol = 2;
						break;
						case 0x04:
							keyCol = 1;
						break;
						case 0x08:
							keyCol = 0;
						break;
					}
					switch(keyRow){
						case 0x01:
							keyRow = 3;
						break;
						case 0x02:
							keyRow = 2;
						break;
						case 0x04:
							keyRow = 1;
						break;
						case 0x08:
							keyRow = 0;
						break;
					}
					keyValue = keyCol+(keyRow*4);
					KeyloopCnt ++;  //轮询计数

					// //检测按键是否松开过
					// if(keyValue != perKey)
					// {//新按键
					// 	perKey = keyValue;
					// }
					// else
					// {//未松开过
					// 	keyValue = 0xff;  //强制送空按键值
					// }
				}
				else
				{
					keyValue = KEY_NULL;
					perKey = keyValue;
				}
		}
		else
		{
			keyValue = KEY_NULL;
			perKey = keyValue;
		}
	}
	else
	{
		keyValue = KEY_NULL;
		perKey = keyValue;
	}
	
	P2M1 = 0x00;
	P2M0 = 0x00;
	/**恢复数码管状态**/
	P0 = p0buf;
	P2 = p2buf;
	P15 = 0;
	/**end**/

	Global_KeyValue = keyValue;
	return keyValue;

}


//此函数被定时器间断性调用。
//
// unsigned char getKeypad(void)
// {
// 	static unsigned char perKey = 0;
// 	unsigned char keyValue=0xff; //空按键值
// 	unsigned char keyRow,keyCol;
// 		/**以下为保存数码管状态**/
// 		unsigned char p0buf,p2buf;
// 		P15 = 1;
// 		p2buf = P2;
// 		p0buf = P0;
// 		P0 = 0x00;
// 		/**end**/
	
// 	//低四位开漏模式
// 	P2M1 = 0x0f;
// 	P2M0 = 0x0f;
// 	//高四位输出1，低四位输出0
// 	KeyPad_Port = 0xf0;
// 	//读取高四位管脚值，判断按键在哪行。
// 	keyRow =((~KeyPad_Port>>4) & 0x0f);
// 	if(keyRow != 0)
// 	{
// 		KDelay1ms();
// 		//按键扫描消抖
// 		if(keyRow == ((~KeyPad_Port>>4) & 0x0f)) 
// 		{
// 				//高四位设为开漏模式
// 				P2M1 = 0xf0;
// 				P2M0 = 0xf0;
// 				//高四位输出0，低四位输出1
// 				KeyPad_Port = 0x0f;
// 				keyCol = (~(KeyPad_Port) & 0x0f);
// 				if(keyCol != 0)
// 				{
// 					switch(keyCol){
// 						case 0x01:
// 							keyCol = 3;
// 						break;
// 						case 0x02:
// 							keyCol = 2;
// 						break;
// 						case 0x04:
// 							keyCol = 1;
// 						break;
// 						case 0x08:
// 							keyCol = 0;
// 						break;
// 					}
// 					switch(keyRow){
// 						case 0x01:
// 							keyRow = 3;
// 						break;
// 						case 0x02:
// 							keyRow = 2;
// 						break;
// 						case 0x04:
// 							keyRow = 1;
// 						break;
// 						case 0x08:
// 							keyRow = 0;
// 						break;
// 					}
// 					keyValue = keyCol+(keyRow*4);
// 					//检测按键是否松开过
// 					if(keyValue != perKey)
// 					{//新按键
// 						perKey = keyValue;
// 					}
// 					else
// 					{//未松开过
// 						keyValue = 0xff;  //强制送空按键值
// 					}
// 				}
// 				else
// 				{
// 					keyValue = 0xff;
// 					perKey = keyValue;
// 				}
// 		}
// 		else
// 		{
// 			keyValue = 0xff;
// 			perKey = keyValue;
// 		}
// 	}
// 	else
// 	{
// 		keyValue = 0xff;
// 		perKey = keyValue;
// 	}
	
// 	P2M1 = 0x00;
// 	P2M0 = 0x00;
// 	/**恢复数码管状态**/
// 	P0 = p0buf;
// 	P2 = p2buf;
// 	P15 = 0;
// 	/**end**/
// 	return keyValue;

// }