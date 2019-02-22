#ifndef	__stepMotor_h__
#define	__stepMotor_h__

#include "common.h"

#define    M1_A1_P_ON()
#define    M1_A1_P_OFF()

#define    M1_A1_N_ON()
#define    M1_A1_N_OFF()

#define    M1_B1_P_ON()
#define    M1_B1_P_OFF()

#define    M1_B1_N_ON()
#define    M1_B1_N_OFF()

#define	Angle_MAX		2160//90¶È

extern volatile u16 sm_runangle;
extern volatile u16 sm_setangle;

extern void runSM(void);
extern void initSM(void);
extern void cmdSM(u16 a);

#endif
