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
#include "user_config.h"
#include "zb_common.h"
#include "../../ble/blt_config.h"
#include "../../ble/ll/ll.h"

#include "tl_common.h"
#include "zcl_include.h"
#include "sampleSwitch.h"
#include "app_ui.h"

#if BLE_CONCURRENT_MODE

asm(".equ __FW_OFFSET,      0xC0000");
asm(".global     __FW_OFFSET");

#define  ZIGBEE_AFTER_TIME    (16 * 1000 * 2)	//4ms
#define  BLE_IDLE_TIME   	  (16 * 1000 * 2)	//5ms

unsigned  long  g_process_zigbee_en = 0;
unsigned  long  g_process_clock_timeout;
unsigned  long  g_process_clock_start;


signed char ble_channel = 0;

extern u8	*rf_rxBuf;
extern u8 	rf_busyFlag;
extern u8	blt_state ;
extern  volatile u8	blt_busy;
extern signed char ble_current_channel;
extern unsigned  long  g_process_zigbee_en;
extern _attribute_data_retention_	my_fifo_t	blt_rxfifo;

extern void user_zb_init();
extern void user_ble_init(void);
extern u32 blt_pm_proc(void);

/* system clock configuration
 *
 * platform:
 * 		826x
 * 		8258
 * 		HAWK
 *
 *  */
#if defined(MCU_CORE_826x)
	#if(CLOCK_SYS_CLOCK_HZ == 32000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_32M_PLL;
	#elif(CLOCK_SYS_CLOCK_HZ == 16000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_16M_PLL;
	#else
		#error please config system clock
	#endif
#elif defined(MCU_CORE_8258)
	#if(CLOCK_SYS_CLOCK_HZ == 24000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_24M_Crystal;
	#elif(CLOCK_SYS_CLOCK_HZ == 32000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_32M_Crystal;
	#elif(CLOCK_SYS_CLOCK_HZ == 16000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_16M_Crystal;
	#elif(CLOCK_SYS_CLOCK_HZ == 48000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_48M_Crystal;
	#else
		#error please config system clock
	#endif
#elif defined(MCU_CORE_HAWK)
	#if(CLOCK_SYS_CLOCK_HZ == 16000000)
		SYS_CLK_TYPEDEF g_sysClk = SYS_CLK_16M_PLL;
	#else
		#error please config system clock
	#endif
#endif

enum{
	SYSTEM_RETENTION_NONE,
	SYSTEM_RETENTION_EN,
};

/*
 * platform initiation:
 * 		clock_init: 	system clock selection
 * 		ZB_RADIO_INIT: 	RF module
 * 		gpio_init:		gpio configuration
 * 		ZB_TIMER_INIT:  enable a timer for zigbee mac cca-csma
 *
 * */
static u8 platform_init(void){
	u8 ret = SYSTEM_RETENTION_NONE;

#if defined(MCU_CORE_8258)
	extern void bss_section_clear(void);
	extern void data_section_load();
	if( (analog_read(0x7f) & 0x01) ){	  //recovery from deep sleep
		bss_section_clear();
		data_section_load();
	}else{
		ret = SYSTEM_RETENTION_EN;
	}
#endif

	blc_pm_select_internal_32k_crystal();

	cpu_wakeup_init();

	clock_init(/*SYS_CLK_16M_Crystal*/SYS_CLK_32M_Crystal);//BLE 16M

#if defined(MCU_CORE_8258)
	internalFlashSizeCheck();
	rng_init();   //for random generation
#endif

	gpio_init();

	ZB_RADIO_INIT();

	//ZB_TIMER_INIT();
	return ret;
}

int is_switch_to_ble(void){
	if((get_ble_next_event_tick() - (clock_time() + ZIGBEE_AFTER_TIME)) > BIT(31) ){
		return 1;
	}else{
		return 0;
	}
}

int is_switch_to_zigbee(void){
    if((get_ble_next_event_tick() - (clock_time() + BLE_IDLE_TIME)) < BIT(31) ){
        return 1;
    }else{
    	return 0;
    }
}


