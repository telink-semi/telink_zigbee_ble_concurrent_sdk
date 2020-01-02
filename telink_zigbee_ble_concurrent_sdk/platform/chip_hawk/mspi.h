/********************************************************************************************************
 * @file     mspi.h
 *
 * @brief    This file provides set of driver functions to manage the master spi interface
 *
 * @author   jian.zhang@telink-semi.com
 * @date     Oct. 8, 2016
 *
 * @par      Copyright (c) 2016, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *           
 *           The information contained herein is confidential property of Telink 
 *           Semiconductor (Shanghai) Co., Ltd. and is available under the terms 
 *           of Commercial License Agreement between Telink Semiconductor (Shanghai) 
 *           Co., Ltd. and the licensee or the terms described here-in. This heading 
 *           MUST NOT be removed from this file.
 *
 *           Licensees are granted free, non-transferable use of the information in this 
 *           file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided. 
 *           
 *******************************************************************************************************/
#ifndef _MSPI_H_
#define _MSPI_H_

#include "bsp.h"

/** define data register of the master spi interface */ 
#define REG_MASTER_SPI_DATA     REG_ADDR8(0x0c)
/** define control register of the master spi interface */
#define REG_MASTER_SPI_CTRL     REG_ADDR8(0x0d)

/**
 *  @brief  Define bit field of control register of the master spi interface
 */
enum {
    FLD_MASTER_SPI_CS   =       BIT(0),
    FLD_MASTER_SPI_SDO  =       BIT(1),
    FLD_MASTER_SPI_CONT =       BIT(2),
    FLD_MASTER_SPI_RD   =       BIT(3),
    FLD_MASTER_SPI_BUSY =       BIT(4),
};

static inline void MSPI_Wait(void)
{
    while(REG_MASTER_SPI_CTRL & FLD_MASTER_SPI_BUSY);
}

static inline void MSPI_High(void)
{
    REG_MASTER_SPI_CTRL = FLD_MASTER_SPI_CS;
}

static inline void MSPI_Low(void) {
    REG_MASTER_SPI_CTRL = 0;
}

static inline unsigned char MSPI_Get(void)
{
    return REG_MASTER_SPI_DATA;
}

static inline void MSPI_Write(unsigned char c)
{
    REG_MASTER_SPI_DATA = c;
}

static inline void MSPI_CtrlWrite(unsigned char c)
{
    REG_MASTER_SPI_CTRL = c;
}

static inline unsigned char MSPI_Read(void)
{
    MSPI_Write(0);      // dummy, issue clock 
    MSPI_Wait();
    return MSPI_Get();
}

#endif /* _MSPI_H_ */
