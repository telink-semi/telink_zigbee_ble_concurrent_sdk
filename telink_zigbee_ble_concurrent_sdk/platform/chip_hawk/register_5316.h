/********************************************************************************************************
 * @file     register_5316.h
 *
 * @brief    register configuration header file for hawk
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
#pragma once
#include "../../proj/common/types.h"
#include "irq.h"

#if defined(__cplusplus)
	extern "C" {
#endif

enum{
	FLD_EP_DAT_ACK  = 			BIT(0),
	FLD_EP_DAT_STALL =			BIT(1),
	FLD_EP_STA_ACK = 			BIT(2),
	FLD_EP_STA_STALL = 			BIT(3),
};

#define reg_rf_irq_mask			REG_ADDR16(0xf1c)
#define reg_rf_irq_status		REG_ADDR16(0xf20)

#define reg_dma_chn_en			REG_ADDR8(0x520)
#define reg_dma_chn_irq_msk		REG_ADDR8(0x521)
#define reg_dma_tx_rdy0			REG_ADDR8(0x524)
#define reg_dma_tx_rdy1			REG_ADDR8(0x525)
#define reg_dma_rx_rdy0			REG_ADDR8(0x526)
#define reg_dma_irq_src			reg_dma_rx_rdy0
#define reg_dma_rx_rdy1			REG_ADDR8(0x527)

#define reg_dma0_addr			REG_ADDR16(0x500)
#define reg_dma0_ctrl			REG_ADDR16(0x502)
#define reg_dma1_addr			REG_ADDR16(0x504)
#define reg_dma1_ctrl			REG_ADDR16(0x506)
#define reg_dma2_addr			REG_ADDR16(0x508)
#define reg_dma2_ctrl			REG_ADDR16(0x50a)
#define reg_dma3_addr			REG_ADDR16(0x50c)
#define reg_dma3_ctrl			REG_ADDR16(0x50e)
#define reg_dma4_addr			REG_ADDR16(0x510)
#define reg_dma4_ctrl			REG_ADDR16(0x512)
#define reg_dma5_addr			REG_ADDR16(0x514)
#define reg_dma5_ctrl			REG_ADDR16(0x516)

#define reg_dma_rf_rx_addr		reg_dma2_addr
#define reg_dma_rf_rx_ctrl		reg_dma2_ctrl
#define reg_dma_rf_tx_addr		reg_dma3_addr
#define reg_dma_rf_tx_ctrl		reg_dma3_ctrl

enum{
	FLD_DMA_UART_RX =			BIT(0),		//  not sure ???
	FLD_DMA_UART_TX =			BIT(1),
	FLD_DMA_RF_RX =				BIT(2),		//  not sure ???
	FLD_DMA_RF_TX =				BIT(3),
};

#define		RFDMA_RX_DISABLE		(reg_dma_chn_en &= (~FLD_DMA_RF_RX))
#define		RFDMA_RX_ENABLE			(reg_dma_chn_en |= (FLD_DMA_RF_RX))

#define		RFDMA_TX_DISABLE		(reg_dma_chn_en &= (~FLD_DMA_RF_TX))
#define		RFDMA_TX_ENABLE			(reg_dma_chn_en |= (FLD_DMA_RF_TX))

enum{
	FLD_DMA_BUF_SIZE =			BIT_RNG(0,7),
	FLD_DMA_WR_MEM =			BIT(8),
	FLD_DMA_PINGPONG_EN =		BIT(9),
	FLD_DMA_FIFO_EN =			BIT(10),
	FLD_DMA_AUTO_MODE =			BIT(11),
	FLD_DMA_BYTE_MODE =			BIT(12),
	FLD_DMA_FIFO8 	=			(BIT(15) | BIT(14) | FLD_DMA_WR_MEM | FLD_DMA_PINGPONG_EN),

	FLD_DMA_RPTR_CLR =			BIT(4),
	FLD_DMA_RPTR_NEXT =			BIT(5),
	FLD_DMA_RPTR_SET =			BIT(6),
};



enum{
	FLD_CTRL_EP_AUTO_ADDR = 	BIT(0),
	FLD_CTRL_EP_AUTO_CFG =		BIT(1),
	FLD_CTRL_EP_AUTO_INTF =		BIT(2),
	FLD_CTRL_EP_AUTO_STA =		BIT(3),
	FLD_CTRL_EP_AUTO_SYN =		BIT(4),
	FLD_CTRL_EP_AUTO_DESC =		BIT(5),
	FLD_CTRL_EP_AUTO_FEAT =		BIT(6),
	FLD_CTRL_EP_AUTO_STD =		BIT(7),
};

#define reg_irq_mask			REG_ADDR32(0x640)
#define reg_irq_pri				REG_ADDR32(0x644)
#define reg_irq_src				REG_ADDR32(0x648)
#define reg_irq_src3			REG_ADDR8(0x64a)

enum{
	FLD_CTRL_EP_IRQ_TRANS  = 	BIT_RNG(0,3),
	FLD_CTRL_EP_IRQ_SETUP  =	BIT(4),
	FLD_CTRL_EP_IRQ_DATA  =		BIT(5),
	FLD_CTRL_EP_IRQ_STA  = 		BIT(6),
	FLD_CTRL_EP_IRQ_INTF  = 	BIT(7),
};

enum{
	FLD_USB_EP_BUSY = 			BIT(0),
	FLD_USB_EP_STALL =			BIT(1),
	FLD_USB_EP_DAT0 =			BIT(2),
	FLD_USB_EP_DAT1 =			BIT(3),
	FLD_USB_EP_MONO =			BIT(6),
	FLD_USB_EP_EOF_ISO =		BIT(7),
};

#define reg_tmr_sta				REG_ADDR8(0x623)

#define reg_tmr0_capt			REG_ADDR32(0x624)
#define reg_tmr1_capt			REG_ADDR32(0x628)
#define reg_tmr2_capt			REG_ADDR32(0x62c)
#define reg_tmr_capt(i)			REG_ADDR32(0x624 + ((i) << 2))
#define reg_tmr0_tick			REG_ADDR32(0x630)
#define reg_tmr1_tick			REG_ADDR32(0x634)
#define reg_tmr2_tick			REG_ADDR32(0x638)
#define reg_tmr_tick(i)			REG_ADDR32(0x630 + ((i) << 2))

static inline void dma_channel_enable_all(){
	reg_dma_chn_en = 0xff;
}

static inline void dma_channel_disable_all(){
	reg_dma_chn_en = 0;
}

#define reg_system_tick			REG_ADDR32(0x740)
#define reg_system_tick_irq		REG_ADDR32(0x744)
#define reg_system_wakeup_tick	REG_ADDR32(0x748)
#define reg_system_tick_mode	REG_ADDR8(0x74c)
#define reg_system_tick_ctrl	REG_ADDR8(0x74f)

static inline u32 clock_time(){
	return reg_system_tick;
}

static inline u32 clock_time_exceed(u32 ref, u32 span_us){
	return ((u32)(clock_time() - ref) > span_us * CLOCK_SYS_CLOCK_1US);
}

#define reg_rnd_number			REG_ADDR16(0x448)

static inline u16 rand(void){
	return (u16)((reg_system_tick & 0xffff) ^ reg_rnd_number);
}


#if 0
// enalbe interrupt
static inline u8 irq_enable(){
	u8 r = reg_irq_en;		// don't worry,  the compiler will optimize the return value if not used
	reg_irq_en = 1;
	return r;
}
static inline u8 irq_disable(){
	u8 r = reg_irq_en;		// don't worry,  the compiler will optimize the return value if not used
	reg_irq_en = 0;
	return r;
}
static inline void irq_restore(u8 en){
	reg_irq_en = en;
}
#endif
#if 0
enum{
	FLD_IRQ_TMR0_EN =			BIT(0),
	FLD_IRQ_TMR1_EN =			BIT(1),
	FLD_IRQ_TMR2_EN =			BIT(2),
	FLD_IRQ_USB_PWDN_EN =		BIT(3),
	FLD_IRQ_DMA_EN =			BIT(4),
	FLD_IRQ_DAM_FIFO_EN =		BIT(5),
	FLD_IRQ_UART_EN 	=		BIT(6),
	FLD_IRQ_HOST_CMD_EN =		BIT(7),

	FLD_IRQ_EP0_SETUP_EN =		BIT(8),
	FLD_IRQ_EP0_DAT_EN =		BIT(9),
	FLD_IRQ_EP0_STA_EN =		BIT(10),
	FLD_IRQ_SET_INTF_EN =		BIT(11),
	FLD_IRQ_EP_DATA_EN =		BIT(12),
	FLD_IRQ_IRQ4_EN =			BIT(12),
	FLD_IRQ_ZB_RT_EN =			BIT(13),
	FLD_IRQ_SW_EN =				BIT(14),
	FLD_IRQ_AN_EN =				BIT(15),

	FLD_IRQ_USB_250US_EN =		BIT(16),
	FLD_IRQ_USB_RST_EN =		BIT(17),
	FLD_IRQ_GPIO_EN =			BIT(18),
	FLD_IRQ_PM_EN =				BIT(19),
	FLD_IRQ_SYSTEM_TIMER =		BIT(20),
	FLD_IRQ_GPIO_RISC0_EN =		BIT(21),
	FLD_IRQ_GPIO_RISC1_EN =		BIT(22),
	FLD_IRQ_GPIO_RISC2_EN = 	BIT(23),

	FLD_IRQ_EN =				BIT_RNG(24,31),
};
#endif
#if 0

#ifndef WIN32
	#define REG_BASE_ADDR			0x800000
#else
extern u8 reg_simu_buffer[];
	#define REG_BASE_ADDR			(&reg_simu_buffer[0])
#endif

#define REG_ADDR8(a)			(*(volatile u8*) (REG_BASE_ADDR + (a)))
#define REG_ADDR16(a)			(*(volatile u16*)(REG_BASE_ADDR + (a)))
#define REG_ADDR32(a)			(*(volatile u32*)(REG_BASE_ADDR + (a)))

/*----------------------------------------------------------------------------*/
/*------- IIC register define                                         --------*/
/*----------------------------------------------------------------------------*/
#define reg_i2c_set				REG_ADDR32(0x00)
#define reg_i2c_speed			REG_ADDR8(0x00)
#define reg_i2c_id		        REG_ADDR8(0x01)//I2C Master device Id
#define reg_i2c_slave_id        REG_ADDR8(0x28)//I2C Slave device Id
enum //Use for "reg_i2c_id" and "reg_i2c_slave_id"
{
	FLD_I2C_WRITE_READ_BIT  =  BIT(0),
	FLD_I2C_ID              =  BIT_RNG(1,7),
};

#define reg_i2c_status			REG_ADDR8(0x02)
enum
{
	FLD_I2C_CMD_BUSY		= 	BIT(0),
	FLD_I2C_BUS_BUSY		= 	BIT(1),
	FLD_I2C_NAK				= 	BIT(2),
};

#define reg_i2c_mode			REG_ADDR8(0x03)
enum
{
	FLD_I2C_ADDR_AUTO_INC   =	BIT(0),
	FLD_I2C_MASTER_EN		= 	BIT(1),//1:Enable master.
	FLD_I2C_SLAVE_MAPPING   =	BIT(2),//1:Mapping mode;0:DMA mode.
	FLD_I2C_HOLD_MASTER     =   BIT(3),
	FLD_I2C_SLAVE_EN        =   BIT(4),//1:Enable slave.
};

#define reg_i2c_adr_dat			REG_ADDR16(0x04)
#define reg_i2c_dat_ctrl		REG_ADDR32(0x04)
#define reg_i2c_di_ctrl			REG_ADDR16(0x06)
#define reg_i2c_adr				REG_ADDR8(0x04)
#define reg_i2c_do				REG_ADDR8(0x05)
#define reg_i2c_di				REG_ADDR8(0x06)
#define reg_i2c_ctrl			REG_ADDR8(0x07)
enum //Use for "reg_i2c_ctrl"
{
	FLD_I2C_CMD_ID		= BIT(0),
	FLD_I2C_CMD_ADR		= BIT(1),
	FLD_I2C_CMD_DO		= BIT(2),
	FLD_I2C_CMD_DI		= BIT(3),
	FLD_I2C_CMD_START	= BIT(4),
	FLD_I2C_CMD_STOP	= BIT(5),
	FLD_I2C_CMD_READ_ID	= BIT(6),
	FLD_I2C_CMD_NAK		= BIT(7),
};

