/********************************************************************************************************
 * @file     app_bleCmdHandle.c
 *
 * @brief    HA Router
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

#if (__PROJECT_TL_CONCURRENT_LIGHT__)

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zcl_include.h"

enum{
	/*
	 * the command identifier to configure the zigbee network
	 * */
	APP_BLE_CMD_ZB_NETWORK_JOIN		=	0xFF00,
	APP_BLE_CMD_ZB_NETWORK_KEY_SET	=	0xFF01,
	APP_BLE_CMD_ZB_LINK_KEY_SET		=	0xFF02,

	/*
	 * the command identifier to change some ble setting
	 * */
	APP_BLE_CMD_INTERVAL_SET		=	0xFF10
};

int zb_ble_ci_cmd_handler(u16 clusterId, u8 len, u8 *payload){
	u8 cmdId = payload[0];
	u8 *pCmd = &payload[1];

	if(clusterId == ZCL_CLUSTER_GEN_ON_OFF){
		sampleLight_onOffCb(NULL, cmdId, pCmd);
	}else if(clusterId == ZCL_CLUSTER_GEN_LEVEL_CONTROL){
		sampleLight_levelCb(NULL, cmdId, pCmd);
	}else if(clusterId == APP_BLE_CMD_INTERVAL_SET){
		app_bleConnIntervalSet(payload[0], ((payload[1] << 8) | payload[2]));
	}
}

#endif  /* __PROJECT_TL_DIMMABLE_LIGHT__ */

