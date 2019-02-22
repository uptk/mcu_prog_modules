/*
******************* (C) COPYRIGHT 深圳金迈高智能科技有限公司 *******************
* 文件名称：drv_IR.c
* 描    述：
* 版    本：V0.0.1
* 作    者：Landon
* Q      Q：920639478
* 修改时间：2015/10/27
* 修改记录：
********************************************************************************
*/
#define DRV_IR_GLOBALS

/*********************************头文件包含***********************************/
#include "drv_IR.h"

/*******************************************************************************
函数名称：IR_IO_Init
函数功能：红外接收IO口初始化
入口参数：无
出口参数：无
调    用：外部调用
*******************************************************************************/
void IR_IO_Init(void)
{
	P04_Quasi_Mode;
	P04=1;
}

/*******************************************************************************
函数名称：IR_Init
函数功能：红外接收初始化
入口参数：无
出口参数：无
调    用：外部调用
*******************************************************************************/
void IR_Init(void)
{
	IR_IO_Init();
}

/*******************************************************************************
函数名称：IR_Decode
函数功能：红外解码:在定时中断里调用，定时周期为100us.
入口参数：无
出口参数：无
调    用：外部调用
*******************************************************************************/
void IR_Decode(void)
{
    static u8 Flag = 0;

    switch(IrRecStep)
    {
        case 0://第一步: 检测起始码的低电平时间
        {
            IrIndex = 0;    //接收位数
            if(!IrInput)    //检测低电平
            {
                IrRecCnt ++;    //记录低电平时间
            }
            else//低电平结束，判断低电平时间是否符合起始码
            {
                //if((IrRecCnt>=42)&&(IrRecCnt<=47)) // 码头低电平时间4.5ms
                if((IrRecCnt>=85)&&(IrRecCnt<=95)) // 码头低电平时间9ms
                {
                    IrRecCnt = 1;
                    IrRecStep =1;//切换至下一状态: 起始码高电平判断

                    //清空缓存区
                    //Ir_Buff[0] = 0;
                    //Ir_Buff[1] = 0;
                    //Ir_Buff[2] = 0;
                    //Ir_Buff[3] = 0;
                }
                else//电平时间不符合起始码
                {
                    IrRecCnt = 0;//清零计数器
                    IrRecStep = 0;//切换至初始态
                    return;
                }
            }
            break;
        }

        case 1://第二步: 检测起始码的高电平时间
        {
            if(IrInput)//检测高电平
            {
                IrRecCnt ++;
                if(IrRecCnt >= 50)//高电平时间过长,已超过起始码时间高电平时间太多，退出
                {
                    IrRecCnt = 0;//清零计数器
                    IrRecStep = 0;//切换至初始态
                    return;
                }
            }
            else//高电平结束，判断高电平时间是否符合起始码
            {
                if((IrRecCnt>=40)&&(IrRecCnt<=50))   // 码头高电平时间4.5ms
                {
                    IrRecCnt = 1;
                    IrRecStep = 2;//切换至下一状态: 数据码低电平判断
                    Flag = 0;
                    //清空缓存区
                    Ir_Buff[0] = 0;
                    Ir_Buff[1] = 0;
                    Ir_Buff[2] = 0;
                    Ir_Buff[3] = 0;
                }
                else if((IrRecCnt>=20)&&(IrRecCnt<=27)) //重复码码头高电平时间4.5ms
                {
                    if(Flag)
                    {
                        IrRecCnt = 1;
                        IrRecStep = 0;//切换至下一状态: 数据码低电平判断
                        IrRecFlag = 2;//解码成功标志置1
                    }
                    else
                    {
                        IrRecCnt =0;//清零计数器
                        IrRecStep = 0;//切换至初始态
                        return;
                    }
                }
                else//电平时间不符合起始码
                {
                    IrRecCnt =0;//清零计数器
                    IrRecStep = 0;//切换至初始态
                    return;
                }
            }
            break;
        }

        case 2://第三步: 检测数据码的低电平时间
        {
            if(!IrInput)
            {
                IrRecCnt ++;
                if(IrRecCnt > 10)   //低电平时间过长,退出
                {
                    IrRecCnt = 0;
                    IrRecStep = 0;
                    return;
                }
            }
            else
            {
                if((IrRecCnt >= 4)&&(IrRecCnt <= 7)) //每位开头0.56ms低电平
                {
                    IrRecCnt = 1;
                    IrRecStep = 3;
                }
            else
            {
                IrRecCnt = 0;
                IrRecStep = 0;
                return;
            }
            }
            break;
        }

        case 3://第四步
        {
            if(IrInput)
            {
                IrRecCnt ++;
                if(IrRecCnt > 20)            //低电平时间过长,退出
                {
                    IrRecCnt = 0;
                    IrRecStep = 0;
                    return;
                }
            }
            else
            {
                if((IrRecCnt >= 14)&&(IrRecCnt <= 18))  //高电平时间约为1.68ms,则为数据1
                {
                	Ir_Buff[IrIndex >> 3] |= 1<<(IrIndex&7);
					/*
                    if(IrIndex%8==0) Ir_Buff[IrIndex >> 3] |=0x01;
                    if(IrIndex%8==1) Ir_Buff[IrIndex >> 3] |=0x02;
                    if(IrIndex%8==2) Ir_Buff[IrIndex >> 3] |=0x04;
                    if(IrIndex%8==3) Ir_Buff[IrIndex >> 3] |=0x08;
                    if(IrIndex%8==4) Ir_Buff[IrIndex >> 3] |=0x10;
                    if(IrIndex%8==5) Ir_Buff[IrIndex >> 3] |=0x20;
                    if(IrIndex%8==6) Ir_Buff[IrIndex >> 3] |=0x40;
                    if(IrIndex%8==7) Ir_Buff[IrIndex >> 3] |=0x80;
                    */
                    /*
                    if(IrIndex%8==7) Ir_Buff[IrIndex >> 3] |=0x01;
                    if(IrIndex%8==6) Ir_Buff[IrIndex >> 3] |=0x02;
                    if(IrIndex%8==5) Ir_Buff[IrIndex >> 3] |=0x04;
                    if(IrIndex%8==4) Ir_Buff[IrIndex >> 3] |=0x08;
                    if(IrIndex%8==3) Ir_Buff[IrIndex >> 3] |=0x10;
                    if(IrIndex%8==2) Ir_Buff[IrIndex >> 3] |=0x20;
                    if(IrIndex%8==1) Ir_Buff[IrIndex >> 3] |=0x40;
                    if(IrIndex%8==0) Ir_Buff[IrIndex >> 3] |=0x80;
                    */
                    IrRecCnt = 1;
                    IrIndex ++;
                    IrRecStep = 2;
                }
                else if((IrRecCnt >= 3)&&(IrRecCnt <= 8))//高电平时间约为0.56ms,则为数据0
                {
                    IrRecCnt = 1;
                    IrIndex ++;
                    IrRecStep = 2;
                }
                else//高电平时间不符合
                {
                    IrRecStep = 0;     //退出
                    IrRecCnt = 0;
                    return;
                }
                if(IrIndex >= 32)    //是否接收完32位
                {
                  IrRecStep = 0;//切回初始态
                  IrRecFlag = 1;//解码成功标志置1
                  Flag = 1;//

                }
            }
            break;
        }

        default:
            break;
    }
}

