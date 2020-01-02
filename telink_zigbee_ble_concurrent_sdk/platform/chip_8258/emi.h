/********************************************************************************************************
 * @file     emi.h
 *
 * @brief    EMI configuration header for tlsr8258
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

#ifndef EMI_H_
#define EMI_H_

#include "driver_8258.h"

//singletone mode
void rf_emi_single_tone(RF_PowerTypeDef power_level,signed char rf_chn);

//rx function
void rf_emi_rx(RF_ModeTypeDef mode,signed char rf_chn);
void rf_emi_rx_loop(void);
unsigned int rf_emi_get_rxpkt_cnt(void);
char rf_emi_get_rssi_avg(void);
unsigned char *rf_emi_get_rxpkt(void);

//tx cd mode
void rf_emi_tx_continue_setup(RF_ModeTypeDef rf_mode,RF_PowerTypeDef power_level,signed char rf_chn,unsigned char pkt_type);
void rf_continue_mode_loop(void);

//tx brust mode
void rf_emi_tx_brust_setup(RF_ModeTypeDef rf_mode,RF_PowerTypeDef power_level,signed char rf_chn,unsigned char pkt_type);
void rf_emi_tx_brust_loop(RF_ModeTypeDef rf_mode,unsigned char pkt_type);

//stop tx rx
void rf_emi_stop(void);

#endif /* EMI_H_ */
