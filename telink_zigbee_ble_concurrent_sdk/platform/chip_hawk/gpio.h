/********************************************************************************************************
 * @file     gpio.h
 *
 * @brief    This file provides set of functions to manage GPIOs
 *
 * @author   jian.zhang@telink-semi.com;
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
#ifndef __GPIO_H
#define __GPIO_H

#include "bsp.h"
#include "gpio_default.h"
#include "register_5316.h"


#define AS_GPIO		0
#define AS_MSPI		1
#define AS_SWIRE	2
#define AS_UART		3
#define AS_PWM		4
#define AS_I2C		5
#define AS_SPI		6
#define AS_ETH_MAC	7
#define AS_I2S		8
#define AS_SDM		9
#define AS_DMIC		10
#define AS_USB		11
#define AS_SWS		12
#define AS_SWM		13
#define AS_TEST		14

/* GPIO register define. */
#define reg_gpio_in(i)				REG_ADDR8(0x580+((i>>8)<<3))

#define reg_gpio_ie(i)				REG_ADDR8(0x581+((i>>8)<<3))
#define reg_gpioPA0_4_ie            REG_ADDR8(0x581)
#define analogRegAddr_gpioPA5_7_ie  0xb6
#define analogRegAddr_gpioPB_ie     0xb9

#define reg_gpio_oen(i)				REG_ADDR8(0x582+((i>>8)<<3))
#define reg_gpio_out(i)				REG_ADDR8(0x583+((i>>8)<<3))
#define reg_gpio_pol(i)				REG_ADDR8(0x584+((i>>8)<<3))

#define reg_gpio_ds(i)				REG_ADDR8(0x585+((i>>8)<<3))
#define reg_gpioPA0_4_ds            REG_ADDR8(0x585)
#define analogRegAddr_gpioPA5_7_ds  0xb8
#define analogRegAddr_gpioPB_ds     0xbb

#define reg_gpio_gpio_func(i)		REG_ADDR8(0x586+((i>>8)<<3))
#define reg_gpio_config_func(i)     REG_ADDR16(0x5a8 + ((i>>8)<<1))
//#define reg_gpio_multi_func(i)      REG_ADDR16(0x5a8 + ((i>>8)<<1))

#define reg_gpio_irq_wakeup_en(i)	REG_ADDR8(0x587+((i>>8)<<3))  // reg_irq_mask: FLD_IRQ_GPIO_EN

#define reg_gpio_irq_risc0_en(i)    REG_ADDR8(0x5b8 + (i >> 8))	  // reg_irq_mask: FLD_IRQ_GPIO_RISC0_EN
#define reg_gpio_irq_risc1_en(i)    REG_ADDR8(0x5c0 + (i >> 8))	  // reg_irq_mask: FLD_IRQ_GPIO_RISC1_EN
#define reg_gpio_irq_risc2_en(i)    REG_ADDR8(0x5c8 + (i >> 8))   // reg_irq_mask: FLD_IRQ_GPIO_RISC2_EN

#define reg_gpio_wakeup_and_irq_en  REG_ADDR8(0x5b5)
enum{
    FLD_GPIO_CORE_WAKEUP_EN    = BIT(2),
    FLD_GPIO_CORE_INTERRUPT_EN = BIT(3),
};



/** define BIT operations */
//#define BM_SET(addr,bit)                ( *(addr) |= (bit) )
//#define BM_CLR(addr,bit)                ( *(addr) &= ~(bit) )
//#define BM_IS_SET(addr,bit)             ( *(addr) & (bit) )

/** define GPIO related registers */
#define REG_BASE                0X800000
//#define REG_ADDR_8(addr)        (volatile unsigned char  *)(REG_BASE+addr)
#define REG_GPIO_IN(i)          REG_ADDR8(0x580+((i>>8)<<3))
#define REG_GPIO_IE(i)          REG_ADDR8(0x581+((i>>8)<<3))
#define REG_GPIO_OEN(i)         REG_ADDR8(0x582+((i>>8)<<3))
#define REG_GPIO_OUT(i)         REG_ADDR8(0x583+((i>>8)<<3))
#define REG_GPIO_POL(i)         REG_ADDR8(0x584+((i>>8)<<3))
#define REG_GPIO_DS(i)          REG_ADDR8(0x585+((i>>8)<<3))
#define REG_GPIO_GPIO_FUNC(i)   REG_ADDR8(0x586+((i>>8)<<3))
#define REG_GPIO_IRQ_EN(i)      REG_ADDR8(0x587+((i>>8)<<3))
#define reg_gpio_irq_src(i)     REG_ADDR8(0x5e0+(i>>8))
#define REG_GPIO_2RISC0(i)      REG_ADDR8(0x5b8+(i>>8))
#define REG_GPIO_2RISC1(i)      REG_ADDR8(0x5c0+(i>>8))
#define REG_GPIO_2RISC2(i)      REG_ADDR8(0x5c8+(i>>8))

typedef enum {
    Bit_RESET = 0,
    Bit_SET,
} GPIO_BitActionTypeDef;

