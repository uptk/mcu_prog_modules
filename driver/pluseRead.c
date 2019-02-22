#include "common.h"
#include "pluseRead.h"

volatile u16 pluse_high;
volatile u16 pluse_low;
volatile u16 pluse_duty;
volatile u16 pluse_period;
volatile u16 pluse_freq;
volatile u8 pluseRead_sta;

#define PluseRead_IN()

#define TIMPluseRead_Config()
#define	TIMPluseRead_FLAG_Update
#define	TIMPluseRead_IT_Update
#define	TIMPluseRead_GetCounter()
#define	TIMPluseRead_SetCounter(Counter)
#define	TIMPluseRead_GetAutoreload()
#define	TIMPluseRead_SetAutoreload(Autoreload)
#define	TIMPluseRead_ARRPreloadConfig(NewState)
#define	TIMPluseRead_ClearFlag(TIM_FLAG)
#define TIMPluseRead_GetFlagStatus(TIM_FLAG)
#define	TIMPluseRead_ITConfig(NewState)
#define	TIMPluseRead_Cmd(NewState)

void pluseRead_exti_run(void)
{
    static u16 ht;
    u16 cntr = TIMPluseRead_GetCounter();


    if(pluseRead_sta)
    {
        if(PluseRead_IN())
        {
            pluse_at = ht+cntr;
            pluse_ht = ht;
        }else{
            ht = cntr;
        }
    }else{
        if(PluseRead_IN()){
            pluseRead_sta = 1;
            TIMPluseRead_SetCounter(0);
            TIMPluseRead_ClearFlag(TIMPluseRead_FLAG_Update);
            TIMPluseRead_Cmd(ENABLE);
        }
    }
}

void pluseRead_timer_run(void)
{
    
}
void pluseRead_init(void)
{
}
