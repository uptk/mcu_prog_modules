#ifndef	__common_h__
#define	__common_h__

#include "types.h"
#include "macros.h"
#include <stm32f0xx.h>
#include <stdio.h>
#include "circle.h"
#include "queue.h"

extern void nopDelay(u8 val);
extern	void  delay_us(u8 us);
extern	void delay_ms(u8 ms);
extern void swap8(u8 *buf);
extern u8 checkSum(u8 *s,u8 n);
extern u8 cal_1(u8 val);
extern u8 tryGetInc(u8 rold,u8 rnew);
extern u8 binSearch16(u16 const *a,u8 len,u16 ele);
extern u8 binSearch(u8 const *a,u8 len,u8 ele);
extern u8 nearBinSearch16(u16 const *a,u8 len,u16 ele);
extern u8 nearBinSearch(u8 const *a,u8 len,u8 ele);
extern	u8 n_of(u8 *buf,u8 len,u8 n);
extern	u8 mid_of(u8 *buf,u8 len);
extern unsigned char ACRC[2];
extern void Acrc16(unsigned char *ptr,unsigned int len);



#endif
