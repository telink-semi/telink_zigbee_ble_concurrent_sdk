/********************************************************************************************************
 * @file    bootloader.c
 *
 * @brief   This is the source file for bootloader
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *			All rights reserved.
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

#if (__PROJECT_TL_BOOT_LOADER__)

#include "tl_common.h"
#include "bootloader.h"



/* FLASH address */
#define APP_RUNNING_ADDR				APP_IMAGE_ADDR
#define APP_NEW_IMAGE_ADDR				FLASH_ADDR_OF_OTA_IMAGE

/* SRAM address */
#if defined(MCU_CORE_8258)
	#define MCU_RAM_START_ADDR			0x840000
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
	#define MCU_RAM_START_ADDR			0x0000
#endif

#if defined(MCU_CORE_8258)
	#define REBOOT()					WRITE_REG8(0x602, 0x88)
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
	#define REBOOT()					((void(*)(void))(FLASH_R_BASE_ADDR + APP_IMAGE_ADDR))()
#endif

#define FW_START_UP_FLAG				0x4B
#define FW_RAMCODE_SIZE_MAX				RESV_FOR_APP_RAM_CODE_SIZE
#define FW_START_UP_FLAG_WHOLE			0x544c4e4b



static bool is_valid_fw_bootloader(u32 addr_fw){
	u32 startup_flag = 0;
    flash_read(addr_fw + FLASH_TLNK_FLAG_OFFSET, 4, (u8 *)&startup_flag);

    return ((startup_flag == FW_START_UP_FLAG_WHOLE) ? TRUE : FALSE);
}

void bootloader_with_ota_check(bool powerOn, u32 addr_load, u32 new_image_addr){
	drv_disable_irq();

#if VOLTAGE_DETECT_ENABLE
	/*
	 * !!!recommend setting VOLTAGE_DETECT_ENABLE as 1 to get the stable/safe voltage
	 */
	u16 voltage = voltage_detect(powerOn, VOLTAGE_SAFETY_THRESHOLD);
	if(voltage > VOLTAGE_SAFETY_THRESHOLD)
#endif
	{
		if(new_image_addr != addr_load){
			if(is_valid_fw_bootloader(new_image_addr)){
				bool isNewImageValid = FALSE;

				u32 bufCache[256/4];  //align-4
				u8 *buf = (u8 *)bufCache;

				flash_read(new_image_addr, 256, buf);
				u32 fw_size = *(u32 *)(buf + 0x18);

				if(fw_size <= FLASH_OTA_IMAGE_MAX_SIZE){
					s32 totalLen = fw_size - 4;
					u32 wLen = 0;
					u32 sAddr = new_image_addr;

					u32 crcVal = 0;
					flash_read(new_image_addr + fw_size - 4, 4, (u8 *)&crcVal);

					u32 curCRC = 0xffffffff;

					while(totalLen > 0){
						wLen = (totalLen > 256) ? 256 : totalLen;
						flash_read(sAddr, wLen, buf);
						curCRC = xcrc32(buf, wLen, curCRC);

						totalLen -= wLen;
						sAddr += wLen;
					}

					if(curCRC == crcVal){
						isNewImageValid = TRUE;
					}
				}

#if FLASH_PROTECT_ENABLE
				flash_unlock();
#endif

				if(isNewImageValid){
					u8 readBuf[256];

					for(int i = 0; i < fw_size; i += 256){
						if((i & 0xfff) == 0){
							flash_erase(addr_load + i);
						}

						flash_read(new_image_addr + i, 256, buf);
						flash_write(addr_load + i, 256, buf);

						flash_read(addr_load + i, 256, readBuf);
						if(memcmp(readBuf, buf, 256)){
#if FLASH_PROTECT_ENABLE
							flash_lock();
#endif
							SYSTEM_RESET();
						}

					}
				}

				buf[0] = 0;
				flash_write(new_image_addr + FLASH_TLNK_FLAG_OFFSET, 1, buf);   //clear OTA flag

				//erase the new firmware
				for(int i = 0; i < ((fw_size + 4095)/4096); i++) {
					flash_erase(new_image_addr + i*4096);
				}

#if FLASH_PROTECT_ENABLE
				flash_lock();
#endif
			}
		}
	}

    if(is_valid_fw_bootloader(addr_load)){
#if defined(MCU_CORE_8258)
    	u32 ramcode_size = 0;
        flash_read(addr_load + 0x0c, 2, (u8 *)&ramcode_size);
        ramcode_size *= 16;

        if(ramcode_size > FW_RAMCODE_SIZE_MAX){
            ramcode_size = FW_RAMCODE_SIZE_MAX; // error, should not run here
        }
        flash_read(addr_load, ramcode_size, (u8 *)MCU_RAM_START_ADDR); // copy ram code
#endif
        REBOOT();
    }
}

void bootloader_init(bool powerOn){
	bootloader_with_ota_check(powerOn, APP_RUNNING_ADDR, APP_NEW_IMAGE_ADDR);
}

#endif	/* __PROJECT_TL_BOOT_LOADER__ */
