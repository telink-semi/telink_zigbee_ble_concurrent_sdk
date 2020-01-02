/********************************************************************************************************
 * @file     irq.h
 *
 * @brief    This file provides set of functions to manage the IRQs
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
#ifndef _IRQ_H_
#define _IRQ_H_

#include "bsp.h"
#include "./register_5316.h"

/**
 * interrupt regs struct: begin  0x640
 */
#define REG_IRQ_MASK            REG_ADDR32(0x640)
#define REG_IRQ_PRI             REG_ADDR32(0x644)
#define REG_IRQ_SRC             REG_ADDR32(0x648)
#define REG_IRQ_SRC3            REG_ADDR8(0x64a)
/**
 * General IRQs
 */
typedef enum {
    FLD_IRQ_TMR0_SRC =           BIT(0),
    FLD_IRQ_TMR1_SRC =           BIT(1),
    FLD_IRQ_TMR2_SRC =           BIT(2),
    //FLD_IRQ_USB_PWDN_SRC =       BIT(3),
    FLD_IRQ_DMA_SRC =            BIT(4),
    FLD_IRQ_DAM_FIFO_SRC =       BIT(5),
    FLD_IRQ_UART_SRC     =       BIT(6),
    FLD_IRQ_HOST_CMD_SRC =       BIT(7),

    FLD_IRQ_EP0_SETUP_SRC =      BIT(8),
    FLD_IRQ_EP0_DAT_SRC =        BIT(9),
    FLD_IRQ_EP0_STA_SRC =        BIT(10),
    FLD_IRQ_SET_INTF_SRC =       BIT(11),
    FLD_IRQ_EP_DATA_SRC =        BIT(12),
    FLD_IRQ_IRQ4_SRC =           BIT(12),
    FLD_IRQ_ZB_RT_SRC =          BIT(13),
    FLD_IRQ_SW_SRC =             BIT(14),
    FLD_IRQ_AN_SRC =             BIT(15),

    //FLD_IRQ_USB_250US_SRC =      BIT(16),
    //FLD_IRQ_USB_RST_SRC =        BIT(17),
    FLD_IRQ_GPIO_SRC =           BIT(18),
    FLD_IRQ_PM_SRC =             BIT(19),
    FLD_IRQ_SYSTEM_TIMER_SRC =   BIT(20),
    FLD_IRQ_GPIO_RISC0_SRC =     BIT(21),
    FLD_IRQ_GPIO_RISC1_SRC =     BIT(22),
    FLD_IRQ_GPIO_RISC2_SRC =     BIT(23),
} IRQ_IrqSrcTypeDef;
#define REG_IRQ_EN              REG_ADDR8(0x643)

/**
 * General IRQs
 */
typedef enum {
    FLD_IRQ_TMR0_EN =           BIT(0),
    FLD_IRQ_TMR1_EN =           BIT(1),
    FLD_IRQ_TMR2_EN =           BIT(2),
    //FLD_IRQ_USB_PWDN_EN =       BIT(3),
    FLD_IRQ_DMA_EN =            BIT(4),
    FLD_IRQ_DAM_FIFO_EN =       BIT(5),
    FLD_IRQ_UART_EN     =       BIT(6),
    FLD_IRQ_HOST_CMD_EN =       BIT(7),

    FLD_IRQ_EP0_SETUP_EN =      BIT(8),
    FLD_IRQ_EP0_DAT_EN =        BIT(9),
    FLD_IRQ_EP0_STA_EN =        BIT(10),
    FLD_IRQ_SET_INTF_EN =       BIT(11),
    FLD_IRQ_EP_DATA_EN =        BIT(12),
    FLD_IRQ_IRQ4_EN =           BIT(12),
    FLD_IRQ_ZB_RT_EN =          BIT(13),
    FLD_IRQ_SW_EN =             BIT(14),
//    FLD_IRQ_AN_EN =             BIT(15),

    FLD_IRQ_USB_250US_EN =      BIT(16),
    FLD_IRQ_USB_RST_EN =        BIT(17),
    FLD_IRQ_GPIO_EN =           BIT(18),
    FLD_IRQ_PM_EN =             BIT(19),
    FLD_IRQ_SYSTEM_TIMER =      BIT(20),
    FLD_IRQ_GPIO_RISC0_EN =     BIT(21),
    FLD_IRQ_GPIO_RISC1_EN =     BIT(22),
    FLD_IRQ_GPIO_RISC2_EN =     BIT(23),
} IRQ_IrqTypeDef;

