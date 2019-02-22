#include "common.h"

void nopDelay(u8 val)
{
	while(val--)
		__ASM("NOP");
}

void  delay_us(u8 us)
{
    while(us--)
    {
    	;
    }
}

void delay_ms(u8 ms)
{
	while(ms>0){
		u8 i=0;
		while(i<12){
			i++;
			delay_us(250);
		}
		ms--;
	}
}

void swap8(u8 *buf)
{
	u8 tmp = buf[0];
	buf[0]=buf[1];
	buf[1]=tmp;
}
u8 checkSum(u8 *s,u8 n)
{
	u8 sum = 0;
	while(n--)
		sum += *(s++);
	return sum;
}

/*
*********************************************************************************************************
*                                                  cal_1()
*
* Description :����val��λ1���ĸ���
*
* Argument(s) :
*
* Return(s)   :
*
* Caller(s)   :
*
* Note(s)     :
*********************************************************************************************************
*/
u8 cal_1(u8 val)
{
	u8 ret = 0;
	while(val){
		ret += val&1;
		val >>= 1;
	}
	return ret;
}



/*
*********************************************************************************************************
*                                                tryGetInc()
*
* Description :����roldѭ��������rnew��Ҫ���ӵ���
*
* Argument(s) :
*
* Return(s)   :
*
* Caller(s)   :
*
* Note(s)     :
*********************************************************************************************************
*/
u8 tryGetInc(u8 rold,u8 rnew)
{
	u8 ret;
	if(rnew >= rold)
		ret = (rnew - rold);
	else
		ret = (0xff - (rold - rnew) + 1);
	
	return ret;
}



/*
*********************************************************************************************************
*                                             binSearch16()
*
* Description :���ַ�����ele�ڽ��������е�λ��
*
* Argument(s) :a �������� len ����a��Ԫ������ ele ��Ҫ���ҵ�Ԫ��
*
* Return(s)   :���ز�����ele������Ԫ�ص���������a�е�Ԫ�ض�����ele���򷵻�len
*
* Caller(s)   :
*
* Note(s)     :len>0
*********************************************************************************************************
*/
u8 binSearch16(u16 const *a,u8 len,u16 ele)
{
	u8 f,b,m;
	if(a[0] <= ele)
		return 0;
	if(a[len - 1] > ele)
		return len;
	f = 0;
	b = len - 1;
	while(f <=  b){
		m = (f+b)/2;
		if(ele > a[m]){
			b = m-1;
		}else if(ele < a[m]){
			f = m+1;
		}else
			return m;
	}
	//a[b]>ele>a[f]
	return f;
}
/*
*********************************************************************************************************
*                                             binSearch()
*
* Description :���ַ�����ele�ڽ��������е�λ��
*
* Argument(s) :a �������� len ����a��Ԫ������ ele ��Ҫ���ҵ�Ԫ��
*
* Return(s)   :���ز�����ele������Ԫ�ص���������a�е�Ԫ�ض�����ele���򷵻�len
*
* Caller(s)   :
*
* Note(s)     :len>0
*********************************************************************************************************
*/

u8 binSearch(u8 const *a,u8 len,u8 ele)
{
	u8 f,b,m;
	if(a[0] <= ele)
		return 0;
	if(a[len - 1] > ele)
		return len;
	f = 0;
	b = len - 1;
	while(f <=  b){
		m = (f+b)/2;
		if(ele > a[m]){
			b = m-1;
		}else if(ele < a[m]){
			f = m+1;
		}else
			return m;
	}
	//a[b]>ele>a[f]
	return f;
}

/*
*********************************************************************************************************
*                                             nearBinSearch16()
*
* Description :���ַ����ҽ�������a����ele��ӽ���Ԫ�ص�����
*
* Argument(s) :a �������� len ����a��Ԫ������ ele ��Ҫ���ҵ�Ԫ��
*
* Return(s)   :����a����ele��ӽ���Ԫ�ص�����
*
* Caller(s)   :
*
* Note(s)     :len>0
*********************************************************************************************************
*/
u8 nearBinSearch16(u16 const *a,u8 len,u16 ele)
{
	u8 ret = binSearch16(a,len,ele);
	if(ret <= 0){
		return 0;
	}else if(ret >= len){
		return (len-1);
	}else{
		return ((a[ret-1] - ele)<=(ele - a[ret]))?(ret-1):ret;
	}

}
/*
*********************************************************************************************************
*                                             nearBinSearch()
*
* Description :���ַ����ҽ�������a����ele��ӽ���Ԫ�ص�����
*
* Argument(s) :a �������� len ����a��Ԫ������ ele ��Ҫ���ҵ�Ԫ��
*
* Return(s)   :����a����ele��ӽ���Ԫ�ص�����
*
* Caller(s)   :
*
* Note(s)     :len>0
*********************************************************************************************************
*/

u8 nearBinSearch(u8 const *a,u8 len,u8 ele)
{
	u8 ret = binSearch(a,len,ele);
	if(ret <= 0){
		return 0;
	}else if(ret >= len){
		return (len-1);
	}else{
		return ((a[ret-1] - ele)<=(ele - a[ret]))?(ret-1):ret;
	}
}

