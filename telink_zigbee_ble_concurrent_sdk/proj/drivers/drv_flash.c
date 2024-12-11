/********************************************************************************************************
 * @file    drv_flash.c
 *
 * @brief   This is the source file for drv_flash
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
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

#include "../tl_common.h"

void flash_write(u32 addr, u32 len, u8 *buf){
#if (MODULE_WATCHDOG_ENABLE)
	drv_wd_clear();
#endif

#if (VOLTAGE_DETECT_ENABLE)
	if(drv_get_adc_data() < VOLTAGE_SAFETY_THRESHOLD){return;}
#endif

	flash_write_page(addr, len, buf);
}

bool flash_writeWithCheck(u32 addr, u32 len, u8 *buf){
	s32 toalLen = (s32)len;
	s8 copyLen = 48;
	u8 pTemp[48];
	u8 wLen = 0;
	u32 sAddr = (u32)addr;
	u8 *pSrc = buf;

#if (MODULE_WATCHDOG_ENABLE)
	drv_wd_clear();
#endif

#if (VOLTAGE_DETECT_ENABLE)
	if(drv_get_adc_data() < VOLTAGE_SAFETY_THRESHOLD){
		return FALSE;
	}
#endif

	flash_write_page(addr, len, buf);

	while(toalLen > 0){
		wLen = (toalLen > copyLen) ? copyLen : toalLen;
		flash_read(sAddr, wLen, pTemp);
		if(memcmp(pTemp, pSrc, wLen)){
			return FALSE;
		}
		toalLen -= wLen;
		sAddr += wLen;
		pSrc += wLen;
	}
	return TRUE;
}


void flash_read(u32 addr, u32 len, u8 *buf){
	flash_read_page(addr, len, buf);
}

void flash_erase(u32 addr){
#if (MODULE_WATCHDOG_ENABLE)
	drv_wd_clear();
#endif

#if (VOLTAGE_DETECT_ENABLE)
	if(drv_get_adc_data() < VOLTAGE_SAFETY_THRESHOLD){return;}
#endif

	flash_erase_sector(addr);
}

