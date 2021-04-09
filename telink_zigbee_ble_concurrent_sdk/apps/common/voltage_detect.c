/********************************************************************************************************
 * @file     voltage_detect.c
 *
 * @brief    voltage detection API
 *
 * @author
 * @date     Mar. 1, 2021
 *
 * @par      Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd.
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

#if VOLTAGE_PROTECT_EN

#if PM_ENABLE
	#define VOLTAGE_SAFETY_THRESHOLD   2200
#else
	#define VOLTAGE_SAFETY_THRESHOLD   2500
#endif

volatile u32 T_voltageValue = 0;     //for debug

static u32 voltage_valueGet(void){
	u32 vol = 0;
	for(u32 i = 0; i < 4; i++){
		vol += drv_get_adc_data();
	}
	vol /= 4;
	T_voltageValue = vol;
	return vol;
}


void voltage_detectInit(void){
	drv_adc_init();

#if defined(MCU_CORE_826x)
	drv_adc_mode_pin_set(DRV_ADC_VBAT_MODE, NOINPUT);
#elif defined(MCU_CORE_8258)
	/*
	 * 	VOLTAGE_DETECT_PIN just can use the following pin:
	    GPIO_PB0,GPIO_PB1,
		GPIO_PB2,GPIO_PB3,
		GPIO_PB4,GPIO_PB5,
		GPIO_PB6,GPIO_PB7,
		GPIO_PC4,GPIO_PC5
	 * */
	drv_adc_mode_pin_set(DRV_ADC_VBAT_MODE, VOLTAGE_DETECT_PIN);
#endif

	drv_adc_enable(1);
}


void voltage_protect(u8 sys_start){
	if(sys_start){
#if PM_ENABLE
		u32 curTick = clock_time();
#endif
		while(voltage_valueGet() < VOLTAGE_SAFETY_THRESHOLD){
#if PM_ENABLE
			/* enter low power mode */
			if(clock_time_exceed(curTick, 1000*1000)){
				pm_lowPowerEnter(PLATFORM_MODE_DEEPSLEEP, 0, 0);
			}
#endif
		}
	}else{
		if(voltage_valueGet() < VOLTAGE_SAFETY_THRESHOLD){
#if PM_ENABLE
			/* enter low power mode */
			pm_lowPowerEnter(PLATFORM_MODE_DEEPSLEEP, 0, 0);
#endif
			SYSTEM_RESET();
		}
	}
}
#endif

