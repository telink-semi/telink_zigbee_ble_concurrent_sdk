/********************************************************************************************************
 * @file    zcl_sceneCb.c
 *
 * @brief   This is the source file for zcl_sceneCb
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
#include "private.h"

/*********************************************************************
 * @fn      sampleLight_sceneRecallReqHandler
 *
 * @brief   Handler for ZCL scene recall command. This function will recall scene.
 *
 * @param	pApsdeInd
 * @param	pScene
 *
 * @return  None
 */
static void sampleLight_sceneRecallReqHandler(zclIncomingAddrInfo_t *pAddrInfo, zcl_sceneEntry_t *pScene)
{
	u8 extLen = 0;

#ifdef ZCL_ON_OFF
	extLen += 3;//id + length
	u8 onOff = pScene->extField[extLen];
	extLen += sizeof(u8);//onOff
#endif

#ifdef ZCL_LEVEL_CTRL
	extLen += 3;//id + length
	u8 level = pScene->extField[extLen];
	extLen += sizeof(u8);//level
#endif

#ifdef ZCL_LIGHT_COLOR_CONTROL
	extLen += 3;//id + length
	u16 currentX = BUILD_U16(pScene->extField[extLen], pScene->extField[extLen + 1]);
	extLen += sizeof(u16);
	u16 currentY = BUILD_U16(pScene->extField[extLen], pScene->extField[extLen + 1]);
	extLen += sizeof(u16);
	u16 enhHue = BUILD_U16(pScene->extField[extLen], pScene->extField[extLen + 1]);
	extLen += sizeof(u16);
	u8 saturation = pScene->extField[extLen];
	extLen += sizeof(u8);
	u8 colorLoopActive = pScene->extField[extLen];
	extLen += sizeof(u8);
	u8 colorLoopDir = pScene->extField[extLen];
	extLen += sizeof(u8);
	u16 colorLoopTime = BUILD_U16(pScene->extField[extLen], pScene->extField[extLen + 1]);
	extLen += sizeof(u16);
	u16 colorTemperature = BUILD_U16(pScene->extField[extLen], pScene->extField[extLen + 1]);
	extLen += sizeof(u16);

	u8 mode = ZCL_COLOR_MODE_CURRENT_X_Y;
	if((currentX == 0) && (currentY == 0)){
		if(enhHue || saturation){
			mode = ZCL_COLOR_MODE_CURRENT_HUE_SATURATION;
		}else if(colorTemperature){
			mode = ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS;
		}
	}
#endif

#ifdef ZCL_ON_OFF
	sampleLight_onOffCb(pAddrInfo, onOff, NULL);
#endif
#ifdef ZCL_LEVEL_CTRL
	moveToLvl_t moveToLevel;
	moveToLevel.level = level;
	moveToLevel.transitionTime = pScene->transTime;
	moveToLevel.optPresent = 0;

	sampleLight_levelCb(pAddrInfo, ZCL_CMD_LEVEL_MOVE_TO_LEVEL, &moveToLevel);
#endif
#ifdef ZCL_LIGHT_COLOR_CONTROL
	if(mode == ZCL_COLOR_MODE_CURRENT_HUE_SATURATION){
		zcl_colorCtrlMoveToHueAndSaturationCmd_t move2HueAndSat;
		move2HueAndSat.hue = (u8)(enhHue % 256);
		move2HueAndSat.saturation = saturation;
		move2HueAndSat.transitionTime = pScene->transTime;
		move2HueAndSat.optPresent = 0;
		sampleLight_colorCtrlCb(pAddrInfo, ZCL_CMD_LIGHT_COLOR_CONTROL_MOVE_TO_HUE_AND_SATURATION, &move2HueAndSat);
	}else if(mode == ZCL_COLOR_MODE_CURRENT_X_Y){
		zcl_colorCtrlMoveToColorCmd_t move2Color;
		move2Color.colorX = currentX;
		move2Color.colorY = currentY;
		move2Color.transitionTime = pScene->transTime;
		move2Color.optPresent = 0;
		sampleLight_colorCtrlCb(pAddrInfo, ZCL_CMD_LIGHT_COLOR_CONTROL_MOVE_TO_COLOR, &move2Color);
	}else if(mode == ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS){
		zcl_colorCtrlMoveToColorTemperatureCmd_t move2CT;
		move2CT.colorTemperature = colorTemperature;
		move2CT.transitionTime = pScene->transTime;
		move2CT.optPresent = 0;
		sampleLight_colorCtrlCb(pAddrInfo, ZCL_CMD_LIGHT_COLOR_CONTROL_MOVE_TO_COLOR_TEMPERATURE, &move2CT);
	}
#endif
}

/*********************************************************************
 * @fn      sampleLight_sceneStoreReqHandler
 *
 * @brief   Handler for ZCL scene store command. This function will set scene attribute first.
 *
 * @param   pApsdeInd
 * @param   pScene
 *
 * @return  None
 */
