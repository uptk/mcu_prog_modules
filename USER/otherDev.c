#include "common.h"
#include "otherDev.h"


/*  key     */
u8 key_p;
u8 key_f;
u8 key_vp;
u8 key_vc;
u16 key_lp_Time;


u8 get_key(void)
{
}
void keyScan_10ms_run(void)
{
    u8 ck = get_key();
    if(ck==key_p){
        if(key_f<3)
            key_f++;
        if(key_f>=3){
            key_vp = key_vc;
            key_vc = ck;
            if(key_vp!=key_vc){
                if(key_vc!=KEY_NULL){
                    key_lp_Time = 0;
                }
            }

        }
    }else{
        key_p = ck;
        key_f = 0;
    }
    if(key_vc!=KEY_NULL){
        if(key_lp_Time<0xffff){
            key_lp_Time++;
        }
    }
}

void key_10ms_run(void)
{
    keyScan_10ms_run();
    if(isKeyHappen()){
        
    }
        
}

void key_init(void)
{

}

/*	timer	*/
u8 timer_flag;//指示在哪个调时间阶段
u8 timer_timeout;// sec
xdata u8 h_mark;
xdata u8 m_mark;
bit fault_timer;
xdata u8 sec_test_mark;
xdata u8 t_test_timer;


void timer_init(void)
{
	u8 s,m,h;
	u8 ret=0;
	DS1302IO_Init();
	timer_flag = 0;
	h=DS1302Read(READ_DS1302_HOUR);
	m=DS1302Read(READ_DS1302_MIN);
	s=DS1302Read(READ_DS1302_SEC);

	h&=0xbf;
	m&=0x7f;

	if(s&0x80){
		ret=1;
		s&=0x7f;
	}
	s=bcd2dec(s);
	m=bcd2dec(m);
	
	if(h&0x80){
		ret=1;
		h&=0x3f;
		if(h&0x20){
			h&=0x1f;
			h=bcd2dec(h);
			h+=12;
		}else{
			h=bcd2dec(h);
		}
	}else{
		h=bcd2dec(h);
	}
	if((s>=60)||(m>=60)||(h>=24)){
		ret=1;
		s=0;
		m=0;
		h=0;
	}

	if(ret){
		DS1302_SetTime(s,m,h);
	}
	sys_h_cur = h_mark = h;
	sys_m_cur = m_mark = m;
	//sys_h_on	mem_init中初始化
	//sys_m_on	mem_init中初始化
	//sys_h_off	mem_init中初始化
	//sys_m_off	mem_init中初始化
	fault_timer = 0;
	sec_test_mark = s;
	t_test_timer = 3;
}

void timer_set(u8 s,u8 m,u8 h)
{
	DS1302_SetTime(s,m,h);
	m_mark=m;
	h_mark=h;
	
	t_test_timer = 3;
	sec_test_mark = s;
}
void timer_run(void)// 1s 执行一次
{

	u8 m_cur = bcd2dec(DS1302Read(READ_DS1302_MIN)&0x7f);
	u8 h_cur = bcd2dec(DS1302Read(READ_DS1302_HOUR));	

	if(!timer_flag){
		if((h_mark != h_cur)||(m_mark != m_cur)){

			if(is_alarm_on()){
				if(sys_power){
					if((h_cur == sys_h_off) && (m_cur == sys_m_off)){

						BuzzerStart(POLY_OFF);
						power_off();
					}
				}else{
					if((h_cur == sys_h_on) && (m_cur == sys_m_on)){

						BuzzerStart(POLY_ON);
						power_on();
					}
				}
			}
		}
	}else{
		if(!timer_timeout){

			timer_flag = 0;
		}
	}
	m_mark = m_cur;
	h_mark = h_cur;

	if((timer_flag!=Timer_CurTime_H)&&(timer_flag!=Timer_CurTime_M)){
		if((sys_h_cur != h_cur)||(sys_m_cur != m_cur)){

			sys_h_cur = h_cur;
			sys_m_cur = m_cur;
			setcmd_CurTime();
		}
	}

	//判别DS1302好坏，2s读一次秒，若无变化，则判定为故障，否则无故障
	if(t_test_timer)t_test_timer--;
	
	if(!t_test_timer){
		u8 s_cur = bcd2dec(DS1302Read(READ_DS1302_SEC)&0x7f);
		t_test_timer = 2;
		if(s_cur == sec_test_mark){
			fault_timer = 1;
		}else{
			fault_timer = 0;
			sec_test_mark = s_cur;
		}
	}
}

