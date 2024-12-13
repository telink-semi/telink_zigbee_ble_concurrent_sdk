/********************************************************************************************************
 * @file    app_cfg.h
 *
 * @brief   This is the header file for app_cfg
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

#pragma once

/* Enable C linkage for C++ Compilers: */
#if defined(__cplusplus)
extern "C" {
#endif

/**********************************************************************
 * Version configuration
 */
#include "version_cfg.h"

/**********************************************************************
 * Product Information
 */
/* Debug mode config */
#define TLKAPI_DEBUG_ENABLE						0	//only support gpio simulation Uart mode

/* Board ID */
#define BOARD_8258_EVK								1
#define BOARD_8258_EVK_V1P2							2//C1T139A30_V1.2
#define BOARD_8258_DONGLE							3
#define BOARD_B91_EVK								4
#define BOARD_B91_DONGLE							5
#define BOARD_TL321X_EVK							6
#define BOARD_TL321X_DONGLE							7
#define BOARD_TL721X_EVK							8
#define BOARD_TL721X_DONGLE							9

/* Board define */
#if defined(MCU_CORE_8258)
#if (CHIP_TYPE == TLSR_8258_1M)
	#define FLASH_CAP_SIZE_1M						1
#endif
	#define BOARD									BOARD_8258_DONGLE
	#define CLOCK_SYS_CLOCK_HZ  					48000000
#elif defined(MCU_CORE_B91)
	#define FLASH_CAP_SIZE_1M						1
	#define BOARD									BOARD_B91_DONGLE//BOARD_B91_EVK
	#define CLOCK_SYS_CLOCK_HZ  					48000000
#elif defined(MCU_CORE_TL321X)
	#define FLASH_CAP_SIZE_1M						1
	#define BOARD									BOARD_TL321X_DONGLE//BOARD_TL321X_EVK
	#define CLOCK_SYS_CLOCK_HZ  					96000000
#elif defined(MCU_CORE_TL721X)
	#define FLASH_CAP_SIZE_1M						1
	#define BOARD									BOARD_TL721X_DONGLE//BOARD_TL721X_EVK
	#define CLOCK_SYS_CLOCK_HZ  					120000000
#else
	#error "MCU is undefined!"
#endif

/* Board include */
#if (BOARD == BOARD_8258_DONGLE)
	#include "board_8258_dongle.h"
#elif (BOARD == BOARD_8258_EVK_V1P2)
	#include "board_8258_evk_v1p2.h"
#elif (BOARD == BOARD_B91_EVK)
	#include "board_b91_evk.h"
#elif (BOARD == BOARD_B91_DONGLE)
	#include "board_b91_dongle.h"
#elif (BOARD == BOARD_TL321X_EVK)
	#include "board_tl321x_evk.h"
#elif (BOARD == BOARD_TL321X_DONGLE)
	#include "board_tl321x_dongle.h"
#elif (BOARD == BOARD_TL721X_EVK)
	#include "board_tl721x_evk.h"
#elif (BOARD == BOARD_TL721X_DONGLE)
	#include "board_tl721x_dongle.h"
#endif


/* Voltage detect module */
/* If VOLTAGE_DETECT_ENABLE is set,
 * 1) if MCU_CORE_826x is defined, the DRV_ADC_VBAT_MODE mode is used by default,
 * and there is no need to configure the detection IO port;
 * 2) if MCU_CORE_8258 or MCU_CORE_8278 is defined, the DRV_ADC_VBAT_MODE mode is used by default,
 * we need to configure the detection IO port, and the IO must be in a floating state.
 * 3) if MCU_CORE_B91 is defined, the DRV_ADC_BASE_MODE mode is used by default,
 * we need to configure the detection IO port, and the IO must be connected to the target under test,
 * such as VCC.
 */
#define VOLTAGE_DETECT_ENABLE						0
#define VOLTAGE_SAFETY_THRESHOLD                    2200

/* Flash protect module */
/* Only the firmware area will be locked, the NV data area will not be locked.
 * For details, please refer to drv_flash.c file.
 */
#define FLASH_PROTECT_ENABLE						1

/**********************************************************************
 * EV configuration
 */
typedef enum{
	EV_POLL_ED_DETECT,
	EV_POLL_FACTORY_RST,
	EV_POLL_HCI,
    EV_POLL_IDLE,
	EV_POLL_MAX,
}ev_poll_e;

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
