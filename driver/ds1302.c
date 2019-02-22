#include "common.h"
#include "ds1302.h"

#define	DS1302_DELAY()		delay_us(1)


/*
dec 0~99
*/
u8 dec2bcd(u8 dec)
{
	u8 bcd = dec%10;
	dec/=10;
	bcd |= dec<<4;
	return bcd;
}

u8 bcd2dec(u8 bcd)
{
	u8 b10=bcd>>4;
	u8 b1=bcd&0x0f;
	if((b10<=9)&&(b1<=9)){
		return (b10*10+b1);
	}
	return 100;
}




/*******************************************
;void	DS1302IO_Init(void);
;
*******************************************/
void	DS1302IO_Init(void)
{
	//RST
	DS1302_RST_OUT_MODE();
	DS1302_RST_OUT_L();
	DS1302_DELAY();
	//SCLK
	DS1302_SCL_OUT_MODE();
	DS1302_SCL_OUT_L();
	//SDA
	DS1302_SDA_OUT_MODE();
	DS1302_SDA_OUT_L();
#if 0	
	if((DS1302Read(READ_DS1302_SEC)&0x80)==0x80)//时钟停止
	{
		DS1302Write(0x8e,0x00);//写保护关
		DS1302Write(WRITE_DS1302_SEC,0);
		DS1302Write(0X8E,0X80);
	}
#endif
}
/*******************************************
;void	DS1302_Init(void);
;
*******************************************/
void	DS1302_SetTime(u8 sec,u8 min,u8 hour)
{
	sec = dec2bcd(sec);
	min = dec2bcd(min);
	hour = dec2bcd(hour);
	DS1302Write(0x8e,0x00);//写保护关
	DS1302Write(WRITE_DS1302_SEC,sec);
	DS1302Write(WRITE_DS1302_MIN,min);
	DS1302Write(WRITE_DS1302_HOUR,hour);
//	DS1302Write(WRITE_DS1302_DAY,0x25);
//	DS1302Write(WRITE_DS1302_MONTH,0x12);
//	DS1302Write(WRITE_DS1302_YEAR,0x10);
//	DS1302Write(WRITE_DS1302_WEEK,0x06);
//	DS1302Write(0X90,0X01);
//	DS1302Write(0XC0,0XF0);
	DS1302Write(0X8E,0X80);
}

/***********************************************
before:
RST	OUT		0
SDA	OUT		x
SCL	OUT		0
after:
RST	OUT		0
SDA	OUT		x
SCL	OUT		0
***********************************************/
u8 DS1302Read(u8 cmd)
{
	u8 dat;
	DS1302_RST_OUT_H();
	DS1302_DELAY();
	DS1302WriteByte(cmd);
	DS1302_SDA_IN_MODE();
	dat = DS1302ReadByte();
	DS1302_SDA_OUT_MODE();
	DS1302_RST_OUT_L();
	DS1302_DELAY();
	return dat;
}
/*********************************************
before:
RST	OUT		0
SDA	OUT		x
SCL	OUT		0
after:
RST	OUT		0
SDA	OUT		x
SCL	OUT		0
*********************************************/
void DS1302Write(u8 cmd,u8 dat)
{
	DS1302_RST_OUT_H();
	DS1302_DELAY();
	DS1302WriteByte(cmd);
	DS1302WriteByte(dat);
	DS1302_RST_OUT_L();
	DS1302_DELAY();
}




/********************************************
before:
RST	OUT		1
SDA	OUT		x
SCL	OUT		0
after:
RST	OUT		1
SDA	OUT		x
SCL	OUT		0
********************************************/
void DS1302WriteByte(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		if(dat&0x01){
			DS1302_SDA_OUT_H();
		}else{
			DS1302_SDA_OUT_L();
		}
		DS1302_DELAY();
		DS1302_SCL_OUT_H();
		DS1302_DELAY();
		DS1302_SCL_OUT_L();
		DS1302_DELAY();
		dat>>=1;
	}
}
/*******************************************
before:
RST	OUT		1
SDA	IN		
SCL	OUT		0
after:
RST	OUT		1
SDA	IN		
SCL	OUT		0

*******************************************/
u8 DS1302ReadByte(void)
{
	u8 i, dat;
	for(i=0;i<8;i++)
	{
		dat>>=1;
		if(DS1302_SDA_IN())
		{
			dat|=0x80;
		}
		DS1302_SCL_OUT_H();
		DS1302_DELAY();
		DS1302_SCL_OUT_L();
		DS1302_DELAY();
	}
	return dat;
}
/*******************************************
;void DS1302_brust_Read(u8 *rstr);
;
*******************************************/
/*
void DS1302_brust_Read(u8 *rstr)
{
	u8 i;
	DS1302_RSTOUT = 0;
	DS1302_SCLKOUT = 0;
	DS1302_RSTOUT = 1;
	DS1302WriteByte(0xff);
	for(i=0;i<31;i++)
	{
		*rstr = DS1302ReadByte();
		rstr++;
	}
	DS1302_RSTOUT = 0;
	DS1302_SCLKOUT = 1;
}
*/
/*******************************************
;void DS1302_brust_Write(u8 *wstr);
;
*******************************************/
/*
void DS1302_brust_Write(u8 *wstr)
{
	u8 i;
	u8 *tmpstr;
	tmpstr = wstr;
	DS1302Write(0x8e,0x00);//写保护关
	DS1302_RSTOUT = 0;
	DS1302_SCLKOUT = 0;
	DS1302_RSTOUT = 1;
	DS1302WriteByte(0xfe);
	for(i=0;i<31;i++)
	{
		DS1302WriteByte(*tmpstr);
		tmpstr++;
	}
	DS1302_RSTOUT = 0;
	DS1302_SCLKOUT = 1;
	DS1302Write(0x8e,0x80);//写保护开
}
*/