#define reg_i2c_irq_status		REG_ADDR8(0x21)
enum{
	FLD_I2C_STATUS_WR = BIT(0),
	FLD_SPI_STATUS_WR = BIT(0),
	FLD_I2C_STATUS_RD = BIT(1),
};

#define reg_i2c_mem_map			REG_ADDR16(0x22)


/*----------------------------------------------------------------------------*/
/*------- SPI register define                                         --------*/
/*----------------------------------------------------------------------------*/
#define reg_spi_data			REG_ADDR8(0x08)
#define reg_spi_ctrl			REG_ADDR8(0x09)
enum //Use for "reg_spi_ctrl"
{
	FLD_SPI_CS           = BIT(0),
	FLD_SPI_MASTER_EN    = BIT(1),
	FLD_SPI_DATA_OUT_DIS = BIT(2),
	FLD_SPI_RD           = BIT(3),
	FLD_SPI_ADDR_AUTO_EN = BIT(4),
	FLD_SPI_SLAVE_EN     = BIT(6),
	FLD_SPI_BUSY         = BIT(7),
};

#define reg_spi_sp				REG_ADDR8(0x0a)
enum{
	FLD_MASTER_SPI_CLK = BIT_RNG(0,6),
	FLD_SPI_ENABLE     = BIT(7),
};

#define reg_spi_inv_clk			REG_ADDR8(0x0b)
enum{
	FLD_INVERT_SPI_CLK   = BIT(0),
	FLD_DAT_DLY_HALF_CLK = BIT(1),
};

#define reg_spi_irq_status      reg_i2c_irq_status


/*----------------------------------------------------------------------------*/
/*------- MSPI(Memory SPI) register define                            --------*/
/*----------------------------------------------------------------------------*/
#define reg_master_spi_data		REG_ADDR8(0x0c)
#define reg_master_spi_ctrl		REG_ADDR8(0x0d)
enum //Use for "reg_master_spi_ctrl"
{
	FLD_MASTER_SPI_CS   = BIT(0),
	FLD_MASTER_SPI_SDO  = BIT(1),
	FLD_MASTER_SPI_CONT = BIT(2),
	FLD_MASTER_SPI_RD   = BIT(3),
	FLD_MASTER_SPI_BUSY = BIT(4),
};

#define reg_mspi_mode      		REG_ADDR8(0x0f)
enum
{
	FLD_MSPI_Mode_Dual_Data  = BIT(0),
	FLD_MSPI_Mode_Dual_Addr  = BIT(1),
	FLD_MSPI_Speed     	     = BIT_RNG(2,7),
};


/****************************************************
 otp regs struct: begin  addr : 0x10
 *****************************************************/
#define reg_otp_addr_para		REG_ADDR16(0x10)
enum{
	FLD_OTP_PARA_ADDR = 		BIT_RNG(0,12),
	FLD_OTP_PARA_PTM = 			BIT_RNG(13,15),
};

#define reg_otp_ctrl			REG_ADDR8(0x12)
enum{
	FLD_OTP_CTRL_PCEN = 		BIT(0),
	FLD_OTP_FAST_CLK = 			BIT(1),
	FLD_OTP_OEN = 				BIT(2),
	FLD_OTP_CLK = 				BIT(3),
	FLD_OTP_PCEN_PWDN = 		BIT(4),
	FLD_OTP_WEN_PWDN = 			BIT(5),
	FLD_OTP_OEN_PWDN = 			BIT(6),
	FLD_OTP_CLK_PWDN = 			BIT(7),
};

#define reg_otp_byte_dat		REG_ADDR8(0x13)
#define reg_otp_dat				REG_ADDR32(0x14)
#define reg_otp_blk_code		REG_ADDR8(0x18)


/*----------------------------------------------------------------------------*/
/*------ Reset And Clock register define                                ------*/
/*----------------------------------------------------------------------------*/
#define reg_rst0				REG_ADDR8(0x60)
#define reg_rst0_16				REG_ADDR16(0x60)
#define reg_rst1				REG_ADDR8(0x61)
#define reg_rst2				REG_ADDR8(0x62)
#define reg_rst_clk0			REG_ADDR32(0x60)
enum //Use for "reg_rst_clk0"
{
	FLD_RST_SPI = 				BIT(0),
	FLD_RST_I2C = 				BIT(1),
	FLD_RST_NA_2 = 			    BIT(2),
	FLD_RST_NA_3 = 		   	    BIT(3),
	FLD_RST_MCU = 				BIT(4),
	FLD_RST_NA_5 =		        BIT(5),
	FLD_RST_AIF = 				BIT(6),
	FLD_RST_BB = 				BIT(7),
	FLD_RST_ZB =				BIT(7),

	FLD_RST_SYS_TIMER =			BIT(8),
	FLD_RST_ALGM = 				BIT(9),
	FLD_RST_DMA =				BIT(10),
	FLD_RST_UART = 				BIT(11),
	FLD_RST_PWM = 				BIT(12),
	FLD_RST_AES = 				BIT(13),
	FLD_RST_NA_14 =  			BIT(14),
	FLD_RST_SWR_S =				BIT(15),

	FLD_RST_NA_16 =				BIT(16),
	FLD_RST_NA_17 =				BIT(17),
	FLD_RST_NA_18 =				BIT(18),
	FLD_RST_ADC =				BIT(19),
	FLD_RST_MCIC =			    BIT(20),
	FLD_RST_SOFT_MCIC = 		BIT(21),
	FLD_RST_NA_22 =			    BIT(22),
	FLD_RST_ALG =				BIT(23),

	FLD_CLK_SPI_EN =			BIT(24),
	FLD_CLK_I2C_EN =			BIT(25),
	FLD_CLK_HOSTIRQ =			BIT(26),
	FLD_CLK_NA_27 =		        BIT(27),
	FLD_CLK_MCU_EN =			BIT(28),
	FLD_CLK_FPU_EN =			BIT(29),
	FLD_CLK_AIF_EN =			BIT(30),
	FLD_CLK_ZB_EN =				BIT(31),
};

#define reg_clk_en				REG_ADDR16(0x64)
enum{
	FLD_CLK_SYS_TIMER_16M_AND_SYSCLK_EN = BIT(0),
	FLD_CLK_ALGM_EN = 			BIT(1),
	FLD_CLK_DMA_EN = 			BIT(2),
	FLD_CLK_UART_EN = 			BIT(3),
	FLD_CLK_PWM_EN = 			BIT(4),
	FLD_CLK_AES_EN = 			BIT(5),
	FLD_CLK_32K_TIMER_EN =		BIT(6),
	FLD_CLK_SWIRE_EN = 			BIT(7),

	FLD_CLK_32K_QDEC_EN =		BIT(8),
	FLD_CLK_NA_9 =			    BIT(9),
	FLD_CLK_NA_10 = 			BIT(10),
	FLD_CLK_NA_11 =		        BIT(11),
	FLD_CLK_MCIC_EN =			BIT(12),
	FLD_CLK_QDEC_EN =			BIT(13),
	FLD_CLK_NA_14 =			    BIT(14),
	FLD_CLK_NA_15 =			    BIT(15),
};

#define reg_clk_en0             REG_ADDR8(0x63)
enum
{
	FLD_CLK_EN0_SPI_EN     = BIT(0),
	FLD_CLK_EN0_I2C_EN     = BIT(1),
	FLD_CLK_EN0_HOSTIRQ_EN = BIT(2),
	FLD_CLK_EN0_NA_3       = BIT(3),
	FLD_CLK_EN0_MCU_EN     = BIT(4),
	FLD_CLK_EN0_FPU_EN     = BIT(5),
	FLD_CLK_EN0_AIF_EN     = BIT(6),
	FLD_CLK_EN0_ZB_EN      = BIT(7),
};

#define reg_clk_en1				REG_ADDR8(0x64)
enum
{
	FLD_CLK_EN1_SYS_TIMER_16M_EN = BIT(0),
	FLD_CLK_EN1_ALGM_EN          = BIT(1),
	FLD_CLK_EN1_DMA_EN           = BIT(2),
	FLD_CLK_EN1_UART_EN          = BIT(3),
	FLD_CLK_EN1_PWM_EN           = BIT(4),
	FLD_CLK_EN1_AES_EN           = BIT(5),
	FLD_CLK_EN1_SYS_TIMER_32K_EN = BIT(6),
	FLD_CLK_EN1_SWS_EN           = BIT(7),
};

#define reg_clk_en2				REG_ADDR8(0x65)
enum{
	FLD_CLK_EN2_QDEC_32K_EN     = BIT(0),
	FLD_CLK_EN2_MCIC_EN         = BIT(4),
	FLD_CLK_EN2_QDEC_SYS_CLK_EN = BIT(5),
};

#define reg_clk_sel				REG_ADDR8(0x66)
enum{
	FLD_CLK_SEL_FHS_DIV         = BIT_RNG(0,4),
	FLD_CLK_SEL_SYS_CLK_SRC_SEL = BIT_RNG(5,6),
	FLD_CLK_SEL_FHS_CLK_SRC_SEL = BIT(7),
};

#define reg_fhs_sel				REG_ADDR8(0x70)
enum{
	FLD_FHS_SEL = BIT(0),
};

#define reg_wakeup_en			REG_ADDR8(0x6e)
enum{

	//Digital wake-up source.
	FLD_WAKEUP_SRC_GPIO    = BIT(3),
	FLD_WAKEUP_SRC_QDEC    = BIT(4),
	FLD_WAKEUP_SRC_RST_SYS = BIT(7),
};

#define reg_pwdn_ctrl			REG_ADDR8(0x6f)
enum
{
	FLD_PWDN_CTRL_REBOOT = BIT(5),
	FLD_PWDN_CTRL_SLEEP  = BIT(7),
};

/* RESET and CLKEN register bit define. --------------------------------------*/

/*  RST0 register bit define. */
typedef union
{
	u8 All;
	struct
	{
		u8 SPI_Bit :1;
		u8 I2C_Bit :1;
		u8 :1;
		u8 :1;
		u8 MCU_Bit :1;
		u8 :1;
		u8 AIF_Bit :1;
		u8 ZB_Bit  :1;
	}Bits;
}RST0_Type;

/*  RST1 register bit define. */
typedef union
{
	u8 All;
	struct
	{
		u8 SysTimer_16M_Bit :1;
		u8 ALGM_Bit :1;
		u8 DMA_Bit  :1;
		u8 UART_Bit :1;
		u8 PWM_Bit  :1;
		u8 AES_Bit  :1;
		u8 :1;
		u8 SWS_Bit :1;
	}Bits;
}RST1_Type;

/*  RST2 register bit define. */
typedef union
{
	u8 All;
	struct
	{
		u8 :1;
		u8 :1;
		u8 :1;
		u8 ADC_Bit :1;
		u8 MCIC_Bit :1;
		u8 MCIC_SOFT_RST_Bit :1;
		u8 :1;
		u8 ALG_Bit :1;
	}Bits;
}RST2_Type;


/*  CLKEn0 register bit define. */
typedef union
{
	u8 All;
	struct
	{
		u8 SPI_Bit   : 1;
		u8 I2C_Bit   : 1;
		u8 HOST_IRQ  : 1;
		u8  : 1;
		u8 MCU_Bit   : 1;
		u8 FPU_Bit   : 1;
		u8 AIF_Bit   : 1;
		u8 ZB_Bit    : 1;
	}Bits;
}CLKEn0_Type;

/*  CLKEn1 register bit define. */
typedef union
{
	u8 All;
	struct
	{
		u8 SysTimer_16M_Bit : 1;
		u8 ALGM_Bit		    : 1;
		u8 DMA_Bit          : 1;
		u8 UART_Bit         : 1;
		u8 PWM_Bit          : 1;
		u8 AES_Bit          : 1;
		u8 SysTimer_32K_Bit : 1;
		u8 SWS_Bit : 1;
	}Bits;
}CLKEn1_Type;

/*  CLKEn2 register bit define. */
typedef union
{
	u8 All;
	struct
	{
		u8 QDEC_32K_Bit : 1;
		u8  : 1;
		u8  : 1;
		u8  : 1;
		u8  MCIC_Bit: 1;
		u8  QDEC_SysClk_Bit : 1;
		u8  : 1;
		u8  : 1;
	}Bits;
}CLKEn2_Type;


