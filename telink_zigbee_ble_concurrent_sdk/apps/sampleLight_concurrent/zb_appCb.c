/********************************************************************************************************
 * @file    zb_appCb.c
 *
 * @brief   This is the source file for zb_appCb
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/
#if (__PROJECT_TL_LIGHT__)

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zb_api.h"
#include "zcl_include.h"
#include "bdb.h"
#include "ota.h"
#include "sampleLight.h"
#include "sampleLightCtrl.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */
#define DEBUG_HEART		0

/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * LOCAL FUNCTIONS
 */
void zbdemo_bdbInitCb(u8 status, u8 joinedNetwork);
void zbdemo_bdbCommissioningCb(u8 status, void *arg);
void zbdemo_bdbIdentifyCb(u8 endpoint, u16 srcAddr, u16 identifyTime);


/**********************************************************************
 * GLOBAL VARIABLES
 */
bdb_appCb_t g_zbDemoBdbCb = {zbdemo_bdbInitCb, zbdemo_bdbCommissioningCb, zbdemo_bdbIdentifyCb, NULL};

#ifdef ZCL_OTA
ota_callBack_t sampleLight_otaCb =
{
	sampleLight_otaProcessMsgHandler,
};
#endif

/**********************************************************************
 * LOCAL VARIABLES
 */
#if DUAL_MODE_WITH_MATTER
typedef struct{
	ev_timer_event_t *timeoutEvt;
	u8 timeoutCnt;
}matterCommission_t;

matterCommission_t matterCommission;
#endif

u32 heartInterval = 0;

#if DEBUG_HEART
ev_timer_event_t *heartTimerEvt = NULL;
#endif

/**********************************************************************
 * FUNCTIONS
 */
#if DUAL_MODE_WITH_MATTER
#include "zigbee_ble_switch.h"

static s32 matterCommissionTimeoutCb(void *arg){
	if(matterCommission.timeoutCnt){
		matterCommission.timeoutCnt--;
	}

	printf("matter CMT = %d min\n", matterCommission.timeoutCnt);

	if(matterCommission.timeoutCnt == 0){
		printf("ble adv stopped\n");
		ble_task_stop();

		nv_flashSingleItemRemove(NV_MODULE_APP, NV_ITEM_APP_COMM_TIMEOUT, 1);

		matterCommission.timeoutEvt = NULL;
		return -1;
	}

	return 0;
}

static void matterCommissionWindowInit(void){

	if(nv_flashReadNew(1, NV_MODULE_APP, NV_ITEM_APP_COMM_TIMEOUT, 1, &matterCommission.timeoutCnt) != NV_SUCC){
		matterCommission.timeoutCnt = 15;
	}else{
		//if jump from matter, use the remaining timeout count.

		u8 flag = 0xff;
		flash_read(JUMP2_MATTER_TAG_ADDR, 1, &flag);

		if(flag == JUMP2_ZIGBEE_TAG_FLAG ||
		   flag == JUMP2_BLE_MAC_TAG_FLAG){
			//if jump from matter
			//use the remaining timeout count
			flag = JUMP2_CLEAR_TAG_FLAG;
			flash_write(JUMP2_MATTER_TAG_ADDR, 1, &flag);
		}else{
			nv_flashSingleItemRemove(NV_MODULE_APP, NV_ITEM_APP_COMM_TIMEOUT, 1);
			matterCommission.timeoutCnt = 15;
		}
	}

	printf("matter CMT[init] = %d min\n", matterCommission.timeoutCnt);

	if(matterCommission.timeoutEvt){
		TL_ZB_TIMER_CANCEL(&matterCommission.timeoutEvt);
	}
	matterCommission.timeoutEvt = TL_ZB_TIMER_SCHEDULE(matterCommissionTimeoutCb, NULL, 60 * 1000);
}

void matterCommissionTimeoutStore(void){
	nv_flashWriteNew(1, NV_MODULE_APP, NV_ITEM_APP_COMM_TIMEOUT, 1, &matterCommission.timeoutCnt);
}
#endif

