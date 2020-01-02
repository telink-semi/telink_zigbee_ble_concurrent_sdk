/********************************************************************************************************
 * @file     bsp.h
 *
 * @brief    This file provides set of common functions for driver
 *
 * @author   kaixin.chen@telink-semi.com; qiuwei.chen@telink-semi.com
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
#ifndef BSP_H
#define BSP_H
#include "../../apps/common/user_config.h"
#include "../../proj/common/types.h"
//#define LED1					  GPIOB_GP0
#define RX_PIN					  GPIOA_GP3
#define TX_PIN					  GPIOA_GP2

/**
 *  Reg operations
 */
#define IOBASE                          0x800000
#define WRITE_REG32(addr,data)          (*(volatile unsigned long  *)((addr)|IOBASE)=data)
#define WRITE_REG16(addr,data)          (*(volatile unsigned short *)((addr)|IOBASE)=data)
#define WRITE_REG8(addr,data)           (*(volatile unsigned char  *)((addr)|IOBASE)=data)

#define READ_REG32(addr)                (*(volatile unsigned long  *)((addr)|IOBASE))
#define READ_REG16(addr)                (*(volatile unsigned short *)((addr)|IOBASE))
#define READ_REG8(addr)                 (*(volatile unsigned char  *)((addr)|IOBASE))

#define REG_ADDR8(a)                    (*(volatile unsigned char*) (IOBASE + (a)))
#define REG_ADDR16(a)                   (*(volatile unsigned short*)(IOBASE + (a)))
#define REG_ADDR32(a)                   (*(volatile unsigned int*)(IOBASE + (a)))

#define write_reg32(addr,data)          (*(volatile unsigned long  *)(addr)=data)
#define write_reg16(addr,data)          (*(volatile unsigned short *)(addr)=data)
#define write_reg8(addr,data)           (*(volatile unsigned char  *)(addr)=data)
#define read_reg32(addr)                (*(volatile unsigned long  *)(addr))
#define read_reg16(addr)                (*(volatile unsigned short *)(addr))
#define read_reg8(addr)                 (*(volatile unsigned char  *)(addr))

//#define analog_read(addr)           ReadAnalogReg(addr)
//#define analog_write(addr,value)    WriteAnalogReg(addr, value)

/** define BIT operations */
#define BIT(n)                  		( 1<<(n) )
#define NBIT(n)                  		( ~BIT(n) )
#define BIT_MASK_LEN(len)       		(BIT(len)-1)
#define BIT_RNG(s, e)  					(BIT_MASK_LEN((e)-(s)+1) << (s))

#define BM_SET(x, mask)         		( (x) |= (mask) )
#define BM_CLR(x, mask)       			( (x) &= ~(mask) )
#define BM_IS_SET(x, mask)   			( (x) & (mask) )
#define BM_IS_CLR(x, mask)   			( (~x) & (mask) )
#define BM_FLIP(x, mask)      			( (x) ^=  (mask) )

#define     SETB(v,n)   (*(volatile unsigned char  *)v |= n)
#define     CLRB(v,n)   (*(volatile unsigned char  *)v &= ~n)
#define     TEST(v,n)   (((*(volatile unsigned char  *)v) & n) ? 1:0)


#define BIT_SET(x, mask)         ( (x) |= (mask) )
#define BIT_CLR(x, mask)         ( (x) &= ~(mask) )
#define BIT_IS_SET(x, mask)      ( (x) & (mask) )
#define BIT_IS_CLR(x, mask)      ( (~x) & (mask) )
#define BIT_FLIP(x, mask)        ( (x) ^=  (mask) )

#define SET_BIT_FLD(x, mask)     BIT_SET(x, mask)
#define CLR_BIT_FLD(x, mask)     BIT_CLR(x, mask)
#define FLIP_BIT_FLD(x, mask)    BIT_FLIP(x, mask)


/**
 *
 */
#define NULL        0
#define	ADR_IO		0x800000
#define TCMD_UNDER_RD		0x80
#define TCMD_UNDER_WR		0x40
#define TCMD_UNDER_BOTH		0xc0
#define TCMD_MASK		0x3f

#define TCMD_WRITE		0x3
#define TCMD_WAIT		0x7
#define TCMD_WAREG		0x8

extern unsigned long pm_systick_offset;
#if 0
typedef struct TBLCMDSET {
	unsigned short	adr;
	unsigned char	dat;
	unsigned char	cmd;
} TBLCMDSET;
#endif

typedef struct {
	unsigned short	adr;
	unsigned char	dat;
	unsigned char	cmd;
} BSP_TblCmdSetTypeDef;

