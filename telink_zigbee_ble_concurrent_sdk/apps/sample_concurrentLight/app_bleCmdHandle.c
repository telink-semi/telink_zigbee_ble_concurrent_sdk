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
#include "sampleLight.h"

enum{
	/*
	 * the command identifier to configure the zigbee network
	 * */
	APP_BLE_CMD_ZB_NETWORK_JOIN			=	0xFF00,
	APP_BLE_CMD_ZB_NETWORK_KEY_SET		=	0xFF01,
	APP_BLE_CMD_ZB_LINK_KEY_SET			=	0xFF02,
	APP_BLE_CMD_ZB_NWK_MANAGEMENT_SET	=	0xFF03,
	APP_BLE_CMD_ZB_NETWORK_JOIN_DIRECT	=	0xFF04,

	/*
	 * the command identifier to change some ble setting
	 * */
	APP_BLE_CMD_INTERVAL_SET		=	0xFF10
};

typedef struct{
	u16 panId;
	u16 nwkAddr;
	u8  channel;
}joinNetworkInfo_t;

joinNetworkInfo_t  g_joinNetworkInfo = {0};

s32 sampleLight_bdbNetworkJoinDirect(void *arg){
	u8 extPanId[] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};
	u8 nwkKey[] = {0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0, 0x01};

	if(SUCCESS == bdb_join_direct(g_joinNetworkInfo.channel, g_joinNetworkInfo.panId, g_joinNetworkInfo.nwkAddr, extPanId, nwkKey, SS_SEMODE_DISTRIBUTED, 1)){
		return -1;
	}

	return 0;
}

int zb_ble_ci_cmd_handler(u16 clusterId, u8 len, u8 *payload){
	u8 cmdId = payload[0];
	u8 *pCmd = &payload[1];

	int ret = 0;

	if(clusterId == APP_BLE_CMD_ZB_NWK_MANAGEMENT_SET){
		u16 dstAddr = 0xfffd;
		u8 sn = 0;
		zdo_mgmt_nwk_update_req_t req;

		req.nwk_manager_addr = 0x1234;
		req.scan_ch = 0x07fff800;
		req.scan_duration = ZDO_NWK_MANAGER_ATTRIBUTES_CHANGE;
		req.nwk_update_id = 0x00;

		zb_mgmtNwkUpdateReq(dstAddr, &req, &sn);
	}else if(clusterId == ZCL_CLUSTER_GEN_ON_OFF){
		sampleLight_onOffCb(NULL, cmdId, pCmd);
	}else if(clusterId == ZCL_CLUSTER_GEN_LEVEL_CONTROL){
		sampleLight_levelCb(NULL, cmdId, pCmd);
	}else if(clusterId == APP_BLE_CMD_INTERVAL_SET){
		app_bleConnIntervalSet(payload[0], ((payload[1] << 8) | payload[2]));
	}else if(clusterId == APP_BLE_CMD_ZB_NETWORK_JOIN_DIRECT){
		if(gLightCtx.timerSteering){
			TL_ZB_TIMER_CANCEL(&gLightCtx.timerSteering);
		}
		g_joinNetworkInfo.channel = payload[0];
		g_joinNetworkInfo.panId = ((u16)payload[1] | ((u16)payload[2] << 8));
		g_joinNetworkInfo.nwkAddr = ((u16)payload[3] | ((u16)payload[4] << 8));

		TL_ZB_TIMER_SCHEDULE(sampleLight_bdbNetworkJoinDirect, NULL, 100 * 1000);
	}else{
		ret = -1;
	}
	return ret;
}

#endif  /* __PROJECT_TL_DIMMABLE_LIGHT__ */

