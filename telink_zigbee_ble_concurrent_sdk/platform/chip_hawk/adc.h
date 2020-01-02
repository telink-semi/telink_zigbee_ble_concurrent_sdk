/********************************************************************************************************
 * @file     adc.h
 *
 * @brief    This file provides set of driver functions to manage the adc module
 *
 * @author   junyuan.zhang@telink-semi.com;
 * @date     may. 8, 2017
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
#ifndef 	_ADC_H
#define 	_ADC_H

#include "bsp.h"

extern unsigned char ADC_Pre_Scale;
extern unsigned char ADC_Vref;
extern unsigned char ADC_VBAT_Scale;

extern const unsigned char  VBAT_tab[4];
extern const unsigned char  Vref_tab[4];

typedef enum {
	L_CH 	= 1,
	R_CH 	= 2,
	M_CH  	= 4,
	RNS_CH 	= 8,
}ADC_ChTypeDef;

/**
 *  ADC reference voltage
 */
typedef enum {
	RV_0P6,
	RV_0P9,
	RV_1P2,
	RV_VBAT,
}ADC_RefVolTypeDef;

#define    REG_ADC_VREF					ReadAnalogReg(0x80+103)
enum{
	ADC_VREF_L_CH  = BIT_RNG(0,1),
	ADC_VREF_R_CH  = BIT_RNG(2,3),
	ADC_VREF_M_CH  = BIT_RNG(4,5),
};

/**
 *ADC analog input channel
 */
///ADC analog negative input channel selection enum
typedef enum {
	NOINPUTN,
	A6N,
	A7N,
	B0N,
	B1N,
	B2N,
	B3N,
	B4N,
	B5N,
	B6N,
	B7N,
	PGA_N0,
	PGA_N1,
	TEMSENSORN,
	RSSI_N,
	GND,
}ADC_InputNchTypeDef;

///ADC analog positive input channel selection enum
typedef enum {
	NOINPUTP,
	A6P,
	A7P,
	B0P,
	B1P,
	B2P,
	B3P,
	B4P,
	B5P,
	B6P,
	B7P,
	PGAP0,
	RSVD_PGAP1,
	TEMSENSORP,
	RSSI_P,
	VBAT,
}ADC_InputPchTypeDef;

#define    REG_ADC_AIN_MISC				ReadAnalogReg(0x80+104)
enum{
	ADC_MISC_N_INPUT  = BIT_RNG(0,3),
	ADC_MISC_P_INPUT  = BIT_RNG(4,7),
};
#define    REG_ADC_AIN_LEFT				ReadAnalogReg(0x80+105)
enum{
	ADC_LEFT_N_INPUT  = BIT_RNG(0,3),
	ADC_LEFT_P_INPUT  = BIT_RNG(4,7),
};
#define    REG_ADC_AIN_RIGHT			ReadAnalogReg(0x80+106)
enum{
	ADC_RIGHT_N_INPUT  = BIT_RNG(0,3),
	ADC_RIGHT_P_INPUT  = BIT_RNG(4,7),
};

/**
 *ADC resolution
 */
typedef enum {
	RES8,
	RES10,
	RES12,
	RES14,
}ADC_ResTypeDef;
/**
 *ADC channel input mode
 */
typedef enum {
	SINGLEEND,
	DIFFERENTIAL
}ADC_InputModeTypeDef;
#define    REG_ADC_RES_LR				ReadAnalogReg(0x80+107)
enum{
	ADC_LEFT_RESOLUTION   = BIT_RNG(0,1),
	ADC_RIGHT_RESOLUTION  = BIT_RNG(4,5),
};
#define    REG_ADC_MODE					ReadAnalogReg(0x80+108)
enum{
	ADC_MISC_RESOLUTION   = BIT_RNG(0,1),
	ADC_LEFT_MODE   = BIT(4),
	ADC_RIGHT_MODE  = BIT(5),
	ADC_MISC_MODE   = BIT(6),
};
/**
 *ADC Sampling time
 */
typedef enum {
	S_3,
	S_6,
	S_9,
	S_12,
	S_15,
	S_18,
	S_21,
	S_24,
	S_27,
	S_30,
	S_33,
	S_36,
	S_39,
	S_42,
	S_45,
	S_48,
}ADC_SampCycTypeDef;
#define    REG_ADC_STB_SAMLR			ReadAnalogReg(0x80+109)
enum{
	ADC_LEFT_STBSAMP   = BIT_RNG(0,3),
	ADC_RIGHT_STBSAMP   = BIT_RNG(4,7),
};
#define    REG_ADC_STB_SAMM				ReadAnalogReg(0x80+110)
enum{
	ADC_MISC_STBSAMP   = BIT_RNG(0,3),
};

#define    REG_ADC_MAX_MC        		ReadAnalogReg(0x80+111)
#define    REG_ADC_MAX_C        		ReadAnalogReg(0x80+112)
#define    REG_ADC_MAX_LENGTH        	ReadAnalogReg(0x80+113)

enum{
	ADC_R_MAX_S   = BIT_RNG(0,3),
	ADC_R_MAX_C   = BIT_RNG(4,5),
	ADC_R_MAX_MC  = BIT_RNG(6,7),
};