/* RESET and CLKEN register struct define. -----------------------------------*/

/*  RST register struct define. */
typedef struct
{
	RST0_Type   RST0;
	RST1_Type	RST1;
	RST2_Type   RST2;
}RESET_TypeDef;

/*  CLKEn register struct define. */
typedef struct
{
	CLKEn0_Type ClkEn0;
	CLKEn1_Type ClkEn1;
	CLKEn2_Type ClkEn2;
}CLK_TypeDef;

/* System Clock Select register bit define. */
typedef union
{
	volatile u8 ClkSelAll;
	struct
	{
		u8 SYS_CLK_SRC_DIV :5;
		u8 SYS_CLK_SRC     :2;
		u8 FHS_CLK_SRC_L   :1;
	}ClkSelBits;
}SYSCLK_TypeDef;

#define RESET  		  ((RESET_TypeDef*)(REG_BASE_ADDR + 0x60))
#define CLOCK_EN      ((CLK_TypeDef*)(REG_BASE_ADDR + 0x63))
#define SYSCLK_SEL    ((SYSCLK_TypeDef*)(REG_BASE_ADDR + 0x66))


/****************************************************
  OTP  addr : 0x71
 *****************************************************/
#define reg_dcdc_clk			REG_ADDR8(0x71)

/****************************************************
 dev_id regs struct: begin  addr : 0x74
 *****************************************************/
//#define reg_id_wr_en			REG_ADDR8(0x74)
//#define reg_product_id			REG_ADDR32(0x7c)
//#define reg_func_id				REG_ADDR8(0x7c)
//enum{
//	FLD_ID_USB_SYS_CLOCK = 		BIT(0),
//	FLD_ID_MAC_CLOCK = 			BIT(1),
//	FLD_ID_SBC_CLOCK = 			BIT(2),
//	FLD_ID_RISC32_ENABLE = 		BIT(3),
//	FLD_ID_I2S_ENABLE = 		BIT(4),
//	FLD_ID_SDM_ENABLE = 		BIT(5),
//	FLD_ID_RF_ENABLE = 			BIT(6),
//	FLD_ID_ZB_ENABLE = 			BIT(7),
//};
//
//#define reg_ver_id				REG_ADDR8(0x7d)
//#define reg_prod_id				REG_ADDR16(0x7e)
//
#define reg_mcu_wakeup_mask		REG_ADDR32(0x78)

/****************************************************
 mac regs struct: begin  addr : 0xa0
 *****************************************************/
//#define reg_mac_ctrl			REG_ADDR8(0x80)
//enum{
//	FLD_MAC_CTRL_TX_EN = 		BIT(0),
//	FLD_MAC_CTRL_RX_EN =		BIT(1),
//	FLD_MAC_CTRL_SPD_100M =		BIT(6),
//	FLD_MAC_CTRL_PHY_RST =		BIT(7),
//};
//
//#define reg_mac_irq_sta			REG_ADDR8(0x81)
//enum{
//	FLD_MAC_STA_TX_DONE = 		BIT(0),
//	FLD_MAC_STA_RX_DONE =		BIT(1),
//	FLD_MAC_STA_TX_ERR =		BIT(2),
//	FLD_MAC_STA_RX_ERR =		BIT(3),
//	FLD_MAC_STA_RX_CRC =		BIT(4),
//};
//
//#define reg_mii_tx_data			REG_ADDR16(0x82)
//#define reg_mii_rx_data			REG_ADDR16(0x84)
//#define reg_mii_clk				REG_ADDR8(0x86)
//enum{
//	FLD_MII_PHY_ID  = 			BIT_RNG(0,4),
//	FLD_MII_CLK_DIV =			BIT_RNG(5,7),
//};
//#define reg_mii_ctrl			REG_ADDR8(0x87)
//enum{
//	FLD_MII_INTERNAL_REG  = 	BIT_RNG(0,4),
//	FLD_MII_BUSY =				BIT(5),
//	FLD_MII_WR =				BIT(6),
//	FLD_MII_PREAM_EN =			BIT(7),
//};

/*----------------------------------------------------------------------------*/
/*------  UART register define                                          ------*/
/*----------------------------------------------------------------------------*/
#define reg_uart_clk_div		REG_ADDR16(0x94)
enum{
	FLD_UART_CLK_DIV    = BIT_RNG(0,14),
	FLD_UART_CLK_DIV_EN = BIT(15)
};

#define reg_uart_ctrl0			REG_ADDR16(0x96)
enum{
	FLD_UART_BWPC      = BIT_RNG(0,3),// must larger than 2.
	FLD_UART_RX_DMA_EN = BIT(4),
	FLD_UART_TX_DMA_EN = BIT(5),
	FLD_UART_RX_IRQ_EN = BIT(6),
	FLD_UART_TX_IRQ_EN = BIT(7),

	FLD_UART_CTS_I_SELECT =	BIT(8),
	FLD_UART_CTS_EN       = BIT(9),
	FLD_UART_PARITY_EN    =	BIT(10),
    FLD_UART_PARITY_SEL   = BIT(11),
    FLD_UART_STOP_BIT     = BIT_RNG(12,13),
    FLD_UART_TTL          = BIT(14),
    FLD_UART_LOOPBACK     = BIT(15),
};

#define reg_uart_ctrl2         REG_ADDR16(0x98)
enum {
    FLD_UART_CTRL2_RTS_TRIG_LVL   = BIT_RNG(0,3),
    FLD_UART_CTRL2_RTS_PARITY     = BIT(4),
    FLD_UART_CTRL2_RTS_MANUAL_VAL = BIT(5),
    FLD_UART_CTRL2_RTS_MANUAL_EN  = BIT(6),
    FLD_UART_CTRL2_RTS_EN         = BIT(7),

	FLD_UART_CTRL3_RX_IRQ_TRIG_LEVEL = BIT_RNG(8,11),
	FLD_UART_CTRL3_TX_IRQ_TRIG_LEVEL = BIT_RNG(12,15),
};

typedef union
{
	u8 All;
	struct
	{
		u8 RTS_TriggerLevel     :4;
		u8 RTS_ValueInvert      :1;
		u8 RTS_Value            :1;
		u8 RTS_ManualModeEnable :1;
		u8 RTS_Enable           :1;
	}Bits;
}UART_RtsTypeDef;
#define UART_CTRL2    ((UART_RtsTypeDef*)(REG_BASE_ADDR + 0x98))

#define reg_uart_rx_timeout		REG_ADDR16(0x9a)
enum{
	FLD_UART_TIMEOUT_BW = 		BIT_RNG(0,7),		//  timeout bit width
	FLD_UART_TIMEOUT_MUL = 		BIT_RNG(8,9),
};


#define reg_uart_status0       REG_ADDR8(0x9d)
enum{
	FLD_UART_IRQ_FLAG    = BIT(3),
	FLD_UART_RX_ERR_CLR  = BIT(6),
	FLD_UART_RX_ERR_FLAG = BIT(7),
};
#define reg_uart_status1       REG_ADDR8(0x9e)
enum{
	FLD_UART_TX_DONE    = BIT(0),
	FLD_UART_TX_BUF_IRQ = BIT(1),
	FLD_UART_RX_DONE    = BIT(2),
	FLD_UART_RX_BUF_IRQ = BIT(3),
};

/*----------------------------------------------------------------------------*/
/*------  SWS register define                                           ------*/
/*----------------------------------------------------------------------------*/
#define reg_swire_data			REG_ADDR8(0xb0)
#define reg_swire_ctrl1			REG_ADDR8(0xb1)
enum //Use for "reg_swire_ctrl1"
{
	FLD_SWIRE_WR  = 			BIT(0),
	FLD_SWIRE_RD  = 			BIT(1),
	FLD_SWIRE_CMD =				BIT(2),
	FLD_SWIRE_USB_DET =			BIT(6),
	FLD_SWIRE_USB_EN =			BIT(7),
};

#define reg_swire_clk_div		REG_ADDR8(0xb2)
enum
{
	FLD_SWIRE_CLK_DIV_Pos = BIT_RNG(0,6),
};

#define reg_swire_id      		REG_ADDR8(0xb3)
enum
{
	FLD_SWIRE_ID_SLAVE_ID_Pos      = BIT_RNG(0,6),
	FLD_SWIRE_ID_SLAVE_FIFO_EN_Pos = BIT(7),
};

/*----------------------------------------------------------------------------*/
/*------  Analog register(ALG) Read/Write Control register define       ------*/
/*----------------------------------------------------------------------------*/
#define reg_ana_ctrl32			REG_ADDR32(0xb8)	// for performance, set addr and data at a time
#define reg_ana_addr_data		REG_ADDR16(0xb8)	// for performance, set addr and data at a time
#define reg_ana_addr			REG_ADDR8(0xb8)
#define reg_ana_data			REG_ADDR8(0xb9)
#define reg_ana_ctrl			REG_ADDR8(0xba)
enum // 文档不正确，请使用以下定义.Use for "reg_ana_ctrl"
{
	FLD_ANA_BUSY  = 			BIT(0),
	FLD_ANA_RSV	=				BIT(4),
	FLD_ANA_RW  = 				BIT(5),
	FLD_ANA_START  = 			BIT(6),
	FLD_ANA_CYC  = 				BIT(7),
};

/****************************************************
 USB regs struct: begin  addr : 0x100
 *****************************************************/
#define reg_ctrl_ep_ptr			REG_ADDR8(0x100)
#define reg_ctrl_ep_dat			REG_ADDR8(0x101)
#define reg_ctrl_ep_ctrl		REG_ADDR8(0x102)

// same for all endpoints
enum{
	FLD_EP_DAT_ACK  = 			BIT(0),
	FLD_EP_DAT_STALL =			BIT(1),
	FLD_EP_STA_ACK = 			BIT(2),
	FLD_EP_STA_STALL = 			BIT(3),
};

#define reg_ctrl_ep_irq_sta		REG_ADDR8(0x103)
enum{
	FLD_CTRL_EP_IRQ_TRANS  = 	BIT_RNG(0,3),
	FLD_CTRL_EP_IRQ_SETUP  =	BIT(4),
	FLD_CTRL_EP_IRQ_DATA  =		BIT(5),
	FLD_CTRL_EP_IRQ_STA  = 		BIT(6),
	FLD_CTRL_EP_IRQ_INTF  = 	BIT(7),
};

#define reg_ctrl_ep_irq_mode	REG_ADDR8(0x104)
enum{
	FLD_CTRL_EP_AUTO_ADDR = 	BIT(0),
	FLD_CTRL_EP_AUTO_CFG =		BIT(1),
	FLD_CTRL_EP_AUTO_INTF =		BIT(2),
	FLD_CTRL_EP_AUTO_STA =		BIT(3),
	FLD_CTRL_EP_AUTO_SYN =		BIT(4),
	FLD_CTRL_EP_AUTO_DESC =		BIT(5),
	FLD_CTRL_EP_AUTO_FEAT =		BIT(6),
	FLD_CTRL_EP_AUTO_STD =		BIT(7),
};

#define reg_usb_ctrl			REG_ADDR8(0x105)
enum{
	FLD_USB_CTRL_AUTO_CLK = 	BIT(0),
	FLD_USB_CTRL_LOW_SPD = 		BIT(1),
	FLD_USB_CTRL_LOW_JITT =		BIT(2),
	FLD_USB_CTRL_TST_MODE = 	BIT(3),
};

#define reg_usb_cyc_cali		REG_ADDR16(0x106)
#define reg_usb_mdev			REG_ADDR8(0x10a)
#define reg_usb_host_conn		REG_ADDR8(0x10b)
enum{
	FLD_USB_MDEV_SELF_PWR = 	BIT(0),
	FLD_USB_MDEV_SUSP_STA = 	BIT(1),
};

#define reg_usb_sups_cyc_cali	REG_ADDR8(0x10c)
#define reg_usb_intf_alt		REG_ADDR8(0x10d)

#define reg_usb_ep8123_ptr		REG_ADDR32(0x110)
#define reg_usb_ep8_ptr			REG_ADDR8(0x110)
#define reg_usb_ep1_ptr			REG_ADDR8(0x111)
#define reg_usb_ep2_ptr			REG_ADDR8(0x112)
#define reg_usb_ep3_ptr			REG_ADDR8(0x113)
#define reg_usb_ep4567_ptr		REG_ADDR32(0x114)
#define reg_usb_ep4_ptr			REG_ADDR8(0x114)
#define reg_usb_ep5_ptr			REG_ADDR8(0x115)
#define reg_usb_ep6_ptr			REG_ADDR8(0x116)
#define reg_usb_ep7_ptr			REG_ADDR8(0x117)
#define reg_usb_ep_ptr(i)		REG_ADDR8(0x110+((i) & 0x07))

