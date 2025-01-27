/********************************************************************************************************
 * @file    drv_hw.c
 *
 * @brief   This is the source file for drv_hw
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

/*
 * system clock configuration
 */
#if defined(MCU_CORE_8258)
    #if (CLOCK_SYS_CLOCK_HZ == 24000000)
        #define SYS_CLOCK_VALUE    SYS_CLK_24M_Crystal
    #elif (CLOCK_SYS_CLOCK_HZ == 16000000)
        #define SYS_CLOCK_VALUE    SYS_CLK_16M_Crystal
    #elif (CLOCK_SYS_CLOCK_HZ == 48000000)
        #define SYS_CLOCK_VALUE    SYS_CLK_48M_Crystal
    #else
        #error please config system clock
    #endif
#elif defined(MCU_CORE_B91)
    #if (CLOCK_SYS_CLOCK_HZ == 48000000)
        #define CLOCK_INIT         CCLK_48M_HCLK_48M_PCLK_24M
    #else
        #error please config system clock
    #endif
#elif defined(MCU_CORE_TL721X)
    #if (CLOCK_SYS_CLOCK_HZ == 120000000)
        #define CLOCK_INIT         PLL_240M_CCLK_120M_HCLK_60M_PCLK_60M_MSPI_48M
    #else
        #error please config system clock
    #endif
#elif defined(MCU_CORE_TL321X)
    #if (CLOCK_SYS_CLOCK_HZ == 96000000)
        #define CLOCK_INIT         PLL_192M_CCLK_96M_HCLK_48M_PCLK_24M_MSPI_48M
    #else
        #error please config system clock
    #endif
#endif

//system ticks per US
u32 sysTimerPerUs;

static void randInit(void)
{
#if defined(MCU_CORE_8258)
    random_generator_init();
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
    trng_init();
#endif
}

/*********************************************************************
 * @fn      internalFlashSizeCheck
 *
 * @brief   This function is provided to get and update to the correct flash address
 * 			where are stored the right MAC address and pre-configured parameters.
 * 			NOTE: It should be called before ZB_RADIO_INIT().
 *
 * @param   None
 *
 * @return  None
 */
static void internalFlashSizeCheck(void){
#if defined(MCU_CORE_8258) || defined(MCU_CORE_B91) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
#if defined(MCU_CORE_TL721X)
    u32 mid = flash_read_mid_with_device_num(SLAVE0);
#else
    u32 mid = flash_read_mid();
#endif

    u8 *pMid = (u8 *)&mid;

    if ((pMid[2] < FLASH_SIZE_512K) || \
        ((g_u32MacFlashAddr == FLASH_ADDR_OF_MAC_ADDR_1M) && (pMid[2] < FLASH_SIZE_1M)) || \
        ((g_u32MacFlashAddr == FLASH_ADDR_OF_MAC_ADDR_2M) && (pMid[2] < FLASH_SIZE_2M)) || \
        ((g_u32MacFlashAddr == FLASH_ADDR_OF_MAC_ADDR_4M) && (pMid[2] < FLASH_SIZE_4M))) {
        /* Flash space not matched. */
        while(1);
    }

    switch(pMid[2]){
        case FLASH_SIZE_1M:
            g_u32MacFlashAddr = FLASH_ADDR_OF_MAC_ADDR_1M;
            g_u32CfgFlashAddr = FLASH_ADDR_OF_F_CFG_INFO_1M;
            break;
        case FLASH_SIZE_2M:
            g_u32MacFlashAddr = FLASH_ADDR_OF_MAC_ADDR_2M;
            g_u32CfgFlashAddr = FLASH_ADDR_OF_F_CFG_INFO_2M;
            break;
        case FLASH_SIZE_4M:
            g_u32MacFlashAddr = FLASH_ADDR_OF_MAC_ADDR_4M;
            g_u32CfgFlashAddr = FLASH_ADDR_OF_F_CFG_INFO_4M;
            break;
        default:
            break;
    }
#endif
}

#if VOLTAGE_DETECT_ENABLE || defined(MCU_CORE_8258)
static void voltage_detect_init(u32 detectPin)
{
    drv_adc_init();

#if defined(MCU_CORE_8258)
    drv_adc_mode_pin_set(DRV_ADC_VBAT_MODE, (GPIO_PinTypeDef)detectPin);
#elif defined(MCU_CORE_B91)
    drv_adc_mode_pin_set(DRV_ADC_BASE_MODE, (adc_input_pin_def_e)detectPin);
#elif defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
    drv_adc_mode_pin_set(DRV_ADC_BASE_MODE, (adc_input_pch_e)detectPin);
#endif

    drv_adc_enable(1);
    WaitUs(100);
}
#endif

#if VOLTAGE_DETECT_ENABLE
#define VOLTAGE_DEBOUNCE_NUM    5
u16 voltage_detect(bool powerOn, u16 volThreshold)
{
    u16 voltage = drv_get_adc_data();
    u32 curTick = clock_time();
    s32 debounceNum = VOLTAGE_DEBOUNCE_NUM;
    u16 v_min = 0;

    //printf("VDD: %d\n", voltage);
    if(powerOn || voltage <= volThreshold){
        while(debounceNum > 0){
            WaitUs(100);
            voltage = drv_get_adc_data();
            if(voltage > volThreshold){
                debounceNum--;
            }else{
                debounceNum = VOLTAGE_DEBOUNCE_NUM;
                v_min = voltage;
            }

            if(clock_time_exceed(curTick, 1000 * 1000)){
                return v_min;
            }
        }
    }

    return voltage;
}
#endif