//GPIO types
typedef enum {
    GPIO_GROUPA    = 0x000,
    GPIO_GROUPB    = 0x100,
    GPIO_GROUPC    = 0x200,
    GPIO_GROUPD    = 0x300,
    GPIO_GROUPE    = 0x400,
} GPIO_GroupTypeDef;

/**
 *  @brief  Define pull-up/down types 
 */
typedef enum {
    PULL_NONE      = 0,
    PULL_UP_1M     = 1,
    PULL_UP_10K    = 2,
    PULL_DOWN_100K = 3,
} GPIO_PullTypeDef;

typedef enum {
	PAD_FUNCTION_MUX_0 = 0,
	PAD_FUNCTION_MUX_1 = 1,
	PAD_FUNCTION_MUX_2 = 2,
	PAD_FUNCTION_MUX_3 = 3,
}GPIO_FunctionMuxTypeDef;

typedef enum {
    GPIOA_GP0  = GPIO_GROUPA | BIT(0), GPIO_PWM0A0=GPIOA_GP0,  GPIO_PWM3A0=GPIOA_GP0, GPIO_DMIC_DI=GPIOA_GP0,
    GPIOA_GP1  = GPIO_GROUPA | BIT(1),                          GPIO_DMIC_CK=GPIOA_GP1,
    GPIOA_GP2  = GPIO_GROUPA | BIT(2), GPIO_PWM0NA2=GPIOA_GP2,  GPIO_DOA2=GPIOA_GP2,
    GPIOA_GP3  = GPIO_GROUPA | BIT(3), GPIO_PWM1A3=GPIOA_GP3,   GPIO_DIA3=GPIOA_GP3,
    GPIOA_GP4  = GPIO_GROUPA | BIT(4), GPIO_PWM1NA4=GPIOA_GP4,  GPIO_CKA4=GPIOA_GP4,
    GPIOA_GP5  = GPIO_GROUPA | BIT(5), GPIO_PWM2NA5=GPIOA_GP5,  GPIO_CNA5=GPIOA_GP5,
    GPIOA_GP6  = GPIO_GROUPA | BIT(6), GPIO_PA6 = GPIOA_GP6  , GPIO_UTXA6=GPIOA_GP6,
    GPIOA_GP7  = GPIO_GROUPA | BIT(7), GPIO_PA7 = GPIOA_GP7  , GPIO_URXA7=GPIOA_GP7, GPIO_SWM=GPIOA_GP7,
    GPIOA_ALL  = GPIO_GROUPA | 0X00ff,  

    GPIOB_GP0  = GPIO_GROUPB | BIT(0), GPIO_PWM2B0=GPIOB_GP0,   GPIO_SWS=GPIOB_GP0,
    GPIOB_GP1  = GPIO_GROUPB | BIT(1), GPIO_PWM2NB1=GPIOB_GP1,
    GPIOB_GP2  = GPIO_GROUPB | BIT(2), GPIO_PWM3B2=GPIOB_GP2,   GPIO_UTXB2=GPIOB_GP2,
    GPIOB_GP3  = GPIO_GROUPB | BIT(3), GPIO_PWM3NB3=GPIOB_GP3,  GPIO_URXB3=GPIOB_GP3,
    GPIOB_GP4  = GPIO_GROUPB | BIT(4), GPIO_PWM4B4=GPIOB_GP4,   GPIO_CNB4=GPIOB_GP4,
    GPIOB_GP5  = GPIO_GROUPB | BIT(5), GPIO_PWM4NB5=GPIOB_GP5,  GPIO_DOB5=GPIOB_GP5,
    GPIOB_GP6  = GPIO_GROUPB | BIT(6), GPIO_PWM5B6=GPIOB_GP6,   GPIO_DIB6=GPIOB_GP6,
    GPIOB_GP7  = GPIO_GROUPB | BIT(7), GPIO_PWM5NB7=GPIOB_GP7,  GPIO_CKB7=GPIOB_GP7,
    GPIOB_ALL  = GPIO_GROUPB | 0x00ff,

    GPIOC_GP0  = GPIO_GROUPC | BIT(0),GPIO_PWM0C0=GPIOC_GP0,    GPIO_I2C_SDA=GPIOC_GP0,
    GPIOC_GP1  = GPIO_GROUPC | BIT(1),GPIO_PWM1C1=GPIOC_GP1,    GPIO_I2C_SCK=GPIOC_GP1,
    GPIOC_GP2  = GPIO_GROUPC | BIT(2),GPIO_PWM2C2=GPIOC_GP2,    GPIO_UTXC2=GPIOC_GP2,
    GPIOC_GP3  = GPIO_GROUPC | BIT(3),GPIO_PWM3C3=GPIOC_GP3,    GPIO_URXC3=GPIOC_GP3,
    GPIOC_GP4  = GPIO_GROUPC | BIT(4),GPIO_PWM4C4=GPIOC_GP4,    GPIO_URTSC4=GPIOC_GP4,
    GPIOC_GP5  = GPIO_GROUPC | BIT(5),GPIO_PWM4C5=GPIOC_GP5,    GPIO_UCTSC5=GPIOC_GP5,
    GPIOC_GP6  = GPIO_GROUPC | BIT(6),
    GPIOC_GP7  = GPIO_GROUPC | BIT(7),
    GPIOC_ALL  = GPIO_GROUPC | 0x00ff,

//    GPIOD_GP0  = GPIO_GROUPD | BIT(0),
//    GPIOD_GP1  = GPIO_GROUPD | BIT(1),
//    GPIOD_GP2  = GPIO_GROUPD | BIT(2),
//    GPIOD_GP3  = GPIO_GROUPD | BIT(3),
//    GPIOD_GP4  = GPIO_GROUPD | BIT(4),
//    GPIOD_GP5  = GPIO_GROUPD | BIT(5),GPIO_PWM0D5=GPIOD_GP5,
//    GPIOD_GP6  = GPIO_GROUPD | BIT(6),GPIO_PWM1D6=GPIOD_GP6,
//    GPIOD_GP7  = GPIO_GROUPD | BIT(7),GPIO_PWM2D7=GPIOD_GP7,
//    GPIOD_ALL  = GPIO_GROUPD | 0x00ff,

    GPIOE_GP0  = GPIO_GROUPE | BIT(0),GPIO_PWM0E0=GPIOE_GP0,    GPIO_SDMP=GPIOE_GP0,
    GPIOE_GP1  = GPIO_GROUPE | BIT(1),GPIO_PWM1E1=GPIOE_GP1,    GPIO_SDMN=GPIOE_GP1,
    GPIOE_GP2  = GPIO_GROUPE | BIT(2),                          GPIO_DM=GPIOE_GP2,
    GPIOE_GP3  = GPIO_GROUPE | BIT(3),                          GPIO_DP=GPIOE_GP3,
//    GPIOE_GP4  = GPIO_GROUPE | BIT(4),                          GPIO_MSDO=GPIOE_GP4,
//    GPIOE_GP5  = GPIO_GROUPE | BIT(5),                          GPIO_MCLK=GPIOE_GP5,
//    GPIOE_GP6  = GPIO_GROUPE | BIT(6),                          GPIO_MSCN=GPIOE_GP6,
//    GPIOE_GP7  = GPIO_GROUPE | BIT(7),                          GPIO_MSDI=GPIOE_GP7,
//    GPIOE_ALL  = GPIO_GROUPE | 0x00ff,


}GPIO_PinTypeDef;


