/********************************************************************************************************
 * @file     concurrent_main.c
 *
 * @brief	 Common main entry
 *
 * @author
 * @date     Dec. 1, 2017
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
#include "tl_common.h"
#include "zb_api.h"
#include "zcl_include.h"
#include "bdb.h"
#include "ota.h"
#include "sampleSwitch.h"
#include "app_ui.h"
#include "stack/ble/ll/ll_pm.h"

#if PM_ENABLE
#include "pm_interface.h"

/**
 *  @brief Definition for wakeup source and level for PM
 */
pm_pinCfg_t g_switchPmCfg[] = {
	{
		BUTTON1,
		PM_WAKEUP_LEVEL
	},
	{
		BUTTON2,
		PM_WAKEUP_LEVEL
	}
};


bool app_zigbeeIdle(void){
	bool ret = 0;
	keepaliveMsgSendStop();
	ret = (g_switchAppCtx.state != APP_STATE_ZB_JOINNING       \
			&& bdb_isIdle() && !tl_stackBusy() && zb_isTaskDone() && zb_timerTaskIdle());

	if(ret){
		secondClockStop();
	}
	return ret;
}


s32 app_pollRateHold(void *arg){
	if(!tl_stackBusy()){
		zb_setPollRate(0);
		g_switchAppCtx.timerPollHold = NULL;
		return -1;
	}

	return 0;
}

void app_zigbeePollRateRecovery(void){
	zb_setPollRate(RESPONSE_POLL_RATE);
	extern void secondClockRun(void);
	secondClockRun();

	if(g_switchAppCtx.timerPollHold){
		TL_ZB_TIMER_CANCEL(&g_switchAppCtx.timerPollHold);
	}
	g_switchAppCtx.timerPollHold = TL_ZB_TIMER_SCHEDULE(app_pollRateHold, NULL, 500 * 1000);
}

void app_pm_init(void){
	pm_wakeupPinConfig(g_switchPmCfg, sizeof(g_switchPmCfg)/sizeof(pm_pinCfg_t));

	bls_pm_setWakeupSource(PM_WAKEUP_PAD);
	bls_pm_setConditionCb(app_zigbeeIdle);
}

volatile u8 T_app_pm_taskCnt[4] = {0};
extern u32 blt_pm_proc(void);
void app_pm_task(void){
	T_app_pm_taskCnt[0]++;

	u8 T_bleAllowSleep = 0;
	u8 T_zbAllowSleep = 0;

	if(blt_pm_proc()){
		/* enter deep sleep */
		T_bleAllowSleep = 1;
	}

	if(app_zigbeeIdle()){
		if(!g_switchAppCtx.keyPressed){
			T_zbAllowSleep = 1;
		}
	}

	if(T_bleAllowSleep && T_zbAllowSleep){
		pm_deepSleepEnter(PLATFORM_MODE_DEEPSLEEP, PLATFORM_WAKEUP_PAD, 0);
	}
}
#endif
