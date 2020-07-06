/********************************************************************************************************
 * @file     zigbee_ble_switch.h
 *
 * @brief    the function for ble/zigbee switch
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

extern volatile u8 zigbee_process;

_attribute_ram_code_ void switch_to_zb_context(void);

_attribute_ram_code_ void switch_to_ble_context(void);

int is_switch_to_ble(void);

int is_switch_to_zigbee(void);

void ble_task_stop(void);

void ble_task_restart(void);

void concurrent_mode_main_loop (void);

#endif