#define reg_usb_ep8123_dat		REG_ADDR32(0x118)
#define reg_usb_ep8_dat			REG_ADDR8(0x118)
#define reg_usb_ep1_dat			REG_ADDR8(0x119)
#define reg_usb_ep2_dat			REG_ADDR8(0x11a)
#define reg_usb_ep3_dat			REG_ADDR8(0x11b)
#define reg_usb_ep4567_dat		REG_ADDR32(0x11c)
#define reg_usb_ep4_dat			REG_ADDR8(0x11c)
#define reg_usb_ep5_dat			REG_ADDR8(0x11d)
#define reg_usb_ep6_dat			REG_ADDR8(0x11e)
#define reg_usb_ep7_dat			REG_ADDR8(0x11f)
#define reg_usb_ep_dat(i)		REG_ADDR8(0x118+((i) & 0x07))

#define reg_usb_ep8_ctrl		REG_ADDR8(0x120)
#define reg_usb_ep1_ctrl		REG_ADDR8(0x121)
#define reg_usb_ep2_ctrl		REG_ADDR8(0x122)
#define reg_usb_ep3_ctrl		REG_ADDR8(0x123)
#define reg_usb_ep4_ctrl		REG_ADDR8(0x124)
#define reg_usb_ep5_ctrl		REG_ADDR8(0x125)
#define reg_usb_ep6_ctrl		REG_ADDR8(0x126)
#define reg_usb_ep7_ctrl		REG_ADDR8(0x127)
#define reg_usb_ep_ctrl(i)		REG_ADDR8(0x120+((i) & 0x07))

enum{
	FLD_USB_EP_BUSY = 			BIT(0),
	FLD_USB_EP_STALL =			BIT(1),
	FLD_USB_EP_DAT0 =			BIT(2),
	FLD_USB_EP_DAT1 =			BIT(3),
	FLD_USB_EP_MONO =			BIT(6),
	FLD_USB_EP_EOF_ISO =		BIT(7),
};

#define reg_usb_ep8123_buf_addr	REG_ADDR32(0x128)
#define reg_usb_ep8_buf_addr	REG_ADDR8(0x128)
#define reg_usb_ep1_buf_addr	REG_ADDR8(0x129)
#define reg_usb_ep2_buf_addr	REG_ADDR8(0x12a)
#define reg_usb_ep3_buf_addr	REG_ADDR8(0x12b)
#define reg_usb_ep4567_buf_addr	REG_ADDR32(0x12c)
#define reg_usb_ep4_buf_addr	REG_ADDR8(0x12c)
#define reg_usb_ep5_buf_addr	REG_ADDR8(0x12d)
#define reg_usb_ep6_buf_addr	REG_ADDR8(0x12e)
#define reg_usb_ep7_buf_addr	REG_ADDR8(0x12f)
#define reg_usb_ep_buf_addr(i)	REG_ADDR8(0x128+((i) & 0x07))

#define reg_usb_ram_ctrl		REG_ADDR8(0x130)
enum{
	FLD_USB_CEN_PWR_DN =		BIT(0),
	FLD_USB_CLK_PWR_DN =		BIT(1),
	FLD_USB_WEN_PWR_DN =		BIT(3),
	FLD_USB_CEN_FUNC =			BIT(4),
};

#define reg_usb_iso_mode		REG_ADDR8(0x138)
#define reg_usb_irq				REG_ADDR8(0x139)
#define reg_usb_mask			REG_ADDR8(0x13a)
#define reg_usb_ep8_send_max	REG_ADDR8(0x13b)
#define reg_usb_ep8_send_thre	REG_ADDR8(0x13c)
#define reg_usb_ep8_fifo_mode	REG_ADDR8(0x13d)
#define reg_usb_ep_max_size		REG_ADDR8(0x13e)

enum{
	FLD_USB_ENP8_FIFO_MODE =	BIT(0),
	FLD_USB_ENP8_FULL_FLAG =	BIT(1),
};
//#define reg_rf_irq_mask			REG_ADDR16(0xf1c)
//#define reg_rf_irq_status		REG_ADDR16(0xf20)
/****************************************************
	RF : begin  addr : 0x4e8
 *****************************************************/
#define reg_rf_tx_mode1			REG_ADDR8(0x400)
#define reg_rf_tx_mode			REG_ADDR16(0x400)
enum{
	FLD_RF_TX_DMA_EN =			BIT(0),
	FLD_RF_TX_CRC_EN =			BIT(1),
	FLD_RF_TX_BANDWIDTH =		BIT_RNG(2,3),
	FLD_RF_TX_OUTPUT = 			BIT(4),
	FLD_RF_TX_TST_OUT =			BIT(5),
	FLD_RF_TX_TST_EN =			BIT(6),
	FLD_RF_TX_TST_MODE =		BIT(7),
	FLD_RF_TX_ZB_PN_EN =		BIT(8),
	FLD_RF_TX_ZB_FEC_EN =		BIT(9),
	FLD_RF_TX_ZB_INTL_EN =		BIT(10),	// interleaving
	FLD_RF_TX_1M2M_PN_EN =		BIT(11),
	FLD_RF_TX_1M2M_FEC_EN =		BIT(12),
	FLD_RF_TX_1M2M_INTL_EN =	BIT(13), 	// interleaving
};
#define reg_rf_tx_buf_sta		REG_ADDR32(0x41c)

#define reg_rf_rx_sense_thr		REG_ADDR8(0x422)
#define reg_rf_rx_auto			REG_ADDR8(0x426)
enum{
	FLD_RF_RX_IRR_GAIN =		BIT(0),
	FLD_RF_RX_IRR_PHASE =		BIT(1),
	FLD_RF_RX_DAC_I =			BIT(2),
	FLD_RF_RX_DAC_Q =			BIT(3),
	FLD_RF_RX_LNA_GAIN =		BIT(4),
	FLD_RF_RX_MIX2_GAIN =		BIT(5),
	FLD_RF_RX_PGA_GAIN =		BIT(6),
	FLD_RF_RX_CAL_EN =			BIT(7),
};
#define reg_rf_rx_sync			REG_ADDR8(0x427)
enum{
	FLD_RF_FREQ_COMP_EN =		BIT(0),
	FLD_RF_ADC_SYNC =			BIT(1),
	FLD_RF_ADC_INP_SIGNED =		BIT(2),
	FLD_RF_SWAP_ADC_IQ =		BIT(3),
	FLD_RF_NOTCH_FREQ_SEL =		BIT(4),
	FLD_RF_NOTCH_BAND_SEL = 	BIT(5),
	FLD_RF_NOTCH_EN = 			BIT(6),
	FLD_RF_DN_CONV_FREQ_SEL =	BIT(7),
};

#define reg_rf_rx_mode			REG_ADDR8(0x428)
enum{
	FLD_RF_RX_EN =				BIT(0),
	FLD_RF_RX_MODE_1M =			BIT(1),
	FLD_RF_RX_MODE_2M =			BIT(2),
	FLD_RF_RX_LOW_IF =			BIT(3),
	FLD_RF_RX_BYPASS_DCOC =		BIT(4),
	FLD_RF_RX_MAN_FINE_TUNE = 	BIT(5),
	FLD_RF_RX_SINGLE_CAL =		BIT(6),
	FLD_RF_RX_LOW_PASS_FILTER =	BIT(7),
};

#define reg_rf_rx_pilot			REG_ADDR8(0x42b)
enum{
	FLD_RF_PILOT_LEN =			BIT_RNG(0,3),
	FLD_RF_ZB_SFD_CHK =			BIT(4),
	FLD_RF_1M_SFD_CHK =			BIT(5),
	FLD_RF_2M_SFD_CHK = 		BIT(6),
	FLD_RF_ZB_OR_AUTO = 		BIT(7),
};

#define reg_rf_rx_chn_dc		REG_ADDR32(0x42c)
#define reg_rf_rx_q_chn_cal		REG_ADDR8(0x42f)
enum{
	FLD_RF_RX_DCQ_HIGH =		BIT_RNG(0,6),
	FLD_RF_RX_DCQ_CAL_START =	BIT(7),
};
#define reg_rf_rx_pel			REG_ADDR16(0x434)
#define reg_rf_rx_pel_gain		REG_ADDR32(0x434)
#define reg_rf_rx_rssi_offset	REG_ADDR8(0x439)

#define reg_rf_rx_hdx			REG_ADDR8(0x43b)
enum{
	FLD_RX_HEADER_LEN =			BIT_RNG(0,3),
	FLD_RT_TICK_LO_SEL = 		BIT(4),
	FLD_RT_TICK_HI_SEL = 		BIT(5),
	FLD_RT_TICK_FRAME = 		BIT(6),
	FLD_PKT_LEN_OUTP_EN = 		BIT(7),
};

#define reg_rf_rx_gctl			REG_ADDR8(0x43c)
enum{
	FLD_RX_GCTL_CIC_SAT_LO_EN =	BIT(0),
	FLD_RX_GCTL_CIC_SAT_HI_EN = BIT(1),
	FLD_RX_GCTL_AUTO_PWR =		BIT(2),
	FLD_RX_GCTL_ADC_RST_VAL =	BIT(4),
	FLD_RX_GCTL_ADC_RST_EN =	BIT(5),
	FLD_RX_GCTL_PWR_CHG_DET_S =	BIT(6),
	FLD_RX_GCTL_PWR_CHG_DET_N = BIT(7),
};
#define reg_rf_rx_peak			REG_ADDR8(0x43d)
enum{
	FLD_RX_PEAK_DET_SRC_EN =	BIT_RNG(0,2),
	FLD_TX_PEAK_DET_EN =		BIT(3),
	FLD_PEAK_DET_NUM =			BIT_RNG(4,5),
	FLD_PEAK_MAX_CNT_PRD =		BIT_RNG(6,7),
};

#define reg_rf_rx_status		REG_ADDR8(0x443)
enum{
	FLD_RF_RX_STATE =			BIT_RNG(0,3),
	FLD_RF_RX_STA_RSV = 		BIT_RNG(4,5),
	FLD_RF_RX_INTR = 			BIT(6),
	FLD_RF_TX_INTR =			BIT(7),
};

#define reg_rf_irq_mask			REG_ADDR16(0xf1c)
#define reg_rf_irq_status		REG_ADDR16(0xf20)
#define reg_rf_fsm_timeout		REG_ADDR32(0xf2c)

#define		CLEAR_ALL_RFIRQ_STATUS   ( reg_rf_irq_status = 0xffff )

enum{
	FLD_RF_IRQ_RX = 			BIT(0),
	FLD_RF_IRQ_TX =				BIT(1),
	FLD_RF_IRQ_RX_TIMEOUT =		BIT(2),
	FLD_RF_IRQ_CRC =			BIT(4),
	FLD_RF_IRQ_CMD_DONE  =		BIT(5),
	FLD_RF_IRQ_FSM_TIMEOUT  =	BIT(6),
	FLD_RF_IRQ_RETRY_HIT =		BIT(7),
	FLD_RF_IRQ_FIRST_TIMEOUT =	BIT(10),
};


enum{
	FLD_RF_IRX_RX_TIMEOUT =		BIT(2),
	FLD_RF_IRX_CMD_DONE  =		BIT(5),
	FLD_RF_IRX_RETRY_HIT =		BIT(7),
};

// The value for FLD_RF_RX_STATE
enum{
	RF_RX_STA_IDLE = 0,
	RF_RX_STA_SET_GAIN = 1,
	RF_RX_STA_CIC_SETTLE = 2,
	RF_RX_STA_LPF_SETTLE = 3,
	RF_RX_STA_PE = 4,
	RF_RX_STA_SYN_START = 5,
	RF_RX_STA_GLOB_SYN = 6,
	RF_RX_STA_GLOB_LOCK = 7,
	RF_RX_STA_LOCAL_SYN = 8,
	RF_RX_STA_LOCAL_LOCK = 9,
	RF_RX_STA_ALIGN = 10,
	RF_RX_STA_ADJUST = 11,
	RF_RX_STA_DEMOD = 12,		// de modulation
	RF_RX_STA_FOOTER = 13,
};

