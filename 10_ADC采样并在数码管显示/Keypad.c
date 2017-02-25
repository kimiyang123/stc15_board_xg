#include "keypad.h"
#include <intrins.h>

void KDelay1ms()		//@11.0592MHz
{
	unsigned char i, j;
	_nop_();
	_nop_();
	_nop_();
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}


unsigned char getKeypad(void)
{
	static unsigned char perKey = 0;
	unsigned char keyValue=0xff; //�հ���ֵ
	unsigned char keyRow,keyCol;
		/**����Ϊ���������״̬**/
		unsigned char p0buf,p2buf;
		P15 = 1;
		p2buf = P2;
		p0buf = P0;
		P0 = 0x00;
		/**end**/
	//����λ��©ģʽ
	P2M1 = 0x0f;
	P2M0 = 0x0f;
	//����λ���1������λ���0
	KeyPad_Port = 0xf0;
	//��ȡ����λ�ܽ�ֵ���жϰ��������С�
	keyRow =((~KeyPad_Port>>4) & 0x0f);
	if(keyRow != 0)
	{
		KDelay1ms();
		//����ɨ������
		if(keyRow == ((~KeyPad_Port>>4) & 0x0f)) 
		{
				//����λ��Ϊ��©ģʽ
				P2M1 = 0xf0;
				P2M0 = 0xf0;
				//����λ���0������λ���1
				KeyPad_Port = 0x0f;
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
					//��ⰴ���Ƿ��ɿ���
					if(keyValue != perKey)
					{//�°���
						perKey = keyValue;
					}
					else
					{//δ�ɿ���
						keyValue = 0xff;  //ǿ���Ϳհ���ֵ
					}
				}
				else
				{
					keyValue = 0xff;
					perKey = keyValue;
				}
		}
		else
		{
			keyValue = 0xff;
			perKey = keyValue;
		}
	}
	else
	{
		keyValue = 0xff;
		perKey = keyValue;
	}
	
	P2M1 = 0x00;
	P2M0 = 0x00;
	/**�ָ������״̬**/
	P0 = p0buf;
	P2 = p2buf;
	P15 = 0;
	/**end**/
	return keyValue;
	

}