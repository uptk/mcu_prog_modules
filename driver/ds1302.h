#ifndef _DS1302_H_
#define _DS1302_H_

#ifdef DS_GLOBALS
#define DS_EXT 
#else 
#define DS_EXT  extern
#endif

#include <common.h>
//

#if 0
#define	DS1302_SDA_OUT_MODE()		do{PC_DDR |= BIT5;PC_CR1 |= BIT5;PC_CR2 &= ~BIT5;}while(0)
#define	DS1302_SDA_OUT_H()			do{PC_ODR |= BIT5;}while(0)
#define	DS1302_SDA_OUT_L()			do{PC_ODR &= ~BIT5;}while(0)
#define	DS1302_SDA_IN_MODE()		do{PC_DDR &= ~BIT5;PC_CR1 |= BIT5;PC_CR2 &= ~BIT5;}while(0)
#define	DS1302_SDA_IN()				((PC_IDR&BIT5)==BIT5)

#define	DS1302_SCL_OUT_MODE()		do{PC_DDR |= BIT6;PC_CR1 |= BIT6;PC_CR2 &= ~BIT6;}while(0)
#define	DS1302_SCL_OUT_H()			do{PC_ODR |= BIT6;}while(0)
#define	DS1302_SCL_OUT_L()			do{PC_ODR &= ~BIT6;}while(0)

#define	DS1302_RST_OUT_MODE()		do{PC_DDR |= BIT4;PC_CR1 |= BIT4;PC_CR2 &= ~BIT4;}while(0)
#define	DS1302_RST_OUT_H()			do{PC_ODR |= BIT4;}while(0)
#define	DS1302_RST_OUT_L()			do{PC_ODR &= ~BIT4;}while(0)
#else
#define	DS1302_SDA_OUT_MODE()		do{P10_Quasi_Mode;}while(0)
#define	DS1302_SDA_OUT_H()			do{P10=1;}while(0)
#define	DS1302_SDA_OUT_L()			do{P10=0;}while(0)
#define	DS1302_SDA_IN_MODE()		do{P10_Quasi_Mode;P10=1;}while(0)
#define	DS1302_SDA_IN()				P10

#define	DS1302_SCL_OUT_MODE()		do{P00_Quasi_Mode;}while(0)
#define	DS1302_SCL_OUT_H()			do{P00=1;}while(0)
#define	DS1302_SCL_OUT_L()			do{P00=0;}while(0)

#define	DS1302_RST_OUT_MODE()		do{P11_Quasi_Mode;}while(0)
#define	DS1302_RST_OUT_H()			do{P11=1;}while(0)
#define	DS1302_RST_OUT_L()			do{P11=0;}while(0)
#endif

#define WRITE_DS1302_SEC 0x80
#define READ_DS1302_SEC 0x81
#define WRITE_DS1302_MIN 0x82
#define READ_DS1302_MIN 0x83
#define WRITE_DS1302_HOUR 0x84
#define READ_DS1302_HOUR 0x85
#define WRITE_DS1302_DAY 0x86
#define READ_DS1302_DAY 0x87
#define WRITE_DS1302_MONTH 0x88
#define READ_DS1302_MONTH 0x89
#define WRITE_DS1302_WEEK 0x8A
#define READ_DS1302_WEEK 0x8B
#define WRITE_DS1302_YEAR 0x8C
#define READ_DS1302_YEAR 0x8D
#define WRITE_DS1302_PROTECT 0x8E
#define READ_DS1302_PROTECT 0x8F
#define WRITE_DS1302_BURSTCLOCK 0xBE
#define READ_DS1302_BURSTCLOCK 0xBF
#define WRITE_DS1302_BURSTRAM 0xFE
#define READ_DS1302_BURSTRAM 0xFF



DS_EXT  void  	DS1302IO_Init(void);
DS_EXT	u8      DS1302Read(u8 cmd);
DS_EXT  u8		  DS1302ReadByte(void);
DS_EXT	void    DS1302Write(u8 cmd,u8 dat);
DS_EXT  void		DS1302WriteByte(u8 dat);
//DS_EXT  void		DS1302_burst_Read(u8 *rstr);
//DS_EXT  void		DS1302_burst_Write(u8 *wstr);
DS_EXT  void	DS1302_SetTime(u8 sec,u8 min,u8 hour);
extern u8 dec2bcd(u8 dec);
extern u8 bcd2dec(u8 bcd);

#endif