enum{
	DISABLE = 0,
	ENABLE  = 1,
};
#define    REG_ADC_EN_SCNT        	ReadAnalogReg(0x80+114)
enum{
	ADC_LEFT_EN   = BIT(0),
	ADC_RIGHT_EN  = BIT(1),
	ADC_MISC_EN   = BIT(2),
	ADC_RNS_EN    = BIT(3),
	ADC_MAX_SCNT  = BIT_RNG(4,6),
};

#define    REG_ADC_CLK_DIV        		ReadAnalogReg(0x80+116)

#define    REG_ADC_RNGL        			ReadAnalogReg(0x80+117)
#define    REG_ADC_RNGH        			ReadAnalogReg(0x80+118)
#define    REG_ADC_MISCL        		ReadAnalogReg(0x80+119)
#define    REG_ADC_MISCH        		ReadAnalogReg(0x80+120)
enum{
	ADC_MISC_DATA   = BIT_RNG(0,6),
	ADC_MISC_VLD    = BIT(7),
};
#define		CHECK_ADC_MISC_STATUS		((REG_ADC_MISCH & ADC_MISC_VLD)?1:0)

typedef enum {
	VBAT_DIV_OFF,
	VBAT_DIV_4,
	VBAT_DIV_3,
	VBAT_DIV_2,
}ADC_VbatDivTypeDef;
#define    REG_ADC_VBAT_DIV        		ReadAnalogReg(0x80+121)
enum{
	ADC_VBAT_DIV   = BIT_RNG(2,3),
};

#define    REG_ADC_PRE_SCALING        		ReadAnalogReg(0x80+122)

enum{
	ADC_PRE_SCALING   = BIT_RNG(6,7),
};
typedef enum{
	ADC_PRE_SCALE_1_1,
	ADC_PRE_SCALE_1_2,
	ADC_PRE_SCALE_1_4,
	ADC_PRE_SCALE_1_8,
}ADC_PreScalingTypeDef;

#define    REG_ADC_MODE_PD        		ReadAnalogReg(0x80+124)
enum{
	ADC_MODE         = BIT(4),
	ADC_POWER_DOWN   = BIT(5),
};

typedef enum{
	NORMAL_MODE      = 0,
	RNS_MODE         = BIT(4),
}ADCModeTypeDef;

typedef enum {
	SAR_ADC_RNG_MODE   = 0,
	R_RNG_MODE_0       = 2,
	R_RNG_MODE_1       = 3,
	ADC_DAT12_RNG_MODE = 4,
	ADC_DAT5_RNG_MODE  = 6,
}RNG_SrcTypeDef;

typedef enum {
	READ_UPDATA        = BIT(3),
	CLOCLK_UPDATA      = BIT(4),
}RNG_UpdataTypeDef;


/**
 * @brief      This function sets ADC resolution for channel Misc
 * @param[in]  adcRes - enum variable adc resolution.
 * @param[in]  ch_n  - enum variable of adc channel
 * @return     none
 */
extern void ADC_ResSet(ADC_ResTypeDef adcRes,ADC_ChTypeDef ch_n);

extern void ADC_State_Length_Set(short R_max_mc,short R_max_c,unsigned char R_max_s);
extern void ADC_State_SCNT_EN(ADC_ChTypeDef ad_ch,unsigned char cnt);

/**
 * @brief      This function sets ADC input channel
 * @param[in]  adcInCha - enum variable of adc input channel.
 * @return     none
 */
extern void ADC_AnaSingleEndChSet(ADC_InputPchTypeDef adcInCha, ADC_ChTypeDef ch_n);
extern void ADC_AnaDiffChSet(ADC_InputPchTypeDef adcInPCha,ADC_InputNchTypeDef adcInNCha, ADC_ChTypeDef ch_n);

/**
 * @brief      This function sets ADC sample time(the number of adc clocks for each sample)
 * @param[in]  adcST - enum variable of adc sample time.
 * @param[in]  ch_n  - enum variable of adc channel
 * @return     none
 */
extern void ADC_SampleTimeSet( ADC_SampCycTypeDef adcST, ADC_ChTypeDef ch_n);

/**
 * @brief      This function sets ADC reference voltage for the Misc and L channel
 * @param[in]  adcRF - enum variable of adc reference voltage.
 * @param[in]  ch_n  - enum variable of adc channel
 * @return     none
 */
extern void ADC_RefVoltageSet(ADC_RefVolTypeDef adcRF,ADC_ChTypeDef ch_n);
extern void ADC_VbatDivSet(ADC_VbatDivTypeDef vbat_div);
extern void ADC_modeSet(ADCModeTypeDef stat);
extern void ADC_ScaleSet(ADC_PreScalingTypeDef stat);

/**
 * @brief  get adc sampled value
 * @param  none
 * @return sampled_value, raw data
 */
extern unsigned short ADC_SampleValueGet(void);

/**
 * Name     :RNG_Set
 * Function :Set the source and mode of the random number generator
 * Input    :RNG_SrcTypeDef stat
 *          :RNG_SrcTypeDef|RNG_UpdataTypeDef
 * return   :None
 */
extern void RNG_Set(RNG_SrcTypeDef stat,RNG_UpdataTypeDef stat1);
/**
 * Name     :RNG_read
 * Function :Read the value of the random number generator
 * Input    :None
 * return   :unsigned short RngValue
 *          :random number
 */
extern unsigned short RNG_Read(void);

#endif

