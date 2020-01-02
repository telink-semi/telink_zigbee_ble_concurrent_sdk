/********************************************************************************************************
 * @file     pwm.h
 *
 * @brief    This file provides set of functions for PWM module
 *
 * @author   junjun.xu@telink-semi.com; qiuwei.chen@telink-semi.com
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

#ifndef _PWM_H
#define _PWM_H

#include "bsp.h"
#include "gpio.h"

#define		PWM_MODE			0x782
#define		PWM_CC0				0x783
#define		PWM_CC1				0x784
#define		PWM_CC2				0x785
#define		PHASE_TIME_BASE		0x788
#define		CSC_VALUE_BASE		0x794
#define		CYC_VALUE_BASE		0x796
#define		SFN_VALUE_BASE		0x7ac

/**
 * @brief  enum variable, the number of PWM channels supported
 */
typedef enum{
	PWM0 = 0,
	PWM1,
	PWM2,
	PWM3,
	PWM4,
	PWM5,
}PWM_NTypeDef;

/**
 * @brief  enum variable used for PWM work mode setting
 */
typedef enum{
	NORMAL=0x00,
	COUNT,
	IR = 0x03,
	IR_FIFO = 0x07,
	IR_DMA_FIFO =0x0f,
}PWM_ModeTypeDef;

/**
 * pwm interrupt source
 */
typedef enum{
	NOIRQ = 0xff,
	PWM0PNUM = 0,
	PWM0_IR_DMA_FIFO,
	PWM0CYCLEDONE,
	PWM1CYCLEDONE,
	PWM2CYCLEDONE,
	PWMIRQSOURCENUM,
}PWM_IrqSourceTypeDef;

/**
 *
 */
#define    PWM_INT_STATUS_REG             READ_REG8(0x7b1)
enum{
	PWM0_PNUM_INT_CLR  = BIT(0),
	PWM0_IR_DMA_FIFO_INT_CLR  = BIT(1),
	PWM0_CYCLE_DONE_INT= BIT(2),
	PWM1_CYCLE_DONE_INT= BIT(3),
	PWM2_CYCLE_DONE_INT= BIT(4),
};
#define    PWM0_FRAME_INT_STATUS_CLEAR    PWM_INT_STATUS_REG |= PWM0_PNUM_INT_CLR;
#define    PWM1_FRAME_INT_STATUS_CLEAR    PWM_INT_STATUS_REG |= PWM1_PNUM_INT_CLR;

#define    PWM0_FRAME_DONE_INT_STATUS     PWM_INT_STATUS_REG & PWM0_PNUM_INT_CLR;
#define    PWM1_FRAME_DONE_INT_STATUS     PWM_INT_STATUS_REG & PWM1_PNUM_INT_CLR;

/**
 *
 */
#define    PWM_PNUM_REG_BASE              0x7ac
#define    PWM_SET_FRAME_NUM(v,n)   	  ( *(volatile unsigned short *)(PWM_PNUM_REG_BASE + (v << 1)) = (n) )

#define    PWM0_PNUM_REG                  READ_REG16(0x7ac)
#define    PWM0_SET_FRAME(n)              PWM0_PNUM_REG = (n)


/**
 *
 */
#define    PWM_CTRL_REG                   READ_REG8(0x780)
enum{
	PWM0_EN   = BIT(0),
	PWM1_EN   = BIT(1),
	PWM2_EN   = BIT(2),
	PWM3_EN   = BIT(3),
	PWM4_EN   = BIT(4),
	PWM5_EN   = BIT(5),
};
#define    PWM_START(v)                   PWM_CTRL_REG |= BIT(v);
#define    PWM0_START                     PWM_CTRL_REG |= PWM0_EN;
#define    PWM1_START					  PWM_CTRL_REG |= PWM1_EN;

#define	   PWM_STOP(v)					  PWM_CTRL_REG &= (~BIT(v));
#define    PWM0_STOP					  PWM_CTRL_REG &= (~PWM0_EN);
#define    PWM1_STOP					  PWM_CTRL_REG &= (~PWM1_EN);


/**
 *	@brief	   Initiate the PWM function include setting and enabling the PWM clock.
 *  @param[in] none
 *	@return	   none
 */
extern void PWM_Init(unsigned char pwmCLKdiv);

/**
 * 	@brief     set the pwm clock,the function is similar to the pwm_Init.
 * 	           eg:pwm clock = 140 000 using function PWM_InitClk(140000);
 * 	           limite: system_clock/pwm_clk <= 0xff. system_clock = CLOCK_SYS_CLOCK_HZ
 *             because the pwmCLKdiv range from 0 to 0xff,so if the pwmCLKdiv can not out of range
 * 	@param[in] pwm_clk - pwm clock to set.
 * 	@return    0: set error, pwmCLKdiv is out of the range:0 to 0xff ;
 *             1: success       
 */
