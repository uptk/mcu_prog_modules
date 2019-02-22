#ifndef __otherDev_h__
#define __otherDev_h__

#include "common.h"

/*  key     */

#define KEY_NULL              0
#define	isKeyHappen()		((key_vc != KEY_NULL)||(key_vp != KEY_NULL))
#define	isKeyPrs(n)			((key_vp==KEY_NULL) && (key_vc==(n)))
#define	isKeyRel(n)			((key_vp==(n)) && (key_vc==KEY_NULL))
#define	isKeyPrsAt(n,t)		((key_vc==(n)) && (key_lp_Time == (t)))
#define	isKeyRelLess(n,t)	(isKeyRel(n) && (key_lp_Time < (t)))
extern void key_10ms_run(void);
extern void key_init(void);

#endif /* __otherDev_h__ */