/* GPIO Alternative Function define. */
#define AS_GPIO		0
#define AS_AF       (!0)

#define AS_MSPI		1
#define AS_SWIRE	2
#define AS_UART		3
#define AS_PWM		4
#define AS_I2C		5
#define AS_SPI		6
#define AS_ETH_MAC	7
#define AS_I2S		8
#define AS_SDM		9
#define AS_DMIC		10
#define AS_USB		11
#define AS_SWS		12
#define AS_SWM		13
#define AS_TEST		14
#define AS_ADC		15
#define AS_KS       16
#define AS_DEBUG    17

/* PA Port Alternative Function define. (Use for 5316) */
//PA0
#define GPIOA0_PWM0                       0
#define GPIOA0_PWM3                       1
#define GPIOA0_32K_CLK_OUTPUT             2
#define GPIOA0_RESERVE_3                  3
//PA1
#define GPIOA1_PWM3N                      0
#define GPIOA1_UART_CTS                   1
#define GPIOA1_RESERVE_2                  2
#define GPIOA1_RESERVE_3                  3
//PA2
#define GPIOA2_PWM1N                      0
#define GPIOA2_UART_RTS                   1
#define GPIOA2_RESERVE_2                  2
#define GPIOA2_RESERVE_3                  3
//PA3
#define GPIOA3_PWM4                       0
#define GPIOA3_UART_TX                    1
#define GPIOA3_I2C_MCK                    2
#define GPIOA3_I2C_SD_OR_SPI_DI           3
//PA4
#define GPIOA4_PWM2                       0
#define GPIOA4_UART_RX                    1
#define GPIOA4_I2C_MSD                    2
#define GPIOA4_I2C_CK_OR_SPI_CK           3
//PA5
#define GPIOA5_PWM5                       0
#define GPIOA5_I2C_CK                     1
#define GPIOA5_RESERVE_2                  2
#define GPIOA5_I2C_MCK                    3
//PA6
#define GPIOA6_PWM4N                      0
#define GPIOA6_I2C_SD                     1
#define GPIOA6_RX_CYC2LNA                 2
#define GPIOA6_I2C_MSD                    3
//PA7
#define GPIOA7_PWM5                       0
#define GPIOA7_SYS_CLK_OUTPUT             1
#define GPIOA7_TX_CYC2PA                  2
#define GPIOA7_RESERVE_3                  3

