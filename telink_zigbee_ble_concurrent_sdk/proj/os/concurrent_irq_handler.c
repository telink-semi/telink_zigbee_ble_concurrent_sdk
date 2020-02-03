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
extern int zb_rf802154_tx_flag;
_attribute_ram_code_ void zb_irq_handler(void){

	u16  src_rf = rf_irq_src_get();
	if(src_rf & FLD_RF_IRQ_TX){
        //zb_tx_irq_cnt++;
        zb_rf802154_tx_flag = 0;
		rf_tx_irq_handler();
	}

	if(src_rf & FLD_RF_IRQ_RX){
        //zb_rx_irq_cnt++;
		rf_rx_irq_handler();
	}
#if 0
	u32 src = irq_get_src();

	if(IRQ_TIMER1_ENABLE && (src & FLD_IRQ_TMR1_EN)){
		reg_irq_src = FLD_IRQ_TMR1_EN;
		timer_irq1_handler();
	}

    if((src & FLD_IRQ_TMR2_EN)){
		reg_irq_src = FLD_IRQ_TMR2_EN;
	}

	if((src & FLD_IRQ_GPIO_EN)==FLD_IRQ_GPIO_EN)
	{
		gpio_irq_handler();
	}
#endif
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

volatile int zb_irq_flag = 0;

_attribute_ram_code_ void irq_handler(void)
{
    volatile unsigned char mode_flag;
    mode_flag = read_reg8(0x404);
    #if 1
    u16  src_rf = rf_irq_src_get();
	if((src_rf & FLD_RF_IRQ_TX)&&(zb_rf802154_tx_flag == 1)){
        //zb_tx_irq_cnt++;
        zb_rf802154_tx_flag = 0;
        if(mode_flag == 0xf5)
        {
            zb_irq_flag = 1;
        }
		rf_tx_irq_handler();
	}

    #endif

    #if 1
    u32 src = reg_irq_src;
	if(src & FLD_IRQ_SYSTEM_TIMER){
		//log_task_begin (TR_T_irq_sysTimer);

		//reg_irq_src = FLD_IRQ_SYSTEM_TIMER;

		//irq_ll_system_timer();
		irq_blt_sdk_handler();

		//log_task_end (TR_T_irq_sysTimer);
	}
    #endif
    
    if(ble_stack_idle()&& (ble_rxfifo_empty()))
    {
        if(mode_flag == 0xf5)
        {
            zb_irq_flag = 2;
        }
        zb_irq_handler();
    }else
    {
        if(mode_flag == 0xc0)
        {
            zb_irq_flag = 3;
        }
        irq_blt_sdk_handler();
    }
}

#endif

