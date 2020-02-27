/********************************************************************************************************
 * @file     zb_appCb.c
 *
 * @brief    call back function for zigbee
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
#include "zb_api.h"
#include "zcl_include.h"
#include "bdb.h"
#include "sampleGw.h"
#if ZBHCI_EN
#include "zbhci.h"
#endif

/**********************************************************************
 * LOCAL CONSTANTS
 */

//configure zigbee network
#define ZB_BLE_CI_CMD_CFG_SET_CHANNEL           0x0001
#define ZB_BLE_CI_CMD_CFG_SET_PANID             0x0002
#define ZB_BLE_CI_CMD_CFG_SET_SHORT_ADDR        0x0003
#define ZB_BLE_CI_CMD_CFG_SET_EXT_PANID         0x0004
#define ZB_BLE_CI_CMD_CFG_SET_NWK_KEY           0x0005
#define ZB_BLE_CI_CMD_CFG_START_NWK             0x0006

//light control
#define ZB_BLE_CI_CMD_LIGHT_TOGGLE_BROADCAST    0x0010
#define ZB_BLE_CI_CMD_LIGHT_TOGGLE_UNICAST      0x0011
#define ZB_BLE_CI_CMD_LIGHT_TOGGLE_UNICAST_BY_SEQ 0x0012
//end

//data
#define ZB_BLE_CI_DATA_DEFAULT_CHANNEL          13
#define ZB_BLE_CI_DATA_DEFAULT_PANID            0xface
//end
extern u16 ChipId;
u8 zb_ble_ci_channel = ZB_BLE_CI_DATA_DEFAULT_CHANNEL;
u16 zb_ble_ci_panid = ZB_BLE_CI_DATA_DEFAULT_PANID;
u16 zb_ble_ci_short_addr = MAC_SHORT_ADDR_BROADCAST;
u8 zb_ble_ci_extPanId[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77};
u8 zb_ble_ci_nwkKey[16] = { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89,
			  	  	  	0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0, 0x01};

u16 zb_ble_ci_cmd_light_toggle_dest_addr;

#define SAMPLE_SWITCH_ENDPOINT 0x01

//
typedef struct
{
    unsigned char isActive;
    unsigned char seqNO;
    //unsigned char nwk_addr[2];
    unsigned short nwk_addr;
    unsigned char ieee_addr[8];
}device_list_node_t;

device_list_node_t device_list[16];

void init_device_list()
{
    int i;
    for(i=0;i<16;i++)
    {
        device_list[i].isActive = 0;
    }
}

void DevAnnounceIndCB(void *arg){
    static unsigned char sequence_number = 0;
    device_list_node_t *ptr = NULL;
    int i;

    zdo_device_annce_req_t *devAnnInd = (zdo_device_annce_req_t *)arg;
    for(i=0;i<16;i++)
    {
        if(device_list[i].isActive == 0)
        {
            ptr = &(device_list[i]);
            break;
        }
    }

    if(ptr == NULL)
    {
        return;
    }

    ptr->isActive = 1;
    ptr->seqNO = sequence_number;
    sequence_number++;
    //memcpy(ptr->nwk_addr, &devAnnInd->nwk_addr_local, 2);
    ptr->nwk_addr = devAnnInd->nwk_addr_local;
    memcpy(ptr->ieee_addr, devAnnInd->ieee_addr_local, 8);
}
//

//begin
void onoff_light_unicast(void * p){
	epInfo_t dstEpInfo;
	TL_SETSTRUCTCONTENT(dstEpInfo, 0);

	dstEpInfo.dstAddrMode = APS_SHORT_DSTADDR_WITHEP;
	dstEpInfo.dstEp = SAMPLE_SWITCH_ENDPOINT;
	dstEpInfo.dstAddr.shortAddr = zb_ble_ci_cmd_light_toggle_dest_addr;
	dstEpInfo.profileId = HA_PROFILE_ID;
	dstEpInfo.txOptions = APS_TX_OPT_ACK_TX;
	dstEpInfo.radius = 0;

	zcl_onOff_toggleCmd(SAMPLE_SWITCH_ENDPOINT, &dstEpInfo, FALSE);
}

