/********************************************************************************************************
 * @file     app_ui.h
 *
 * @brief    application UI header
 *
 * @author
 * @date     Dec. 1, 2016
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
#ifndef _APP_PM_H_
#define _APP_PM_H_

/**********************************************************************
 * CONSTANT
 */
void app_pm_init(void);

void app_pm_task(void);

u8 app_zigbeeIdle(void);

void app_zigbeePollRateRecovery(void);

#endif	/* _APP_PM_H_ */