int ble_stack_idle(void){
    if(g_process_zigbee_en&&(blt_busy == 0)&&((blt_state == 8)||(blt_state == 1))){
        return 1;
    }else{
        return 0;
    }
}


void switch_to_zb_context(void){
	rf_baseband_reset();
	backup_ble_rf_context();
	ZB_RADIO_RX_BUF_CLEAR(rf_rxBuf);
	restore_zigbee_rf_context(rf_rxBuf);
	//rf_drv_250k();
	write_reg8(0x401, 0);
	ZB_RADIO_INIT();
	ZB_RADIO_TRX_CFG((RF_PKT_BUFF_LEN));
	ble_channel = ble_current_channel;
	rf_setChannel(rf_getChannel());
	rf_setTrxState(RF_STATE_RX);
	sleep_us(150);//delete
	reg_rf_irq_status = 0xffff;
	reg_irq_mask |= FLD_IRQ_ZB_RT_EN;
	reg_rf_irq_mask |= (FLD_RF_IRQ_TX | FLD_RF_IRQ_RX);
	//Rf_BaseBandReset ();
}

void switch_to_ble_context(void){
    // do some rf init, set to ble mode
	ZB_RADIO_RX_DISABLE;
	ZB_RADIO_RX_BUF_CLEAR(rf_rxBuf);
	backup_zigbee_rf_context();
	rf_baseband_reset();

	restore_ble_rf_context();
	reg_irq_mask &= ~FLD_IRQ_ZB_RT_EN;
	reg_rf_irq_status = 0xffff;
	reg_irq_mask |= FLD_IRQ_ZB_RT_EN;
	//rf_drv_1m ();
	ble_rf_drv_init(RF_MODE_BLE_1M);
	rf_set_ble_channel (ble_channel);

	g_process_zigbee_en = 0;
}

volatile u8 zigbee_process = 0;
void zb_task(void){
    tl_zbTaskProcedure();

#if(MODULE_WATCHDOG_ENABLE)
	wd_clear();
#endif

	ev_main();
}

void concurrent_mode_main_loop (void){
	u8 r = 0;

	 if(zigbee_process == 0){
		 /*
		  * ble task
		  *
		  * */
		 blt_sdk_main_loop();

		 DBG_ZIGBEE_STATUS(0x30);

		 r = irq_disable();
		 if(get_ble_event_state() && is_switch_to_zigbee()){
			 /*
			  * ready to switch to ZIGBEE mode
			  *
			  * */
			 DBG_ZIGBEE_STATUS(0x31);

			 ZB_RADIO_RX_DISABLE;
			 switch_to_zb_context();
			 zigbee_process = 1;
			 ZB_RADIO_RX_ENABLE;
			 irq_restore(r);
			 zb_task();

			 DBG_ZIGBEE_STATUS(0x32);
		 }else{
			 irq_restore(r);
		 }
	 }else{
		 /*
		  * now in zigbee mode
		  *
		  * */
		 DBG_ZIGBEE_STATUS(0x33);

		 r = irq_disable();
		 if(!rf_busyFlag && is_switch_to_ble()){
			 /*
			  * ready to switch to BLE mode
			  *
			  * */
			 zigbee_process = 0;
			 switch_to_ble_context();
			 irq_restore(r);

			 DBG_ZIGBEE_STATUS(0x34);
			 return;
		 }
		 irq_restore(r);

		 DBG_ZIGBEE_STATUS(0x35);
		 zb_task();
	 }
}

int main (void) {
	if(platform_init() == SYSTEM_RETENTION_NONE){
		os_init(0);
	}

#if(TX_POWER_CAL_ENABLE)
	app_txPowerCal();
#endif

	user_zb_init();
	//backup the registers
	backup_zigbee_rf_context();

    ble_rf_drv_init(RF_MODE_BLE_1M);
	user_ble_init();

#if PM_ENABLE
	app_pm_init();
#endif

    irq_enable();
	while (1) {
    	concurrent_mode_main_loop ();

    	app_key_handler();

#if PM_ENABLE
    	app_pm_task();
#endif
	}
}

#endif
