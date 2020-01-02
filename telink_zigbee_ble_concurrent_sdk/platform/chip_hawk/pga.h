/*******************************************************************************************************
 * @file     pga.h
 *
 * @brief    This file provides set of functions to manage the PGA module
 *
 * @author   qiuwei.chen@telink-semi.com;
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
 ********************************************************************************************************/
#ifndef		_PGA_H
#define		_PGA_H
#include "bsp.h"

#define     REG_PGA_INPUT_SEL1           READ_REG8(0x28)
#define     REG_PGA_INPUT_SEL2            READ_REG8(0x29)
enum{
	PGA_INPUT_A2A3_DIS   = BIT(0),
	PGA_INPUT_C4C5_EN    = BIT(0),
};
/**
 *  set ANA_C<3> and ANA_C<2> as positive and minus input of the PGA
 */
#define		SET_PGAchannel_ONE	   REG_PGA_INPUT_SEL1 &= (~PGA_INPUT_A2A3_DIS);
/**
 *  set ANA_C<5> and ANA_C<4> as positive and minus input of the PGA
 */
#define		SET_PGAchannel_TWO	   REG_PGA_INPUT_SEL1 |= PGA_INPUT_C4C5_EN;

#define     AREG_PGA_MUTE          0x86
enum{
	PGA_MUTE = BIT(2),
};

typedef enum {
	DBP0,
	DB20,
}PGA_PreAmpValTypeDef;

typedef enum {
	DB0,
	DB3,
	DB6,
	DB9,
}PGA_PostAmpValTypeDef;

/**
 * @brief     select the input pin of PGA. PGA has two groups of AMIC input pin.
 *            A<4>/A<5> and A<2>/A<3>
 * @param[in] chM - 1: select the A<4>/A<5> as the input pin of PGA
 *                  0: select the A<2>/A<3> as the input pin of PGA
 * @return    none
 */
extern void PGA_SetChannel(unsigned char chM);

/**
 * @brief     PGA output enable or disable function, call this function to enable or disable the PGA output
 * @param[in] enDis - '1' enable output/mute off audio; '0' disable output/mute  on audio
 * @return    none
 */
extern void PGA_SetOutput(unsigned char enDis);

/**
 * @brief     adjust pre-amplifier gain value
 * @param[in] preGV - enum var of PREAMPValue, 0DB or 20DB
 * @return    1: adjusted success;
 *            0: adjust error
 */
extern unsigned char PGA_PreGainAdjust(PGA_PreAmpValTypeDef preGV);

/**
 * @brief      adjust post-amplifier gain value
 * @param[in]  posGV - enum var of POSTAMPValue, 0,3,6 or 9dB
 * @return     1: adjusted success;
 *             0: adjust error
 */
extern unsigned char PGA_PostGainAdjust(PGA_PostAmpValTypeDef posGV);

/**
 * @brief  pga initiate function, call this function to enable the PGA module.
 *         the input channel deafult set to ANA_C<3> and ANA_C<2>
 * @param  none
 * @return none
 */
extern void PGA_Init(void);




#endif
