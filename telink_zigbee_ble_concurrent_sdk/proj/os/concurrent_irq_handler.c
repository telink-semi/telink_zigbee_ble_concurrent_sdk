/********************************************************************************************************
 * @file     concurrent_irq_handler.c
 *
 * @brief    Interface of interrupt handler
 *
 * @author
 * @date     Oct. 8, 2016
 *
 * @par      Copyright (c) 2016, Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *           The information contained herein is confidential property of Telink
 *           Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *           of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *           Co., Ltd. and the licensee or the terms described here-in. This heading
 *           MUST NOT be removed from this file.
 *
 *           Licensees are granted free, non-transferable use of the information in this
 *           file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/
#include "../tl_common.h"
#include "../../zigbee/mac/includes/mac_phy.h"

#include "stack/ble/blt_config.h"
#include "stack/ble/ll/ll.h"

void gpio_user_irq_handler(void);
void timer_irq1_handler(void);
void usb_suspend_irq_handler(void);
void eth_rx_irq_handler(void);
void rf_rx_irq_handler(void);
void rf_tx_irq_handler(void);
void timer_irq2_handler(void);
// called by irq in cstartup.s

#if (MODULE_UART_ENABLE)
#include "../drivers/drv_uart.h"
#endif

#if BLE_CONCURRENT_MODE

extern u8 rfMode;
extern volatile u8 zigbee_process;

extern void switch_to_ble_context(void);
volatile u8 T_irqExceptCnt[2] = {0};


extern volatile u8 rf_busyFlag;
_attribute_ram_code_ void irq_handler(void){
	u32 src = reg_irq_src;
	u32 msk = reg_irq_mask;
	u16  src_rf = rf_irq_src_get();
	extern void irq_blt_sdk_handler(void);

	if(zigbee_process){
		DBG_ZIGBEE_STATUS(0x20);

		/* first check the BLE sync event(system timer interrupt, just only be used by ble stack),
		 * and then check if the zigbee phy layer is busy
		 * if it isn't busy, clear rf interrupt status and switch to BLE directly
		 * if it's busy, need to wait till the zigbee tx event is finish */
		if(src & FLD_IRQ_SYSTEM_TIMER){
			/*
			 * when ble is idle/adv, the mask "FLD_IRQ_SYSTEM_TIMER" is disable,
			 * but the timer capture value is still valid,
			 * so the status will be triggered once the tick counter reach this capture value
			 *
			 */
			if(msk & FLD_IRQ_SYSTEM_TIMER){
				if(zb_rfSwitchAllow()){
					src_rf = 0;    //clear it to skip the rf_tx_irq_handler/rf_rx_irq_handler

					/* need switch to ble mode */
					switch_to_ble_context();
					zigbee_process = 0;
					T_irqExceptCnt[0]++;
					irq_blt_sdk_handler();

					DBG_ZIGBEE_STATUS(0x23);
				}else{
					T_irqExceptCnt[1]++;
				}
			}else{
				reg_irq_src = FLD_IRQ_SYSTEM_TIMER;
			}
		}

		if(src_rf & FLD_RF_IRQ_TX){
			rf_tx_irq_handler();
			DBG_ZIGBEE_STATUS(0x21);
		}
		if(src_rf & FLD_RF_IRQ_RX){
			DBG_ZIGBEE_STATUS(0x22);
			rf_rx_irq_handler();
		}


	}else{
		DBG_ZIGBEE_STATUS(0x24);
		irq_blt_sdk_handler();
	}

#if (MODULE_UART_ENABLE)
    u16  dma_irq_source = dma_chn_irq_status_get();
	if(dma_irq_source & FLD_DMA_CHN_UART_RX){
		dma_chn_irq_status_clr(FLD_DMA_CHN_UART_RX);
		uart_rx_irq_handler();
	}else if(dma_irq_source & FLD_DMA_CHN_UART_TX){
		dma_chn_irq_status_clr(FLD_DMA_CHN_UART_TX);
		uart_tx_irq_handler();
	}else{
		dma_chn_irq_status_clr(~(FLD_DMA_CHN_UART_TX | FLD_DMA_CHN_UART_RX));
	}
#endif
}

#endif