#if DEBUG_HEART
static s32 heartTimerCb(void *arg){
	if(heartInterval == 0){
		heartTimerEvt = NULL;
		return -1;
	}

	gpio_toggle(LED_POWER);

	return heartInterval;
}
#endif

s32 sampleLight_bdbNetworkSteerStart(void *arg){
	bdb_networkSteerStart();

	return -1;
}

#if FIND_AND_BIND_SUPPORT
s32 sampleLight_bdbFindAndBindStart(void *arg){
	bdb_findAndBindStart(BDB_COMMISSIONING_ROLE_TARGET);

	return -1;
}
#endif

/*********************************************************************
 * @fn      zbdemo_bdbInitCb
 *
 * @brief   application callback for bdb initiation
 *
 * @param   status - the status of bdb init BDB_INIT_STATUS_SUCCESS or BDB_INIT_STATUS_FAILURE
 *
 * @param   joinedNetwork  - 1: node is on a network, 0: node isn't on a network
 *
 * @return  None
 */
void zbdemo_bdbInitCb(u8 status, u8 joinedNetwork){
	printf("bdbInitCb: sta = %x\n", status);

	if(status == BDB_INIT_STATUS_SUCCESS){
		if(joinedNetwork){
			heartInterval = 1000;

#ifdef ZCL_OTA
			ota_queryStart(OTA_PERIODIC_QUERY_INTERVAL);
#endif
		}else{
			heartInterval = 500;

			u16 jitter = 0;
			do{
				jitter = zb_random() % 0x0fff;
			}while(jitter == 0);
			TL_ZB_TIMER_SCHEDULE(sampleLight_bdbNetworkSteerStart, NULL, jitter);
		}

#if DUAL_MODE_WITH_MATTER
		matterCommissionWindowInit();
#endif
	}else{
		heartInterval = 200;
	}

#if DEBUG_HEART
	if(heartTimerEvt){
		TL_ZB_TIMER_CANCEL(&heartTimerEvt);
	}
	heartTimerEvt = TL_ZB_TIMER_SCHEDULE(heartTimerCb, NULL, heartInterval);
#endif
}

/*********************************************************************
 * @fn      zbdemo_bdbCommissioningCb
 *
 * @brief   application callback for bdb commissioning
 *
 * @param   status - the status of bdb commissioning
 *
 * @param   arg
 *
 * @return  None
 */
void zbdemo_bdbCommissioningCb(u8 status, void *arg){
	printf("bdbCommCb: sta = %x\n", status);

	switch(status){
		case BDB_COMMISSION_STA_SUCCESS:
			heartInterval = 1000;

			printf("chn = %d, panId = %x\n", g_zbMacPib.phyChannelCur, g_zbNIB.panId);

#if DUAL_MODE_WITH_MATTER
			//change startUp attribute to ZCL_START_UP_ONOFF_SET_ONOFF_TO_PREVIOUS
			g_zcl_onOffAttrs.startUpOnOff = ZCL_START_UP_ONOFF_SET_ONOFF_TO_PREVIOUS;
#endif

			light_blink_start(2, 200, 200);

#ifdef ZCL_OTA
	    	ota_queryStart(OTA_PERIODIC_QUERY_INTERVAL);
#endif

#if FIND_AND_BIND_SUPPORT
			if(!gLightCtx.bdbFindBindFlg){
				gLightCtx.bdbFindBindFlg = TRUE;
				TL_ZB_TIMER_SCHEDULE(sampleLight_bdbFindAndBindStart, NULL, 1000);
			}
#endif
			break;
		case BDB_COMMISSION_STA_IN_PROGRESS:
			break;
		case BDB_COMMISSION_STA_NOT_AA_CAPABLE:
			break;
		case BDB_COMMISSION_STA_NO_NETWORK:
		case BDB_COMMISSION_STA_TCLK_EX_FAILURE:
		case BDB_COMMISSION_STA_TARGET_FAILURE:
			{
				u16 jitter = 0;
				do{
					jitter = zb_random() % 0x2710;
				}while(jitter < 5000);
				TL_ZB_TIMER_SCHEDULE(sampleLight_bdbNetworkSteerStart, NULL, jitter);
			}
			break;
		case BDB_COMMISSION_STA_FORMATION_FAILURE:
			break;
		case BDB_COMMISSION_STA_NO_IDENTIFY_QUERY_RESPONSE:
			break;
		case BDB_COMMISSION_STA_BINDING_TABLE_FULL:
			break;
		case BDB_COMMISSION_STA_NO_SCAN_RESPONSE:
			break;
		case BDB_COMMISSION_STA_NOT_PERMITTED:
			break;
		case BDB_COMMISSION_STA_REJOIN_FAILURE:
			zb_rejoinReq(zb_apsChannelMaskGet(), g_bdbAttrs.scanDuration);
			break;
		case BDB_COMMISSION_STA_FORMATION_DONE:
#ifndef ZBHCI_EN
			tl_zbMacChannelSet(DEFAULT_CHANNEL);  //set default channel
#endif
			break;
		default:
			break;
	}
}



