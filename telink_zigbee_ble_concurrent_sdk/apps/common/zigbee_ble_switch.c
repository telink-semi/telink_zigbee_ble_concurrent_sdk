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
#include "zigbee_ble_switch.h"
#include "user_config.h"
#include "zb_common.h"
#include "stack/ble/blt_config.h"
#include "stack/ble/ll/ll.h"

#include "tl_common.h"

#if BLE_CONCURRENT_MODE

#if BLE_MASTER_ROLE_ENABLE
ble_master_cb_t  g_bleMasterHandler = {
	.serviceCb = NULL,
	.updateCb = NULL
};
extern int blm_disconnect;
#endif

signed char ble_channel = 0;
volatile u8 zigbee_process = 0;
static u32 g_bleTaskTick = 0;

extern u8	*rf_rxBuf;
extern signed char ble_current_channel;
extern u8 g_ble_txPowerSet;

#define ZB_RF_ISR_RECOVERY		do{  \
									if(zigbee_process == 1)	reg_rf_irq_mask |= (FLD_RF_IRQ_TX | FLD_RF_IRQ_RX);  \
								}while(0)


_attribute_ram_code_ void switch_to_zb_context(void){
	rf_baseband_reset();
	//dma_reset();    //!!!remove it, or it will cause uart-tx-irq miss if uart_tx is started
	backup_ble_rf_context();
	ZB_RADIO_RX_BUF_CLEAR(rf_rxBuf);
	restore_zigbee_rf_context(rf_rxBuf);

	ZB_RADIO_INIT();
	ZB_RADIO_TRX_CFG((RF_PKT_BUFF_LEN));
	ZB_RADIO_TX_POWER_SET(g_zb_txPowerSet);    //switch tx power for to zb mode

	ble_channel = ble_current_channel;
	rf_setChannel(rf_getChannel());
	rf_setTrxState(RF_STATE_RX);

	//sleep_us(150);//remove it, it isn't necessary for rx mode

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
	//dma_reset();   //!!! remove it, or it will cause uart-tx-irq miss if uart_tx is started

	restore_ble_rf_context();
	reg_irq_mask &= ~FLD_IRQ_ZB_RT_EN;
	reg_rf_irq_status = 0xffff;
	reg_irq_mask |= FLD_IRQ_ZB_RT_EN;

	ble_rf_drv_init(RF_MODE_BLE_1M);
	ZB_RADIO_TX_POWER_SET(g_ble_txPowerSet);    //switch tx power for ble mode
	//rf_set_ble_channel (ble_channel);
	rf_set_tx_rx_off();//GaoQiu add
}

#if SCAN_IN_ADV_STATE
/*
 * ble is doing scan in the state of ADV
 *
 * @param ref_tick  beginning time the ADV
 *
 * @param index     is to control the scan interval, scan interval is (ADV-interval * index/16)
 *
 * */
static u32	blc_scan_busy_in_adv(u32 ref_tick, u8 index){
	unsigned int ret = 0;
	if(blts.scan_extension_mask & BLS_FLAG_SCAN_IN_ADV_MODE){
		ret = ((unsigned int)((ref_tick + (blta.adv_interval >> 4) * (index & 0x0f)) - reg_system_tick)) < BIT(30);
	}
	return ret;
}
#endif


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


void zb_ble_switch_proc(void){
	u8 r = 0;

	 if(zigbee_process == 0){
		 g_bleTaskTick = clock_time();

		 /*
		  * ble task
		  *
		  * */
#if SCAN_IN_ADV_STATE
		 /* add scan functionality after advertising during ADV state, just for slave mode */
		 do{
			 /* disable pm during scan */
	#if PM_ENABLE
			 if(blt_state == BLS_LINK_STATE_ADV){
				 bls_pm_setSuspendMask (SUSPEND_DISABLE);
			 }
	#endif

			 blt_sdk_main_loop();
		 }while((blt_state == BLS_LINK_STATE_ADV) && blc_scan_busy_in_adv(g_bleTaskTick,2));//MY_ADV_INTERVAL*3/4

		 /* enable pm after scan */
	#if PM_ENABLE
		 bls_pm_setSuspendMask (SUSPEND_ADV | SUSPEND_CONN);
	#endif

#else
		 blt_sdk_main_loop();
#endif
		 DBG_ZIGBEE_STATUS(0x30);

#if BLE_MASTER_ROLE_ENABLE
		 if(g_bleMasterHandler.updateCb){
			 g_bleMasterHandler.updateCb();
		 }
#endif

		 r = irq_disable();

		 if(((get_ble_event_state() && is_switch_to_zigbee()) || blt_state == BLS_LINK_STATE_IDLE)
#if BLE_MASTER_ROLE_ENABLE
			 && !blm_disconnect
#endif
			 ){
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

		 if(!zb_rfTxDoing() && is_switch_to_ble() && blt_state != BLS_LINK_STATE_IDLE){
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

void concurrent_mode_main_loop(void){
	zb_ble_switch_proc();

#if BLE_MASTER_ROLE_ENABLE
	u8 bleMode = !zigbee_process;
	if(bleMode && g_bleMasterHandler.serviceCb){
		g_bleMasterHandler.serviceCb();
		g_bleMasterHandler.serviceCb = NULL;
	}
#endif
}

ble_sts_t ble_task_stop(void){
	ble_sts_t ret = BLE_SUCCESS;

	u8 r = irq_disable();

	if(blt_state == BLS_LINK_STATE_CONN){
		ret = bls_ll_terminateConnection(HCI_ERR_OP_CANCELLED_BY_HOST);//cut any ble connections
	}else{
		ret = bls_ll_setAdvEnable(0);

		/* rf irq is cleared in the "bls_ll_setAdvEnable",
		 * so that the rf tx/rx interrupt will be missed if the "bls_ll_setAdvEnable" is called in Zigbee mode
		 */
		if(ret == BLE_SUCCESS){
			ZB_RF_ISR_RECOVERY;
		}
	}

	irq_restore(r);
	return ret;
}

ble_sts_t ble_task_restart(void){
	u8 r = irq_disable();

	ble_sts_t ret = bls_ll_setAdvEnable(1);
	/* rf irq is cleared in the "bls_ll_setAdvEnable",
	 * so that the rf tx/rx interrupt will be missed if the "bls_ll_setAdvEnable" is called in Zigbee mode
	 */
	if(ret == BLE_SUCCESS){
		ZB_RF_ISR_RECOVERY;
	}

	irq_restore(r);
	return ret;
}

#if BLE_MASTER_ROLE_ENABLE
void ble_master_serviceCbRegister(master_service_t cb){
	g_bleMasterHandler.serviceCb = cb;
};

void ble_master_updateIndCbRegister(master_update_t cb){
	g_bleMasterHandler.updateCb = cb;
};
#endif

#endif