/* PB Port Alternative Function define */
//PB0
#define GPIOB0_PWM3                       0
#define GPIOB0_SPI_MCN                    1
#define GPIOB0_RX_CYC2LNA_OR_SPI_CN       2
#define GPIOB0_RESERVE_3                  3
//PB1
#define GPIOB1_PWM1                       0
#define GPIOB1_SPI_MDO                    1
#define GPIOB1_TX_CYC2LNA_OR_SPI_DO       2
#define GPIOB1_RESERVE_3                  3
//PB2
#define GPIOB2_PWM2                       0
#define GPIOB2_SPI_MDI                    1
#define GPIOB2_UART_CTS_OR_SPI_DI         2
#define GPIOB2_I2C_MCK                    3
//PB3
#define GPIOB3_PWM0                       0
#define GPIOB3_SPI_MCK                    1
#define GPIOB3_UART_RTS_OR_SPI_CK         2
#define GPIOB3_I2C_MSD                    3
//PB4
#define GPIOB4_PWM1N                      0
#define GPIOB4_RESERVE_1                  1
#define GPIOB4_UART_TX                    2
#define GPIOB4_RESERVE_3                  3
//PB5
#define GPIOB5_PWM4                       0
#define GPIOB5_RESERVE_1                  1
#define GPIOB5_UART_RX                    2
#define GPIOB5_RESERVE_3                  3
//PB6
#define GPIOB6_PWM0N                      0
#define GPIOB6_I2C_MCK                    1
#define GPIOB6_UART_RTS                   2
#define GPIOB6_RESERVE_3                  3
//PB7
#define GPIOB7_PWM1                       0
#define GPIOB7_I2C_MSD                    1
#define GPIOB7_UART_CTS                   2
#define GPIOB7_RESERVE_3                  3

/* PC Port Alternative Function define */
//PC0
#define GPIOC0_RESERVE_0                  0
#define GPIOC0_RESERVE_1                  1
#define GPIOC0_RESERVE_2                  2
#define GPIOC0_RESERVE_3                  3
//PC1
#define GPIOC1_PWM2N                      0
#define GPIOC1_RESERVE_1                  1
#define GPIOC1_RESERVE_2                  2
#define GPIOC1_RESERVE_3                  3
//PC2
#define GPIOC2_SPI_CN                     0
#define GPIOC2_PWM0N                      1
#define GPIOC2_SPI_MCN                    2
#define GPIOC2_UART_CTS                   3
//PC3
#define GPIOC3_SPI_DO                     0
#define GPIOC3_PWM5N                      1
#define GPIOC3_SPI_MDO                    2
#define GPIOC3_UART_RTS                   3
//PC4
#define GPIOC4_SPI_DI_OR_I2C_SD           0
#define GPIOC4_I2C_MSD                    1
#define GPIOC4_SPI_MDI                    2
#define GPIOC4_UART_TX                    3
//PC5
#define GPIOC5_SPI_CK_OR_I2C_CK           0
#define GPIOC5_I2C_MCK                    1
#define GPIOC5_SPI_MCK                    2
#define GPIOC5_UART_RX                    3
//PC6
#define GPIOC6_PWM4                       0
#define GPIOC6_RESERVE_1                  1
#define GPIOC6_RESERVE_2                  2
#define GPIOC6_RESERVE_3                  3
//PC7
#define GPIOC7_SWS                        0
#define GPIOC7_PWM3                       1
#define GPIOC7_RESERVE_2                  2
#define GPIOC7_RESERVE_3                  3
/* End of GPIO Alternative Function define. */

static inline void gpio_core_wakeup_enable_all (int en)
{
    if (en) {
        BM_SET(reg_gpio_wakeup_and_irq_en, FLD_GPIO_CORE_WAKEUP_EN);
    }
    else {
        BM_CLR(reg_gpio_wakeup_and_irq_en, FLD_GPIO_CORE_WAKEUP_EN);
    }
}

static inline void gpio_core_irq_enable_all (int en)
{
    if (en) {
        BM_SET(reg_gpio_wakeup_and_irq_en, FLD_GPIO_CORE_INTERRUPT_EN);
    }
    else {
        BM_CLR(reg_gpio_wakeup_and_irq_en, FLD_GPIO_CORE_INTERRUPT_EN);
    }
}

static inline int gpio_is_output_en(u32 pin){
	return !BM_IS_SET(reg_gpio_oen(pin), pin & 0xff);
}

static inline void gpio_set_output_en(u32 pin, u32 value)
{
	u8	bit = pin & 0xff;
	if(!value){
		BM_SET(reg_gpio_oen(pin), bit);
	}else{
		BM_CLR(reg_gpio_oen(pin), bit);
	}
}

static inline void gpio_write(u32 pin, u32 value){
	u8	bit = pin & 0xff;
	if(value){
		BM_SET(reg_gpio_out(pin), bit);
	}else{
		BM_CLR(reg_gpio_out(pin), bit);
	}
}

static inline void gpio_toggle(u32 pin) {
	reg_gpio_out(pin) ^= (pin & 0xFF);
}


static inline u32 gpio_read(u32 pin){
	return BM_IS_SET(reg_gpio_in(pin), pin & 0xff);
}

static inline u32 gpio_read_cache(u32 pin, u8 *p){
	return p[pin>>8] & (pin & 0xff);
}

static inline void gpio_read_all(u8 *p){
	p[0] = REG_ADDR8(0x580);//PA
	p[1] = REG_ADDR8(0x588);//PB
	p[2] = REG_ADDR8(0x590);//PC
//	p[3] = REG_ADDR8(0x598);//PD
//	p[4] = REG_ADDR8(0x5a0);//PE
//	p[5] = REG_ADDR8(0x5a8);//PF
}

