#ifndef	__TYPES_H__
#define	__TYPES_H__

typedef	unsigned char u8;
typedef	signed char s8;

typedef	unsigned short u16;
typedef	signed short s16;

typedef	unsigned long u32;
typedef	signed long s32;

typedef	volatile u8 reg8_t;

typedef struct{
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 1;
    u8 b4 : 1;
    u8 b5 : 1;
    u8 b6 : 1;
    u8 b7 : 1;
}BitField_T;


#endif
