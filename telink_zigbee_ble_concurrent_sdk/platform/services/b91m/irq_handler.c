/********************************************************************************************************
 * @file    irq_handler.c
 *
 * @brief   This is the source file of irq_handler for b91m
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

#include "tl_common.h"
#include "zigbee_ble_switch.h"

extern void rf_rx_irq_handler(void);
extern void rf_tx_irq_handler(void);
extern void irq_blt_sdk_handler(void);
extern void switch_to_ble_context(void);
extern bool zb_rfSwitchAllow(void);

volatile u8 T_DBG_testIrq[16] = {0};
volatile u8 T_taskBleStop = 0;
volatile u8 T_DBG_sysTickIrq = 0;

void rf_irq_handler(void)
{
	if(CURRENT_SLOT_GET() == DUALMODE_SLOT_ZIGBEE){
		T_DBG_testIrq[0]++;
		if(rf_get_irq_status(FLD_RF_IRQ_RX)){
			rf_clr_irq_status(FLD_RF_IRQ_RX);
			T_DBG_testIrq[1]++;
			rf_rx_irq_handler();
		}else if(rf_get_irq_status(FLD_RF_IRQ_TX)){
			rf_clr_irq_status(FLD_RF_IRQ_TX);
			T_DBG_testIrq[2]++;
			rf_tx_irq_handler();
		}else{
			T_DBG_testIrq[3]++;
			rf_clr_irq_status(0xffff);
		}
	}else{
		irq_blt_sdk_handler ();
	}
}

void timer0_irq_handler(void)
{
	if(timer_get_irq_status(TMR_STA_TMR0)){
		timer_clr_irq_status(TMR_STA_TMR0);
		drv_timer_irq0_handler();
	}
}

void timer1_irq_handler(void)
{
	if(timer_get_irq_status(TMR_STA_TMR1)){
		timer_clr_irq_status(TMR_STA_TMR1);
		drv_timer_irq1_handler();
	}
}

void stimer_irq_handler(void)
{
	if(T_taskBleStop){
		T_DBG_sysTickIrq++;
	}
	if(CURRENT_SLOT_GET() == DUALMODE_SLOT_ZIGBEE){
		if(stimer_get_irq_status(FLD_SYSTEM_IRQ)){
			if(zb_rfSwitchAllow()){
				stimer_clr_irq_status(FLD_SYSTEM_IRQ);
				/* need switch to ble mode */
				switch_to_ble_context();

				irq_blt_sdk_handler();
				//DBG_ZIGBEE_STATUS(0x23);
			}else{

			}
		}
	}else{
		irq_blt_sdk_handler ();
	}
}

void gpio_irq_handler(void)
{
	T_DBG_testIrq[5]++;
	gpio_clr_irq_status(FLD_GPIO_IRQ_CLR);
	drv_gpio_irq_handler();
}

void gpio_risc0_irq_handler(void)
{
	T_DBG_testIrq[6]++;
	gpio_clr_irq_status(FLD_GPIO_IRQ_GPIO2RISC0_CLR);
	drv_gpio_irq_risc0_handler();
}

void gpio_risc1_irq_handler(void)
{
	T_DBG_testIrq[7]++;
	gpio_clr_irq_status(FLD_GPIO_IRQ_GPIO2RISC1_CLR);
	drv_gpio_irq_risc1_handler();
}

void uart0_irq_handler(void)
{
	if(uart_get_irq_status(UART0, UART_TXDONE)){
		T_DBG_testIrq[8]++;
		drv_uart_tx_irq_handler();
	}

	if(uart_get_irq_status(UART0, UART_RXDONE)){
		T_DBG_testIrq[9]++;
		drv_uart_rx_irq_handler();
	}
}