static inline void gpio_set_interrupt_pol(u32 pin, u32 falling){
	u8	bit = pin & 0xff;
	if(falling){
		BM_SET(reg_gpio_pol(pin), bit);
	}else{
		BM_CLR(reg_gpio_pol(pin), bit);
	}
}

static inline void gpio_en_interrupt(u32 pin, int en){  // reg_irq_mask: FLD_IRQ_GPIO_EN
	u8	bit = pin & 0xff;
	if(en){
		BM_SET(reg_gpio_irq_wakeup_en(pin), bit);
	}
	else{
		BM_CLR(reg_gpio_irq_wakeup_en(pin), bit);
	}
}

static inline void gpio_set_interrupt(u32 pin, u32 falling){
	u8	bit = pin & 0xff;
	BM_SET(reg_gpio_irq_wakeup_en(pin), bit);
	if(falling){
		BM_SET(reg_gpio_pol(pin), bit);
	}else{
		BM_CLR(reg_gpio_pol(pin), bit);
	}
}

static inline void gpio_en_interrupt_risc0(u32 pin, int en){  // reg_irq_mask: FLD_IRQ_GPIO_RISC0_EN
	u8	bit = pin & 0xff;
	if(en){
		BM_SET(reg_gpio_irq_risc0_en(pin), bit);
	}
	else{
		BM_CLR(reg_gpio_irq_risc0_en(pin), bit);
	}
}

static inline void gpio_set_interrupt_risc0(u32 pin, u32 falling){
	u8	bit = pin & 0xff;
	BM_SET(reg_gpio_irq_risc0_en(pin), bit);
	if(falling){
		BM_SET(reg_gpio_pol(pin), bit);
	}else{
		BM_CLR(reg_gpio_pol(pin), bit);
	}
}

static inline void gpio_en_interrupt_risc1(u32 pin, int en){  // reg_irq_mask: FLD_IRQ_GPIO_RISC1_EN
	u8	bit = pin & 0xff;
	if(en){
		BM_SET(reg_gpio_irq_risc1_en(pin), bit);
	}
	else{
		BM_CLR(reg_gpio_irq_risc1_en(pin), bit);
	}
}

static inline void gpio_set_interrupt_risc1(u32 pin, u32 falling){
	u8	bit = pin & 0xff;
	BM_SET(reg_gpio_irq_risc1_en(pin), bit);
	if(falling){
		BM_SET(reg_gpio_pol(pin), bit);
	}else{
		BM_CLR(reg_gpio_pol(pin), bit);
	}
}

static inline void gpio_en_interrupt_risc2(u32 pin, int en){  // reg_irq_mask: FLD_IRQ_GPIO_RISC2_EN
	u8	bit = pin & 0xff;
	if(en){
		BM_SET(reg_gpio_irq_risc2_en(pin), bit);
	}
	else{
		BM_CLR(reg_gpio_irq_risc2_en(pin), bit);
	}
}

static inline void gpio_set_interrupt_risc2(u32 pin, u32 falling){
	u8	bit = pin & 0xff;
	BM_SET(reg_gpio_irq_risc2_en(pin), bit);
	if(falling){
		BM_SET(reg_gpio_pol(pin), bit);
	}else{
		BM_CLR(reg_gpio_pol(pin), bit);
	}
}