typedef struct {
	unsigned char 	 rst0;
	unsigned char    rst1;
	unsigned char    rst2;
	unsigned char    clk0;
	unsigned char 	 clk1;
	unsigned char    clk2;
	unsigned char    clkctl;
} BSP_SysCtlTypeDef;


#define TCMD_UNDER_RD		0x80
#define TCMD_UNDER_WR		0x40
#define TCMD_UNDER_BOTH		0xc0
#define TCMD_MASK			0x3f

#define TCMD_WRITE			0x3
#define TCMD_WAIT			0x7
#define TCMD_WAREG			0x8

typedef struct TBLCMDSET {
	unsigned short	adr;
	unsigned char	dat;
	unsigned char	cmd;
} TBLCMDSET;

/**
 *  rst0
 */
enum {
	FLD_RST_SPI = 				BIT(0),
	FLD_RST_I2C = 				BIT(1),
	//FLD_RST_USB = 				BIT(2),
	//FLD_RST_USB_PHY = 			BIT(3),
	FLD_RST_MCU = 				BIT(4),
	//FLD_RST_MAC =				BIT(5),
	FLD_RST_AIF = 				BIT(6),
	//FLD_RST_BB = 				BIT(7),
	FLD_RST_ZB =				BIT(7),
	FLD_RST0_ALL =				0xff,
};

/**
 *  rst1
 */
enum {
	FLD_RST_SYS_TIMER = 		BIT(0),
	FLD_RST_ALGM = 				BIT(1),
	FLD_RST_DMA =				BIT(2),
	FLD_RST_UART = 				BIT(3),
	FLD_RST_PWM = 				BIT(4),
	FLD_RST_AES = 				BIT(5),
	//FLD_RST_BBPLL48M =			BIT(6),
	FLD_RST_SWR =				BIT(7),
	FLD_RST1_ALL =				0xff,
};
/**
 *  rst2
 */
enum {
	//FLD_RST_SBC =				BIT(0),
	//FLD_RST_AUD =				BIT(1),
	//FLD_RST_DFIFO =				BIT(2),
	FLD_RST_ADC =				BIT(3),
	FLD_RST_MCIC =				BIT(4),
	FLD_RST_SOFT_MCIC = 		BIT(5),
	FLD_RST_MSPI =				BIT(6),
	FLD_RST_ALGS =				BIT(7),
	FLD_RST2_ALL =				0xff,
};

/**
 *  clk0
 */
enum {
	FLD_CLK_SPI_EN =			BIT(0),
	FLD_CLK_I2C_EN =			BIT(1),
	//FLD_CLK_USB_EN =			BIT(2),
	//FLD_CLK_USB_PHY_EN =		BIT(3),
	FLD_CLK_MCU_EN =			BIT(4),
	FLD_CLK_MAC_EN =			BIT(5),
	FLD_CLK_AIF_EN =			BIT(6),
	FLD_CLK_ZB_EN =				BIT(7),
	FLD_CLK0_EN_ALL =			0xff,
};

/**
 *  clk1
 */
enum {
	FLD_CLK_SYS_TIMER_EN = 		BIT(0),
	FLD_CLK_ALGM_EN = 			BIT(1),
	FLD_CLK_DMA_EN = 			BIT(2),
	FLD_CLK_UART_EN = 			BIT(3),
	FLD_CLK_PWM_EN = 			BIT(4),
	FLD_CLK_AES_EN = 			BIT(5),
	FLD_CLK_32K_TIMER_EN =		BIT(6),
	FLD_CLK_SWIRE_EN = 			BIT(7),
	FLD_CLK1_EN_ALL =			0xff,
};
/**
 *  clk2
 */
enum {
	FLD_CLK_32K_QDEC_EN =		BIT(0),
	FLD_CLK_AUD_EN =			BIT(1),
	FLD_CLK_DIFIO_EN = 			BIT(2),
	FLD_CLK_KEYSCAN_EN =		BIT(3),
	FLD_CLK_MCIC_EN =			BIT(4),
	FLD_CLK_QDEC_EN =			BIT(5),
	FLD_CLK_32K_PWM_EN = 		BIT(6),
	FLD_CLK_32K_KEYSCAN_EN =	BIT(7),
	FLD_CLK2_EN_ALL =			0xff,
};


typedef enum {
    SYS_CLK_RC = 0,
    SYS_CLK_HS_DIV = 1,
} BSP_SysClkSelTypeDef;

extern unsigned long TickPerUs;

extern unsigned long CLOCK_SYS_CLOCK_1US;

extern void WaitUs_RC (int us);


extern void PM_24M_RC_CAL(void);

