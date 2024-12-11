/********************************************************************************************************
 * @file    zcl_onOffCb.c
 *
 * @brief   This is the source file for zcl_onOffCb
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
#include "samplePlug.h"
#include "samplePlugCtrl.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */
#define ZCL_ONOFF_TIMER_INTERVAL		100    //the timer interval to change the offWaitTime/onTime attribute of the ONOFF cluster

/**********************************************************************
 * LOCAL VARIABLES
 */
static ev_timer_event_t *onWithTimedOffTimerEvt = NULL;
static ev_timer_event_t *onWithTimedOffTimerEvt_2 = NULL;

/**********************************************************************
 * FUNCTIONS
 */

/*********************************************************************
 * @fn      sampleLight_onOffInit
 *
 * @brief
 *
 * @param   None
 *
 * @return  None
 */
void sampleLight_onOffInit(void)
{
	zcl_onOffAttr_t *pOnOff = zcl_onoffAttrGet(SAMPLE_LIGHT_ENDPOINT);
	if(pOnOff){
		sampleLight_onOffUpdate(SAMPLE_LIGHT_ENDPOINT, pOnOff->onOff);
	}

#if PLUG_EP_2_SUPPORT
	zcl_onOffAttr_t *pOnOff_2 = zcl_onoffAttrGet(SAMPLE_LIGHT_ENDPOINT_2);
	if(pOnOff_2){
		sampleLight_onOffUpdate(SAMPLE_LIGHT_ENDPOINT_2, pOnOff_2->onOff);
	}
#endif
}

/*********************************************************************
 * @fn      sampleLight_onOffUpdate
 *
 * @brief
 *
 * @param   ZCL_CMD_ONOFF_ON / ZCL_ONOFF_STATUS_OFF / ZCL_CMD_ONOFF_TOGGLE
 *
 * @return  None
 */
void sampleLight_onOffUpdate(u8 ep, u8 cmd)
{
	bool onOff = ZCL_ONOFF_STATUS_ON;

	zcl_onOffAttr_t *pCurOnOffAttr = zcl_onoffAttrGet(ep);
	if(!pCurOnOffAttr){
		return;
	}

	if(cmd == ZCL_CMD_ONOFF_ON){
		onOff = ZCL_ONOFF_STATUS_ON;
	}else if(cmd == ZCL_CMD_ONOFF_OFF){
		onOff = ZCL_ONOFF_STATUS_OFF;
	}else if(cmd == ZCL_CMD_ONOFF_TOGGLE){
		onOff = (pCurOnOffAttr->onOff == ZCL_ONOFF_STATUS_ON) ? ZCL_ONOFF_STATUS_OFF
															  : ZCL_ONOFF_STATUS_ON;
	}else{
		return;
	}

	//update attributes
	if(onOff == ZCL_ONOFF_STATUS_ON){
		pCurOnOffAttr->globalSceneControl = TRUE;
		pCurOnOffAttr->onOff = ZCL_ONOFF_STATUS_ON;
		if(pCurOnOffAttr->onTime == 0){
			pCurOnOffAttr->offWaitTime = 0;
		}
	}else{
		pCurOnOffAttr->onOff = ZCL_ONOFF_STATUS_OFF;
		pCurOnOffAttr->onTime = 0;
	}

#ifdef ZCL_SCENE
	zcl_sceneAttr_t *pScene = zcl_sceneAttrGet(ep);
	if(pScene){
		pScene->sceneValid = 0;
	}
#endif

	light_refresh(ep);
}

/*********************************************************************
 * @fn      sampleLight_OnWithTimedOffTimerCb
 *
 * @brief   timer event to process the ON_WITH_TIMED_OFF command
 *
 * @param   arg
 *
 * @return  0: timer continue on; -1: timer will be canceled
 */
static s32 sampleLight_OnWithTimedOffTimerCb(void *arg)
{
	u8 ep = (u8)((u32)arg);

	zcl_onOffAttr_t *pOnOff = zcl_onoffAttrGet(ep);
	if(!pOnOff){
		return 0;
	}

	if((pOnOff->onOff == ZCL_ONOFF_STATUS_ON) && pOnOff->onTime){
		pOnOff->onTime--;
		if(pOnOff->onTime <= 0){
			pOnOff->offWaitTime = 0;
			sampleLight_onOffUpdate(ep, ZCL_CMD_ONOFF_OFF);
		}
	}

	if((pOnOff->onOff == ZCL_ONOFF_STATUS_OFF) && pOnOff->offWaitTime){
		pOnOff->offWaitTime--;
		if(pOnOff->offWaitTime <= 0){
			if(ep == SAMPLE_LIGHT_ENDPOINT){
				onWithTimedOffTimerEvt = NULL;
			}else{
				onWithTimedOffTimerEvt_2 = NULL;
			}
			return -1;
		}
	}

	if(pOnOff->onTime || pOnOff->offWaitTime){
		return 0;
	}else{
		if(ep == SAMPLE_LIGHT_ENDPOINT){
			onWithTimedOffTimerEvt = NULL;
		}else{
			onWithTimedOffTimerEvt_2 = NULL;
		}
		return -1;
	}
}

