/********************************************************************************************************
 * @file     pm_interface.c
 *
 * @brief    Power management interface
 *
 * @author
 * @date     Feb. 1, 2017
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
#include "zb_task_queue.h"
#include "zb_common.h"

#if(PM_ENABLE)
#include "pm_interface.h"

void pm_wakeupPinConfig(pm_pinCfg_t *pmCfg, int pinNum){
	pm_pinCfg_t *p = pmCfg;
	for(s32 i = 0; i < pinNum; i++){
		platform_wakeup_pad_cfg(p->wakeupPin, p->wakeLevel, 1);
		p++;
	}
}

u8 pm_wakeupValid(pm_pinCfg_t *pmCfg, int pinNum){
	pm_pinCfg_t *p = pmCfg;
	for(s32 i = 0; i < pinNum; i++){
		if((p->wakeLevel == PLATFORM_WAKEUP_LEVEL_HIGH) && gpio_read(p->wakeupPin)){
			return 0;
		}

		if((p->wakeLevel == PLATFORM_WAKEUP_LEVEL_LOW) && !gpio_read(p->wakeupPin)){
			return 0;
		}
		p++;
	}
	return 1;
}


void pm_lowPowerEnter(platform_mode_e mode, platform_wakeup_e wakeUpSrc, u32 ms){

	u8 r = irq_disable();
	u32 interval = ms;
	if(wakeUpSrc & PLATFORM_WAKEUP_TIMER){
		/* If ms is 0, we use default value 120s for sleep mode. */
		interval = (ms == 0) ? (120 * 1000) : ms;

		interval = (ev_nearestInterval() <= (interval * CLOCK_SYS_CLOCK_1US * 1000)) ? ev_nearestInterval() / (CLOCK_SYS_CLOCK_1US * 1000)
																				 : interval;
	}

	if(interval || (wakeUpSrc & PLATFORM_WAKEUP_PAD)){
		extern void rf_paShutDown(void);
		rf_paShutDown();

		if(mode == PLATFORM_MODE_DEEPSLEEP || mode == PLATFORM_MODE_DEEPSLEEP_RET_SRAM_LOW32K){
			deep_sleep_flag_set(ss_outgoingFrameCntGet());
		}
		platform_lowpower_enter(mode, wakeUpSrc, interval);
	}

	irq_restore(r);
}

void pm_suspendEnter(platform_wakeup_e wakeUpSrc, u32 ms){
	pm_lowPowerEnter(PLATFORM_MODE_SUSPEND, wakeUpSrc, ms);
}

void pm_deepSleepEnter(platform_mode_e mode, platform_wakeup_e wakeUpSrc, u32 ms){
	pm_lowPowerEnter(mode, wakeUpSrc, ms);
}


#endif
