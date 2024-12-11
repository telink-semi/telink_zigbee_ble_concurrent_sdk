/********************************************************************************************************
 * @file    zcl_samplePlugCb.c
 *
 * @brief   This is the source file for zcl_samplePlugCb
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
#if (__PROJECT_TL_PLUG__)

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zb_api.h"
#include "zcl_include.h"
#include "ota.h"
#include "samplePlug.h"
#include "samplePlugCtrl.h"
#include "private.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */



/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * LOCAL FUNCTIONS
 */
#ifdef ZCL_READ
static void sampleLight_zclReadRspCmd(u16 clusterId, zclReadRspCmd_t *pReadRspCmd);
#endif
#ifdef ZCL_WRITE
static void sampleLight_zclWriteReqCmd(u16 clusterId, zclWriteCmd_t *pWriteReqCmd);
static void sampleLight_zclWriteRspCmd(zclWriteRspCmd_t *pWriteRspCmd);
#endif
#ifdef ZCL_REPORT
static void sampleLight_zclCfgReportCmd(zclCfgReportCmd_t *pCfgReportCmd);
static void sampleLight_zclCfgReportRspCmd(zclCfgReportRspCmd_t *pCfgReportRspCmd);
static void sampleLight_zclReportCmd(zclReportCmd_t *pReportCmd);
#endif
static void sampleLight_zclDfltRspCmd(zclDefaultRspCmd_t *pDftRspCmd);


/**********************************************************************
 * GLOBAL VARIABLES
 */


/**********************************************************************
 * LOCAL VARIABLES
 */
#ifdef ZCL_IDENTIFY
static ev_timer_event_t *identifyTimerEvt = NULL;
#if PLUG_EP_2_SUPPORT
static ev_timer_event_t *identifyTimerEvt_2 = NULL;
#endif
#endif

/**********************************************************************
 * FUNCTIONS
 */
void sampleLight_zclIdentifyCmdHandler(u8 ep, u16 srcAddr, u16 identifyTime);

/*********************************************************************
 * @fn      sampleLight_zclProcessIncomingMsg
 *
 * @brief   Process ZCL Foundation incoming message.
 *
 * @param   pInMsg - pointer to the received message
 *
 * @return  None
 */
void sampleLight_zclProcessIncomingMsg(zclIncoming_t *pInHdlrMsg)
{
//	printf("sampleLight_zclProcessIncomingMsg\n");

	switch(pInHdlrMsg->hdr.cmd)
	{
#ifdef ZCL_READ
		case ZCL_CMD_READ_RSP:
			sampleLight_zclReadRspCmd(pInHdlrMsg->msg->indInfo.cluster_id, pInHdlrMsg->attrCmd);
			break;
#endif
#ifdef ZCL_WRITE
		case ZCL_CMD_WRITE:
		case ZCL_CMD_WRITE_NO_RSP:
			sampleLight_zclWriteReqCmd(pInHdlrMsg->msg->indInfo.cluster_id, pInHdlrMsg->attrCmd);
			break;
		case ZCL_CMD_WRITE_RSP:
			sampleLight_zclWriteRspCmd(pInHdlrMsg->attrCmd);
			break;
#endif
#ifdef ZCL_REPORT
		case ZCL_CMD_CONFIG_REPORT:
			sampleLight_zclCfgReportCmd(pInHdlrMsg->attrCmd);
			break;
		case ZCL_CMD_CONFIG_REPORT_RSP:
			sampleLight_zclCfgReportRspCmd(pInHdlrMsg->attrCmd);
			break;
		case ZCL_CMD_REPORT:
			sampleLight_zclReportCmd(pInHdlrMsg->attrCmd);
			break;
#endif
		case ZCL_CMD_DEFAULT_RSP:
			sampleLight_zclDfltRspCmd(pInHdlrMsg->attrCmd);
			break;
		default:
			break;
	}
}

#ifdef ZCL_READ
/*********************************************************************
 * @fn      sampleLight_zclReadRspCmd
 *
 * @brief   Handler for ZCL Read Response command.
 *
 * @param
 *
 * @return  None
 */
static void sampleLight_zclReadRspCmd(u16 clusterId, zclReadRspCmd_t *pReadRspCmd)
{
    printf("rcv readRsp: cId = %x\n", clusterId);
}
#endif

#ifdef ZCL_WRITE
/*********************************************************************
 * @fn      sampleLight_zclWriteReqCmd
 *
 * @brief   Handler for ZCL Write Request command.
 *
 * @param
 *
 * @return  None
 */
