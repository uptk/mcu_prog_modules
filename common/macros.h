#ifndef	__macros_h__
#define __macros_h__

#include "types.h"

#define	BIT0			(1<<0)
#define	BIT1			(1<<1)
#define	BIT2			(1<<2)
#define	BIT3			(1<<3)
#define	BIT4			(1<<4)
#define	BIT5			(1<<5)
#define	BIT6			(1<<6)
#define	BIT7			(1<<7)

#define	BITX(n)		(1<<(((n)>=7)?7:(n)))

#define	arraySizeOf(a)		(sizeof(a)/(sizeof((a)[0])))

#define	N1(n)		(((n)>=8)?0xff:(u8)(((u16)1<<(n))-1))

#define	NULL			((void *)0)
#endif
