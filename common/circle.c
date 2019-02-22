#include "types.h"
#include "macros.h"
#include "circle.h"

u8 circle_next_idx(circle_t *d,u8 n)
{
	u8 idx = n + d->idx;
	while(idx >= d->len){
		idx -= d->len;
	}
	return idx;
}
u8 circle_prev_idx(circle_t *d,u8 n)
{
	u8 idx = d->idx;
	while(n > idx){
		idx += d->len;
	}
	return (idx - n);
}
u16 circle_next(circle_t *d,u8 n)
{
	return d->buf[circle_next_idx(d,n)];
}
u16 circle_prev(circle_t *d,u8 n)
{
	return d->buf[circle_prev_idx(d,n)];
}
void circle_init(circle_t *d)
{
	d->idx = d->n = 0;
	d->sum = 0;
}
u8 circle_in(circle_t *d,u16 dat)
{
	d->idx = circle_next_idx(d,1);
	if(d->n >= d->len){
		d->sum -= d->buf[d->idx];
	}else
		d->n++;
	d->sum += d->buf[d->idx] = dat;
	return d->idx;
}

u16 circle_max(circle_t *d)
{
	u8 i = 0;
	u16 max = 0;
	while(i < d->n){
		u16 val = circle_prev(d,i);
		if(max < val){
			max = val;
		}
		i++;
	}
	return max;
}
u16 circle_min(circle_t *d)
{
	u8 i = 0;
	u16 min = 0xffff;
	while(i < d->n){
		u16 val = circle_prev(d,i);
		if(min > val){
			min = val;
		}
		i++;
	}
	return ((i==0)?0:min);
}