static void sampleLight_sceneStoreReqHandler(u8 ep, zcl_sceneEntry_t *pScene)
{
	/* receive Store Scene Request command, get the latest Scene info to save */
	u8 extLen = 0;

#ifdef ZCL_ON_OFF
	zcl_onOffAttr_t *pOnOff = zcl_onoffAttrGet(ep);
	if(pOnOff){
		pScene->extField[extLen++] = LO_UINT16(ZCL_CLUSTER_GEN_ON_OFF);
		pScene->extField[extLen++] = HI_UINT16(ZCL_CLUSTER_GEN_ON_OFF);
		pScene->extField[extLen++] = 1;
		pScene->extField[extLen++] = pOnOff->onOff;
	}
#endif

#ifdef ZCL_LEVEL_CTRL
	zcl_levelAttr_t *pLevel = zcl_levelAttrGet(ep);
	if(pLevel){
		pScene->extField[extLen++] = LO_UINT16(ZCL_CLUSTER_GEN_LEVEL_CONTROL);
		pScene->extField[extLen++] = HI_UINT16(ZCL_CLUSTER_GEN_LEVEL_CONTROL);
		pScene->extField[extLen++] = 1;
		pScene->extField[extLen++] = pLevel->curLevel;
	}
#endif

#ifdef ZCL_LIGHT_COLOR_CONTROL
	zcl_lightColorCtrlAttr_t *pColor = zcl_colorAttrGet(ep);
	if(pColor){
		pScene->extField[extLen++] = LO_UINT16(ZCL_CLUSTER_LIGHTING_COLOR_CONTROL);
		pScene->extField[extLen++] = HI_UINT16(ZCL_CLUSTER_LIGHTING_COLOR_CONTROL);
		pScene->extField[extLen++] = 13;

		//currentX and currentY
		if(pColor->enhancedColorMode == ZCL_COLOR_MODE_CURRENT_X_Y){
			pScene->extField[extLen++] = LO_UINT16(pColor->currentX);
			pScene->extField[extLen++] = HI_UINT16(pColor->currentX);
			pScene->extField[extLen++] = LO_UINT16(pColor->currentY);
			pScene->extField[extLen++] = HI_UINT16(pColor->currentY);
		}else{
			pScene->extField[extLen++] = 0;
			pScene->extField[extLen++] = 0;
			pScene->extField[extLen++] = 0;
			pScene->extField[extLen++] = 0;
		}
		//enhancedCurrentHue and currentSaturation
		if(pColor->enhancedColorMode == ZCL_COLOR_MODE_CURRENT_HUE_SATURATION){
			pScene->extField[extLen++] = LO_UINT16(pColor->currentHue);
			pScene->extField[extLen++] = HI_UINT16(pColor->currentHue);
			pScene->extField[extLen++] = pColor->currentSaturation;
		}else{
			pScene->extField[extLen++] = 0;
			pScene->extField[extLen++] = 0;
			pScene->extField[extLen++] = 0;
		}
		//colorLoopActive
		pScene->extField[extLen++] = 0;
		//colorLoopDirection
		pScene->extField[extLen++] = 0;
		//colorLoopTime
		pScene->extField[extLen++] = 0;
		pScene->extField[extLen++] = 0;
		//colorTemperatureMireds
		if(pColor->enhancedColorMode == ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS){
			pScene->extField[extLen++] = LO_UINT16(pColor->colorTemperatureMireds);
			pScene->extField[extLen++] = HI_UINT16(pColor->colorTemperatureMireds);
		}else{
			pScene->extField[extLen++] = 0;
			pScene->extField[extLen++] = 0;
		}
	}
#endif

	pScene->extFieldLen = extLen;
}

/*********************************************************************
 * @fn      sampleLight_sceneCb
 *
 * @brief   Handler for ZCL Scene command.
 *
 * @param   pApsdeInd
 *
 * @return  None
 */
status_t sampleLight_sceneCb(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload)
{
	status_t status = ZCL_STA_SUCCESS;

	if(pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT ||
	   pAddrInfo->dstEp == SAMPLE_LIGHT_ENDPOINT_2){
		if(pAddrInfo->dirCluster == ZCL_FRAME_CLIENT_SERVER_DIR){
			switch(cmdId){
				case ZCL_CMD_SCENE_STORE_SCENE:
					sampleLight_sceneStoreReqHandler(pAddrInfo->dstEp, (zcl_sceneEntry_t *)cmdPayload);
					break;
				case ZCL_CMD_SCENE_RECALL_SCENE:
					sampleLight_sceneRecallReqHandler(pAddrInfo, (zcl_sceneEntry_t *)cmdPayload);
					break;
				default:
#if PRIVATE_FEAT
					status = private_sceneReqHandler(pAddrInfo, cmdId, cmdPayload);
#else
					status = ZCL_STA_UNSUP_MANU_CLUSTER_COMMAND;
#endif
					break;
			}
		}
	}

	return status;
}

#endif  /* __PROJECT_TL_PLUG__ */