/*********************************************************************
 * @fn      sampleLight_OnWithTimedOffTimerStart
 *
 * @brief   start the OnWithTimedOff timer
 *
 * @param
 *
 * @return
 */
static void sampleLight_OnWithTimedOffTimerStart(u8 ep)
{
	if(ep == SAMPLE_LIGHT_ENDPOINT){
		if(onWithTimedOffTimerEvt){
			TL_ZB_TIMER_CANCEL(&onWithTimedOffTimerEvt);
		}
		onWithTimedOffTimerEvt = TL_ZB_TIMER_SCHEDULE(sampleLight_OnWithTimedOffTimerCb, (void *)((u32)ep), ZCL_ONOFF_TIMER_INTERVAL);
	}else{
		if(onWithTimedOffTimerEvt_2){
			TL_ZB_TIMER_CANCEL(&onWithTimedOffTimerEvt_2);
		}
		onWithTimedOffTimerEvt_2 = TL_ZB_TIMER_SCHEDULE(sampleLight_OnWithTimedOffTimerCb, (void *)((u32)ep), ZCL_ONOFF_TIMER_INTERVAL);
	}
}

/*********************************************************************
 * @fn      sampleLight_onoff_onWithTimedOffProcess
 *
 * @brief
 *
 * @param   cmd
 *
 * @return  None
 */
static void sampleLight_onoff_onWithTimedOffProcess(u8 ep, zcl_onoff_onWithTimeOffCmd_t *cmd)
{
	zcl_onOffAttr_t *pOnOff = zcl_onoffAttrGet(ep);
	if(!pOnOff){
		return;
	}

	if(cmd->onOffCtrl.bits.acceptOnlyWhenOn && (pOnOff->onOff == ZCL_ONOFF_STATUS_OFF)){
		return;
	}

	if(pOnOff->offWaitTime && (pOnOff->onOff == ZCL_ONOFF_STATUS_OFF)){
		pOnOff->offWaitTime = min2(pOnOff->offWaitTime, cmd->offWaitTime);
	}else{
		pOnOff->onTime = max2(pOnOff->onTime, cmd->onTime);
		pOnOff->offWaitTime = cmd->offWaitTime;
		sampleLight_onOffUpdate(ep, ZCL_CMD_ONOFF_ON);
	}

	if((pOnOff->onTime < 0xFFFF) && (pOnOff->offWaitTime < 0xFFFF)){
		if(pOnOff->onTime || pOnOff->offWaitTime){
			sampleLight_OnWithTimedOffTimerStart(ep);
		}
	}
}

/*********************************************************************
 * @fn      sampleLight_onoff_offWithEffectProcess
 *
 * @brief
 *
 * @param   cmd
 *
 * @return  None
 */
static void sampleLight_onoff_offWithEffectProcess(u8 ep, zcl_onoff_offWithEffectCmd_t *cmd)
{
	zcl_onOffAttr_t *pOnOff = zcl_onoffAttrGet(ep);
	if(!pOnOff){
		return;
	}

	pOnOff->globalSceneControl = FALSE;

	//TODO:

	sampleLight_onOffUpdate(ep, ZCL_CMD_ONOFF_OFF);
}

/*********************************************************************
 * @fn      sampleLight_onoff_onWithRecallGlobalSceneProcess
 *
 * @brief
 *
 * @param   cmd
 *
 * @return  None
 */
static void sampleLight_onoff_onWithRecallGlobalSceneProcess(u8 ep)
{
	zcl_onOffAttr_t *pOnOff = zcl_onoffAttrGet(ep);
	if(!pOnOff){
		return;
	}

	pOnOff->globalSceneControl = TRUE;

	//TODO:
}

/*********************************************************************
 * @fn      sampleLight_onOffCb
 *
 * @brief   Handler for ZCL ONOFF command. This function will set ONOFF attribute first.
 *
 * @param	pAddrInfo
 * @param   cmdId - onoff cluster command id
 * @param	cmdPayload
 *
 * @return  status_t
 */
status_t sampleLight_onOffCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	if(pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT ||
	   pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT_2){
		switch(cmdId){
			case ZCL_CMD_ONOFF_ON:
			case ZCL_CMD_ONOFF_OFF:
			case ZCL_CMD_ONOFF_TOGGLE:
				sampleLight_onOffUpdate(pAddrInfo->dstEp, cmdId);
				break;
			case ZCL_CMD_OFF_WITH_EFFECT:
				sampleLight_onoff_offWithEffectProcess(pAddrInfo->dstEp, (zcl_onoff_offWithEffectCmd_t *)cmdPayload);
				break;
			case ZCL_CMD_ON_WITH_RECALL_GLOBAL_SCENE:
				sampleLight_onoff_onWithRecallGlobalSceneProcess(pAddrInfo->dstEp);
				break;
			case ZCL_CMD_ON_WITH_TIMED_OFF:
				sampleLight_onoff_onWithTimedOffProcess(pAddrInfo->dstEp, (zcl_onoff_onWithTimeOffCmd_t *)cmdPayload);
				break;
			default:
				break;
		}
	}

	return ZCL_STA_SUCCESS;
}

#endif  /* __PROJECT_TL_PLUG__ */
