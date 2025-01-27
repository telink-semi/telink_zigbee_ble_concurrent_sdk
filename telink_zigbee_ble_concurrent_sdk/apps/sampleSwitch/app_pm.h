
/********************************************************************************************************
 * @file    app_pm.h
 *
 * @brief   This is the header file for app_pm
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

#ifndef _APP_PM_H_
#define _APP_PM_H_

/**********************************************************************
 * CONSTANT
 */
extern drv_pm_pinCfg_t g_switchPmCfg[];

void app_pm_init(void);
void app_pm_task(void);
void app_pm_wakeupPinCfg(void);
u8 app_zigbeeIdle(void);
void app_zigbeePollRateRecovery(void);

/*
 * in order to protect battery, force the system to enter cut-off mode once the battery voltage is too low
 * in this mode, the chip stay low power mode until changing a new battery
 * */
void app_enterCutOffMode(void);

#endif  /* _APP_PM_H_ */
