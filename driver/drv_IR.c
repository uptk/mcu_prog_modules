/*
******************* (C) COPYRIGHT ���ڽ��������ܿƼ����޹�˾ *******************
* �ļ����ƣ�drv_IR.c
* ��    ����
* ��    ����V0.0.1
* ��    �ߣ�Landon
* Q      Q��920639478
* �޸�ʱ�䣺2015/10/27
* �޸ļ�¼��
********************************************************************************
*/
#define DRV_IR_GLOBALS

/*********************************ͷ�ļ�����***********************************/
#include "drv_IR.h"

/*******************************************************************************
�������ƣ�IR_IO_Init
�������ܣ��������IO�ڳ�ʼ��
��ڲ�������
���ڲ�������
��    �ã��ⲿ����
*******************************************************************************/
void IR_IO_Init(void)
{
	P04_Quasi_Mode;
	P04=1;
}

/*******************************************************************************
�������ƣ�IR_Init
�������ܣ�������ճ�ʼ��
��ڲ�������
���ڲ�������
��    �ã��ⲿ����
*******************************************************************************/
void IR_Init(void)
{
	IR_IO_Init();
}

/*******************************************************************************
�������ƣ�IR_Decode
�������ܣ��������:�ڶ�ʱ�ж�����ã���ʱ����Ϊ100us.
��ڲ�������
���ڲ�������
��    �ã��ⲿ����
*******************************************************************************/
void IR_Decode(void)
{
    static u8 Flag = 0;

    switch(IrRecStep)
    {
        case 0://��һ��: �����ʼ��ĵ͵�ƽʱ��
        {
            IrIndex = 0;    //����λ��
            if(!IrInput)    //���͵�ƽ
            {
                IrRecCnt ++;    //��¼�͵�ƽʱ��
            }
            else//�͵�ƽ�������жϵ͵�ƽʱ���Ƿ������ʼ��
            {
                //if((IrRecCnt>=42)&&(IrRecCnt<=47)) // ��ͷ�͵�ƽʱ��4.5ms
                if((IrRecCnt>=85)&&(IrRecCnt<=95)) // ��ͷ�͵�ƽʱ��9ms
                {
                    IrRecCnt = 1;
                    IrRecStep =1;//�л�����һ״̬: ��ʼ��ߵ�ƽ�ж�

                    //��ջ�����
                    //Ir_Buff[0] = 0;
                    //Ir_Buff[1] = 0;
                    //Ir_Buff[2] = 0;
                    //Ir_Buff[3] = 0;
                }
                else//��ƽʱ�䲻������ʼ��
                {
                    IrRecCnt = 0;//���������
                    IrRecStep = 0;//�л�����ʼ̬
                    return;
                }
            }
            break;
        }

        case 1://�ڶ���: �����ʼ��ĸߵ�ƽʱ��
        {
            if(IrInput)//���ߵ�ƽ
            {
                IrRecCnt ++;
                if(IrRecCnt >= 50)//�ߵ�ƽʱ�����,�ѳ�����ʼ��ʱ��ߵ�ƽʱ��̫�࣬�˳�
                {
                    IrRecCnt = 0;//���������
                    IrRecStep = 0;//�л�����ʼ̬
                    return;
                }
            }
            else//�ߵ�ƽ�������жϸߵ�ƽʱ���Ƿ������ʼ��
            {
                if((IrRecCnt>=40)&&(IrRecCnt<=50))   // ��ͷ�ߵ�ƽʱ��4.5ms
                {
                    IrRecCnt = 1;
                    IrRecStep = 2;//�л�����һ״̬: ������͵�ƽ�ж�
                    Flag = 0;
                    //��ջ�����
                    Ir_Buff[0] = 0;
                    Ir_Buff[1] = 0;
                    Ir_Buff[2] = 0;
                    Ir_Buff[3] = 0;
                }
                else if((IrRecCnt>=20)&&(IrRecCnt<=27)) //�ظ�����ͷ�ߵ�ƽʱ��4.5ms
                {
                    if(Flag)
                    {
                        IrRecCnt = 1;
                        IrRecStep = 0;//�л�����һ״̬: ������͵�ƽ�ж�
                        IrRecFlag = 2;//����ɹ���־��1
                    }
                    else
                    {
                        IrRecCnt =0;//���������
                        IrRecStep = 0;//�л�����ʼ̬
                        return;
                    }
                }
                else//��ƽʱ�䲻������ʼ��
                {
                    IrRecCnt =0;//���������
                    IrRecStep = 0;//�л�����ʼ̬
                    return;
                }
            }
            break;
        }

        case 2://������: ���������ĵ͵�ƽʱ��
        {
            if(!IrInput)
            {
                IrRecCnt ++;
                if(IrRecCnt > 10)   //�͵�ƽʱ�����,�˳�
                {
                    IrRecCnt = 0;
                    IrRecStep = 0;
                    return;
                }
            }
            else
            {
                if((IrRecCnt >= 4)&&(IrRecCnt <= 7)) //ÿλ��ͷ0.56ms�͵�ƽ
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

        case 3://���Ĳ�
        {
            if(IrInput)
            {
                IrRecCnt ++;
                if(IrRecCnt > 20)            //�͵�ƽʱ�����,�˳�
                {
                    IrRecCnt = 0;
                    IrRecStep = 0;
                    return;
                }
            }
            else
            {
                if((IrRecCnt >= 14)&&(IrRecCnt <= 18))  //�ߵ�ƽʱ��ԼΪ1.68ms,��Ϊ����1
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
                else if((IrRecCnt >= 3)&&(IrRecCnt <= 8))//�ߵ�ƽʱ��ԼΪ0.56ms,��Ϊ����0
                {
                    IrRecCnt = 1;
                    IrIndex ++;
                    IrRecStep = 2;
                }
                else//�ߵ�ƽʱ�䲻����
                {
                    IrRecStep = 0;     //�˳�
                    IrRecCnt = 0;
                    return;
                }
                if(IrIndex >= 32)    //�Ƿ������32λ
                {
                  IrRecStep = 0;//�лس�ʼ̬
                  IrRecFlag = 1;//����ɹ���־��1
                  Flag = 1;//

                }
            }
            break;
        }

        default:
            break;
    }
}

