#include "common.h"
#include "drv_I2C.h"

#define	I2C_DELAY()		delay_us(6)//10us



void InitI2cIO(void)
{
	I2C_SDA_OUT_MODE();
	I2C_SCL_OUT_MODE();
	I2C_SCL_OUT_H();
	I2C_SDA_OUT_H();
	I2C_DELAY();
}

/*
before:
SDA	OUT		1		x
SCL OUT		1		0
after:
SDA	OUT		0
SCL	OUT		0
*/
void StartI2c(void)
{
	I2C_SDA_OUT_H();
	I2C_DELAY();
	I2C_SCL_OUT_H();
	I2C_DELAY();
	I2C_SDA_OUT_L();
	I2C_DELAY();
	I2C_SCL_OUT_L();
	I2C_DELAY();
}

/*
before:
SDA	OUT		x
SCL	OUT		0
after:
SDA	OUT		1
SCL	OUT		1
*/
void StopI2c(void)
{
	I2C_SDA_OUT_L();	//发送结束条件的数据信号
	I2C_DELAY();
	I2C_SCL_OUT_H();   //发送结束条件的时钟信号   
	I2C_DELAY();//结束条件建立时间大于4μs
	I2C_SDA_OUT_H();   //发送I2C总线结束信号
	I2C_DELAY();
}

/*
before:
SDA	OUT		x
SCL	OUT		0
after:
SDA	OUT		x
SCL	OUT		0
*/
void AckI2c(u8 a)
{
	if(a==0) 
		I2C_SDA_OUT_L();     //在此发出应答或非应答信号
	else   
		I2C_SDA_OUT_H();
	I2C_DELAY();    
	I2C_SCL_OUT_H();
	I2C_DELAY();        //时钟低电平周期大于4μs
	I2C_SCL_OUT_L();
	I2C_DELAY(); 
}

/*	
before:
SDA	OUT		x
SCL	OUT		0
after:
SDA	OUT		x
SCL	OUT		0
*/
u8 SendByte(u8 c)
{
	u8 BitCnt;
	u8 ret;

	for(BitCnt=0;BitCnt<8;BitCnt++) //要传送的数据长度为8位
	{
	   if(c&0x80)   
	   		I2C_SDA_OUT_H();   //判断发送位
	   else 
	   		I2C_SDA_OUT_L();
	   c<<=1;
	   I2C_DELAY();
	   I2C_SCL_OUT_H(); //置时钟线为高，通知被控器开始接收数据位
	   I2C_DELAY();      //保证时钟高电平周期大于4μs*/	           
	   I2C_SCL_OUT_L();
	   //I2C_DELAY();
	}
	   //8位发送完后释放数据线，准备接收应答位
	I2C_SDA_IN_MODE();
	I2C_DELAY(); 
	I2C_SCL_OUT_H();
	I2C_DELAY();
	if(I2C_SDA_IN()) 
		ret=0;
	else   
		ret=1;     //判断是否接收到应答信号
	I2C_SCL_OUT_L();	
	I2C_DELAY();
	I2C_SDA_OUT_MODE();
	return ret;
}
/*
before:
SDA	OUT		x
SCL	OUT		0
after:
SDA	OUT		x
SCL	OUT		0
*/
u8 RcvByte(void)
{
	u8 retc;
	u8 BitCnt;
	retc=0;
	
	I2C_SDA_IN_MODE();
	for(BitCnt=0;BitCnt<8;BitCnt++)
	{		  
	   I2C_SCL_OUT_H();
	   I2C_DELAY();
	   retc=retc<<1;
	   if(I2C_SDA_IN()) retc=retc+1; //读数据位,接收的数据位放入retc中
	   I2C_SCL_OUT_L();
	   I2C_DELAY();
	}
	I2C_SDA_OUT_MODE();
	return(retc);

}

u8 Send_cmd(u8 Devi_Addr,u8 cmd)
{
	u8 Ack;
		
	StartI2c();	
	if(Ack=SendByte(Devi_Addr)){
		Ack=SendByte(cmd);
	}
	StopI2c();
	return Ack;	
}


u8 Read_str(u8 Devi_Addr,u8 Word_Addr,u8 count,u8 *str)
{ 
	u8 Ack;

	if(!Send_cmd(Devi_Addr,Word_Addr)){
		return 0;
	}
	StartI2c();
	if(Ack=SendByte(Devi_Addr+1)){
		u8 i = 0;
		while(i<count){
			str[i++]=RcvByte();
			if(i<count)
				AckI2c(0);
			else
				AckI2c(1);
		}
	}
	StopI2c();
	return Ack;	
}


u8 Send_str(u8 Devi_Addr,u8 Word_Addr,u8 count,u8 *str)
{
	
	u8 Ack;
	StartI2c();	
	if(SendByte(Devi_Addr)&&SendByte(Word_Addr)){
		u8 i;
		Ack = 1;
		for(i=0;i<count;i++)
		{	
			if(!(Ack=SendByte(str[i]))){
				break;
			}
		}
	}else{
		Ack = 0;
	}
	StopI2c();
	return Ack;	
}
//



