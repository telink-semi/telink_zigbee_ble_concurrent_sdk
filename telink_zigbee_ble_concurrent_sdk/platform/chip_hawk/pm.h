/********************************************************************************************************
 * @file     pm.h
 *
 * @brief    This file provides set of functions for power management module
 *
 * @author   jian.zhang@telink-semi.com
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
#ifndef PM_H
#define PM_H

#include "bsp.h"

enum {
	// WAKEUP_SRC_ANA 0 -- 2  not supported
	 PM_WAKEUP_CORE  = BIT(5),
	 PM_WAKEUP_TIMER = BIT(6),
	 PM_WAKEUP_COMP  = BIT(7),
	 PM_WAKEUP_PAD   = BIT(8),
};

/**
 *  @brief  Define wake up source 
 */
typedef enum {
    WAKEUP_SRC_PAD        = BIT(4),  
    WAKEUP_SRC_DIG_GPIO   = BIT(5) | 0X0800,
    WAKEUP_SRC_DIG_QDEC   = BIT(5) | 0X1000,  //0x6e[4] of 8267 is qdec wakeup enbale bit
    WAKEUP_SRC_TIMER      = BIT(6), 
    WAKEUP_SRC_COMP       = BIT(7), 
} WakeupSrc_TypeDef;

/**
 *  @brief  Define wake up status
 */
typedef enum {
    WAKEUP_STATUS_COMP       = BIT(0),
    WAKEUP_STATUS_TIMER      = BIT(1),  
    WAKEUP_STATUS_DIG        = BIT(2), 
    WAKEUP_STATUS_PAD        = BIT(3),
} WakeupStatus_TypeDef;

/**
 *  @brief  Define low power mode 
 */
enum {
    SUSPEND_MODE    = 0,
    DEEPSLEEP_MODE  = 1,
};

/**
 *  @brief  Define wakeup GPIO pin 
 */
typedef enum{
    GROUPA_PIN0  = 0X000 | BIT(0),
    GROUPA_PIN1  = 0X000 | BIT(1),
    GROUPA_PIN2  = 0X000 | BIT(2),
    GROUPA_PIN3  = 0X000 | BIT(3),
    GROUPA_PIN4  = 0X000 | BIT(4),
    GROUPA_PIN5  = 0X000 | BIT(5),
    GROUPA_PIN6  = 0X000 | BIT(6),
    GROUPA_PIN7  = 0X000 | BIT(7),
    GROUPA_ALL   = 0X000 | 0X00ff,

    GROUPB_PIN0  = 0X100 | BIT(0),
    GROUPB_PIN1  = 0X100 | BIT(1),
    GROUPB_PIN2  = 0X100 | BIT(2),
    GROUPB_PIN3  = 0X100 | BIT(3),
    GROUPB_PIN4  = 0X100 | BIT(4),
    GROUPB_PIN5  = 0X100 | BIT(5),
    GROUPB_PIN6  = 0X100 | BIT(6),
    GROUPB_PIN7  = 0X100 | BIT(7),
    GROUPB_ALL   = 0X100 | 0x00ff,

    GROUPC_PIN0  = 0X200 | BIT(0),
    GROUPC_PIN1  = 0X200 | BIT(1),
    GROUPC_PIN2  = 0X200 | BIT(2),
    GROUPC_PIN3  = 0X200 | BIT(3),
    GROUPC_PIN4  = 0X200 | BIT(4),
    GROUPC_PIN5  = 0X200 | BIT(5),
    GROUPC_PIN6  = 0X200 | BIT(6),
    GROUPC_PIN7  = 0X200 | BIT(7),
    GROUPC_ALL   = 0X200 | 0x00ff,

    GROUPD_PIN0  = 0X300 | BIT(0),
    GROUPD_PIN1  = 0X300 | BIT(1),
    GROUPD_PIN2  = 0X300 | BIT(2),
    GROUPD_PIN3  = 0X300 | BIT(3),
    GROUPD_PIN4  = 0X300 | BIT(4),
    GROUPD_PIN5  = 0X300 | BIT(5),
    GROUPD_PIN6  = 0X300 | BIT(6),
    GROUPD_PIN7  = 0X300 | BIT(7),
    GROUPD_ALL   = 0X300 | 0x00ff,

    GROUPE_PIN0  = 0X400 | BIT(0),
    GROUPE_PIN1  = 0X400 | BIT(1),
    GROUPE_PIN2  = 0X400 | BIT(2),
    GROUPE_PIN3  = 0X400 | BIT(3),
    GROUPE_ALL   = 0X400 | 0x000f,
} Pin_TypeDef;

/**
 * @brief      This function configures pad wakeup select.
 * @param[in]  st  - enable or disable the 16us filter(1: Enable, 0: Disable)
 * @return     none
 */
extern void PM_FilterEN(unsigned char st);

/**
 * @brief      This function configures a pad pin as the wakeup pin.
 * @param[in]  Pin - the pin needs to be configured as wakeup pin
 * @param[in]  Pol - the wakeup polarity of the pad pin(0: low-level wakeup, 1: high-level wakeup)
 * @param[in]  En  - enable or disable the wakeup function for the pan pin(1: Enable, 0: Disable) 
 * @return     none
 */
extern void PM_PadSet(Pin_TypeDef Pin, int Pol, int En);

/**
 * @brief      This function configures a GPIO pin as the wakeup pin.
 * @param[in]  Pin - the pin needs to be configured as wakeup pin
 * @param[in]  Pol - the wakeup polarity of the pad pin(0: low-level wakeup, 1: high-level wakeup)
 * @param[in]  En  - enable or disable the wakeup function for the pan pin(1: Enable, 0: Disable) 
 * @return     none
 */
extern void PM_GPIOSet(Pin_TypeDef Pin, int Pol, int En);

/**
 * @brief   This function serves to initialize the related analog registers
 *          to default values after MCU is waked up from deep sleep mode.
 * @param   none
 * @return  none
 */
extern void PM_WakeupInit(void);

/**
 * @brief      This function makes the MCU actually enter low power mode.
 * @param[in]  DeepSleep - set whether to enter deep sleep mode(1: enter deep sleep, 0: enter suspend)
 * @param[in]  WakeupSrc - set wakeup source
 * @param[in]  WakeupTick-  set the tick value of System_Timer at the wakeup moment when 
 *             32k Timer is set as a wakeup source 
 * @return     sources that wake the MCU up from low power mode
 */
extern int PM_LowPwrEnter(int DeepSleep, int WakeupSrc, unsigned long WakeupTick); 

/**
 * @brief  This function return the source mask that wakeup the low power mode.
 * @param  none
 * @return sources that wake the MCU up from low power mode
 */
extern unsigned char PM_WakeUpStatusGet(void);

/**
 * @brief  This function clear the wakeup source status register
 * @param  none
 * @return sources that wake the MCU up from low power mode
 */
extern void PM_WakeUpStatusClear(unsigned char Mask); 

/**
 * @brief   This function serves to enable the 32k external crystal as source of 32K Timer. 
 * @param   none
 * @return  none
 */
extern void PM_32kPadEnable(void);


#endif //PM_H
