#ifndef	__queue_h__
#define	__queue_h__

#include "types.h"
#include "macros.h"

typedef struct{
	volatile u8 * const buf;
	u8 const len;
	volatile u8 front;
	volatile u8 rear;
}queue_t;

extern void inQ(queue_t *q,u8 d);
extern u8 outQ(queue_t *q);
extern void initQ(queue_t *q);
extern u8 is_emptyQ(queue_t *q);
extern u8 is_fullQ(queue_t *q);
#endif