//end
void onoff_light_broadcast(void * p){
	epInfo_t dstEpInfo;
	TL_SETSTRUCTCONTENT(dstEpInfo, 0);

	dstEpInfo.dstAddrMode = APS_SHORT_DSTADDR_WITHEP;
	dstEpInfo.dstEp = SAMPLE_SWITCH_ENDPOINT;
	dstEpInfo.dstAddr.shortAddr = 0xfffc;
	dstEpInfo.profileId = HA_PROFILE_ID;
	dstEpInfo.txOptions = 0;//APS_TX_OPT_ACK_TX;
	dstEpInfo.radius = 0;

	zcl_onOff_toggleCmd(SAMPLE_SWITCH_ENDPOINT, &dstEpInfo, FALSE);
}


int zb_ble_ci_cmd_handler(u16 cmd_type , u8 * payload)
{
    if(cmd_type == ZB_BLE_CI_CMD_CFG_SET_CHANNEL)
    {
        zb_ble_ci_channel = payload[0];
    }else if(cmd_type == ZB_BLE_CI_CMD_CFG_SET_PANID)
    {
        zb_ble_ci_panid = payload[0];
        zb_ble_ci_panid <<= 8;
        zb_ble_ci_panid |= payload[1];
    }else if(cmd_type == ZB_BLE_CI_CMD_CFG_SET_SHORT_ADDR)
    {
        zb_ble_ci_short_addr = payload[0];
        zb_ble_ci_short_addr <<= 8;
        zb_ble_ci_short_addr |= payload[1];
    }else if(cmd_type == ZB_BLE_CI_CMD_CFG_SET_EXT_PANID)
    {
        memcpy(zb_ble_ci_extPanId,payload,8);
    }else if(cmd_type == ZB_BLE_CI_CMD_CFG_SET_NWK_KEY)
    {
        memcpy(zb_ble_ci_nwkKey,payload,16);
    }else if(cmd_type == ZB_BLE_CI_CMD_CFG_START_NWK)
    {
#if 0
        if(zb_ble_ci_short_addr == MAC_SHORT_ADDR_BROADCAST)
        {
            zb_joinAFixedNetwork(zb_ble_ci_channel,  zb_ble_ci_panid, ChipId, zb_ble_ci_extPanId, zb_ble_ci_nwkKey);
        }
        else
        {
            zb_joinAFixedNetwork(zb_ble_ci_channel,  zb_ble_ci_panid, zb_ble_ci_short_addr, zb_ble_ci_extPanId, zb_ble_ci_nwkKey);
        }
	    bdb_init((af_simple_descriptor_t *)&sampleLight_simpleDesc, &g_bdbCommissionSetting, &g_zbDemoBdbCb, 1);
        memcpy(ss_ib.trust_center_address, g_invalid_addr, EXT_ADDR_LEN);
#endif

    }else if(cmd_type == ZB_BLE_CI_CMD_LIGHT_TOGGLE_BROADCAST)
    {
        tl_zbTaskPost(onoff_light_broadcast, NULL);
    }else if(cmd_type == ZB_BLE_CI_CMD_LIGHT_TOGGLE_UNICAST)
    {
        zb_ble_ci_cmd_light_toggle_dest_addr = payload[0];
        zb_ble_ci_cmd_light_toggle_dest_addr <<= 8;
        zb_ble_ci_cmd_light_toggle_dest_addr |= payload[1];
        tl_zbTaskPost(onoff_light_unicast, NULL);
    }else if(cmd_type == ZB_BLE_CI_CMD_LIGHT_TOGGLE_UNICAST_BY_SEQ)
    {
        unsigned char seqNum = payload[0];
        int i;

        for(i = 0;i < 16;i++)
        {
            if((device_list[i].isActive)&&(device_list[i].seqNO == seqNum))
            {
                //zb_ble_ci_cmd_light_toggle_dest_addr = device_list[i].nwk_addr[0];
                //zb_ble_ci_cmd_light_toggle_dest_addr <<= 8;
                //zb_ble_ci_cmd_light_toggle_dest_addr |= device_list[i].nwk_addr[1];
                zb_ble_ci_cmd_light_toggle_dest_addr = device_list[i].nwk_addr;
                tl_zbTaskPost(onoff_light_unicast, NULL);
                break;
            }
        }
    }
}

#endif  /* __PROJECT_TL_CONCURRENT_GW__ */
