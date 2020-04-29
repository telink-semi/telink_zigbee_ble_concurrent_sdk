/********************************************************************************************************
 * @file     user_config.c
 *
 * @brief    for TLSR chips
 *
 * @author	 telink
 * @date     Sep. 30, 2010
 *
 * @par      Copyright (c) 2010, Telink Semiconductor (Shanghai) Co., Ltd.
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
#include "../../proj/tl_common.h"

#if __PROJECT_TL_BOOT_LOADER__
asm(".equ __BOOT_LOADER_EN,         1");
asm(".equ __FW_OFFSET,      		0");
asm(".equ __FW_RAMCODE_SIZE_MAX,    0x4000");

#else
#if BOOT_LOAD_MODE
asm(".equ __FW_OFFSET,      		0xC0000");
#else
asm(".equ __FW_OFFSET,      		0");
#endif
asm(".equ __BOOT_LOADER_EN,         0");
asm(".equ __FW_RAMCODE_SIZE_MAX,    0x4000");
#endif

asm(".equ __MCU_RUN_SRAM_EN,         0");

asm(".global     __MCU_RUN_SRAM_EN");
asm(".global     __BOOT_LOADER_EN");
asm(".global     __FW_OFFSET");
asm(".global     __FW_RAMCODE_SIZE_MAX");

/**
  * @}
  */

/**
  * @}
  */


