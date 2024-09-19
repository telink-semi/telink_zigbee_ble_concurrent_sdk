/********************************************************************************************************
 * @file    software_pa.c
 *
 * @brief   This is the source file for BLE SDK
 *
 * @author  BLE GROUP
 * @date    06,2022
 *
 * @par     Copyright (c) 2022, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
 *
 *******************************************************************************************************/
#include "compiler.h"
#include "software_pa.h"
#include "../gpio.h"


_attribute_data_retention_sec_	rf_pa_callback_t  blc_rf_pa_cb = 0;

unsigned int rfpa_txen_pin = 0;
unsigned int rfpa_rxen_pin = 0;

_attribute_ram_code_
void app_rf_pa_handler(int type)
{
#if(PA_ENABLE)
	if(type == PA_TYPE_TX_ON){
		gpio_set_low_level(rfpa_rxen_pin);
		gpio_set_high_level(rfpa_txen_pin);
	}
	else if(type == PA_TYPE_RX_ON){
		gpio_set_low_level(rfpa_txen_pin);
		gpio_set_high_level(rfpa_rxen_pin);
	}
	else{
		gpio_set_low_level(rfpa_rxen_pin);
		gpio_set_low_level(rfpa_txen_pin);
	}
#endif
}


/**
 * @brief	RF software PA initialization
 * @param	none
 * @return	none
 */
void rf_pa_init(unsigned int TXEN_pin, unsigned int RXEN_pin)
{
#if(PA_ENABLE)
	rfpa_txen_pin = TXEN_pin;
    rfpa_rxen_pin = RXEN_pin;

	gpio_function_en(rfpa_txen_pin);
    gpio_input_dis(rfpa_txen_pin);        //disable input
    gpio_output_en(rfpa_txen_pin);         //enable output
    gpio_set_level(rfpa_txen_pin, 0);

    gpio_function_en(rfpa_rxen_pin);
    gpio_input_dis(rfpa_rxen_pin);        //disable input
    gpio_output_en(rfpa_rxen_pin);         //enable output
    gpio_set_level(rfpa_rxen_pin, 0);
    blc_rf_pa_cb = app_rf_pa_handler;
#endif
}