static inline void gpio_init(void){
	//return;
	//|Input| IE |OEN|Output| DS |GPIO function|

	/* GPIOA Init ------------------------------------------------------------*/
	//PA IE settings
	reg_gpioPA0_4_ie = (PA0_INPUT_ENABLE<<0)| (PA1_INPUT_ENABLE<<1)|(PA2_INPUT_ENABLE<<2)|(PA3_INPUT_ENABLE<<3)|(PA4_INPUT_ENABLE<<4);
	analog_write(analogRegAddr_gpioPA5_7_ie, (PA5_INPUT_ENABLE<<5)|(PA6_INPUT_ENABLE<<6)|(PA7_INPUT_ENABLE<<7));
	//PA OEN settings
	reg_gpio_pa_oen = (PA0_OUTPUT_ENABLE?0:BIT(0))|(PA1_OUTPUT_ENABLE?0:BIT(1))|(PA2_OUTPUT_ENABLE?0:BIT(2))|(PA3_OUTPUT_ENABLE?0:BIT(3))|
					  (PA4_OUTPUT_ENABLE?0:BIT(4))|(PA5_OUTPUT_ENABLE?0:BIT(5))|(PA6_OUTPUT_ENABLE?0:BIT(6))|(PA7_OUTPUT_ENABLE?0:BIT(7));
    //PA Output settings
	reg_gpio_pa_out = (PA0_DATA_OUT<<0)|(PA1_DATA_OUT<<1)|(PA2_DATA_OUT<<2)|(PA3_DATA_OUT<<3)|
			          (PA4_DATA_OUT<<4)|(PA5_DATA_OUT<<5)|(PA6_DATA_OUT<<6)|(PA7_DATA_OUT<<7);
	//PA DS settings
	reg_gpioPA0_4_ds = (PA0_DATA_STRENGTH<<0)|(PA1_DATA_STRENGTH<<1)|(PA2_DATA_STRENGTH<<2)|(PA3_DATA_STRENGTH<<3)|(PA4_DATA_STRENGTH<<4);
	analog_write(analogRegAddr_gpioPA5_7_ds, (PA5_DATA_STRENGTH<<5)|(PA6_DATA_STRENGTH<<6)|(PA7_DATA_STRENGTH<<7));
	//PA GPIO function
    reg_gpio_pa_gpio = (PA0_FUNC == AS_GPIO?BIT(0):0)|(PA1_FUNC == AS_GPIO?BIT(1):0)|(PA2_FUNC == AS_GPIO?BIT(2):0)|(PA3_FUNC == AS_GPIO?BIT(3):0)|
    				   (PA4_FUNC == AS_GPIO?BIT(4):0)|(PA5_FUNC == AS_GPIO?BIT(5):0)|(PA6_FUNC == AS_GPIO?BIT(6):0)|(PA7_FUNC == AS_GPIO?BIT(7):0);

    /* GPIOB Init ------------------------------------------------------------*/
    //PB IE settings
    analog_write(analogRegAddr_gpioPB_ie,(PB0_INPUT_ENABLE<<0)|(PB1_INPUT_ENABLE<<1)|(PB2_INPUT_ENABLE<<2)|(PB3_INPUT_ENABLE<<3)|
    									 (PB4_INPUT_ENABLE<<4)|(PB5_INPUT_ENABLE<<5)|(PB6_INPUT_ENABLE<<6)|(PB7_INPUT_ENABLE<<7));
    //PB OEN settings
    reg_gpio_pb_oen = (PB0_OUTPUT_ENABLE?0:BIT(0))|(PB1_OUTPUT_ENABLE?0:BIT(1))|(PB2_OUTPUT_ENABLE?0:BIT(2))|(PB3_OUTPUT_ENABLE?0:BIT(3))|
    				  (PB4_OUTPUT_ENABLE?0:BIT(4))|(PB5_OUTPUT_ENABLE?0:BIT(5))|(PB6_OUTPUT_ENABLE?0:BIT(6))|(PB7_OUTPUT_ENABLE?0:BIT(7));
    //PB Output settings
    reg_gpio_pb_out = (PB0_DATA_OUT<<0)|(PB1_DATA_OUT<<1)|(PB2_DATA_OUT<<2)|(PB3_DATA_OUT<<3)|
    		          (PB4_DATA_OUT<<4)|(PB5_DATA_OUT<<5)|(PB6_DATA_OUT<<6)|(PB7_DATA_OUT<<7);
    //PB DS settings
    analog_write(analogRegAddr_gpioPB_ds,(PB0_DATA_STRENGTH<<0)|(PB1_DATA_STRENGTH<<1)|(PB2_DATA_STRENGTH<<2)|(PB3_DATA_STRENGTH<<3)|
    									 (PB4_DATA_STRENGTH<<4)|(PB5_DATA_STRENGTH<<5)|(PB6_DATA_STRENGTH<<6)|(PB7_DATA_STRENGTH<<7));
    //PB GPIO function
    reg_gpio_pb_gpio = (PB0_FUNC == AS_GPIO?BIT(0):0)|(PB1_FUNC == AS_GPIO?BIT(1):0)|(PB2_FUNC == AS_GPIO?BIT(2):0)|(PB3_FUNC == AS_GPIO?BIT(3):0)|
    				   (PB4_FUNC == AS_GPIO?BIT(4):0)|(PB5_FUNC == AS_GPIO?BIT(5):0)|(PB6_FUNC == AS_GPIO?BIT(6):0)|(PB7_FUNC == AS_GPIO?BIT(7):0);

    /* PC Init ---------------------------------------------------------------*/
	reg_gpio_pc_setting1 =
		(PC0_INPUT_ENABLE<<8) | (PC1_INPUT_ENABLE<<9) |(PC2_INPUT_ENABLE<<10)|(PC3_INPUT_ENABLE<<11) |
		(PC4_INPUT_ENABLE<<12)| (PC5_INPUT_ENABLE<<13)|(PC6_INPUT_ENABLE<<14)|(PC7_INPUT_ENABLE<<15) |
		((PC0_OUTPUT_ENABLE?0:1)<<16)|((PC1_OUTPUT_ENABLE?0:1)<<17)|((PC2_OUTPUT_ENABLE?0:1)<<18)|((PC3_OUTPUT_ENABLE?0:1)<<19) |
		((PC4_OUTPUT_ENABLE?0:1)<<20)|((PC5_OUTPUT_ENABLE?0:1)<<21)|((PC6_OUTPUT_ENABLE?0:1)<<22)|((PC7_OUTPUT_ENABLE?0:1)<<23) |
		(PC0_DATA_OUT<<24)|(PC1_DATA_OUT<<25)|(PC2_DATA_OUT<<26)|(PC3_DATA_OUT<<27)|
		(PC4_DATA_OUT<<28)|(PC5_DATA_OUT<<29)|(PC6_DATA_OUT<<30)|(PC7_DATA_OUT<<31);
	reg_gpio_pc_setting2 =
		(PC0_DATA_STRENGTH<<8) |(PC1_DATA_STRENGTH<<9) |(PC2_DATA_STRENGTH<<10)|(PC3_DATA_STRENGTH<<11)|
		(PC4_DATA_STRENGTH<<12)|(PC5_DATA_STRENGTH<<13)|(PC6_DATA_STRENGTH<<14)|(PC7_DATA_STRENGTH<<15)|
		(PC0_FUNC==AS_GPIO ? BIT(16):0)|(PC1_FUNC==AS_GPIO ? BIT(17):0)|(PC2_FUNC==AS_GPIO ? BIT(18):0)|(PC3_FUNC==AS_GPIO ? BIT(19):0) |
		(PC4_FUNC==AS_GPIO ? BIT(20):0)|(PC5_FUNC==AS_GPIO ? BIT(21):0)|(PC6_FUNC==AS_GPIO ? BIT(22):0)|(PC7_FUNC==AS_GPIO ? BIT(23):0);

	/* PE Init ---------------------------------------------------------------*/
	//PE IE settings
//	reg_gpio_pe_ie = (PE0_INPUT_ENABLE<<0)|(PE1_INPUT_ENABLE<<1)|(PE2_INPUT_ENABLE<<2)|(PE3_INPUT_ENABLE<<3);
	//PE OEN settings
//	reg_gpio_pe_oen = (PE0_OUTPUT_ENABLE ?0:BIT(0))|(PE1_OUTPUT_ENABLE ?0:BIT(1))|(PE2_OUTPUT_ENABLE ?0:BIT(2))|(PE3_OUTPUT_ENABLE ?0:BIT(3));
	//PE Output settings
//	reg_gpio_pe_out = (PE0_DATA_OUT<<0)|(PE1_DATA_OUT<<1)|(PE2_DATA_OUT<<2)|(PE3_DATA_OUT<<3);
	//PE DS settings
//	reg_gpio_pe_ds = (PE0_DATA_STRENGTH<<0)|(PE1_DATA_STRENGTH<<1)|(PE2_DATA_STRENGTH<<2)|(PE3_DATA_STRENGTH<<3);
	//PE GPIO function
//	reg_gpio_pe_gpio = (PE0_FUNC == AS_GPIO ?BIT(0):0)|(PE1_FUNC == AS_GPIO ?BIT(1):0)|(PE2_FUNC == AS_GPIO ?BIT(2):0)|(PE3_FUNC == AS_GPIO ?BIT(3):0);

		u8 areg = analog_read (0x0a) & 0x0f;

		analog_write (0x0a, areg | (PULL_WAKEUP_SRC_PA0<<4)|
							(PULL_WAKEUP_SRC_PA1<<6));

		analog_write (0x0b,  PULL_WAKEUP_SRC_PA2 |
							(PULL_WAKEUP_SRC_PA3<<2) |
							(PULL_WAKEUP_SRC_PA4<<4) |
							(PULL_WAKEUP_SRC_PA5<<6));

		analog_write (0x0c,  PULL_WAKEUP_SRC_PA6 |
							(PULL_WAKEUP_SRC_PA7<<2) |
							(PULL_WAKEUP_SRC_PB0<<4) |
							(PULL_WAKEUP_SRC_PB1<<6));

		analog_write (0x0d,  PULL_WAKEUP_SRC_PB2 |
							(PULL_WAKEUP_SRC_PB3<<2) |
							(PULL_WAKEUP_SRC_PB4<<4) |
							(PULL_WAKEUP_SRC_PB5<<6));

		analog_write (0x0e,  PULL_WAKEUP_SRC_PB6 |
							(PULL_WAKEUP_SRC_PB7<<2) |
							(PULL_WAKEUP_SRC_PC0<<4) |
							(PULL_WAKEUP_SRC_PC1<<6));

		analog_write (0x0f,  PULL_WAKEUP_SRC_PC2 |
							(PULL_WAKEUP_SRC_PC3<<2) |
							(PULL_WAKEUP_SRC_PC4<<4) |
							(PULL_WAKEUP_SRC_PC5<<6));

		analog_write (0x10,  PULL_WAKEUP_SRC_PC6 |
							(PULL_WAKEUP_SRC_PC7<<2));
}

