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

#if (__PROJECT_TL_CONCURRENT_SWITCH__)

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zcl_include.h"
#include "sampleSwitch.h"
#include "app_ui.h"

enum{
	/*
	 * the command identifier to configure the zigbee network
	 * */
	APP_BLE_CMD_ZB_NETWORK_JOIN		=	0xFF00,
	APP_BLE_CMD_ZB_FACTORY_RESET	=	0xFF01,
	APP_BLE_CMD_ZB_NETWORK_KEY_SET	=	0xFF02,
	APP_BLE_CMD_ZB_LINK_KEY_SET		=	0xFF03,
};

int zb_ble_ci_cmd_handler(u16 cmdId, u8 len, u8 *payload){
	if(cmdId == APP_BLE_CMD_ZB_NETWORK_JOIN){
		bdb_networkSteerStart();
		g_switchAppCtx.state = APP_STATE_ZB_JOINNING;
	}else if(cmdId == APP_BLE_CMD_ZB_FACTORY_RESET){
		zb_resetDevice2FN();
	}
}

#endif  /* __PROJECT_TL_DIMMABLE_LIGHT__ */

