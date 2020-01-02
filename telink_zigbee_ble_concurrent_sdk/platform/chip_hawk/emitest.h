/********************************************************************************************************
 * @file     emitest.h
 *
 * @brief    This file provides set of functions for emi test
 *
 * @author   kaixin.chen@telink-semi.com
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
#ifndef EMITEST_H_
#define EMITEST_H_
/**
*	@brief		This function must be invoked before EMI test. It serves to record
*				related parameters before test.
*   @param      none
*	@return		none
*/
extern void RF_EmiInit(void);
/**
*	@brief		This function is used for carrier mode during EMI test. 
*				The "RF_Init" and "RF_EmiInit" should be invoked before
*				this function is invoked.
*
*	@param[in]	PowerLevel   Parameter type is enum.
*	@param[in]	RF_Channel   Unit is MHz. The frequency is set as
*							(2400 + RF_Channel) MHz.(0~100)
*
*	@return		none
*/
extern void	RF_EmiCarrierOnlyTest(enum M_RF_POWER PowerLevel,signed char RF_Channel);
/**
*	@brief		This function is used for CD (Carrier + Data) mode during EMI test. 
*				The "RF_EmiDataUpdate" should be invoked to continuously update data
*				on carrier which are a sequence of random numbers.
*				The "RF_Init" and "RF_EmiInit" should be invoked before
*				this function is invoked.
*
*	@param[in]	PowerLevel   Parameter type is enum.
*	@param[in]	RF_Channel   Unit is MHz. The frequency is set as (2400 + RF_Channel) MHz.(0~100)
*
*	@return		none
*/
extern void	RF_EmiCarrierDataTest(enum M_RF_POWER PowerLevel,signed char RF_Channel);
/**
*	@brief		This function serves to update data (random number) on carrier,
*				and it should follow the “RF_EmiCarrierDataTest” function.
*				Example:
*				RF_EmiCarrierDataTest(power_level,rf_chn);
*				while(1)
*				{
*					RF_EmiDataUpdate();
*				}
*				In actual application, “while(1)” can be replaced by other judging
*				condition to set when to stop updating data on carrier.
*   @param      none
*	@return		none
*/
extern void RF_EmiDataUpdate(void);
/**
*	@brief		This function is used for Rx mode during EMI test. 
*				The "RF_Init" and "RF_EmiInit"should be invoked before
*				this function is invoked.
*
*	@param[in]	Addr   Pointer for Rx buffer in RAM (Generally it’s starting
*						address of an array.Should be 4-byte aligned)
*	@param[in]	RF_Channel        Unit is MHz. The frequency is set as
*							 (2400 + RF_Channel) MHz.(0~100)
*	@param[in]	BufferSize   Rx buffer size(It’s an integral multiple of 16)
*	@param[in]	PingpongEn   Enable/Disable Ping-Pong buffer
*							  1:Enable   0:Disable
*
*	@return		none
*/
extern void RF_EmiRxTest(unsigned char *Addr,signed char RF_Channel,signed char BufferSize,unsigned char  PingpongEn);
/**
*	@brief		This function is initialization interface for Tx mode during EMI test. 
*				The "RF_Init" and "RF_EmiInit" should be invoked before
*				this function is invoked.
*				After Tx mode initialization, the "RF_EmiSingleTx" should be
*				invoked to transmit packets.
*				(Note: Each invoked RF_EmiSingleTx only sends a packet.)
*
*	@param[in]	PowerLevel   Set Tx power level. Parameter type is enum.
*	@param[in]	RF_Channel   Unit is MHz. The frequency is set as
*							(2400 + RF_Channel) MHz.(0~100)
*
*	@return		none
*/
extern void RF_EmiTxInit(enum M_RF_POWER PowerLevel,signed char RF_Channel);
/**
*	@brief		This function is used in combination with the “RF_EmiTxInit” for
*				Tx mode during EMI test. It serves to send a packet.
*
*				Example: 
*				RF_EmiTxInit(power_level,rf_chn);
*				while(1) 
*				{
*					WaitUs(20000);
*					RF_EmiSingleTx(packet);
*				}
*				In actual application, “while(1)” can be replaced by other judging condition.
*
*	@param[in]	Addr    Tx packet address in RAM. Should be 4-byte aligned.
*
*	@return		none
*/
extern void RF_EmiSingleTx(unsigned char *Addr);

#endif /* EMITEST_H_ */