void gpio_setup_up_down_resistor(u32 gpio, u32 up_down);
void gpio_set_50k_pullup(u8 enable);
 int gpio_is_input_en(u32 pin);
void gpio_set_input_en(u32 pin, u32 value);
void gpio_set_data_strength(u32 pin, u32 value);
void gpio_set_wakeup(u32 pin, u32 pol, int en);
void gpio_set_func(u32 pin, u32 func);
void gpio_clear_gpio_int_flag(void);


/**
 * @brief      This function set the GPIO function of a pin.
 * @param[in]  pin - the pin needs to set the GPIO function
 * @param[in]  value - enable or disable the pin's GPIO function(0: disable, 1: enable)
 * @return     none
 */
extern void GPIO_SetGPIOEnable(GPIO_PinTypeDef pin, GPIO_BitActionTypeDef value);

/**
 * @brief This function set the output function of a pin.
 * @param[in]  pin - the pin needs to set the output function
 * @param[in]  value - enable or disable the pin's output function(0: disable, 1: enable)
 * @return     none
 */
extern void GPIO_SetOutputEnable(GPIO_PinTypeDef pin, GPIO_BitActionTypeDef value);

/**
 * @brief      This function set the input function of a pin.
 * @param[in]  pin - the pin needs to set the input function
 * @param[in]  value - enable or disable the pin's input function(0: disable, 1: enable)
 * @return     none
 */