static startup_state_e platform_wakeup_init(void)
{
    startup_state_e state = SYSTEM_BOOT;

#if defined(MCU_CORE_8258)
    cpu_wakeup_init();
#elif defined(MCU_CORE_B91)
    sys_init(DCDC_1P4_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M);
#elif defined(MCU_CORE_TL721X)
#if (BLE_APP_PM_ENABLE || PM_ENABLE)
    blc_pm_select_internal_32k_crystal();   //for ble
#endif
    sys_init(LDO_0P94_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M);
#elif defined(MCU_CORE_TL321X)
#if (BLE_APP_PM_ENABLE || PM_ENABLE)
    blc_pm_select_internal_32k_crystal();   //for ble
#endif
    sys_init(DCDC_1P25_LDO_1P8, VBAT_MAX_VALUE_GREATER_THAN_3V6, INTERNAL_CAP_XTAL24M);
#endif

#if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
    wd_32k_stop();
    wd_stop();
#endif

#if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
    pm_update_status_info(1);
#endif

#if defined(MCU_CORE_8258)
    state = (startup_state_e)pm_get_mcu_status();
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
    if (g_pm_status_info.mcu_status == MCU_STATUS_DEEPRET_BACK) {
        state = SYSTEM_DEEP_RETENTION;
    } else if (g_pm_status_info.mcu_status == MCU_STATUS_DEEP_BACK) {
        state = SYSTEM_DEEP;
    }
#endif

    return state;
}

/****************************************************************************************************
* @brief 		platform initialization function
*
* @param[in] 	none
*
* @return	  	startup_state_e.
*/
startup_state_e drv_platform_init(void)
{
    startup_state_e state = platform_wakeup_init();

#if defined(MCU_CORE_8258)
    clock_init(SYS_CLOCK_VALUE);
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
    CLOCK_INIT;
#endif

    /* Get system ticks per US, must be after the clock is initialized. */
#if defined(MCU_CORE_8258)
    sysTimerPerUs = sys_tick_per_us;
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
    sysTimerPerUs = SYSTEM_TIMER_TICK_1US;
#endif

    gpio_init(TRUE);

#if (TLKAPI_DEBUG_ENABLE)
    DEBUG_TX_PIN_INIT();
#endif

    if (state != SYSTEM_DEEP_RETENTION) {
        randInit();
        internalFlashSizeCheck();

#if FLASH_PROTECT_ENABLE
        flash_loadOpt();
        flash_lock();
#endif

#if PM_ENABLE
        PM_CLOCK_INIT();
#endif
    } else {
#if PM_ENABLE
        drv_pm_wakeupTimeUpdate();
#endif
    }

    /* Get calibration info to improve performance */
    drv_calibration();

#if VOLTAGE_DETECT_ENABLE
    voltage_detect_init(VOLTAGE_DETECT_ADC_PIN);
#endif

#if defined(MCU_CORE_TL721X) || defined(MCU_CORE_TL321X)
    /* AES enable after clock_init */
    ske_dig_en();
#endif

#if defined(MCU_CORE_8258)
    if (flash_is_zb()) {
#if (!VOLTAGE_DETECT_ENABLE) || !defined(VOLTAGE_DETECT_ENABLE)
        voltage_detect_init(VOLTAGE_DETECT_ADC_PIN);
#endif
        flash_safe_voltage_set(VOLTAGE_SAFETY_THRESHOLD);
        flash_unlock_mid13325e();  //add it for the flash which sr is expired
    }
#endif

    ZB_RADIO_INIT();

    //ZB_TIMER_INIT();

    return state;
}

void drv_enable_irq(void)
{
#if defined(MCU_CORE_8258)
    irq_enable();
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
    core_interrupt_enable();
#endif
}

_attribute_ram_code_ u32 drv_disable_irq(void)
{
#if defined(MCU_CORE_8258)
    return (u32)irq_disable();
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
    return core_interrupt_disable();
#endif
}

_attribute_ram_code_ u32 drv_restore_irq(u32 en)
{
#if defined(MCU_CORE_8258)
    irq_restore((u8)en);
    return 0;
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
    return core_restore_interrupt(en);
#endif
}

void drv_wd_setInterval(u32 ms)
{
    wd_set_interval_ms(ms);
}

void drv_wd_start(void)
{
    wd_start();
}

void drv_wd_clear(void)
{
    wd_clear();
}

u32 drv_u32Rand(void)
{
#if defined(MCU_CORE_8258)
    return rand();
#elif defined(MCU_CORE_B91) || defined(MCU_CORE_TL321X) || defined(MCU_CORE_TL721X)
    return trng_rand();
#else
    return 0;
#endif
}

void drv_generateRandomData(u8 *pData, u8 len)
{
    u32 randNums = 0;
    /* if len is odd */
    for (u8 i = 0; i < len; i++) {
        if ((i & 3) == 0) {
            randNums = drv_u32Rand();
        }

        pData[i] = randNums & 0xff;
        randNums >>= 8;
    }
}