/*
*********************************************************************************************************
*                                                  n_of()
*
* Description :�󳤶�Ϊlen��Ԫ��Ϊ8λ�޷�����������buf���ŵ�nλ��Ԫ����ֵ��n��0��ʼ��
*
* Argument(s) :buf 8λ�޷�������; len buf��Ԫ�ظ���; n ��buf��С������������������ţ���0��ʼ����
*
* Return(s)   :buf���ŵ�nλ��Ԫ����ֵ
*
* Caller(s)   :
*
* Note(s)     :len>0 && n<len
*********************************************************************************************************
*/
u8 n_of(u8 *buf,u8 len,u8 n)
{
    u8 i;
    u8 ret;
    u8 n_min;
    u8 n_max;
    u8 n_flag=0;

    if(n>=len)
        n = len-1;
    for(i=0;i<len;i++){
        //if(buf[i]>n_min&&buf[i]<n_max){
        if( ((!(n_flag&0x01))||(buf[i]>n_min))&&
            ((!(n_flag&0x02))||(buf[i]<n_max))
        ){
            u8 j;
            u8 rank_min = 0;
            u8 rank_max = 0;
            for(j=0;j<len;j++){
                if(j!=i){
                    if(buf[i]>=buf[j]){
                        rank_max++;
                        if(buf[i]>buf[j]){
                            rank_min++;
                        }
                    }

                }
            }
            if(rank_max<n){
                if(n_flag&0x01){
                    if(buf[i]>n_min){
                        n_min = buf[i];
                    }
                }else{
                    n_min = buf[i];
                    n_flag |= 0x01;
                }
            }else if(rank_min>n){
                if(n_flag&0x02){
                    if(buf[i]<n_max){
                        n_max = buf[i];
                    }
                }else{
                    n_flag |= 0x02;
                    n_max = buf[i];
                }
            }else{
                ret = buf[i];
                break;
            }
        }
    }
    return ret;
}

/*

*/
/*
*********************************************************************************************************
*                                                 mid_of()
*
* Description :�󳤶�Ϊlen��8λ�޷�������buf����λ��
*
* Argument(s) :buf 8λ�޷�������;len buf��Ԫ�ظ���
*
* Return(s)   :buf����λ��
*
* Caller(s)   :
*
* Note(s)     :len>0
*********************************************************************************************************
*/
u8 mid_of(u8 *buf,u8 len)
{
    if(len&0x01){
        return n_of(buf,len,(len-1)/2);
    }else{
        u8 n1 = len/2;
        u8 n2 = n1-1;
        return (n_of(buf,len,n1)+n_of(buf,len,n2)+1)/2;
    }
}




/*����CRC��Ĳ���Ϊ��

(1).Ԥ��16λ�Ĵ���ΪFFFFH���ƴ˼Ĵ���ΪCRC�Ĵ�����

(2).�ѵ�һ��8λ������CRC�Ĵ����ĵ�λ����򣬰ѽ������CRC�Ĵ�����

(3).�ѼĴ�������������һλ(����λ)����0����λ��������λ��

(4).������λΪ0���ظ���3��(�ٴ���λ)������λΪ1��CRC�Ĵ��������ʽA001��1010 0000 0000 0001���������

(5).�ظ�����3��4��ֱ������8�Σ���������8λ����ȫ�������˴���

(6).�ظ�����2������5��������һ��8λ���ݵĴ���

(7).���õ���CRC�Ĵ�����ΪCRC�롣(CRC�� = CRC_L +CRC_H)

*/

/*****************crcУ��**********************************************/

//crc���ɺ���������crc�洢��Ԥ�ȶ��ڵ�������

//���÷�ʽcrc16��ָ�����ݵ�ָ�룬��ҪУ������ݳ��ȣ�

unsigned char ACRC[2];//��������

void Acrc16(unsigned char *ptr,unsigned int len)

{

unsigned long wcrc=0XFFFF;//Ԥ��16λcrc�Ĵ�������ֵȫ��Ϊ1

unsigned char temp;//�����м����

int i=0,j=0;//�������

for(i=0;i<len;i++)//ѭ������ÿ������

{

temp=*ptr&0X00FF;//����λ������crc�Ĵ������

ptr++;//ָ���ַ���ӣ�ָ���¸�����

wcrc^=temp;//�����ݴ���crc�Ĵ���

for(j=0;j<8;j++)//ѭ���������ݵ�

{

if(wcrc&0X0001)//�ж����Ƴ����ǲ���1�������1�������ʽ�������

{

wcrc>>=1;//�Ƚ���������һλ

wcrc^=0XA001;//������Ķ���ʽ�������

}

else//�������1����ֱ���Ƴ�

{

wcrc>>=1;//ֱ���Ƴ�

}

}

}

temp=wcrc;//crc��ֵ

ACRC[0]=wcrc;//crc�ĵͰ�λ

ACRC[1]=wcrc>>8;//crc�ĸ߰�λ

}