extern void GPIO_SetInputEnable(GPIO_PinTypeDef pin, GPIO_BitActionTypeDef value);

/**
 * @brief      This function determines whether the output function of a pin is enabled.
 * @param[in]  pin - the pin needs to determine whether its output function is enabled.
 * @return     1: the pin's output function is enabled ;
 *             0: the pin's output function is disabled
 */
extern int GPIO_IsOutputEnable(GPIO_PinTypeDef pin);

/**
 * @brief     This function determines whether the input function of a pin is enabled.
 * @param[in] pin - the pin needs to determine whether its input function is enabled.
 * @return    1: the pin's input function is enabled ;
 *            0: the pin's input function is disabled
 */
extern int GPIO_IsInputEnable(GPIO_PinTypeDef pin);

/**
 * @brief      This function set the pin's driving strength.
 * @param[in]  pin - the pin needs to set the driving strength
 * @param[in]  value - the level of driving strength(1: strong 0: poor)
 * @return     none
 */
extern void GPIO_SetDataStrength(GPIO_PinTypeDef pin, GPIO_BitActionTypeDef value);

/**
 * @brief     This function set the pin's output level as high.
 * @param[in] pin - the pin needs to set its output level
 * @return    none
 */
extern void GPIO_SetBit(GPIO_PinTypeDef pin);

/**
 * @brief     This function set the pin's output level as low.
 * @param[in] pin - the pin needs to set its output level
 * @return    none
 */
extern void GPIO_ResetBit(GPIO_PinTypeDef pin);

/**
 * @brief     This function set the pin's output level.
 * @param[in] pin - the pin needs to set its output level
 * @param[in] value - value of the output level(1: high 0: low) 
 * @return    none
 */
extern void GPIO_WriteBit(GPIO_PinTypeDef pin, GPIO_BitActionTypeDef value);

/**
 * @brief     This function read the pin's input level.
 * @param[in] pin - the pin needs to read its input level
 * @return    the pin's input level(1: high 0: low)
 *            eg:0x08 indicate the GP3 is high level.
 *            all value:0x80.0x40.0x20.0x10.0x08.0x04.0x02.0x01.0x00
 */
extern unsigned long GPIO_ReadInputBit(GPIO_PinTypeDef pin);

/**
 * @brief     This function read the pin's output level.
 * @param[in] pin - the pin needs to read its output level
 * @return    the pin's output level(1: high 0: low)
 */
extern unsigned long GPIO_ReadOutputBit(GPIO_PinTypeDef pin);

/**
 * @brief      This function read all the pins' input level.
 * @param[out] p - the buffer used to store all the pins' input level
 * @return     none
 */
extern void GPIO_ReadAll(unsigned char *p);

/**
 * @brief     This function read a pin's input level from the buffer.
 * @param[in] pin - the pin needs to read its input level from the buffer
 * @param[in] buf - the buf from which to read the pin's input level
 * @return    none
 */
extern unsigned long GPIO_ReadCache(GPIO_PinTypeDef pin, unsigned char *p);

/**
 * @brief     This function set a pin's pull-up/down resistor.
 * @param[in] pin  - the pin needs to set its pull-up/down resistor
 * @param[in] type - the type of the pull-up/down resistor
 * @return    none
 */
extern void GPIO_PullSet(GPIO_PinTypeDef pin, GPIO_PullTypeDef type);

/**
 * @brief     This function enables a pin's IRQ function.
 * @param[in] pin - the pin needs to enables its IRQ function.
 * @return    none
 */
extern void GPIO_EnableInterrupt(GPIO_PinTypeDef pin);

/**
 * @brief     This function set a pin's polarity that trig its IRQ.
 * @param[in] pin - the pin needs to set its edge polarity that trig its IRQ
 * @param[in] falling - value of the edge polarity(1: falling edge 0: rising edge)
 * @return    none
 */
extern void GPIO_SetInterruptPolarity(GPIO_PinTypeDef pin, GPIO_BitActionTypeDef falling);

/**
 * @brief     This function set a pin's IRQ.
 * @param[in] pin - the pin needs to enable its IRQ
 * @param[in] falling - value of the edge polarity(1: falling edge 0: rising edge)
 * @return    none
 */
extern void GPIO_SetInterrupt(GPIO_PinTypeDef pin, GPIO_BitActionTypeDef falling);

/**
 * @brief     This function disables a pin's IRQ function.
 * @param[in] pin - the pin needs to disables its IRQ function.
 * @return    none
 */
extern void GPIO_ClearInterrupt(GPIO_PinTypeDef pin);

#if 0
/**
 * @brief     This function determines whether a pin's IRQ occurs.
 * @param[in] pin - the pin needs to determine whether its IRQ occurs.
 * @return    none
 */
 extern int GPIO_IsInterruptOccur(GPIO_PinTypeDef pin);

#endif /* #if 0 */

#endif //GPIO_H 
