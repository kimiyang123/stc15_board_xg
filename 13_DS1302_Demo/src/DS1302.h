#ifndef __DS1302_H__
#define __DS1302_H__

    #include "STC15f2K60S2.h"
    #include <intrins.h>

// DS1302管脚定义
    #define DS_DAT  P41
    #define DS_CLK  P43
    #define DS_CE   P42

   //                       write address 
    #define DS1302_ADDR_SECONDS     0X80
    #define DS1302_ADDR_MINUTES     0X82
    #define DS1302_ADDR_HOUR        0X84
    #define DS1302_ADDR_DATE        0X86
    #define DS1302_ADDR_MONTH       0X88
    #define DS1302_ADDR_DAY         0X8A
    #define DS1302_ADDR_YEAR        0X8C

    #define DS1302_ADDR_WRITE_PROTECT     0X8E
    #define DS1302_ADDR_TCSDS       0X90

    #define WRITE_PROTECT_Enable    0x80
    #define WRITE_PROTECT_Disable   0x00

    typedef struct
    {
        unsigned char Year;
        unsigned char Month;
        unsigned char Date;   
        unsigned char Day; //周
    }str_Day;

    typedef struct 
    {
        unsigned char Hour;
        unsigned char Minute;
        unsigned char Second;
    }str_Time;

    enum Week_Enum
    {
        Mon = 1,
        Tues,
        Wed,
        Thurs,
        Fri,
        Sat,
        Sun
    };

    void Ds1302_Init();

    void Ds_Write(unsigned char Addr,unsigned char dat);
    unsigned char Ds_Read(unsigned char Addr);

    str_Day Get_Day();
    str_Time Get_Time();

    void set_Day( str_Day _setDay );
    void set_Time(str_Time _setTime);



#endif