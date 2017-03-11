#include <STC15f2K60S2.h>
#include <intrins.h>
#include "src/DS1302.h"
#include "src/SegLED.h"
#include "src/sys_time.h"
#include "src/Keypad.h"


void Timer0Init(void);
// void SettingTime(unsigned char nowtime);
unsigned char EnterNum(unsigned char defNum,unsigned char numBit,unsigned char showONbit,
                        unsigned char MinNum,unsigned char MaxNum);


void ShowTimeOnLED(str_Time _Time)
{
    LED_Show_int(_Time.Hour,0,2);
    LED_Show_int(_Time.Minute,3,2);
    LED_Show_int(_Time.Second,6,2);
    DispBuf[2] = 0x40;
    DispBuf[5] = 0x40;
}

int main()
{
    unsigned char schang=0;
    unsigned long enterTicks = 0;

    str_Time myTime; //定义时间类型结构体
    str_Day myDay; //定义日期类型结构体

    unsigned char state = 0;
    unsigned char perState =0xff;
    unsigned char num=0;

    P4M0 = 0x00;
    P4M1 = 0x01;
    BeepPin = 0; //蜂鸣器关闭

    DelayMs(1000);

    P4M0 = 0x00;
    P4M1 = 0x00;

    Ds1302_Init();
    SegLED_Init();
    Timer0Init();

    myTime = Get_Time();
    myDay = Get_Day();

    // myTime.Second = 00;
    // myTime.Minute = 44;
    // myTime.Hour = 8;

    // myDay.Year=17;
    // myDay.Month = 03;
    // myDay.Date = 04;
    // myDay.Day = Sun ;
    
    EA = 1;

    // while (1)
    // {
    //     //LED_Show_int(ticks/100,0,3);
    //     num = Keypad_Loop();
    //     if(num != KEY_NULL)
    //     {
    //         LED_Show_int(num,5,3);
    //     }
    // }

    while (1)
    {
        
        switch (state)
        {
            case 0: //显示时间
                if(perState != state)
                {
                    perState = state;
                    LED_Show_Clear();
                    enterTicks = ticks;
                    ShowTimeOnLED(myTime);
                }

                // num = GetKey();
                // if(num != KEY_NULL)
                // {
                //     LED_Show_int( num,0,3 );
                //     //Beep_On(20);
                // }
                    

                if(ticks % 100 == 0 )
                {
                    myTime = Get_Time();
                    ShowTimeOnLED(myTime);
                    // LED_Show_int(myTime.Hour,0,2);
                    // LED_Show_int(myTime.Minute,3,2);
                    // LED_Show_int(myTime.Second,6,2);
                }

                if ( ticks - enterTicks >= 60000)
                {
                    state = 1;
                }

                switch (GetKey())
                {
                    case KEY_OK:
                        state = 2; 
                    break;
                    case KEY_D:
                        state = 1;  //显示日期
                    break;
                default:
                    break;
                }

            break;

            case 1: //显示日期
                 if(perState != state)
                {
                    enterTicks = ticks;
                    perState = state;
                    LED_Show_Clear();
                    myDay = Get_Day();
                    LED_Show_int(myDay.Year ,0,2);
                    LED_Show_int(myDay.Month,3,2);
                    LED_Show_int(myDay.Date,6,2);
                }

                if (ticks - enterTicks >= 5000)
                {
                    state = 0;
                }


                switch (GetKey())
                {
                    case KEY_OK:
                        state = 2; 
                    break;
                    case KEY_D:
                        state = 0;  //显示日期
                    break;
                default:
                    break;
                }

            break;

            case 2:  //修改时钟模式
                
                if(perState != state)
                {
                    // key = KEY_NULL;
                    perState = state;
                    LED_Show_Clear();
                    ShowTimeOnLED(myTime);
                    // LED_Show_int(myTime.Hour,0,2);
                    // LED_Show_int(myTime.Minute,3,2);
                    // LED_Show_int(myTime.Second,6,2);

                    myTime.Hour = EnterNum(myTime.Hour,2,0,0,23);
                    //LED_Show_Clear();
                    myTime.Minute = EnterNum(myTime.Minute,2,3,0,59);
                    //LED_Show_Clear();
                    myTime.Second = EnterNum(myTime.Second,2,6,0,59);
                    set_Time(myTime);
                }

                state = 3;

            
            break;

            case 3: //修改日期模式
                if(perState != state)
                {
                    perState = state;

                    LED_Show_Clear();
                    LED_Show_int(myDay.Year ,0,2);
                    LED_Show_int(myDay.Month,3,2);
                    LED_Show_int(myDay.Date,6,2);
                    myDay.Year = EnterNum(myDay.Year,2,0,0,99);
                    //LED_Show_Clear();
                    myDay.Month = EnterNum(myDay.Month,2,3,1,12);
                    //LED_Show_Clear();
                    myDay.Date = EnterNum(myDay.Date,2,6,1,31);
                    set_Day(myDay);
                }

                state = 0;

            break;

            default:
            break;
        }
        
    }
    
    
} 


unsigned char EnterNum(unsigned char defNum,unsigned char numBit,unsigned char showONbit,
                        unsigned char MinNum,unsigned char MaxNum)
{
    unsigned char i=0;
    unsigned char _keynow;
    for ( i = showONbit; i < numBit+showONbit; i++)
    {
        LED_Flash_Ctrl_ON(1<<(7-i));
    }
    if(defNum<MinNum) defNum = MinNum;
    else if(defNum>MaxNum) defNum = MaxNum;

    LED_Show_int(defNum ,showONbit,numBit);

    _keynow = GetKey();
    while(_keynow != KEY_OK)
    {
        _keynow = GetKey();
        switch (_keynow)
        {
            case KEY_A:
                if(++defNum>MaxNum) defNum = MinNum;
                LED_Show_int(defNum ,showONbit,numBit);
                // key = KEY_NULL;
            break;
            case KEY_B:
                if(defNum-- <= MinNum) defNum = MaxNum;
                LED_Show_int(defNum ,showONbit,numBit);
                // key = KEY_NULL;
            break;
            case KEY_OK:

            break;
            default:
                
            break;
        }  

    }
    // key = KEY_NULL;
    LED_Flash_Clear();
    return defNum;
}