static void sampleLight_zclWriteReqCmd(u16 clusterId, zclWriteCmd_t *pWriteReqCmd)
{
	u8 numAttr = pWriteReqCmd->numAttr;
	zclWriteRec_t *attr = pWriteReqCmd->attrList;

	if(clusterId == ZCL_CLUSTER_GEN_ON_OFF){
		for(u8 i = 0; i < numAttr; i++){
			if(attr[i].attrID == ZCL_ATTRID_START_UP_ONOFF){
				zcl_onOffAttr_save();
			}
		}
	}else if(clusterId == ZCL_CLUSTER_GEN_IDENTIFY){
		for(u8 i = 0; i < numAttr; i++){
			if(attr[i].attrID == ZCL_ATTRID_IDENTIFY_TIME){
				sampleLight_zclIdentifyCmdHandler(SAMPLE_LIGHT_ENDPOINT, 0xFFFE, g_zcl_identifyAttrs.identifyTime);
			}
		}
	}
}

/*********************************************************************
 * @fn      sampleLight_zclWriteRspCmd
 *
 * @brief   Handler for ZCL Write Response command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void sampleLight_zclWriteRspCmd(zclWriteRspCmd_t *pWriteRspCmd)
{
//    printf("sampleLight_zclWriteRspCmd\n");

}
#endif


/*********************************************************************
 * @fn      sampleLight_zclDfltRspCmd
 *
 * @brief   Handler for ZCL Default Response command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void sampleLight_zclDfltRspCmd(zclDefaultRspCmd_t *pDftRspCmd)
{
//  printf("sampleLight_zclDfltRspCmd\n");
#ifdef ZCL_OTA
	if( (pDftRspCmd->commandID == ZCL_CMD_OTA_UPGRADE_END_REQ) &&
		(pDftRspCmd->statusCode == ZCL_STA_ABORT) ){
		if(zcl_attr_imageUpgradeStatus == IMAGE_UPGRADE_STATUS_DOWNLOAD_COMPLETE){
			ota_upgradeAbort();
		}
	}
#endif
}

#ifdef ZCL_REPORT
/*********************************************************************
 * @fn      sampleLight_zclCfgReportCmd
 *
 * @brief   Handler for ZCL Configure Report command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void sampleLight_zclCfgReportCmd(zclCfgReportCmd_t *pCfgReportCmd)
{
//    printf("sampleLight_zclCfgReportCmd\n");

}

/*********************************************************************
 * @fn      sampleLight_zclCfgReportRspCmd
 *
 * @brief   Handler for ZCL Configure Report Response command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void sampleLight_zclCfgReportRspCmd(zclCfgReportRspCmd_t *pCfgReportRspCmd)
{
//    printf("sampleLight_zclCfgReportRspCmd\n");

}

/*********************************************************************
 * @fn      sampleLight_zclReportCmd
 *
 * @brief   Handler for ZCL Report command.
 *
 * @param   pInHdlrMsg - incoming message to process
 *
 * @return  None
 */
static void sampleLight_zclReportCmd(zclReportCmd_t *pReportCmd)
{
//    printf("sampleLight_zclReportCmd\n");

}
#endif

#ifdef ZCL_BASIC
/*********************************************************************
 * @fn      sampleLight_basicCb
 *
 * @brief   Handler for ZCL Basic Reset command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t sampleLight_basicCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	if(cmdId == ZCL_CMD_BASIC_RESET_FAC_DEFAULT){
		//Reset all the attributes of all its clusters to factory defaults
		//zcl_nv_attr_reset();
	}

	//return ZCL_STA_SUCCESS;
	return ZCL_STA_UNSUP_CLUSTER_COMMAND;
}
#endif

#ifdef ZCL_IDENTIFY
static s32 sampleLight_zclIdentifyTimerCb(void *arg)
{
	u8 ep = (u8)((u32)arg);

	if(ep == SAMPLE_LIGHT_ENDPOINT){
		if(g_zcl_identifyAttrs.identifyTime <= 0){
			light_blink_stop(ep);

			identifyTimerEvt = NULL;
			return -1;
		}
		g_zcl_identifyAttrs.identifyTime--;
	}
#if PLUG_EP_2_SUPPORT
	else{
		if(g_zcl_identifyAttrs_2.identifyTime <= 0){
			light_blink_stop(ep);

			identifyTimerEvt_2 = NULL;
			return -1;
		}
		g_zcl_identifyAttrs_2.identifyTime--;
	}
#endif

	return 0;
}

static void sampleLight_zclIdentifyTimerStop(u8 ep)
{
	if(ep == SAMPLE_LIGHT_ENDPOINT){
		if(identifyTimerEvt){
			TL_ZB_TIMER_CANCEL(&identifyTimerEvt);
		}
	}
#if PLUG_EP_2_SUPPORT
	else{
		if(identifyTimerEvt_2){
			TL_ZB_TIMER_CANCEL(&identifyTimerEvt_2);
		}
	}
#endif
}

/*********************************************************************
 * @fn      sampleLight_zclIdentifyCmdHandler
 *
 * @brief   Handler for ZCL Identify command. This function will set blink LED.
 *
 * @param   ep
 * @param   srcAddr
 * @param   identifyTime - identify time
 *
 * @return  None
 */