/**
 * enalbe interrupt
 */
extern unsigned char irq_enable(void);
extern unsigned char irq_disable(void);
extern void irq_restore(unsigned char Enable);
extern unsigned int IRQ_MaskGet(void);
extern void IRQ_MaskSet(unsigned int Mask);
extern void IRQ_MaskClr(unsigned int Mask);
extern unsigned int IRQ_SrcGet(void);
extern void IRQ_SrcClr(IRQ_IrqSrcTypeDef IrqSrc);
extern void IRQ_SrcAllClr(void);
extern void IRQ_EnableType(unsigned int TypeMask);
extern void IRQ_DisableType(unsigned int TypeMask);

/**
 * RF module irq
 */
typedef enum {
    FLD_RF_IRQ_RX =             BIT(0),
    FLD_RF_IRQ_TX =             BIT(1),
    FLD_RF_IRQ_RX_TIMEOUT =     BIT(2),
    FLD_RF_IRQ_CRC =            BIT(4),
    FLD_RF_IRQ_CMD_DONE  =      BIT(5),
    FLD_RF_IRQ_RETRY_HIT =      BIT(7),
    FLD_RF_IRQ_FIRST_TIMEOUT =  BIT(10)
}IRQ_RfIrqTypeDef;

extern void IRQ_RfIrqEnable(unsigned int RfIrqMask);
extern void IRQ_RfIrqDisable(unsigned int RfIrqMask);
extern void IRQ_RfIrqSrcClr(IRQ_RfIrqTypeDef RfIrqSrc);
extern unsigned short IRQ_RfIrqSrcGet(void);
extern void IRQ_RfIrqSrcAllClr(void);

/**
 * SPI module irq
 */
typedef enum {
    FLD_SPI_IRQ_HOST_CMD    = BIT(1),
    FLD_SPI_IRQ_HOST_RD_TAG = BIT(2),
} IRQ_SpiIrqTypeDef;

extern void IRQ_SpiIrqEn(void);
extern void IRQ_SpiIrqDis(void);
extern unsigned char IRQ_SpiIrqSrcGet(void);
extern void IRQ_SpiIrqSrcClr(void);

/**
 * I2C module irq
 */
typedef enum{
	FLD_I2C_IRQ_HOST_CMD    = BIT(0),
	FLD_I2C_IRQ_HOST_RD_TAG = BIT(1),
} IRQ_I2CIrqTypeDef;
typedef enum {
	I2C_IRQ_NONE = 0,
	I2C_IRQ_HOST_WRITE_ONLY,
	I2C_IRQ_HOST_READ_ONLY,
}I2C_I2CIrqSrcTypeDef;

extern void IRQ_I2CIrqEnable(void);
extern void IRQ_I2CIrqDisable(void);
extern I2C_I2CIrqSrcTypeDef I2C_SlaveIrqGet(void);
extern void I2C_SlaveIrqClr(I2C_I2CIrqSrcTypeDef src);
/**
 * UART module irq
 */
typedef enum {
    FLD_UART_IRQ_RX    = BIT(0),
    FLD_UART_IRQ_TX    = BIT(1),
} IRQ_UartIrqTypeDef;
extern void IRQ_UartDmaIrqEnable(unsigned int UARTIrqMask);
extern void IRQ_UartDmaIrqDisable(unsigned int UARTIrqMask);
extern unsigned char IRQ_UartDmaIrqSrcGet(void);
extern void IRQ_UartDmaIrqSrcClr(void);


#endif /* _IRQ_H_ */