#define reg_rx_rnd_mode			REG_ADDR8(0x447)
enum{
	FLD_RX_RND_SRC =			BIT(0),
	FLD_RX_RND_MANU_MODE =		BIT(1),
	FLD_RX_RND_AUTO_RD =		BIT(2),
	FLD_RX_RND_FREE_MODE =		BIT(3),
	FLD_RX_RND_CLK_DIV =		BIT_RNG(4,7),
};
#define reg_rnd_number			REG_ADDR16(0x448)

#define reg_bb_max_tick			REG_ADDR16(0x44c)
#define reg_rf_rtt				REG_ADDR32(0x454)
enum{
	FLD_RTT_CAL =				BIT_RNG(0,7),
	FLD_RTT_CYC1 =				BIT_RNG(8,15),
	FLD_RTT_LOCK =				BIT_RNG(16,23),
	FLD_RT_SD_DLY_40M =			BIT_RNG(24,27),
	FLD_RT_SD_DLY_BYPASS = 		BIT(28),
};

#define reg_rf_chn_rssi			REG_ADDR8(0x458)

#define reg_rf_rx_gain_agc(i)	REG_ADDR32(0x480+((i)<<2))

#define reg_rf_rx_dci			REG_ADDR8(0x4cb)	//  different from the document, why
#define reg_rf_rx_dcq			REG_ADDR8(0x4cf)	//  different from the document, why

#define reg_pll_rx_coarse_tune	REG_ADDR16(0x4d0)
#define reg_pll_rx_coarse_div	REG_ADDR8(0x4d2)
#define reg_pll_rx_fine_tune	REG_ADDR16(0x4d4)
#define reg_pll_rx_fine_div		REG_ADDR8(0x4d6)
#define reg_pll_tx_coarse_tune	REG_ADDR16(0x4d8)
#define reg_pll_tx_coarse_div	REG_ADDR8(0x4da)
#define reg_pll_tx_fine_tune	REG_ADDR16(0x4dc)
#define reg_pll_tx_fine_div		REG_ADDR8(0x4de)

#define reg_pll_rx_frac			REG_ADDR32(0x4e0)
#define reg_pll_tx_frac			REG_ADDR32(0x4e4)

#define reg_pll_tx_ctrl			REG_ADDR8(0x4e8)
#define reg_pll_ctrl16			REG_ADDR16(0x4e8)
#define reg_pll_ctrl			REG_ADDR32(0x4e8)
enum{
	FLD_PLL_TX_CYC0 =			BIT(0),
	FLD_PLL_TX_SOF =			BIT(1),
	FLD_PLL_TX_CYC1 =			BIT(2),
	FLD_PLL_TX_PRE_EN =			BIT(3),
	FLD_PLL_TX_VCO_EN =			BIT(4),
	FLD_PLL_TX_PWDN_DIV =		BIT(5),
	FLD_PLL_TX_MOD_EN =			BIT(6),
	FLD_PLL_TX_MOD_TRAN_EN =	BIT(7),
	FLD_PLL_RX_CYC0 =			BIT(8),
	FLD_PLL_RX_SOF = 			BIT(9),
	FLD_PLL_RX_CYC1 =			BIT(10),
	FLD_PLL_RX_PRES_EN = 		BIT(11),
	FLD_PLL_RX_VCO_EN =			BIT(12),
	FLD_PLL_RX_PWDN_DIV =		BIT(13),
	FLD_PLL_RX_PEAK_EN =		BIT(14),
	FLD_PLL_RX_TP_CYC = 		BIT(15),
	FLD_PLL_SD_RSTB =			BIT(16),
	FLD_PLL_SD_INTG_EN =		BIT(17),
	FLD_PLL_CP_TRI = 			BIT(18),
	FLD_PLL_PWDN_INTG1 = 		BIT(19),
	FLD_PLL_PWDN_INTG2 =		BIT(20),
	FLD_PLL_PWDN_INTG_DIV =		BIT(21),
	FLD_PLL_PEAK_DET_EN =		BIT(22),
	FLD_PLL_OPEN_LOOP_EN =		BIT(23),
	FLD_PLL_RX_TICK_EN =		BIT(24),
	FLD_PLL_TX_TICK_EN =		BIT(25),
	FLD_PLL_RX_ALWAYS_ON =		BIT(26),
	FLD_PLL_TX_ALWAYS_ON =		BIT(27),
	FLD_PLL_MANUAL_MODE_EN =	BIT(28),
	FLD_PLL_CAL_DONE_EN =		BIT(29),
	FLD_PLL_LOCK_EN =			BIT(30),
};
#define reg_pll_rx_ctrl			REG_ADDR8(0x4e9)
enum{
	FLD_PLL_RX2_CYC0 =			BIT(0),
	FLD_PLL_RX2_SOF = 			BIT(1),
	FLD_PLL_RX2_CYC1 =			BIT(2),
	FLD_PLL_RX2_PRES_EN = 		BIT(3),
	FLD_PLL_RX2_VCO_EN =		BIT(4),
	FLD_PLL_RX2_PD_DIV =		BIT(5),
	FLD_PLL_RX2_PEAK_EN =		BIT(6),
	FLD_PLL_RX2_TP_CYC = 		BIT(7),
};

#define reg_pll_ctrl_a			REG_ADDR8(0x4eb)
enum{
	FLD_PLL_A_RX_TICK_EN =		BIT(0),
	FLD_PLL_A_TX_TICK_EN =		BIT(1),
	FLD_PLL_A_RX_ALWAYS_ON =	BIT(2),
	FLD_PLL_A_TX_ALWAYS_ON =	BIT(3),
	FLD_PLL_A_MANUAL_MODE_EN =	BIT(4),
	FLD_PLL_A_CAL_DONE_EN =		BIT(5),
	FLD_PLL_A_LOCK_EN =			BIT(6),
};
// pll polarity
#define reg_pll_pol_ctrl		REG_ADDR16(0x4ec)
enum{
	FLD_PLL_POL_TX_PRE_EN =		BIT(0),
	FLD_PLL_POL_TX_VCO_EN =		BIT(1),
	FLD_PLL_POL_TX_PD_DIV =		BIT(2),
	FLD_PLL_POL_MOD_EN =		BIT(3),
	FLD_PLL_POL_MOD_TRAN_EN =	BIT(4),
	FLD_PLL_POL_RX_PRE_EN =		BIT(5),
	FLD_PLL_POL_RX_VCO_EN =		BIT(6),
	FLD_PLL_POL_RX_PD_DIV =		BIT(7),
	FLD_PLL_POL_SD_RSTB =		BIT(8),
	FLD_PLL_POL_SD_INTG_EN =	BIT(9),
	FLD_PLL_POL_CP_TRI =		BIT(10),
	FLD_PLL_POL_TX_SOF =		BIT(11),
	FLD_PLL_POL_RX_SOF =		BIT(12),
};

#define reg_rf_rx_cap			REG_ADDR16(0x4f0)		//  电容
#define reg_rf_tx_cap			REG_ADDR16(0x4f0)		//  电容

/*----------------------------------------------------------------------------*/
/*------  DMA register define                                           ------*/
/*----------------------------------------------------------------------------*/
#define reg_dma0_addr			REG_ADDR16(0x500)
#define reg_dma0_ctrl			REG_ADDR16(0x502)
#define reg_dma1_addr			REG_ADDR16(0x504)
#define reg_dma1_ctrl			REG_ADDR16(0x506)
#define reg_dma2_addr			REG_ADDR16(0x508)
#define reg_dma2_ctrl			REG_ADDR16(0x50a)
#define reg_dma3_addr			REG_ADDR16(0x50c)
#define reg_dma3_ctrl			REG_ADDR16(0x50e)
//#define reg_dma4_addr			REG_ADDR16(0x510)
//#define reg_dma4_ctrl			REG_ADDR16(0x512)
#define reg_dma5_addr			REG_ADDR16(0x514)
#define reg_dma5_ctrl			REG_ADDR16(0x516)
enum //Use for "reg_dma0_ctrl","reg_dma1_ctrl","reg_dma2_ctrl","reg_dma3_ctrl","reg_dma5_ctrl"
{
	FLD_DMA_BUF_SIZE =			BIT_RNG(0,7),

	FLD_DMA_WR_MEM =			BIT(8),
	FLD_DMA_PINGPONG_EN =		BIT(9),
	FLD_DMA_FIFO_EN =			BIT(10),
	FLD_DMA_AUTO_MODE =			BIT(11),
	FLD_DMA_RSVD   =			BIT(12),
	FLD_DMA_BYTE_MODE_EN =      BIT(13),
	FLD_DMA_FIFO8 	=			(BIT(15) | BIT(14) | FLD_DMA_WR_MEM | FLD_DMA_PINGPONG_EN),

	FLD_DMA_RPTR_CLR =			BIT(4),
	FLD_DMA_RPTR_NEXT =			BIT(5),
	FLD_DMA_RPTR_SET =			BIT(6),
};

#define reg_dma_chn_en			REG_ADDR8(0x520)
#define reg_dma_chn_irq_msk		REG_ADDR8(0x521)
#define reg_dma_tx_rdy0			REG_ADDR8(0x524)
#define reg_dma_tx_rdy1			REG_ADDR8(0x525)
#define reg_dma_rx_rdy0			REG_ADDR8(0x526)
#define reg_dma_irq_src			reg_dma_rx_rdy0
#define reg_dma_rx_rdy1			REG_ADDR8(0x527)
enum{
	FLD_DMA_UART_RX =			BIT(0),
	FLD_DMA_UART_TX =			BIT(1),
	FLD_DMA_RF_RX =				BIT(2),
	FLD_DMA_RF_TX =				BIT(3),
	FLD_DMA_PWM =               BIT(5),
};

// The default channel assignment
#define reg_dma_uart_rx_addr	reg_dma0_addr
#define reg_dma_uart_rx_ctrl	reg_dma0_ctrl
#define reg_dma_uart_tx_addr	reg_dma1_addr
#define reg_dma_uart_tx_ctrl	reg_dma1_ctrl

#define reg_dma_rf_rx_addr		reg_dma2_addr
#define reg_dma_rf_rx_ctrl		reg_dma2_ctrl
#define reg_dma_rf_tx_addr		reg_dma3_addr
#define reg_dma_rf_tx_ctrl		reg_dma3_ctrl


/*----------------------------------------------------------------------------*/
#define reg_rf_manual_irq_status REG_ADDR16(0x526)   //Rx buf 0 data received
#define FLD_RF_MANUAL_IRQ_RX     BIT(2)


#define reg_dma_rx_rptr			REG_ADDR8(0x528)
#define reg_dma_rx_wptr			REG_ADDR8(0x529)

#define reg_dma_tx_rptr			REG_ADDR8(0x52a)
#define reg_dma_tx_wptr			REG_ADDR8(0x52b)
#define reg_dma_tx_fifo			REG_ADDR16(0x52c)
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*------  AES register define                                           ------*/
/*----------------------------------------------------------------------------*/
#define reg_aes_ctrl            REG_ADDR8(0x540)
enum
{	FLD_AES_Decrypt   = BIT(0),
	FLD_AES_Feed_Data = BIT(1),
	FLD_AES_Finished  = BIT(2),
};
#define reg_aes_data            REG_ADDR32(0x548)
#define reg_aes_key(key_id) 	REG_ADDR8(0x550 + key_id)
#define reg_aes_key0            REG_ADDR8(0x550)
#define reg_aes_key1            REG_ADDR8(0x551)
#define reg_aes_key2            REG_ADDR8(0x552)
#define reg_aes_key3            REG_ADDR8(0x553)
#define reg_aes_key4            REG_ADDR8(0x554)
#define reg_aes_key5            REG_ADDR8(0x555)
#define reg_aes_key6            REG_ADDR8(0x556)
#define reg_aes_key7            REG_ADDR8(0x557)
#define reg_aes_key8            REG_ADDR8(0x558)
#define reg_aes_key9            REG_ADDR8(0x559)
#define reg_aes_key10           REG_ADDR8(0x55a)
#define reg_aes_key11           REG_ADDR8(0x55b)
#define reg_aes_key12           REG_ADDR8(0x55c)
#define reg_aes_key13           REG_ADDR8(0x55d)
#define reg_aes_key14           REG_ADDR8(0x55e)
#define reg_aes_key15           REG_ADDR8(0x55f)

