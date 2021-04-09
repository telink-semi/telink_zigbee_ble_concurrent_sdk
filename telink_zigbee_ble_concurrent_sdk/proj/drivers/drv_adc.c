/********************************************************************************************************
 * @file	drv_adc.c
 *
 * @brief	This is the source file for drv_adc
 *
 * @author	Zigbee Group
 * @date	2019
 *
 * @par     Copyright (c) 2019, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions
 *              in binary form must reproduce the above copyright notice, this list of
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *
 *              3. Neither the name of TELINK, nor the names of its contributors may be
 *              used to endorse or promote products derived from this software without
 *              specific prior written permission.
 *
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or
 *              relating to such deletion(s), modification(s) or alteration(s).
 *
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************************************/
#include "../tl_common.h"

#if	defined(MCU_CORE_826x)
	#define ADC_VALUE_GET_WITH_BASE_MODE(v)		(3300 * (v - 128)/(16384 - 256))//Vref(mV) * (v - 128)/(2^14 - 2^8)
	#define ADC_VALUE_GET_WITH_VBAT_MODE(v)		(3*(1428*(v - 128)/(16384 - 256)))
#endif


/****
* brief: ADC initiate function
* param[in] null
*
* @return	  1: set success ;
*             0: set error
*/
bool drv_adc_init(void)
{
#if	defined(MCU_CORE_826x)
	ADC_Init();
	AUDIO2ADC();
#elif defined(MCU_CORE_8258) || defined(MCU_CORE_8278)
	adc_init();
#endif
	return TRUE;
}

/****
* brief: get the sample data
* param[in] null
* @return,the result
*/
u16 drv_get_adc_data(void)
{
#if defined(MCU_CORE_826x)
	u32 tmpSum = 0;
	for(u8 i = 0; i < 8; i++){
		tmpSum += ADC_SampleValueGet();
	}
	tmpSum /= 8;
	if(tmpSum < 128){
		tmpSum = 128;
	}
	return (u16)ADC_VALUE_GET_WITH_VBAT_MODE(tmpSum);
#elif defined(MCU_CORE_8258) || defined(MCU_CORE_8278)
	return (u16)adc_sample_and_get_result();
#endif
}

/****
* brief: Set ADC mode and pin
* param[in] mode, base or vbat mode
* param[in] pin, the pin number
* @return
*/
#if defined(MCU_CORE_826x)
void drv_adc_mode_pin_set(drv_adc_mode_t mode, ADC_InputPTypeDef pin)
{
	if(mode == DRV_ADC_BASE_MODE){
		ADC_ParamSetting(pin, SINGLEEND, RV_AVDD, RES14, S_3);
	}else if(mode == DRV_ADC_VBAT_MODE){
		ADC_BatteryCheckInit(Battery_Chn_VCC);
	}
}
#elif defined(MCU_CORE_8258) || defined(MCU_CORE_8278)
void drv_adc_mode_pin_set(drv_adc_mode_t mode, GPIO_PinTypeDef pin)
{
	if(mode == DRV_ADC_BASE_MODE){
		adc_base_init(pin);
	}else if(mode == DRV_ADC_VBAT_MODE){
		adc_vbat_init(pin);
	}
}
#endif

/**
 * @brief      This function sets sar_adc power.
 * @param[in]  enable enable=1 : power on. enable=0: power off.
 * @return     none
 */
void drv_adc_enable(bool enable)
{
#if defined(MCU_CORE_826x)
	if(enable){
		EN_ADCCLK;
	}else{
		DIS_ADCCLK;
	}
#elif defined(MCU_CORE_8258) || defined(MCU_CORE_8278)
	adc_power_on_sar_adc((unsigned char)enable);
#endif
}


