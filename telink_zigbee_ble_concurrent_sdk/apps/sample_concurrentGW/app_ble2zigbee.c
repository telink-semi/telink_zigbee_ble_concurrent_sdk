/********************************************************************************************************
 * @file     app_ble2zigbee.c
 *
 * @brief    call back function for ble, transfer ble command to zigbee operation
 *
 * @author
 * @date     Dec. 1, 2016
 *
 * @par      Copyright (c) 2016, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *			 The information contained herein is confidential and proprietary property of Telink
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in.
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/

#if (__PROJECT_TL_CONCURRENT_GW__)

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zbhci.h"

/**
 * @brief      the callback of the ble indication, transfer the command to zigbee operation
 *
 * @param[in]   cmdId  command identifier
 *
 * @param[in]   payload command payload
 *
 *
 * @return      None
 */
volatile u8 T_bleCmdDbg[64] = {0};
int zb_ble_ci_cmd_handler(u16 cmdId, u8 len, u8 * payload){
	T_bleCmdDbg[0] = len;
	memcpy((u8*)&T_bleCmdDbg[1], (u8*)&cmdId, 2);
	memcpy((u8*)&T_bleCmdDbg[3], payload, len);
	zbhciCmdHandler(cmdId, (u16)len, payload);

	return 0;
}

#endif  /* __PROJECT_TL_CONCURRENT_GW__ */