/****************************************************
 audio regs struct: begin  addr : 0x560
 *****************************************************/
//#define reg_aud_ctrl			REG_ADDR8(0x560)
//enum{
//	FLD_AUD_ENABLE	 =			BIT(0),
//	FLD_AUD_SDM_PLAY_EN = 		BIT(1),
//	FLD_AUD_SHAPPING_EN =		BIT(2),
//	FLD_AUD_PN_SHAPPING_BYPASS =    BIT(2),
//	FLD_AUD_SHAPING_EN         =    BIT(3),
//	FLD_AUD_PN2_GENERATOR_EN   =    BIT(4),
//	FLD_AUD_PN1_GENERATOR_EN   =    BIT(5),
//	FLD_AUD_CONST_VAL_INPUT_EN =    BIT(6),
//};
//
//#define reg_aud_vol_ctrl		REG_ADDR8(0x561)
//#define reg_aud_pn1				REG_ADDR8(0x562)
//#define reg_aud_pn2				REG_ADDR8(0x563)
//
//#define reg_ascl_step			REG_ADDR16(0x564)
//#define reg_aud_base_adr		REG_ADDR16(0x568)
//#define reg_aud_buff_size		REG_ADDR8(0x56a)
//#define reg_aud_rptr			REG_ADDR16(0x56c)
//#define reg_sdm_ptr				reg_aud_rptr
//
//#define	AUD_SDM_STEP(i,o)		(0x8000*(i/100)/(o/100))
//
//static inline u16 get_sdm_rd_ptr (void) {
//	return reg_aud_rptr << 0;
//}
//
//enum {
//	FLD_AUD_PN_1BIT		= 0x104050,
//	FLD_AUD_PN_4BITS	= 0x0c404c,
//};
//
//#define reg_aud_const			REG_ADDR32(0x56)
//
//
//#define reg_aud_filter			REG_ADDR16(0xb80)
//enum {
//	FLD_AUD_FLT_IBFT	=	BIT(0),
//	FLD_AUD_FLT_AUTO	=	BIT(1),
//	FLD_AUD_FLT_FIFO0	=	BIT(2),
//	FLD_AUD_FLT_FIFO1	=	BIT(3),
//	FLD_AUD_FLT_BYPASS0	=	BIT(5),
//	FLD_AUD_FLT_BYPASS1	=	BIT(6),
//	FLD_AUD_FLT_BYPASS		=   0x60,
//	FLD_AUD_FLT_I0			=   0x47,
//	FLD_AUD_FLT_I1			=   0x2b,
//	FLD_AUD_FLT_I0I1		=   0x0f,
//	FLD_AUD_FLT_CFGHIGH		= 	0x1000,
//};
//#define reg_aud_sram			REG_ADDR8(0xb81)

#endif


/*----------------------------------------------------------------------------*/
/*-------   GPIO register define                                      --------*/
/*----------------------------------------------------------------------------*/
#define reg_gpio_pa_in			REG_ADDR8(0x580)
#define reg_gpio_pa_ie			REG_ADDR8(0x581)
#define reg_gpio_pa_oen			REG_ADDR8(0x582)
#define reg_gpio_pa_out			REG_ADDR8(0x583)
#define reg_gpio_pa_pol			REG_ADDR8(0x584)
#define reg_gpio_pa_ds			REG_ADDR8(0x585)
#define reg_gpio_pa_gpio		REG_ADDR8(0x586)
#define reg_gpio_pa_irq_en		REG_ADDR8(0x587)

#define reg_gpio_pb_in			REG_ADDR8(0x588)
#define reg_gpio_pb_ie			REG_ADDR8(0x589)
#define reg_gpio_pb_oen			REG_ADDR8(0x58a)
#define reg_gpio_pb_out			REG_ADDR8(0x58b)
#define reg_gpio_pb_pol			REG_ADDR8(0x58c)
#define reg_gpio_pb_ds			REG_ADDR8(0x58d)
#define reg_gpio_pb_gpio		REG_ADDR8(0x58e)
#define reg_gpio_pb_irq_en		REG_ADDR8(0x58f)

#define reg_gpio_pc_in			REG_ADDR8(0x590)
#define reg_gpio_pc_ie			REG_ADDR8(0x591)
#define reg_gpio_pc_oen			REG_ADDR8(0x592)
#define reg_gpio_pc_out			REG_ADDR8(0x593)
#define reg_gpio_pc_pol			REG_ADDR8(0x594)
#define reg_gpio_pc_ds			REG_ADDR8(0x595)
#define reg_gpio_pc_gpio		REG_ADDR8(0x596)
#define reg_gpio_pc_irq_en		REG_ADDR8(0x597)


#define reg_gpio_pe_in			REG_ADDR8(0x5a0)
#define reg_gpio_pe_ie			REG_ADDR8(0x5a1)
#define reg_gpio_pe_oen			REG_ADDR8(0x5a2)
#define reg_gpio_pe_out			REG_ADDR8(0x5a3)
#define reg_gpio_pe_pol			REG_ADDR8(0x5a4)
#define reg_gpio_pe_ds			REG_ADDR8(0x5a5)
#define reg_gpio_pe_gpio		REG_ADDR8(0x5a6)
#define reg_gpio_pe_irq_en		REG_ADDR8(0x5a7)

#define reg_gpio_pc_setting1	REG_ADDR32(0x590)
#define reg_gpio_pc_setting2	REG_ADDR32(0x594)

typedef union
{
    u16 RegAll;
    struct
	{
		u16 P0_AF :2;
		u16 P1_AF :2;
		u16 P2_AF :2;
		u16 P3_AF :2;
		u16 P4_AF :2;
		u16 P5_AF :2;
		u16 P6_AF :2;
		u16 P7_AF :2;
	}RegBits;
}GPIO_AFTypeDef;

#define GPIOA_AF  ((GPIO_AFTypeDef *)(REG_BASE_ADDR + 0x5a8))
#define GPIOB_AF  ((GPIO_AFTypeDef *)(REG_BASE_ADDR + 0x5aa))
#define GPIOC_AF  ((GPIO_AFTypeDef *)(REG_BASE_ADDR + 0x5ac))

//#define reg_gpio_ctrl			REG_ADDR32(0x5a4)
//enum{
//	GPIO_WAKEUP_EN = BIT(0),
//	GPIO_IRQ_EN	   = BIT(1),
//	I2S_SLAVE_EN   = BIT(2),
//	RMII_REFCLK_OUTPUT_EN = BIT(3),
//};

//#define reg_gpio_config_func0 REG_ADDR8(0x5b0)
//enum{
//	FLD_DMIC_DI_PWM0    =   BIT(0),
//	FLD_SPI_DO_PWM0_N   =   BIT(2),
//	FLD_SPI_DI_PWM1     =   BIT(3),
//	FLD_SPI_CK_PWM1_N   =   BIT(4),
//	FLD_SPI_CN_PWM2_N   =   BIT(5),
//	FLD_NULL_UART_TX    =   BIT(6),
//	FLD_UART_RX_SWM     =   BIT(7),
//};
//
//#define reg_gpio_config_func1 REG_ADDR8(0x5b1)
//enum{
//	FLD_PWM2_SWS        =   BIT(0),
//	FLD_UART_TX_PWM3    =   BIT(2),
//	FLD_UART_RX_PWM3N   =   BIT(3),
//	FLD_SPI_CN_PWM4     =   BIT(4),
//	FLD_SPI_DO_PWM4N    =   BIT(5),
//	FLD_SPI_DI_PWM5     =   BIT(6),
//	FLD_SPI_CK_PWM5N    =   BIT(7),
//};
//
//#define reg_gpio_config_func2  REG_ADDR8(0x5b2)
//enum{
//	FLD_I2C_DI_PWM0     =   BIT(0),
//	FLD_I2C_CK_PWM1     =   BIT(1),
//	FLD_UART_TX_PWM2    =   BIT(2),
//	FLD_UART_RX_PWM3    =   BIT(3),
//	FLD_UART_RTS_PWM4   =   BIT(4),
//	FLD_UART_CTS_PWM5   =   BIT(5),
//};
//
//#define reg_gpio_config_func3 REG_ADDR8(0x5b3)
//enum{
//	FLD_CN_BB_GAIN3		=	BIT(0),
//	FLD_CK_BB_GAIN2		=	BIT(1),
//	FLD_DO_BB_GAIN1		=	BIT(2),
//	FLD_DI_BB_GAIN0		=	BIT(3),
////	FLD_I2S_LCK_PWM2	=	BIT(4),//NOT SURE
//	FLD_I2S_DO_RXDV		=	BIT(5),
//	FLD_I2S_DI_RXER		=	BIT(6),
//	FLD_I2S_DI_TXSD		=	BIT(7),
//};
//#define reg_gpio_config_func4 REG_ADDR8(0x5b4)
//enum{
//	FLD_DMIC_CK_RX_CLK	=	BIT(0),
//	FLD_I2S_DI_RX_DAT	=	BIT(1),
//};

//5316 must
#define reg_gpio_wakeup_irq		REG_ADDR8(0x5b5)
enum{
	FLD_GPIO_WAKEUP_EN	  =	BIT(2),
	FLD_GPIO_INTERRUPT_EN =	BIT(3),
};

//5316 must
#define reg_gpio_pb_multi_func_select  REG_ADDR8(0x5b6)
enum
{
	FLD_PB_MULTI_FUNC_SEL = BIT(3),//1:UART; 0:SPI(PB0-PB3)
};

#if 0
/*----------------------------------------------------------------------------*/
/*-------   Timer and Watchdog register define                        --------*/
/*----------------------------------------------------------------------------*/
#define reg_tmr_ctrl			REG_ADDR32(0x620)
#define reg_tmr_ctrl16			REG_ADDR16(0x620)		// 因为0x622 不要写
#define reg_tmr_ctrl8			REG_ADDR8(0x620)
enum{
	FLD_TMR0_EN     = BIT(0),
	FLD_TMR0_MODE   = BIT_RNG(1,2),
	FLD_TMR1_EN     = BIT(3),
	FLD_TMR1_MODE   = BIT_RNG(4,5),
	FLD_TMR2_EN     = BIT(6),
	FLD_TMR2_MODE   = BIT_RNG(7,8),
	FLD_TMR_WD_CAPT = BIT_RNG(9,22),
	FLD_TMR_WD_EN   = BIT(23),
	FLD_TMR0_STA    = BIT(24),
	FLD_TMR1_STA    = BIT(25),
	FLD_TMR2_STA    = BIT(26),
	FLD_CLR_WD      = BIT(27),
};

#define reg_tmr_sta				REG_ADDR8(0x623)
enum{
	FLD_TMR_STA_TMR0 = BIT(0),//write 1 clear.
	FLD_TMR_STA_TMR1 = BIT(1),
	FLD_TMR_STA_TMR2 = BIT(2),
	FLD_TMR_STA_WD   = BIT(3),
};

#define reg_tmr0_capt			REG_ADDR32(0x624)
#define reg_tmr1_capt			REG_ADDR32(0x628)
#define reg_tmr2_capt			REG_ADDR32(0x62c)
#define reg_tmr_capt(i)			REG_ADDR32(0x624 + ((i) << 2))
#define reg_tmr0_tick			REG_ADDR32(0x630)
#define reg_tmr1_tick			REG_ADDR32(0x634)
#define reg_tmr2_tick			REG_ADDR32(0x638)
#define reg_tmr_tick(i)			REG_ADDR32(0x630 + ((i) << 2))

//Watchdog
#define reg_watchdog_reset_flg  REG_ADDR8(0x72)
#define WATCHDOG_TIMEOUT_COEFF	18		//  check register definiton, 0x622
#define WATCHDOG_DISABLE		(reg_tmr_ctrl &= ~FLD_TMR_WD_EN)
#define WATCHDOG_CLEAR			(reg_tmr_sta  |= FLD_TMR_STA_WD)


