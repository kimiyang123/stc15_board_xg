#ifndef _UART_H_
#define _UART_H_

	#include <STC15F2K60S2.H>
	
	void UartInit(void);
	void Uart_SendData(unsigned char dat);
	void Uart_SendString(char *s);


#endif