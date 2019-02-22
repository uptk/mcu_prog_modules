#ifndef _drv_I2C_h_
#define	_drv_I2C_h_

#include "common.h"



#define I2C_SCL_OUT_MODE()  P13_OpenDrain_Mode
#define I2C_SCL_OUT_H() 	P13=1
#define I2C_SCL_OUT_L()		P13=0


#define I2C_SDA_OUT_MODE()  P14_OpenDrain_Mode
#define I2C_SDA_IN_MODE()	P14_OpenDrain_Mode;P14=1

#define I2C_SDA_OUT_H() 	P14=1
#define I2C_SDA_OUT_L()		P14=0
#define I2C_SDA_IN()		P14



extern void InitI2cIO(void);
extern void StartI2c(void);
extern void StopI2c(void);
extern void AckI2c(u8 a);
extern u8	RcvByte(void);
extern u8 SendByte(u8 c);
extern u8 Send_cmd(u8 Devi_Addr,u8 cmd);
extern u8 Read_str(u8 Devi_Addr,u8 Word_Addr,u8 count,u8 *str);
extern u8 Send_str(u8 Devi_Addr,u8 Word_Addr,u8 count,u8 *str);

#endif
