#include "common.h"
#include "SPI.h"

/*
        SPI协议
SPI接口在内部硬件实际上是两个简单的移位寄存器,传输的数据为8位，
在主器件产生的从器件使能信号和移位脉冲下，按位传输，高位在前，低位在后
CS      设备使能
SCK     时钟线，
        CPOL=0则SCK空闲时低电平，CPOL=1则SCK空闲时高电平，
        CPHA=0则SCK第1个边沿读数据，CPHA=1则SCK第2个边沿读数据
        设备的CPOL CPHA和主机的应当一致
SDO     数据输出，接设备的SDI
SDI     数据输入，接设备的SDO
MSB在前
CPOL和CPHA不同组合有四种SPI模式
    CPOL    CPHA
0   0       0
1   0       1
2   1       0
3   1       1

*/

/*
*********************************************************************************************************
*                                                 Spi_0_Read()
*
* Description :模式0SPI写8位无符号数v，并返回读到的8位数
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
u8 Spi_0_Read(u8 v)
{
    u8 i;
    u8 ret;
    for(i=0;i<8;i++){
        if(v&0x80)
            SDO_ON();
        else
            SDO_OFF();
        v<<=1;
        SPI_DELAY();
        SCK_ON();
        SPI_DELAY();
        ret<<=1;
        if(SDI_IN())
            ret |= 0x01;
        SCK_OFF();
    }
    return ret;
}

/*
*********************************************************************************************************
*                                                 Spi_1_Read()
*
* Description :模式1SPI写8位无符号数v，并返回读到的8位数
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
u8 Spi_1_Read(u8 v)
{
    u8 i;
    u8 ret;
    SPI_DELAY();
    for(i=0;i<8;i++){
        if(v&0x80)
            SDO_ON();
        else
            SDO_OFF();
        v<<=1;
        SCK_ON();
        SPI_DELAY();
        SCK_OFF();
        SPI_DELAY();
        ret<<=1;
        if(SDI_IN())
            ret |= 0x01;
    }
    return ret;
}

/*
*********************************************************************************************************
*                                                 Spi_2_Read()
*
* Description :模式2SPI写8位无符号数v，并返回读到的8位数
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
u8 Spi_2_Read(u8 v)
{
    u8 i;
    u8 ret;
    for(i=0;i<8;i++){
        if(v&0x80)
            SDO_ON();
        else
            SDO_OFF();
        v<<=1;
        SPI_DELAY();
        SCK_OFF();
        SPI_DELAY();
        ret<<=1;
        if(SDI_IN())
            ret |= 0x01;
        SCK_ON();
    }
    return ret;
}

/*
*********************************************************************************************************
*                                                 Spi_3_Read()
*
* Description :模式3SPI写8位无符号数v，并返回读到的8位数
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
u8 Spi_3_Read(u8 v)
{
    u8 i;
    u8 ret;
    SPI_DELAY();
    for(i=0;i<8;i++){
        if(v&0x80)
            SDO_ON();
        else
            SDO_OFF();
        v<<=1;
        SCK_OFF();
        SPI_DELAY();
        SCK_ON();
        SPI_DELAY();
        ret<<=1;
        if(SDI_IN())
            ret |= 0x01;
    }
    return ret;
}


