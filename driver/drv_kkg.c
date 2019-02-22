#include "common.h"
#include "drv_kkg.h"


static volatile u8 zc_sta;
static volatile u8 zc_delay;
static volatile u8 zc_level;
static volatile u16 zc_temp_cntr;
volatile u16 zc_period;

void zc_1ms_run(void)
{
	if(zc_delay<100){
		zc_delay++;
		if(zc_delay==2){
			zc_level = ZC_IN();
			ZC_EXTI_ON();
		}
	}

}

void zc_exti_run(void)
{
	ZC_EXTI_OFF();
	zc_delay = 0;

	if(!zc_level){//上升沿
		u16 cntr = TIMKKG_GetCounter();
		TIMKKG_SetCounter(0);	
		if(zc_sta==4 //&&
           // (!TIMKKG_GetFlagStatus(TIMKKG_FLAG_Update))
		){
			zc_temp_cntr += cntr;
			zc_period = zc_temp_cntr;
		}else{
			zc_period = 0;
		}
		if(isACPeriod(zc_period)){
			zc_sta = 0;
			TIMKKG_SetAutoreload(ZC0_DELAY);
		}else{
			zc_sta = 4;
			TIMKKG_SetAutoreload(ZC_TIMEOUT);
		}
		KKG_INACT();
		zc_temp_cntr =0;
		TIMKKG_ClearFlag(TIMKKG_FLAG_Update);
		TIMKKG_Cmd(ENABLE);
	}
}

void zc_timer_run(void)
{
	TIMKKG_ClearFlag(TIMKKG_FLAG_Update);
	zc_temp_cntr+=TIMKKG_GetAutoreload();
	switch(zc_sta)
	{
	case 0://第1个过零
		if(isNeedTrig()){
			zc_sta = 1;
			KKG_ACT();
			TIMKKG_SetAutoreload(KKG_TRIG_DELAY);
		}else{
			zc_sta = 2;
			TIMKKG_SetAutoreload(zc_period/2);
		}
		break;
	case 1://触发KKG_TRIG_DELAY后恢复
		KKG_INACT();
		TIMKKG_SetAutoreload(zc_period/2-KKG_TRIG_DELAY);
		zc_sta = 2;
		break;
	case 2://第2个过零
		if(isNeedTrig()){
			zc_sta = 3;
			KKG_ACT();
			TIMKKG_SetAutoreload(KKG_TRIG_DELAY);
		}else{
			zc_sta = 4;
			TIMKKG_SetAutoreload(ZC_TIMEOUT);
		}
		break;
	case 3://触发KKG_TRIG_DELAY后恢复
		KKG_INACT();
		TIMKKG_SetAutoreload(ZC_TIMEOUT);
		zc_sta = 4;
		break;
	case 4://等待超时
		zc_period = 0;
		zc_sta = 5;
	default:
		KKG_INACT();
		TIMKKG_Cmd(DISABLE);
		break;
	}
}
	
void kkg_init(void)
{
	KKG_GpioConfig();
	ZC_GpioConfig();
	TIMKKG_Config();
	KKG_INACT();
	ZC_EXTI_OFF();
	zc_delay = 0;
	zc_period = 0;
	zc_temp_cntr = 0;
	zc_sta = 0xff;
	TIMKKG_ARRPreloadConfig(DISABLE);
	TIMKKG_SetAutoreload(ZC_TIMEOUT);
	TIMKKG_SetCounter(0);	
	TIMKKG_ClearFlag(TIMKKG_FLAG_Update);
	TIMKKG_ITConfig(TIMKKG_IT_Update,ENABLE);
	TIMKKG_Cmd(DISABLE);
}

