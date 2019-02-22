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
* Description :计算val各位1个的个数
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
* Description :计算rold循环递增到rnew需要增加的数
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
* Description :二分法查找ele在降序数组中的位置
*
* Argument(s) :a 降序数组 len 数组a的元素数量 ele 需要查找的元素
*
* Return(s)   :返回不大于ele的最大的元素的索引，若a中的元素都大于ele，则返回len
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
* Description :二分法查找ele在降序数组中的位置
*
* Argument(s) :a 降序数组 len 数组a的元素数量 ele 需要查找的元素
*
* Return(s)   :返回不大于ele的最大的元素的索引，若a中的元素都大于ele，则返回len
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
* Description :二分法查找降序数组a中与ele最接近的元素的索引
*
* Argument(s) :a 降序数组 len 数组a的元素数量 ele 需要查找的元素
*
* Return(s)   :数组a中与ele最接近的元素的索引
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
* Description :二分法查找降序数组a中与ele最接近的元素的索引
*
* Argument(s) :a 降序数组 len 数组a的元素数量 ele 需要查找的元素
*
* Return(s)   :数组a中与ele最接近的元素的索引
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
* Description :求长度为len的元素为8位无符号数的数组buf中排第n位的元素数值，n从0开始排
*
* Argument(s) :buf 8位无符号数组; len buf的元素个数; n 将buf从小到大排序，所求数的序号，从0开始排序
*
* Return(s)   :buf中排第n位的元素数值
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
* Description :求长度为len的8位无符号数组buf的中位数
*
* Argument(s) :buf 8位无符号数组;len buf的元素个数
*
* Return(s)   :buf的中位数
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




/*计算CRC码的步骤为：

(1).预置16位寄存器为FFFFH。称此寄存器为CRC寄存器；

(2).把第一个8位数据与CRC寄存器的低位相异或，把结果放于CRC寄存器；

(3).把寄存器的内容右移一位(朝低位)，用0填补最高位，检查最低位；

(4).如果最低位为0：重复第3步(再次移位)如果最低位为1：CRC寄存器与多项式A001（1010 0000 0000 0001）进行异或；

(5).重复步骤3和4，直到右移8次，这样整个8位数据全部进行了处理；

(6).重复步骤2到步骤5，进行下一个8位数据的处理；

(7).最后得到的CRC寄存器即为CRC码。(CRC码 = CRC_L +CRC_H)

*/

/*****************crc校验**********************************************/

//crc生成函数，并将crc存储在预先定于的数组中

//调用方式crc16（指向数据的指针，需要校验的数据长度）

unsigned char ACRC[2];//定义数组

void Acrc16(unsigned char *ptr,unsigned int len)

{

unsigned long wcrc=0XFFFF;//预置16位crc寄存器，初值全部为1

unsigned char temp;//定义中间变量

int i=0,j=0;//定义计数

for(i=0;i<len;i++)//循环计算每个数据

{

temp=*ptr&0X00FF;//将八位数据与crc寄存器亦或

ptr++;//指针地址增加，指向下个数据

wcrc^=temp;//将数据存入crc寄存器

for(j=0;j<8;j++)//循环计算数据的

{

if(wcrc&0X0001)//判断右移出的是不是1，如果是1则与多项式进行异或。

{

wcrc>>=1;//先将数据右移一位

wcrc^=0XA001;//与上面的多项式进行异或

}

else//如果不是1，则直接移出

{

wcrc>>=1;//直接移出

}

}

}

temp=wcrc;//crc的值

ACRC[0]=wcrc;//crc的低八位

ACRC[1]=wcrc>>8;//crc的高八位

}