/*----------------------------------------------------------------------------*/
/*-------   Interrupt register define                                 --------*/
/*----------------------------------------------------------------------------*/
#define reg_irq_mask			REG_ADDR32(0x640)
#define reg_irq_pri				REG_ADDR32(0x644)
#define reg_irq_src				REG_ADDR32(0x648)
#define reg_irq_src3			REG_ADDR8(0x64a)
//enum//Use for "reg_irq_mask"
//{
//	FLD_IRQ_TMR0_EN       =	BIT(0),
//	FLD_IRQ_TMR1_EN       =	BIT(1),
//	FLD_IRQ_TMR2_EN       =	BIT(2),
//	FLD_IRQ_SYSTEM_TIMER  =	BIT(3),
//	FLD_IRQ_DMA_EN        =	BIT(4),
//	FLD_IRQ_QDEC_EN       =	BIT(5),
//	FLD_IRQ_UART_EN 	  =	BIT(6),
//	FLD_IRQ_HOST_CMD_EN   =	BIT(7),
//
//	FLD_IRQ_RSVD_8        =	BIT(8),
//	FLD_IRQ_RSVD_9        =	BIT(9),
//	FLD_IRQ_RSVD_10       =	BIT(10),
//	FLD_IRQ_RSVD_11       =	BIT(11),
//	FLD_IRQ_SOFT_IRQ_EN   =	BIT(12),
//	FLD_IRQ_ZB_RT_EN      =	BIT(13),
//	FLD_IRQ_PWM_EN        =	BIT(14),
//	FLD_IRQ_AN_EN         =	BIT(15),
//
//	FLD_IRQ_RSVD_16       =	BIT(16),
//	FLD_IRQ_RSVD_17       =	BIT(17),
//	FLD_IRQ_GPIO_EN       =	BIT(18),
//	FLD_IRQ_PM_EN         =	BIT(19),
//	FLD_IRQ_RSVD_20       =	BIT(20),
//	FLD_IRQ_GPIO_RISC0_EN =	BIT(21),
//	FLD_IRQ_GPIO_RISC1_EN =	BIT(22),
//	FLD_IRQ_GPIO_RISC2_EN = BIT(23),
//
//	FLD_IRQ_EN            =	BIT(24),
//
//	//Can not be used
//	FLD_IRQ_USB_PWDN_EN   = BIT(31),
//	FLD_IRQ_USB_RST_EN    = BIT(31),
//};
#define reg_irq_en				REG_ADDR8(0x643)


/*----------------------------------------------------------------------------*/
/*-------   System timer register define                              --------*/
/*----------------------------------------------------------------------------*/
#define reg_system_tick			          REG_ADDR32(0x740)
#define reg_32k_timer_counter_latch       REG_ADDR32(0x744)//Read only
#define reg_32k_timer_calibration_value   REG_ADDR16(0x748)//Read only
#define reg_sys_timer_ctrl                REG_ADDR8(0x74a)
enum//Use for "reg_sys_timer_ctrl"
{
	FLD_SYS_TIMER_EN                 = BIT(7),
	FLD_SYS_TIMER_IRQ_EN             = BIT(6),
	FLD_SYS_TIMER_CAL_MODE           = BIT_RNG(4,5),
	FLD_SYS_TIMER_CAL_EN             = BIT(3),
	FLD_SYS_TIMER_AUTO_MODE          = BIT(2),
	FLD_RSVD                         = BIT(1),
	FLD_SYS_TIMER_WRITE_32K_TICK_EN  = BIT(0),
};

#define reg_sys_timer_cmd_state   REG_ADDR8(0x74b)
#define reg_32k_timer_tick        REG_ADDR32(0x74c)



//8267
#define reg_system_tick_irq		REG_ADDR32(0x744)
#define reg_system_wakeup_tick	REG_ADDR32(0x748)
#define reg_system_tick_mode	REG_ADDR8(0x74c)
#define reg_system_tick_ctrl	REG_ADDR8(0x74f)
enum {
	FLD_SYSTEM_TICK_START	= BIT(0),
	FLD_SYSTEM_TICK_STOP	= BIT(1),
	FLD_SYSTEM_TICK_RUNNING = BIT(1),

	FLD_SYSTEM_TICK_IRQ_EN  = BIT(1),
};


/*----------------------------------------------------------------------------*/
/*-------   PWM register define                                       --------*/
/*----------------------------------------------------------------------------*/
typedef enum {
	PWM0 = 0,
	PWM1,
	PWM2,
}ePWM_IdTypeDef;

#define reg_pwm_enable			REG_ADDR8(0x780)
#define reg_pwm_clk				REG_ADDR8(0x781)
#define reg_pwm0_mode			REG_ADDR8(0x782)
enum //Use for "reg_pwm0_mode"
{
	FLD_PWM0_MODE = BIT_RNG(0,3),
};

typedef enum{
	PWM_MODE_NORMAL      = 0x00,
	PWM_MODE_COUNT       = 0x01,
	PWM_MODE_IR          = 0x03,
	PWM_MODE_IR_FIFO     = 0x07,
	PWM_MODE_IR_DMA_FIFO = 0x0f,
}ePWM_ModeTypeDef;

#define reg_pwm_invert			REG_ADDR8(0x783)
#define reg_pwm_n_invert		REG_ADDR8(0x784)
#define reg_pwm_polarity		REG_ADDR8(0x785)//first polarity

//#define reg_pwm_phase(i)		REG_ADDR16(0x788 + (i << 1))
#define reg_pwm_cycle(i)		REG_ADDR32(0x794 + (i << 2))
#define reg_pwm_cmp(i)			REG_ADDR16(0x794 + (i << 2))
#define reg_pwm_max(i)			REG_ADDR16(0x796 + (i << 2))
enum{
	FLD_PWM_CMP  = BIT_RNG(0,15),
	FLD_PWM_MAX  = BIT_RNG(16,31),
};

#define reg_pwm0_pulse_num		REG_ADDR16(0x7ac)
#define reg_pwm_irq_mask0		REG_ADDR8(0x7b0)
#define reg_pwm_irq_state0		REG_ADDR8(0x7b1)
#define reg_pwm_irq_mask1		REG_ADDR8(0x7b2)
#define reg_pwm_irq_state1		REG_ADDR8(0x7b3)
typedef enum{
	/* PWM Mask0/state0 bit field define. */
	FLD_PWM_IRQ_PWM0_PNUM        = BIT(0),
	FLD_PWM_IRQ_PWM0_IR_DMA_FIFO = BIT(1),
	FLD_PWM_IRQ_PWM0_FRAME       = BIT(2),
	FLD_PWM_IRQ_PWM1_FRAME       = BIT(3),
	FLD_PWM_IRQ_PWM2_FRAME       = BIT(4),

	/* PWM Mask1/state1 bit field define. */
	FLD_PWM_IRQ_PWM0_IR_FIFO_CNT = BIT(0)
}ePWM_IrqTypeDef;


#define reg_pwm_cmp_shadow       REG_ADDR16(0x7c4)
#define reg_pwm_max_shadow		 REG_ADDR16(0x7c6)
#define reg_pwm_fifo_data_entry  REG_ADDR32(0x7c8)
#define reg_pwm_fifo_number      REG_ADDR8(0x7cc)
#define reg_pwm_fifo_state       REG_ADDR8(0x7cd)
enum
{
	FLD_PWM_FIFO_CURRENT_NUM = BIT_RNG(0,3),
	FLD_PWM_FIFO_EMPTY       = BIT(4),
	FLD_PWM_FIFO_FULL        = BIT(5),
};

#define reg_pwm_fifo_clear  		  REG_ADDR8(0x7ce)

static inline void pwm_set_mode(ePWM_IdTypeDef pwm_id, ePWM_ModeTypeDef mode)
{
	if(pwm_id != PWM0)
		return;
	else
	{
		reg_pwm0_mode = mode;//MASK_VAL(FLD_PWM0_MODE,mode);
	}
}

//Set PWM clock frequency
static inline void pwm_set_clk(int system_clock_hz, int pwm_clk){
	reg_rst_clk0 &= ~FLD_RST_PWM;
	reg_clk_en |= FLD_CLK_PWM_EN;
	reg_pwm_clk = (int)system_clock_hz /pwm_clk - 1;
}


static inline void pwm_set_cmp(ePWM_IdTypeDef pwm_id, u16 cmp_tick){
	reg_pwm_cmp(pwm_id) = cmp_tick;
}

static inline void pwm_set_cycle(ePWM_IdTypeDef pwm_id, u16 cycle_tick){
	reg_pwm_max(pwm_id) = cycle_tick;
}


static inline void pwm_set_cycle_and_duty(ePWM_IdTypeDef pwm_id, u16 cycle_tick, u16 cmp_tick){
	reg_pwm_cycle(pwm_id) = MASK_VAL(FLD_PWM_CMP, cmp_tick, FLD_PWM_MAX, cycle_tick);
}


/**
 * @Brief:  Only PWM0 have counter mode in 5316 MCU.
 * @Param:
 * @Retval: None.
 */
static inline void pwm0_set_pulse_num(u16 pulse_num){
	reg_pwm0_pulse_num = pulse_num;
}

static inline void pwm_start(ePWM_IdTypeDef pwm_id){
	BM_SET(reg_pwm_enable, BIT(pwm_id));
}

static inline void pwm_stop(ePWM_IdTypeDef pwm_id){
	BM_CLR(reg_pwm_enable, BIT(pwm_id));
}

//revert PWMx
static inline void pwm_revert(ePWM_IdTypeDef pwm_id){
	reg_pwm_invert |= BIT(pwm_id);
}


//revert PWMx_N
static inline void pwm_n_revert(ePWM_IdTypeDef pwm_id){
	reg_pwm_n_invert |= BIT(pwm_id);
}

/**
 * @Brief: Set PWM first polarity.
 * @Param:
 * @Retval: None.
 */
static inline void pwm_polarity_set(ePWM_IdTypeDef pwm_id, int polarity){
	if(polarity == 0){
		BM_SET(reg_pwm_polarity, BIT(pwm_id));//First low level.
	}else{
		BM_CLR(reg_pwm_polarity, BIT(pwm_id));//First high level.
	}
}


static inline void pwm_interrupt_enable(ePWM_IrqTypeDef irq){
	if(irq == FLD_PWM_IRQ_PWM0_IR_FIFO_CNT)
	{
		reg_pwm_irq_mask1 |= irq;
	}
	else
	{
		reg_pwm_irq_mask0 |= irq;
	}

	reg_irq_mask |= FLD_IRQ_PWM_EN;
}

static inline void pwm_interrupt_disable(ePWM_IrqTypeDef irq){
	if(irq == FLD_PWM_IRQ_PWM0_IR_FIFO_CNT)
	{
		reg_pwm_irq_mask1 &= ~irq;
	}
	else
	{
		reg_pwm_irq_mask0 &= ~irq;
	}

	reg_irq_mask &= ~FLD_IRQ_PWM_EN;
}

static inline unsigned char pwm_get_int_status_flag(ePWM_IrqTypeDef irq)
{
	if(irq == FLD_PWM_IRQ_PWM0_IR_FIFO_CNT)
	{
		return (reg_pwm_irq_state1 & irq) ? 1:0;
	}

	return (reg_pwm_irq_state0 & irq) ? 1:0;
}

static inline void pwm_clear_interrupt_status(ePWM_IrqTypeDef irq){
	if(irq == FLD_PWM_IRQ_PWM0_IR_FIFO_CNT)
	{
		reg_pwm_irq_state1 |= irq;
	}
	else
	{
		reg_pwm_irq_state0 |= irq;
	}
}

static inline void pwm_dma_ir_data_config(u16* pdat)
{
	reg_dma5_addr = (u32)pdat & 0xffff;

	reg_dma5_ctrl  &= ~FLD_DMA_WR_MEM;
}

static inline void pwm_dma_enable(void)
{
	reg_dma_tx_rdy0 |= FLD_DMA_PWM;
}


//////////////////////////////////////////////////////////////
// DFIFO
//////////////////////////////////////////////////////////////

