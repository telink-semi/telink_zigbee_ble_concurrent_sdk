/********************************************************************************************************
 * @file     user_config.c
 *
 * @brief    User build configuration
 *
 * @author
 * @date     Feb. 1, 2017
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
#pragma once

#if (__PROJECT_TL_CONCURRENT_LIGHT__)
    #include "../sample_concurrentLight/app_cfg.h"
#elif (__PROJECT_TL_CONCURRENT_GW__)
    #include "../sample_concurrentGw/app_cfg.h"
#elif (__PROJECT_TL_CONCURRENT_SWITCH__)
    #include "../sample_concurrentSwitch/app_cfg.h"
#else

#endif


