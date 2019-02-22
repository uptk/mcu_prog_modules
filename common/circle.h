#ifndef	__CIRCLE_H__
#define	__CIRCLE_H__
#include "types.h"
#include "macros.h"


typedef struct{
	u16 * const buf;
	u8  const len;
	u8 	idx;
	u8	 n;
	u16 sum;
}circle_t;

extern u8 circle_next_idx(circle_t *d,u8 n);
extern u8 circle_prev_idx(circle_t *d,u8 n);
extern u16 circle_next(circle_t *d,u8 n);
extern u16 circle_prev(circle_t *d,u8 n);
extern u8 circle_in(circle_t *d,u16 dat);
extern void circle_init(circle_t *d);
extern u16 circle_max(circle_t *d);
extern u16 circle_min(circle_t *d);


#endif
