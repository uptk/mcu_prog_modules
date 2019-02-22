#include "types.h"
#include "macros.h"
#include "queue.h"


#define	moveNext(i,len)		((((i)+1)>=(len))?0:((i)+1))
void inQ(queue_t *q,u8 d)
{
	if(!is_fullQ(q)){
		q->buf[q->front] = d;
		q->front = moveNext(q->front,q->len);
	}
}
u8 outQ(queue_t *q)
{
	u8 ret = 0;
	if(!is_emptyQ(q)){
		ret = q->buf[q->rear];
		q->rear = moveNext(q->rear,q->len);
	}
	return ret;
}

void initQ(queue_t *q)
{
	q->front = q->rear = 0;
}
u8 is_emptyQ(queue_t *q)
{
	return (q->front == q->rear);
}
u8 is_fullQ(queue_t *q)
{
	return (moveNext(q->front,q->len) == q->rear);
}
