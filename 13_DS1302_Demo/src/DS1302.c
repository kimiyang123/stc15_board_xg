
#include "DS1302.h"

void Ds_WriteByte(unsigned char dat)
{
    unsigned char i=0;
    // DS_CE = 1; //Control it in Write() function
    DS_CLK = 0;
    DS_DAT = 0;
    for ( i = 0; i < 8; i++)
    {
        DS_CLK = 0;
        if( (dat >> i)&0x01 == 1)
        {
            DS_DAT = 1;
        }
        else
        {
            DS_DAT = 0;
        }
        DS_CLK = 1;
        _nop_();
    }

}

unsigned char Ds_ReadByte()
{
    unsigned char i=0;
    unsigned char recDat = 0;
    unsigned char tmp =0;
    for ( i = 0; i < 8; i++)
    {
        DS_CLK = 0; //data will out on CLK push down 
        recDat >>= 1;
        tmp = DS_DAT;
        recDat |= (tmp<<7) & 0x80; 
        DS_CLK = 1;
        _nop_();
    }
    
    return recDat;
}

void Ds_Write(unsigned char Addr,unsigned char dat)
{
    Addr &= 0xFE; //写地址最低位为0
    DS_CE = 1;
    Ds_WriteByte(Addr);
    Ds_WriteByte(dat);
    DS_CE = 0;
}

unsigned char Ds_Read(unsigned char Addr)
{
    unsigned char temp = 0;
    Addr |= 0x01; // 读地址最低位为1
    DS_CE = 1;
    Ds_WriteByte(Addr);
    temp = Ds_ReadByte();
    DS_CE = 0;

    return temp;
}

void Ds1302_Init()
{
    Ds_Write(DS1302_ADDR_WRITE_PROTECT,WRITE_PROTECT_Disable );
    Ds_Write(DS1302_ADDR_TCSDS,0xA7);
    Ds_Write(DS1302_ADDR_WRITE_PROTECT,WRITE_PROTECT_Enable );
    
}

unsigned char  BCD2Hex(unsigned char BCD)
{
    return ((BCD>>4) & 0x0f)*10+(BCD & 0x0f);
}

unsigned char Hex2BCD(unsigned char Hex)
{
    unsigned char tmp =0;

    tmp =  (Hex%10) + (((Hex/10)&0x0f)<<4);
		
    return tmp;
}

// ****************BLL**********************

str_Day Get_Day()
{
    str_Day _daynow;
    _daynow.Year = BCD2Hex( Ds_Read(DS1302_ADDR_YEAR) );
    _daynow.Month = BCD2Hex( Ds_Read(DS1302_ADDR_MONTH) );
    _daynow.Date = BCD2Hex( Ds_Read(DS1302_ADDR_DATE) );

    _daynow.Day = BCD2Hex( Ds_Read(DS1302_ADDR_DAY) );


   return _daynow;
}

str_Time Get_Time()
{
    str_Time _timenow;

   _timenow.Second = BCD2Hex(Ds_Read(DS1302_ADDR_SECONDS) & 0x7f);
   _timenow.Minute = BCD2Hex(Ds_Read(DS1302_ADDR_MINUTES) & 0x7f);
   _timenow.Hour = BCD2Hex(Ds_Read(DS1302_ADDR_HOUR) & 0x3f);
    
   return _timenow;
}

void set_Day( str_Day _setDay )
{
    Ds_Write( DS1302_ADDR_WRITE_PROTECT,WRITE_PROTECT_Disable );

    Ds_Write( DS1302_ADDR_YEAR ,Hex2BCD(_setDay.Year ) );
    Ds_Write( DS1302_ADDR_MONTH ,Hex2BCD(_setDay.Month ) );
    Ds_Write( DS1302_ADDR_DATE ,Hex2BCD(_setDay.Date ) );

    Ds_Write( DS1302_ADDR_DAY ,Hex2BCD(_setDay.Day ) );

    Ds_Write( DS1302_ADDR_WRITE_PROTECT,WRITE_PROTECT_Enable );
    
}


void set_Time(str_Time _setTime)
{
    Ds_Write( DS1302_ADDR_HOUR,Hex2BCD(_setTime.Hour) );
    Ds_Write( DS1302_ADDR_MINUTES,Hex2BCD(_setTime.Minute) );
    Ds_Write( DS1302_ADDR_SECONDS,Hex2BCD(_setTime.Second) );

}

