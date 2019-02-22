#ifndef __drv_kkg_h__
#define	__drv_kkg_h__

#include "common.h"

#define	KKG_GpioConfig()
#define	KKG_INACT()
#define	KKG_ACT()

#define	ZC_GpioConfig()
#define	ZC_EXTI_ON()
#define	ZC_EXTI_OFF()
#define	ZC_IN()

#define TIMKKG_Config()
#define	TIMKKG_FLAG_Update
#define	TIMKKG_IT_Update
#define	TIMKKG_GetCounter()
#define	TIMKKG_SetCounter(Counter)
#define	TIMKKG_GetAutoreload()
#define	TIMKKG_SetAutoreload(Autoreload)
#define	TIMKKG_ARRPreloadConfig(NewState)
#define	TIMKKG_ClearFlag(TIM_FLAG)
#define TIMKKG_GetFlagStatus(TIM_FLAG)
#define	TIMKKG_ITConfig(NewState)
#define	TIMKKG_Cmd(NewState)

#define	ZC0_DELAY			// 1ms
#define	ZC_TIMEOUT			// 40ms
#define	isACPeriod()		// 10ms ~ 30ms
#define	KKG_TRIG_DELAY		// 1ms

#define	isNeedTrig()

extern volatile u16 zc_period;
extern void zc_1ms_run(void);
extern void zc_exti_run(void);
extern void zc_timer_run(void);
extern void kkg_init(void);

#endif /* __drv_kkg_h__ */

