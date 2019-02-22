#include "common.h"
#include "stepMotor.h"

/*
		0	1	2	3	4	5	6	7
A+	PB1	0	0	1	1	1	1	1	0
A-	PB0	1	0	0	0	1	1	1	1
B+	PA7	1	1	1	0	0	0	1	1
B-	PA6	1	1	1	1	1	0	0	0
		e	c	d	9	b	3	7	6
正转	0->7
反转	7->0
90度	8*90*3步

JX86
内循环
正转90度
外循环
先正转90度，再反转45度	

DINO_24V	660_24V
内循环
正转90度
外循环
先正转90度，再反转90度	

*/

	void lauchSMPin(u8 v)
	{
		if(v&BIT0){
			M1_A1_P_ON();
		}else{
			M1_A1_P_OFF();
		}
		if(v&BIT1){
			M1_A1_N_ON();
		}else{
			M1_A1_N_OFF();
		}
		if(v&BIT2){
			M1_B1_P_ON();
		}else{
			M1_B1_P_OFF();
		}
		if(v&BIT3){
			M1_B1_N_ON();
		}else{
			M1_B1_N_OFF();
		}
	}

void goStep(u8 p)
{
	static u8 const SMSteps[8] = {0x0e,0x0c,0x0d,0x09,0x0b,0x03,0x07,0x06};
	static u8 curStep;
	
	switch(p)
	{
	case 2:
		if(curStep > 0)
			curStep--;
		else
			curStep = arraySizeOf(SMSteps) - 1;
		lauchSMPin(SMSteps[curStep]);
		break;
	case 1:
		curStep++;
		if(curStep >= arraySizeOf(SMSteps))
			curStep = 0;
		lauchSMPin(SMSteps[curStep]);
		break;
	default:
		lauchSMPin(0);
		break;
	}
}


volatile u16 sm_runangle;
volatile u16 sm_setangle;
volatile u8 sm_state;




/*

sm_setangle		0~Angle_MAX
sm_runangle		0~2*Angle_MAX


sm_runangle>Angle_MAX		复位期间
sm_runangle>sm_setangle		定位期间
sm_runangle==sm_setangle	定位完成
*/
void runSM(void)
{
	if(sm_runangle!=sm_setangle){
		if(sm_runangle>Angle_MAX){
			goStep(1);
			sm_runangle--;
		}else if(sm_runangle>sm_setangle){
			goStep(2);
			sm_runangle--;
		}else{
			goStep(1);
			sm_runangle=2*Angle_MAX-1;
		}
		sm_state=1;
	}else{
		if(sm_state){
			goStep(0);
			sm_state=0;
		}
	}

}

void cmdSM(u16 a)
{
	if(sm_setangle!=a){
		if(!sm_state){
			sm_runangle=2*Angle_MAX;
		}
		sm_setangle=a;
	}
}
void initSM(void)
{
	goStep(0);
	sm_state=0;
	sm_runangle=Angle_MAX*2;
	sm_setangle=0;
}

