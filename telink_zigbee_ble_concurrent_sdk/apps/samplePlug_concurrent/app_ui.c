/********************************************************************************************************
 * @file    app_ui.c
 *
 * @brief   This is the source file for app_ui
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
#include "app_ui.h"

/**********************************************************************
 * LOCAL CONSTANTS
 */


/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * GLOBAL VARIABLES
 */
ui_ctx_t gUiCtx;

/**********************************************************************
 * LOCAL FUNCTIONS
 */
void led_on(u32 pin){
	drv_gpio_write(pin, LED_ON);
}

void led_off(u32 pin){
	drv_gpio_write(pin, LED_OFF);
}

void led_init(void){
	led_off(LED_POWER);
	led_off(LED_PERMIT);
}

void localPermitJoinState(void){
	static bool assocPermit = 0;
	if(assocPermit != zb_getMacAssocPermit()){
		assocPermit = zb_getMacAssocPermit();
		if(assocPermit){
			led_on(LED_PERMIT);
		}else{
			led_off(LED_PERMIT);
		}
	}
}

void buttonKeepPressed(u8 btNum){
	if(btNum == VK_SW1){
		gUiCtx.state = APP_FACTORY_NEW_DOING;
		zb_factoryReset();
	}else if(btNum == VK_SW2){

	}
}

void buttonShortPressed(u8 btNum){
	if(btNum == VK_SW1){
		//if(zb_isDeviceJoinedNwk()){
			zcl_onOffAttr_t *pCurOnOffAttr = zcl_onoffAttrGet(SAMPLE_LIGHT_ENDPOINT);
			if(pCurOnOffAttr){
				gLightCtx[0].sta = !pCurOnOffAttr->onOff;
				if(gLightCtx[0].sta){
					sampleLight_onOffUpdate(SAMPLE_LIGHT_ENDPOINT, ZCL_ONOFF_STATUS_ON);
				}else{
					sampleLight_onOffUpdate(SAMPLE_LIGHT_ENDPOINT, ZCL_ONOFF_STATUS_OFF);
				}
			}
#if PLUG_EP_2_SUPPORT
			zcl_onOffAttr_t *pCurOnOffAttr_2 = zcl_onoffAttrGet(SAMPLE_LIGHT_ENDPOINT_2);
			if(pCurOnOffAttr_2){
				gLightCtx[1].sta = !pCurOnOffAttr_2->onOff;
				if(gLightCtx[1].sta){
					sampleLight_onOffUpdate(SAMPLE_LIGHT_ENDPOINT_2, ZCL_ONOFF_STATUS_ON);
				}else{
					sampleLight_onOffUpdate(SAMPLE_LIGHT_ENDPOINT_2, ZCL_ONOFF_STATUS_OFF);
				}
			}
#endif
		//}
	}else if(btNum == VK_SW2){
		/* toggle local permit Joining */
		static u8 duration = 0;
		duration = duration ? 0 : 0xff;
		zb_nlmePermitJoiningRequest(duration);
	}
#if PLUG_EP_2_SUPPORT
	else if(btNum == VK_SW3){
		//if(zb_isDeviceJoinedNwk()){
			zcl_onOffAttr_t *pCurOnOffAttr = zcl_onoffAttrGet(SAMPLE_LIGHT_ENDPOINT_2);
			if(pCurOnOffAttr){
				gLightCtx[1].sta = !pCurOnOffAttr->onOff;
				if(gLightCtx[1].sta){
					sampleLight_onOffUpdate(SAMPLE_LIGHT_ENDPOINT_2, ZCL_ONOFF_STATUS_ON);
				}else{
					sampleLight_onOffUpdate(SAMPLE_LIGHT_ENDPOINT_2, ZCL_ONOFF_STATUS_OFF);
				}
			}
		//}
	}
#endif
}

void keyScan_keyPressedCB(kb_data_t *kbEvt){
//	u8 toNormal = 0;
	u8 keyCode = kbEvt->keycode[0];
//	static u8 lastKeyCode = 0xff;

	buttonShortPressed(keyCode);

	if(keyCode == VK_SW1){
		gUiCtx.keyPressedTime = clock_time();
		gUiCtx.state = APP_FACTORY_NEW_SET_CHECK;
	}
}


void keyScan_keyReleasedCB(u8 keyCode){
	gUiCtx.state = APP_STATE_NORMAL;
}

void app_key_handler(void){
	static u8 valid_keyCode = 0xff;

	if(gUiCtx.state == APP_FACTORY_NEW_SET_CHECK){
		if(clock_time_exceed(gUiCtx.keyPressedTime, 5*1000*1000)){
			buttonKeepPressed(VK_SW1);
		}
	}

	if(kb_scan_key(0 , 1)){
		if(kb_event.cnt){
			keyScan_keyPressedCB(&kb_event);
			if(kb_event.cnt == 1){
				valid_keyCode = kb_event.keycode[0];
			}
		}else{
			keyScan_keyReleasedCB(valid_keyCode);
			valid_keyCode = 0xff;
		}
	}
}

#endif  /* __PROJECT_TL_PLUG__ */