//#define reg_fifo0_data			REG_ADDR32(0x800)
//#define reg_fifo1_data			REG_ADDR32(0x900)
//#define reg_fifo2_data			REG_ADDR32(0xa00)
//
///****************************************************
// dfifo regs define:  begin  0xb00
// *****************************************************/
//#define reg_dfifo0_buf			REG_ADDR32(0xb00)
//#define reg_dfifo1_buf			REG_ADDR32(0xb04)
//#define reg_dfifo2_buf			REG_ADDR32(0xb08)
//enum{
//	FLD_DFIFO_BUF_ADDR =		BIT_RNG(0,15),
//	FLD_DFIFO_BUF_SIZE =		BIT_RNG(16,23),
//};
//
//#define reg_dfifo0_addr			REG_ADDR16(0xb00)
//#define reg_dfifo0_size			REG_ADDR8(0xb02)
//
//#define reg_dfifo_ana_in		REG_ADDR8(0xb03)
//enum{
//	FLD_DFIFO_MIC0_RISING_EDGE = BIT(0),
//	FLD_DFIFO_MIC_ADC_IN 	= BIT(1),
//	FLD_DFIFO_EN               = BIT(4),
//	FLD_DFIFO_WPTR_EN          = BIT(5),
//	FLD_DFIFO_WPTR_CLR         = BIT(6),
//	FLD_DFIFO_AUD_INPUT_MONO =	BIT(4) | BIT(5),
////	FLD_DFIFO_AUD_INPUT_BYPASS = BIT(5),
//};
//enum{
//	REG_AUD_INPUT_SEL_USB = 0,
//	REG_AUD_INPUT_SEL_I2S = 1,
//	REG_AUD_INPUT_SEL_ADC = 2,
//	REG_AUD_INPUT_SEL_DMIC = 3,
//};
//
//#define reg_dfifo_scale			REG_ADDR8(0xb04)
//enum{
//	FLD_DFIFO2_DEC_CIC =		BIT_RNG(0,3),
//	FLD_DFIFO0_DEC_SCALE =		BIT_RNG(4,6),
//};
//
//#define reg_aud_hpf_alc			REG_ADDR8(0xb05)
//enum {
//	FLD_AUD_IN_HPF_SFT	=	BIT_RNG(0,3),
//	FLD_AUD_IN_HPF_BYPASS	=	BIT(4),
//	FLD_AUD_IN_ALC_BYPASS	=	BIT(5),
//	FLD_AUD_IN_LPF_BYPASS   =   BIT(6),
//	FLD_AUD_IN_USB_SET		=  0x3b,
//};
//
//#define reg_aud_alc_vol			REG_ADDR8(0xb06)
//enum {
//	FLD_AUD_MANUAL_VOLUME     =   BIT_RNG(0,5),
//	FLD_AUD_VOLUME_CTRL_MODE  =   BIT(6),
//};
//#define reg_aud_vol_step        REG_ADDR8(0xb0b)
//#define reg_aud_tick_interval   REG_ADDR16(0xb0c)
//enum {
//	FLD_AUD_ALC_VOL_TICK_L    = BIT_RNG(0,7),
//	FLD_AUD_ALC_VOL_TICK_H    = BIT_RNG(8,13),
//};
//
//#define reg_audio_wr_ptr		REG_ADDR16(0xb10)
//#define reg_mic_ptr				reg_audio_wr_ptr
//
//static inline u16 get_mic_wr_ptr (void) {
//	return reg_audio_wr_ptr << 0;
//}


/////////////////////////////////////////////////////////////////////////////

///////////////////// PM register /////////////////////////

#define		rega_deepsleep_flag		0x3f		//0x34 - 0x39 (watch dog reset)
//#define		rega_deepsleep_flag		0x34		//0x3a - 0x3b (power-on reset)
#define		flag_deepsleep_wakeup	(analog_read(0x3f) & 0x40)

#define		rega_wakeup_en_val0		0x41
#define		rega_wakeup_en_val1		0x42
#define		rega_wakeup_en_val2		0x43
#define		raga_gpio_wkup_pol		0x44

#define		raga_pga_gain0		0x86
#define		raga_pga_gain1		0x87

//static inline u16 config_sdm (u32 adr, int size, int sample_rate, int sdm_fmhz) {
//	reg_clk_en2 |= FLD_CLK2_AUD_EN;				//enable audio clock
//	reg_gpio_pe_gpio &= ~(BIT(0) | BIT(1));		//enable SDM function
//	reg_gpio_config_func4 &=  ~(BIT(0) | BIT(1)); //SDM function
//
//	reg_aud_ctrl = FLD_AUD_ENABLE | FLD_AUD_SDM_PLAY_EN | FLD_AUD_SHAPPING_EN;
//
//	SET_SDM_CLOCK_MHZ (sdm_fmhz);
//	reg_aud_base_adr = (u16) adr;
//	reg_aud_buff_size = (size>>4)-1;
//
//	reg_ascl_step = AUD_SDM_STEP (sample_rate, sdm_fmhz*1000000);
//	return reg_ascl_step;
//}
//
//static inline void config_adc_channel1 (int chn_mic) {
//	// adc-pga setting
//	//reg_adc_pga_sel_l = chn_mic >> 8;		//C0, C1, C2 & C3
//	reg_adc_pga_sel_m = reg_adc_pga_sel_l = chn_mic >> 8;		//C0, C1, C2 & C3
//	reg_adc_chn_l_sel = chn_mic | FLD_ADC_DATA_SIGNED;
//	reg_adc_ref = FLD_ADC_VREF_1P3V;
//	reg_aud_alc_vol = 28;
//
//	if (chn_mic) {
//		//analog_write (raga_pga_gain0, 0x50);  //ana_reg0x86[2] pga mute, [3] power down pga, pre_amp move to ana_reg0x87
//		analog_write (raga_pga_gain1, 0x07); //reg0x87[2:1] 00 0db, 01 3db , 10 6db, 11 9db
//	}
//	else {
//		//analog_write (raga_pga_gain0, 0x53);
//		analog_write (raga_pga_gain1, 0x00);
//	}
//}
//
//static inline void config_mic_gain (int vol) {
//	reg_aud_alc_vol = vol;
//}
//
//static inline void config_adc_channel2 (int chn_adc) {
//	reg_adc_chn_r_sel = chn_adc | FLD_ADC_DATA_SIGNED;
//}

#define		SYS_16M_AMIC_16K				0
#define		SYS_32M_AMIC_16K				1
#define		SYS_16M_AMIC_12K				2
#define		SYS_32M_AMIC_12K				3
#define		SYS_32M_AMIC_8K					4
#define		SYS_16M_AMIC_8K					5
#define 	SYS_32M_AMIC_DIR_16K			6
#define 	SYS_48M_AMIC_16K				7
//#define		SYS_16M_AMIC_12K				2

//static inline void config_adc (int chn_mic, int chn_adc, int sample) {
//	reg_clk_en2 |= FLD_CLK2_DIFIO_EN;
//	reg_dfifo_ana_in = FLD_DFIFO_AUD_INPUT_MONO | FLD_DFIFO_MIC_ADC_IN;
//	reg_dfifo_scale = 0x25;				// down scale by 6
//#if TL_MIC_32K_FIR_16K
//	reg_aud_hpf_alc = 9;				// reg0xb05 volume setting
//#else	//clr lpf ,when no fir 32k to 16k
//	reg_aud_hpf_alc = 0x4b;//11;				// reg0xb05 volume setting
//#endif
//	reg_aud_alc_vol = 4;
//
//	config_adc_channel1 (chn_mic);
//	config_adc_channel2 (chn_adc);
//
//	if (sample == SYS_32M_AMIC_16K) {	//32M / (77 + 8 * 16 * 2) = 96K
//		reg_adc_period_chn0 = 77;
//		reg_adc_period_chn12 = 8;
//	}
//	else if (sample == SYS_32M_AMIC_12K) { //32M / (77 + 11 * 16 * 2) = 72K
//		reg_adc_period_chn0 = 92;
//		reg_adc_period_chn12 = 11;
//	}
//	else if (sample == SYS_16M_AMIC_12K) {
//		//16M / (77 + 5 * 16 * 2) = 72K
//		reg_adc_period_chn0 = 64;
//		reg_adc_period_chn12 = 5;		// 32M setting
//	}
//	else if (sample == SYS_32M_AMIC_8K) { //32M / (244 + 8 * 16 * 2) = 64K
//		reg_dfifo_scale = 0x37;				// down scale by 8
//		reg_adc_period_chn0 = 180;
//		reg_adc_period_chn12 = 10;
//	}
//	else if (sample == SYS_16M_AMIC_8K) { //16M / (90 + 5 * 16 * 2) = 64K
//		reg_dfifo_scale = 0x37;				// down scale by 8
//		reg_adc_period_chn0 = 90;
//		reg_adc_period_chn12 = 5;
//	}
//	else if (sample == SYS_32M_AMIC_DIR_16K){
//		/*
//		reg_dfifo_scale  = 0x23;//down scale by 4
//     	reg_adc_period_chn0 = 374;//374;//374;//208;//77
//	 	reg_adc_period_chn12= 8;//8;
//	 	*/
//
//	 	reg_dfifo_scale  = 0x25;//down scale by 6
//     	reg_adc_period_chn0 = 208;//374;//374;//208;//77
//	 	reg_adc_period_chn12= 8;//8;
//        reg_adc_ctrl          = 0x15;
//        reg_aud_alc_vol       = 0x12;//0x24;0x1c;//0x19; // 0xb06[5:0]: manual volume , corespond to  reg0xb04[6:4]
//
//	}
//	else if(sample == SYS_16M_AMIC_16K){
//#if TL_MIC_32K_FIR_16K
//		//16000/(187+4*16)/2 = 16000/251/2 = 31.87 K
//		// down scale by 2
//        reg_dfifo_scale       = 0x21;  // reg0xb04[6:4] cic filter output select 1 , cic[22:5] , reg0xb04[3:0] down scale by 2,
//        reg_adc_period_chn0   = 187;   // reg0x30 T1~4,  250(16M/64K) - 64 = 186 , 0x30[1:0] just for fine tuning
//        reg_adc_period_chn12  = 4;     // reg0x32 T5 = 4x16 = 64 , just T5 no T6, single channel
//
//        reg_adc_ctrl          = 0x15;
//        reg_aud_alc_vol       = 0x24;  //0x1c;//0x19; // 0xb06[5:0]: manual volume , corespond to  reg0xb04[6:4]
//#else
//        //16000/(72+8*16)/5 = 16000/200/5 = 16 K
//        reg_dfifo_scale       = 0x44; //down scale by 5
//       	reg_adc_period_chn0   = 0x48;
//       	reg_adc_period_chn12  = 8;
//
//        reg_adc_ctrl          = 0x15;  // reg0x33[1] = 0 , disable T6 , mono mode[4]/L channel enable[3]/audio enable[1],  talk to zhidong.mao for detail
//        reg_aud_alc_vol       = 0x1c;  // reg0xb06 0x19; // 0xb06[5:0]: manual volume , corespond to  reg0xb04[6:4]
//#endif
//	}
//	else if(sample == SYS_48M_AMIC_16K){
//#if TL_MIC_32K_FIR_16K
//		//48000/(260+15*16)/3 = 48000/500/3 = 32 K
//		reg_dfifo_scale       = 0x22; //down scale by 3
//		reg_adc_period_chn0   = 260;
//		reg_adc_period_chn12  = 15;
//
//        reg_adc_ctrl          = 0x15;
//        reg_aud_alc_vol       = 0x24;
//#else
//		//48000/(260+15*16)/6 = 48000/500/6 = 16 K
//		reg_dfifo_scale       = 0x45; //down scale by 6
//		reg_adc_period_chn0   = 260;
//		reg_adc_period_chn12  = 15;
//
//        reg_adc_ctrl          = 0x15;
//        reg_aud_alc_vol       = 0x1c;
//#endif
//	}
//	else {
//		while(1);  //config adc err
//	}
//}

//static inline void config_mic_buffer (u32 adr, int size) {
//	reg_dfifo0_addr = (u16) adr;
//	reg_dfifo0_size = (size>>4)-1;
//}

static inline void config_timer_interrupt (u32 tick) {
	reg_tmr1_tick = 0;
	reg_tmr1_capt = tick;
	reg_tmr_ctrl8 |= FLD_TMR1_EN;
	reg_irq_mask |= FLD_IRQ_TMR1_EN;
}
#endif


// interrupt source
static inline u32 irq_get_src(){
	return reg_irq_src;
}

static inline unsigned short rf_irq_src_get(void){
    return reg_rf_irq_status;
}


/**
 * @brief      Get IRQ status of uart.
 * @param[in]  irq_src - select tx or rx irq.
 * @return     none
 */
static inline unsigned char dma_chn_irq_status_get(void)
{
    return reg_dma_irq_src;
}

/**
 * @brief      Clear IRQ status of uart.
 * @param[in]  irq_src - select tx or rx irq.
 * @return     none
 */
static inline void dma_chn_irq_status_clr(unsigned char irq_status)
{
	reg_dma_irq_src |= irq_status;
}

#if defined(__cplusplus)
}
#endif


