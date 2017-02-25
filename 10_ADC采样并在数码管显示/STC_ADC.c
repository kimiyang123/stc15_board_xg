
#include "STC_ADC.h"


#define ADC_START  0x08
void InitADC()
{
	P1ASF = 0x00;
	ADC_RES = 0;
	ADC_CONTR = 0x84;//10000100
}


unsigned int get_ADC(char cs)
{
	unsigned int ADC_V;
	P1ASF = (1<<cs);
	ADC_CONTR &= 0xf0;
	ADC_CONTR |= ADC_START|(cs&0x07);
	while(!(ADC_CONTR&0x10));
	
	ADC_V = ADC_RES;
	ADC_V = (ADC_V<<2)|(ADC_RESL & 0x03);
	
	ADC_CONTR &= ~(1<<4);
	
	return ADC_V;	
}
