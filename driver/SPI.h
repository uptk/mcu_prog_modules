#ifndef __SPI_H__
#define __SPI_H__

#include "common.h"
#define SCS_ON()
#define SCS_OFF()
#define SCK_ON()
#define SCK_OFF()
#define SDO_ON()
#define SDO_OFF()
#define SDI_IN()
#define SPI_DELAY()


extern u8 Spi_0_Read(u8 v);
extern u8 Spi_1_Read(u8 v);
extern u8 Spi_2_Read(u8 v);
extern u8 Spi_3_Read(u8 v);

#endif /* __SPI_H__ */
