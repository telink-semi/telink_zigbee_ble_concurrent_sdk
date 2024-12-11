/********************************************************************************************************
 * @file    app_cfg.h
 *
 * @brief   This is the header file for app_cfg
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
#define	UART_PRINTF_MODE				0
#define USB_PRINTF_MODE         		0

/*
 * Enable UART to upgrade image.
 */
#define UART_ENABLE						0//1

/* Board ID */
#define BOARD_B92_EVK					9
#define BOARD_B92_DONGLE				10

/* Board define */
#if defined(MCU_CORE_B92)
	#if DUAL_MODE_WITH_MATTER
		#define FLASH_CAP_SIZE_4M		1
	#else
		#define FLASH_CAP_SIZE_2M		1
	#endif
	#define BOARD						BOARD_B92_EVK//BOARD_B92_DONGLE//BOARD_B92_EVK
	#define CLOCK_SYS_CLOCK_HZ  		48000000
#else
	#error "MCU is undefined!"
#endif

/* Board include */
#if (BOARD == BOARD_B92_EVK)
	#include "board_b92_evk.h"
#elif (BOARD == BOARD_B92_DONGLE)
	#include "board_b92_dongle.h"
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


/* flash write protect */
#define	FLASH_PROTECT_ENABLE                        0

/**********************************************************************
 * EV configuration
 */
typedef enum{
	EV_POLL_UART_PROC,
	EV_POLL_KEY_PRESS,
	EV_POLL_MAX,
}ev_poll_e;

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