extern unsigned char PWM_InitClk(unsigned int pwm_clk);

extern void PWM_CFG_GPIO(GPIO_PinTypeDef pin,PWM_NTypeDef pwm);
/**
 *	@brief	    open a pwm channel and setting the parameters
 *
 *	@param[in]	pwmNumber - enum variable of pwm channel number
 *	@param[in]	pwmWorkM - enum variable of pwm work mode
 *	@param[in]	cscValue - count status value
 *	@param[in]	cycVlaue - cycle value
 *	@param[in]	sfValue - signal frame value for the COUNT and IR mode
 *
 *	@return	    1: set success; 
 *              0: set error, if you set pwm2 - pwm5 to work on the other not normal mode, the function will return 0.
 */
extern unsigned char PWM_Open(PWM_NTypeDef pwmNumber,PWM_ModeTypeDef pwmWorkM,unsigned short cscValue,unsigned short cycValue,unsigned short sfValue);

/**
 *	@brief	    setting a pwm channel of the parameters
 *
 *	@param[in]	pwmNumber - enum variable of pwm channel number
 *	@param[in]	pwmWorkM - enum variable of pwm work mode
 *	@param[in]	cscValue - count status value
 *	@param[in]	cycVlaue - cycle value
 *	@param[in]	sfValue - signal frame value for the COUNT and IR mode
 *
 *	@return	    1: set success;
 *              0: set error, if you set pwm1 - pwm5 to work on the other not normal mode, the function will return 0.
 */
unsigned char PWM_Setting(PWM_NTypeDef pwmNumber,PWM_ModeTypeDef pwmWorkM,unsigned short cscValue,unsigned short cycValue,unsigned short sfValue);
/**
 *	@brief	   close a pwm channel and reset the settings to default
 *	@param[in] pwmNumber - enum variable of pwm channel number
 *	@return	   None
 */
extern void PWM_Close(PWM_NTypeDef pwmNumber);

/**
 *
 *	@brief	   start a pwm channel and enable the output
 *	@param[in] pwmNumber - enum variable of pwm channel number
 *	@return	   none
 */
extern void PWM_Start(PWM_NTypeDef pwmNumber);

/**
 *	@brief	   stop a pwm channel and disable the output
 *	@param[in] pwmNumber - enum variable of pwm channel number
 *	@return	   none
 */
extern void PWM_Stop(PWM_NTypeDef pwmNumber);

/**
 *	@brief	   set the duty cycle of a pwm channel
 *
 *	@param[in] pwmNumber - enum variable of pwm channel number
 *	@param[in] cscValue - count status value
 *	@param[in] cycVlaue - cycle value

 *	@return	   1: set success;
 *             0: set error, if csValue>cycValue
 */
extern unsigned char PWM_DutyCycleSet(PWM_NTypeDef pwmNumber, unsigned short csValue,unsigned short cycValue);

/**
 *	@brief	   enable pwm interrupt
 *	@param[in] pwmNumber - enum variable of pwm channel number
 *	@return	   none
 */
extern unsigned char PWM_InterruptEnable(PWM_IrqSourceTypeDef pwmIrqSrc);

/**
 *	@brief	   disable pwm interrupt
 *	@param[in] pwmNumber - enum variable of pwm channel number
 *	@return	   none
 */
extern unsigned char PWM_InterruptDisable(PWM_IrqSourceTypeDef pwmIrqSrc);
/**
 *	@brief	   get interrupt source
 *  @param[in] none
 *	@return	   pwm irq source, enum variable
 */
extern PWM_IrqSourceTypeDef PWM_InterruptSourceGet(void );
/**
 * @brief     judge whether the interrupt is the parameter's pwm interrupt.
 * @param[in] pwm_x  - enum variable of pwm channel number
 * @return    0 : be not the pwm_x irq ;
 *            0xff: there are no pwm irq ;
 *            pwm_x: if be the pwm_x irq,it will return the pwm_x
 */
extern PWM_IrqSourceTypeDef PWM_ISpwmxInterrupt(PWM_IrqSourceTypeDef pwm_x);

/**
 *	@brief	   clear interrupt status
 *	@param[in] pwmNumber - enum variable of pwm channel number
 *	@return	   none
 */
extern void PWM_InterruptStatusClr(PWM_IrqSourceTypeDef irq_src);

/**
 *	@brief	   Invert PWM-INV output (would generate the same output waveform as PWMN)
 * 	@param[in] pwmNumber - enum variable of pwm number
 *	@return	   none
 */
extern void PWM_INVInvert(PWM_NTypeDef pwmNumber);


#endif /* PWM_8267_H_ */