void sampleLight_zclIdentifyCmdHandler(u8 ep, u16 srcAddr, u16 identifyTime)
{
	if(ep == SAMPLE_LIGHT_ENDPOINT){
		g_zcl_identifyAttrs.identifyTime = identifyTime;

		if(identifyTime == 0){
			sampleLight_zclIdentifyTimerStop(ep);
			light_blink_stop(ep);
		}else{
			if(!identifyTimerEvt){
				light_blink_start(ep, identifyTime, 500, 500);
				identifyTimerEvt = TL_ZB_TIMER_SCHEDULE(sampleLight_zclIdentifyTimerCb, (void *)((u32)ep), 1000);
			}
		}
	}
#if PLUG_EP_2_SUPPORT
	else{
		g_zcl_identifyAttrs_2.identifyTime = identifyTime;

		if(identifyTime == 0){
			sampleLight_zclIdentifyTimerStop(ep);
			light_blink_stop(ep);
		}else{
			if(!identifyTimerEvt_2){
				light_blink_start(ep, identifyTime, 500, 500);
				identifyTimerEvt_2 = TL_ZB_TIMER_SCHEDULE(sampleLight_zclIdentifyTimerCb, (void *)((u32)ep), 1000);
			}
		}
	}
#endif
}

/*********************************************************************
 * @fn      sampleLight_zcltriggerCmdHandler
 *
 * @brief   Handler for ZCL trigger command.
 *
 * @param   ep
 * @param   pTriggerEffect
 *
 * @return  None
 */
static void sampleLight_zcltriggerCmdHandler(u8 ep, zcl_triggerEffect_t *pTriggerEffect)
{
	u8 effectId = pTriggerEffect->effectId;
//	u8 effectVariant = pTriggerEffect->effectVariant;

	switch(effectId){
		case IDENTIFY_EFFECT_BLINK:
			light_blink_start(ep, 1, 500, 500);
			break;
		case IDENTIFY_EFFECT_BREATHE:
			light_blink_start(ep, 15, 300, 700);
			break;
		case IDENTIFY_EFFECT_OKAY:
			light_blink_start(ep, 2, 250, 250);
			break;
		case IDENTIFY_EFFECT_CHANNEL_CHANGE:
			light_blink_start(ep, 1, 500, 7500);
			break;
		case IDENTIFY_EFFECT_FINISH_EFFECT:
			light_blink_start(ep, 1, 300, 700);
			break;
		case IDENTIFY_EFFECT_STOP_EFFECT:
			light_blink_stop(ep);
			break;
		default:
			break;
	}
}

/*********************************************************************
 * @fn      sampleLight_identifyCb
 *
 * @brief   Handler for ZCL Identify command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t sampleLight_identifyCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	if(pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT ||
	   pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT_2){
		if(pAddrInfo->dirCluster == ZCL_FRAME_CLIENT_SERVER_DIR){
			switch(cmdId){
				case ZCL_CMD_IDENTIFY:
					sampleLight_zclIdentifyCmdHandler(pAddrInfo->dstEp, pAddrInfo->srcAddr, ((zcl_identifyCmd_t *)cmdPayload)->identifyTime);
					break;
				case ZCL_CMD_TRIGGER_EFFECT:
					sampleLight_zcltriggerCmdHandler(pAddrInfo->dstEp, (zcl_triggerEffect_t *)cmdPayload);
					break;
				default:
					break;
			}
		}
	}

	return ZCL_STA_SUCCESS;
}
#endif

/*********************************************************************
 * @fn      sampleLight_groupCb
 *
 * @brief   Handler for ZCL Identify command.
 *
 * @param   pAddrInfo
 * @param   cmdId
 * @param   cmdPayload
 *
 * @return  status_t
 */
status_t sampleLight_groupCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	if(pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT ||
	   pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT_2){
		if(pAddrInfo->dirCluster == ZCL_FRAME_CLIENT_SERVER_DIR){
			switch(cmdId){
				case ZCL_CMD_GROUP_ADD_GROUP:
#if PRIVATE_FEAT
					private_zclAddGroupCmdHandler(pAddrInfo->dstEp, pAddrInfo->srcAddr, ((aps_add_group_req_t *)cmdPayload)->group_addr);
#endif
					break;
				default:
					break;
			}
		}
	}

	return ZCL_STA_SUCCESS;
}

#endif  /* __PROJECT_TL_PLUG__ */


