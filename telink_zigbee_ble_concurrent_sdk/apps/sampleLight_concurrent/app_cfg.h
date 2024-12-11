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
 * Product Information
 */
#define ZIGBEE_BLE_MODE								1


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
#define VOLTAGE_DETECT_ADC_PIN						VOLTAGE_DETECT_PIN

/* Watch dog module */
#define MODULE_WATCHDOG_ENABLE						0

/* PA */
#define PA_ENABLE						0

/**********************************************************************
 * BLE configuration
 */
#include "version_cfg.h"

#define ACL_CENTRAL_MAX_NUM							1 // ACL central maximum number
#define ACL_PERIPHR_MAX_NUM							1 // ACL peripheral maximum number

///////////////////////// Feature Configuration////////////////////////////////////////////////
#define ACL_PERIPHR_SMP_ENABLE						1  //1 for smp,  0 no security
#define ACL_CENTRAL_SMP_ENABLE						0  //1 for smp,  0 no security
#define BLE_OTA_SERVER_ENABLE						0

#define BLE_APP_PM_ENABLE							0

#define BLC_PM_DEEP_RETENTION_MODE_EN				0
///////////////////////// OS settings /////////////////////////////////////////////////////////
#define FREERTOS_ENABLE								0
#define OS_SEPARATE_STACK_SPACE						1   //Separate the task stack and interrupt stack space


///////////////////////// UI Configuration ////////////////////////////////////////////////////

///////////////////////// DEBUG  Configuration ////////////////////////////////////////////////
#define DEBUG_GPIO_ENABLE							0

#define TLKAPI_DEBUG_ENABLE							0
#define TLKAPI_DEBUG_CHANNEL         		 		TLKAPI_DEBUG_CHANNEL_GSUART

#define APP_LOG_EN									0
#define APP_FLASH_INIT_LOG_EN						0
#define APP_CONTR_EVT_LOG_EN						0	//controller event
#define APP_HOST_EVT_LOG_EN							0
#define APP_SMP_LOG_EN								0
#define APP_PAIR_LOG_EN								0
#define APP_KEY_LOG_EN								0



/**********************************************************************
 * Zigbee configuration
 */
#define TEST_FOR_CERTIFICATION			0

/* Debug mode config */
#define	UART_PRINTF_MODE				1//0
#define USB_PRINTF_MODE         		0


/* HCI interface */
#define	ZBHCI_UART						0
#define ZBHCI_BLE						0

/* RGB or CCT */
#define COLOR_RGB_SUPPORT				1
#define COLOR_CCT_SUPPORT				0

/* BDB */
#define TOUCHLINK_SUPPORT				1
#define FIND_AND_BIND_SUPPORT			0


/* UART module */
#if ZBHCI_UART
#define	MODULE_UART_ENABLE							1
#endif

#if (ZBHCI_USB_PRINT || ZBHCI_USB_CDC || ZBHCI_USB_HID || ZBHCI_UART)
	#define ZBHCI_EN								1
#endif


/**********************************************************************
 * ZCL cluster support setting
 */
#define ZCL_ON_OFF_SUPPORT							1
#define ZCL_LEVEL_CTRL_SUPPORT						1
#if (COLOR_RGB_SUPPORT || COLOR_CCT_SUPPORT)
#define ZCL_LIGHT_COLOR_CONTROL_SUPPORT				1
#endif
#define ZCL_GROUP_SUPPORT							1
#define ZCL_SCENE_SUPPORT							1
#define ZCL_OTA_SUPPORT								0
#define ZCL_GP_SUPPORT								0
#define ZCL_WWAH_SUPPORT							0
#if TOUCHLINK_SUPPORT
#define ZCL_ZLL_COMMISSIONING_SUPPORT				1
#endif

#define AF_TEST_ENABLE								0



/**********************************************************************
 * Stack configuration
 */
#include "stack_cfg.h"

/**********************************************************************
 * EV configuration
 */
typedef enum{
	EV_POLL_ED_DETECT,
	EV_POLL_HCI,
    EV_POLL_IDLE,
	EV_POLL_MAX,
}ev_poll_e;


/* Board ID */
#define BOARD_B92_EVK					9
#define BOARD_B92_DONGLE				10

/* Board define */
#if defined(MCU_CORE_B92)
	#if DUAL_MODE_WITH_MATTER
		#define FLASH_CAP_SIZE_4M		1
	#else
		#define FLASH_CAP_SIZE_1M		1
	#endif
	#define BOARD						BOARD_B92_EVK//BOARD_B92_DONGLE
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


extern unsigned int  tlk_flash_mid;
extern unsigned int  tlk_flash_vendor;
extern unsigned char tlk_flash_capacity;

/* Disable C linkage for C++ Compilers: */
#if defined(__cplusplus)
}
#endif
