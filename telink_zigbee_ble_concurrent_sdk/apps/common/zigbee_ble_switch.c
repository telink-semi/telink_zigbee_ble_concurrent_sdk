/********************************************************************************************************
 * @file     zigbee_ble_switch.c
 *
 * @brief     the function for ble/zigbee switch
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
#include "user_config.h"
#include "zb_common.h"
#include "stack/ble/blt_config.h"
#include "stack/ble/ll/ll.h"

#include "tl_common.h"

#if BLE_CONCURRENT_MODE

#define  ZIGBEE_AFTER_TIME    (16 * 1000 * 5)	//4ms
#define  BLE_IDLE_TIME   	  (16 * 1000 * 5)	//5ms

signed char ble_channel = 0;
volatile u8 zigbee_process = 0;

extern u8	*rf_rxBuf;
extern signed char ble_current_channel;

_attribute_ram_code_ void switch_to_zb_context(void){
	rf_baseband_reset();
	dma_reset();
	backup_ble_rf_context();
	ZB_RADIO_RX_BUF_CLEAR(rf_rxBuf);
	restore_zigbee_rf_context(rf_rxBuf);

	ZB_RADIO_INIT();
	ZB_RADIO_TRX_CFG((RF_PKT_BUFF_LEN));
	ble_channel = ble_current_channel;
	rf_setChannel(rf_getChannel());
	rf_setTrxState(RF_STATE_RX);

	sleep_us(150);//delete

	reg_rf_irq_status = 0xffff;
	reg_irq_mask |= FLD_IRQ_ZB_RT_EN;
	reg_rf_irq_mask |= (FLD_RF_IRQ_TX | FLD_RF_IRQ_RX);
}


_attribute_ram_code_ void switch_to_ble_context(void){
    // do some rf init, set to ble mode
	ZB_RADIO_RX_DISABLE;
	ZB_RADIO_RX_BUF_CLEAR(rf_rxBuf);
	backup_zigbee_rf_context();
	rf_baseband_reset();
	dma_reset();

	restore_ble_rf_context();
	reg_irq_mask &= ~FLD_IRQ_ZB_RT_EN;
	reg_rf_irq_status = 0xffff;
	reg_irq_mask |= FLD_IRQ_ZB_RT_EN;

	ble_rf_drv_init(RF_MODE_BLE_1M);
	rf_set_ble_channel (ble_channel);
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


void zb_task(void){
    tl_zbTaskProcedure(1);

#if(MODULE_WATCHDOG_ENABLE)
	wd_clear();
#endif

	ev_main(1);
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

		 if(!zb_rfTxDoing() && is_switch_to_ble()){
			 /*
			  * ready to switch to BLE mode
			  *
			  * */
			 zigbee_process = 0;
			 switch_to_ble_context();

			 DBG_ZIGBEE_STATUS(0x34);

			 irq_restore(r);
			 return;
		 }

		 irq_restore(r);
		 DBG_ZIGBEE_STATUS(0x35);
		 zb_task();
	 }
}

#endif
