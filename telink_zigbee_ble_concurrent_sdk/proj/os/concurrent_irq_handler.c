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
extern int zb_rf802154_tx_flag;

extern void switch_to_ble_context(void);
volatile u8 T_irqExceptCnt = 0;
_attribute_ram_code_ void irq_handler(void){
    u32 src = reg_irq_src;
	if(src & FLD_IRQ_SYSTEM_TIMER){
		if(zigbee_process){
			/* need switch to ble mode */
			switch_to_ble_context();
			zigbee_process = 0;
			T_irqExceptCnt++;
		}
		irq_blt_sdk_handler();
	}

    u16  src_rf = rf_irq_src_get();
	if((src_rf & FLD_RF_IRQ_TX) && (zb_rf802154_tx_flag == 1)){
        zb_rf802154_tx_flag = 0;
		rf_tx_irq_handler();
	}

    if(zigbee_process && rfMode == RF_STATE_RX && (src_rf & FLD_RF_IRQ_RX) && ble_stack_idle()&& (ble_rxfifo_empty())){
       rf_rx_irq_handler();
    }else{
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

