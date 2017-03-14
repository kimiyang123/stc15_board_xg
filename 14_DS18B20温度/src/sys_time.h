#ifndef _SYS_TIME_H_
#define _SYS_TIME_H_

    #include <STC15f2K60S2.h>
    #include <intrins.h>
    #include "segLED.h"

    extern volatile unsigned long ticks;

   #define BeepPin  P40

    void Timer0Init(void);
    
    void Beep_On(unsigned char beep_ms);

    void DelayMs(unsigned int Dtime);


#endif