void zbdemo_bdbIdentifyCb(u8 endpoint, u16 srcAddr, u16 identifyTime){
#if FIND_AND_BIND_SUPPORT
	extern void sampleLight_zclIdentifyCmdHandler(u8 endpoint, u16 srcAddr, u16 identifyTime);
	sampleLight_zclIdentifyCmdHandler(endpoint, srcAddr, identifyTime);
#endif
}



#ifdef ZCL_OTA
void sampleLight_otaProcessMsgHandler(u8 evt, u8 status)
{
	if(evt == OTA_EVT_START){
		if(status == ZCL_STA_SUCCESS){

		}else{

		}
	}else if(evt == OTA_EVT_COMPLETE){
		if(status == ZCL_STA_SUCCESS){
			ota_mcuReboot();
		}else{
			ota_queryStart(OTA_PERIODIC_QUERY_INTERVAL);
		}
	}
}
#endif


s32 sampleLight_recoveryStart(void *arg)
{
	SYSTEM_RESET();
	return -1;
}

/*********************************************************************
 * @fn      sampleLight_leaveCnfHandler
 *
 * @brief   Handler for ZDO Leave Confirm message.
 *
 * @param   pRsp - parameter of leave confirm
 *
 * @return  None
 */
void sampleLight_leaveCnfHandler(nlme_leave_cnf_t *pLeaveCnf)
{
    if(pLeaveCnf->status == SUCCESS){
#if DUAL_MODE_WITH_MATTER
    	printf("erase nvs of matter...\n");

    	u8 sectNum = MATTER_NVS_SIZE / FLASH_SECTOR_SIZE;
    	u32 eraseAddr = MATTER_NVS_ADDR;

    	for(s32 i = 0; i < sectNum; i++){
    		flash_erase(eraseAddr);
    		eraseAddr += FLASH_SECTOR_SIZE;
    	}
    	flash_erase(JUMP2_MATTER_TAG_ADDR);
#endif

    	light_blink_start(3, 200, 200);

    	//waiting blink over
        TL_ZB_TIMER_SCHEDULE(sampleLight_recoveryStart, NULL, 2 * 1000);
    }
}

/*********************************************************************
 * @fn      sampleLight_leaveIndHandler
 *
 * @brief   Handler for ZDO leave indication message.
 *
 * @param   pInd - parameter of leave indication
 *
 * @return  None
 */
void sampleLight_leaveIndHandler(nlme_leave_ind_t *pLeaveInd)
{

}

bool sampleLight_nwkUpdateIndicateHandler(nwkCmd_nwkUpdate_t *pNwkUpdate){
	return FAILURE;
}

#endif  /* __PROJECT_TL_DIMMABLE_LIGHT__ */