extern void PM_32K_RC_CAL(void);



typedef enum{
	SYS_CLK_16M_PLL,
	SYS_CLK_24M_RC,
}SYS_CLK_TYPEDEF;


/* used to restore data during deep sleep mode or reset by software */
#define DATA_STORE_FLAG				0x55
#define	REG_DEEP_FLAG				0x34
#define	REG_DEEP_EXCEPT_FLAG		0x3A
#define	REG_FRAMECOUNT				0x35   //4Bytes, from 0x35 to 0x38

/**
 * @brief     This function initializes the clock of each peripheral module of MCU
 * @param[in] SysCtl - the pointer to the value of each peripheral module of MCU
 * @return    none
 */
extern void SysInit(BSP_SysCtlTypeDef *SysCtl);

/**
 * @brief     This function initializes the clock of each peripheral module of MCU
 * @param[in] SYS_CLK - system colck used
 * @return    none
 */
void clock_init(SYS_CLK_TYPEDEF SYS_CLK);

/**
 * @brief       This function initializes  the system clock
 * @param[in]   ClockSrc - the clock source of the system clock
 * @param[in]   ClockDivider - the division factor of system clock if FHS is selected as its clock
 *              source, i.e., system clock = FHS / clock_divider
 * @return      none
 */
extern void SysClockInit(BSP_SysClkSelTypeDef ClockSrc, unsigned char ClockDivider);
/**
 * @brief       This function sets the division factor of system clock if FHS is selected as its clock
 * @param[in]   ClockDivider - the division factor of system clock if FHS is selected as its clock
 *              source, i.e., system clock = FHS / clock_divider
 * @return      none
 */
extern void SysSetClockDivider(unsigned char ClockDivider);
/**
 * @brief  This function gets the current tick count of system timer
 * @param  none
 * @return the current tick count of system timer
 */
extern unsigned int ClockTime(void);
/**
 * @brief      This function determines whether current moment exceeds the reference moment plus
 *             the span time
 * @param[in]  Ref - the moment used as reference
 * @param[in]  SpanUs - the span time
 * @return     whether current moment exceeds the reference moment plus the span time(1: exceed 0: no exceed)
 */
extern unsigned int ClockTimeExceed(unsigned int Ref, unsigned int SpanUs);

/**
 * @brief     This function delays for the specified number of microseconds
 * @param[in] Millisec - the number of microseconds
 * @return    none
 */
//void WaitUs(int Microsec);
/**
 * @brief     This function delays for the specified number of milliseconds
 * @param[in] Millisec - the number of milliseconds
 * @return    none
 */
//void WaitMs(int Millisec);
//-------------------Read/Write register---------------------
/**
 * @brief      This function reads a byte data fromn a specified analog register
 * @param[in]  Addr - the address of the analog register needs to read
 * @return     the content of the analog register needs to read
 */
unsigned char ReadAnalogReg(unsigned char Addr);
/**
 * @brief      This function writes a byte data to a specified analog register
 * @param[in]  Addr - the address of the analog register needs to write
 * @param[in]  Dat  - the data will be written to the analog register
 * @return     none
 */
void WriteAnalogReg (unsigned char Addr, unsigned char Dat);
/**
 * @brief      This function performs a series of operations of writing digital or analog registers
 *             according to a command table
 * @param[in]  Table - pointer to a command table containing several writing commands
 * @param[in]  Size  - number of commands in the table
 * @return     number of commands are carried out
 */
extern int LoadTblCmdSet(const TBLCMDSET * Table, int Size);

/**
 * @brief      This function set the two-byte ID for the chip
 * @param[in]  Id - the two-byte ID
 * @return     none
 */
extern void SetChipId(unsigned short Id);

u8 analog_read(u8 addr);
void analog_write(u8 addr, u8 v);

void sub_wr_ana(unsigned int addr, unsigned char value, unsigned char e, unsigned char s);
void sub_wr(unsigned int addr, unsigned char value, unsigned char e, unsigned char s);
void sub_bit_set(int addr, char bit_pos);
void sub_bit_clr(int addr, char bit_pos);
extern char alg_reg_sr(char addr);
extern void alg_reg_sw(char addr, char data);

#define spi_wr_reg(addr, value)  WriteAnalogReg(addr, value)

void deep_sleep_flag_set(unsigned int a);
u8 deep_sleep_flag_get(void);
u32 deep_sleep_framecount_get(void);
void deep_sleep_except_set(void);
void deep_sleep_except_clr(void);
u8 deep_sleep_except_get(void);

#define SYSTEM_RESET	mcu_reset

#endif /* BSP_H */
