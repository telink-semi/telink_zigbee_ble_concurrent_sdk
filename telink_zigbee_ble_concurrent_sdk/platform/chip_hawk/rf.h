/********************************************************************************************************
 * @file     rf.h
 *
 * @brief    This file provides set of functions for RF module
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
#ifndef		RF_H
#define     RF_H
/**
 *  @brief  Define crystal,Currently only supports RF_OSC_12M
 */
typedef enum {
  RF_OSC_16M = 0,  
  RF_OSC_12M = 1
} RF_OscSelTypeDef;
/**
 *  @brief  Define RF mode
 */
typedef enum {
	 RF_MODE_BLE_2M = 0,
	 RF_MODE_BLE_1M = 1,
	 RF_MODE_ZIGBEE_250K = 2,
	 RF_MODE_NORDIC_1M = 3,
	 RF_MODE_NORDIC_2M = 4,
	 RF_MODE_STANDARD_BLE_1M =5
} RF_ModeTypeDef;
/**
 *  @brief  Define RF state
 */
typedef enum {
  RF_MODE_TX = 0,
  RF_MODE_RX = 1,
  RF_MODE_AUTO=2
} RF_StatusTypeDef;
/**
 *  @brief  Define RF Tx power level
 */
typedef enum {
	RF_POWER_11P8dBm	= 0,
	RF_POWER_9P6dBm		= 1,
	RF_POWER_7P9dBm		= 2,
	RF_POWER_6P3dBm		= 3,
	RF_POWER_4P9dBm		= 4,
	RF_POWER_3P3dBm		= 5,
	RF_POWER_1P6dBm		= 6,
	RF_POWER_0dBm		= 7,
	RF_POWER_m1P5dBm	= 8,
	RF_POWER_m3P1dBm	= 9,
	RF_POWER_m5dBm		= 10,
	RF_POWER_m7P3dBm	= 11,
	RF_POWER_m9P6dBm	= 12,
	RF_POWER_m11P5dBm	= 13,
	RF_POWER_m13P3dBm	= 14,
	RF_POWER_m16dBm		= 15,
	RF_POWER_m17P8dBm	= 16,
	RF_POWER_m19P5dBm	= 17,
	RF_POWER_OFF		= 18
} RF_PowerTypeDef;

/**
 *  ble
 */
#define		RF_BLE_PACKET_LENGTH_OK(p)		(p[0] == (p[13]&0x3f)+17)
#define		RF_BLE_PACKET_CRC_OK(p)			((p[p[0]+3] & 0x51) == 0x40)
/**
 *  zigbee
 */
#define		RF_ZIGBEE_PACKET_LENGTH_OK(p)   (p[0] == p[12]+13)
#define		RF_ZIGBEE_PACKET_CRC_OK(p)	    ((p[p[0]+3] & 0x51) == 0x10)


RF_ModeTypeDef   g_RFMode;
/**
*	@brief		This function should be invoked first,before the “RF_TrxStateSet”
*				is invoked
*
*	@param[in]	OscSel   enum variable of external crystal RF_OSC_16M/RF_OSC_12M
*	@param[in]	RF_Mode      enum variable of RF mode
*	@return		1 :set success;
*               0 :parameters set error
*/
extern	int	 RF_Init(RF_ModeTypeDef RF_Mode);

/**
*	@brief		This function serves to switch RF mode. After this function is
*				invoked, the “RF_TrxStateSet” and “RF_BaseBandReset” should be
*				invoked, as shown below:
*				RF_ModeSet(RF_MODE_BLE_1M);
*		   		RF_TrxStateSet(RF_MODE_TX,20);
*		   		WaitUs(150);//wait pllclock
*		 		RF_BaseBandReset();
*
*	@param[in]	RF_Mode   Set working mode for RF module
*	@return	 	0 :set success;
*              -1 :parameters set error
*/
extern	int RF_ModeSet(RF_ModeTypeDef RF_Mode);

/**
*	@brief	 This function is used during RF mode switch to reset Baseband. 
*   @param   none
*	@return	 none
*/
extern void RF_BaseBandReset (void);

/**
*	@brief	  	This function is to set Rf channel and state(rx/tx/auto),After
*				this function is invoked and state is rx or tx,a 100us~150us
*				delay is needed to lock PLL. Then it’s ready to carry out packet
*				Rx/Tx operations.
*
*	@param[in]	RF_Status - set current status for RF module(tx/rx/auto),
*						  Note: When the “RF_Status” is set as auto mode, the functions
*						  “RF_StartStx”, “RF_StartStxToRx” and “RF_StartSrxToTx”
*						  can be used.
*	@param[in]	RF_Status - Unit is MHz.
*						  The frequency is set as (2400+ channel) MHz.(0~100)
*						  Note: It should be set as the same value for Rx and Tx
*						  terminal.
*	@return	 	0 :set success; 
*              -1 :parameters set error
*/
extern  int  RF_TrxStateSet(RF_StatusTypeDef RF_Status, signed char RF_Channel);
/********************************************************************************
*   @brief      This function is to get the current state of the RF transceiver
*
*   @param[in]  None
*   @return     RF_StatusTypeDef
*/
extern RF_StatusTypeDef RF_TrxStateGet(void);
/********************************************************************************
*	@brief	  	This function is to send packet 
*
*	@param[in]	RF_TxAddr   Tx packet address in RAM. Should be 4-byte aligned.
*					  		 The format for Tx packet in RAM is shown as below:
*					 		(“length” indicates data length, “data” indicates data
*					 		 to be transmitted.)
*	BLE (1M, 2M) mode					Zigbee (250K) mode, Private (2M) mode
*	addr			length+2				addr				Length+1
*	addr+1				0					addr+1					0
*	addr+2				0					addr+2					0
*	addr+3				0					addr+3					0
*	addr+4				0					addr+4				Length+2
*	addr+5			length					addr+5				data(0)
*	addr+6			data(0)					addr+6				data(1)
*	addr+7			data(1)					addr+7				data(2)
*	…	…									…	…
*	addr+5+(length)	data(length-1)			addr+4+(length)		data(length-1)
*					
*	@return	 	none
*/
extern  void RF_TxPkt (unsigned char* RF_TxAddr);

/**
*	@brief	  	Check if all packet data are sent. 
*
*	@return	 	0x00: Packet Tx is not finished yet;
*				0x02: Packet Tx is finished.
*/
extern unsigned char  RF_TxFinish(void);

/**
*	@brief	  	This function serves to clear the Tx finish flag bit.
*				After all packet data are sent, corresponding Tx finish flag bit
*				will be set as 1.By reading this flag bit, it can check whether
*				packet transmission is finished. After the check, it’s needed to
*				manually clear this flag bit so as to avoid misjudgment.
*   @param      none
*	@return	 	none
*/
extern void RF_TxFinishClearFlag (void);

/**
*	@brief	  	This function is to select Tx power level. Parameter type is enum. 
*
*	@param[in]	RF_TxPowerLevel   select Tx power level
*
*	@return	 	none
*/
extern	void RF_PowerLevelSet(RF_PowerTypeDef RF_TxPowerLevel);

/**
*	@brief	  	This function is to set rx buffer
*
*	@param[out]	RF_RxAddr  	Pointer for Rx buffer in RAM(Generally it’s starting
*							address of an array.Should be 4-byte aligned)
*	@param[in]	Size   		Rx buffer size (It’s an integral multiple of 16)
*	@param[in]	PingpongEn 	Enable/Disable Ping-Pong buffer 1：Enable 0：Disable
*							Note:
*							When “PingpongEn” is set as 0, received RF data will
*							be stored in RAM pointed by “ RF_RxAddr”.
*							When “PingpongEn” is set as 1, received RF data will
*							be stored in buffer0 and buffer1 successively.
*							The RAM size reserved for received RF data should be
*							double of “Size”.
*
*	@return	 	none
*/
extern void  RF_RxBufferSet(unsigned char *  RF_RxAddr, int Size, unsigned char  PingpongEn);

/**
*	@brief	  	This function is to get rx buffer result
*
*	@return	 	0:There are received RF data in buffer 0;
*				1:There are received RF data in buffer 1; 
*				2:No RF data is received.
*/
extern unsigned char RF_RxBufferRequest(void);

/**
*	@brief	  	This function serves to clear the flag bit for Rx buffer.
*				After RF data are received, flag bits will be generated for
*				buffer 0 and buffer 1.By reading corresponding flag bit, it can
*				check whether RF Rx event occurs.After the received data
*				are processed, it’s needed to clear flag bits for buffer 0
*				and buffer 1,so as to avoid regarding the old data as new by mistake.

*	@param[in]	RF_RxBufferIdx   0:buffer0  1:buffer1
*
*	@return	 	none
*/
extern void  RF_RxBufferClearFlag(unsigned char  RF_RxBufferIdx);

/**
*	@brief	  	This function serves to start STX mode of auto_mode.
*				This mode will end after a packet is transmitted.
*
*	@param[in]	RF_TxAddr   Tx packet address in RAM. Should be 4-byte aligned.
*	@param[in]	RF_StartTick  Tick value of system timer. It determines when to
*						  	  start STX mode and send packet.
*	@return	 	none
*/
extern void RF_StartStx  (unsigned char* RF_TxAddr,unsigned int RF_StartTick);

/**
*	@brief	  	This function serves to start Srx mode of auto_mode. In this mode,
*				RF module stays in Rx status until a packet is received or it fails to receive packet when timeout expires. 
*				Timeout duration is set by the parameter "RF_RxTimeoutUs". 
*				The address to store received data is set by the function “RF_RxBufferSet”.
*
*	@param[in]	tick   		  	 Tick value of system timer. It determines when to start Srx mode.
*	@param[in]	timeout_us   	 Unit is us. It indicates timeout duration in Rx status.Max value: 0xffffff (16777215)  
*
*	@return	 	none
*/
extern void RF_StartSrx(unsigned int RF_StartTick,unsigned int RF_RxTimeoutUs);

/**
*	@brief	  	This function serves to start StxToRx mode of auto_mode.
*				In this mode, a packet is sent first,RF module waits for 10us,
*				stays in Rx status until data is received or timeout expires,
*				then exits this mode.Timeout duration is set by the parameter
*				“RF_RxTimeoutUs”.The address to store received data is set by the
*				function “RF_RxBufferSet”.
*
*	@param[in]	RF_TxAddr  Tx packet address in RAM. Should be 4-byte aligned.
*	@param[in]	RF_StartTick   	Tick value of system timer. It determines when
*								to start StxToRx mode and send packet.
*	@param[in]	RF_RxTimeoutUs  Unit is us. It indicates timeout duration in
*							 	Rx status.Max value: 0xfff (4095)
*
*	@return	 	none
*/
extern void RF_StartStxToRx  ( unsigned char* RF_TxAddr ,unsigned int RF_StartTick,unsigned short RF_RxTimeoutUs);

/**
*	@brief	  	This function serves to start SrxToTx mode of auto_mode.
*				In this mode,RF module stays in Rx status until a packet is
*				received or it fails to receive packetwhen timeout expires.
*				If a packet is received within the timeout duration, RF module
*				will wait for 10us,send a packet, and then exit this mode.
*				If it fails to receive packet when timeout expires, RF module
*				will directly exit this mode.Timeout duration is set by the
*				parameter "RF_RxTimeoutUs".	The address to store received data is set
*				by the function “RF_RxBufferSet”.
*
*	@param[in]	RF_TxAddr 	Tx packet address in RAM. Should be 4-byte aligned.
*	@param[in]	RF_StartTick   Tick value of system timer. It determines when to
*								start SrxToTx mode.
*	@param[in]	RF_RxTimeoutUs  Unit is us. It indicates timeout duration in Rx status.
*								Max value: 0xffffff (16777215)
*
*	@return	 	none
*/
extern void RF_StartSrxToTx  (unsigned char* RF_TxAddr  ,unsigned int RF_StartTick,unsigned int RF_RxTimeoutUs);

/**
*	@brief	  	Set index number of access_code channel for RF Tx terminal. 
*
*	@param[in]	RF_TxPipeIdx  	Optional range: 0~5
*
*	@return	 	none
*/
extern void RF_TxAccessCodeSelect (unsigned char RF_TxPipeIdx);

/**
*	@brief	  	this function is to set access code of 0/1 channel 
*
*	@param[in]	RF_PipeIdx  	Set index number for access_code channel (only 0 or 1)
*	@param[in]	RF_AccessCode  	Set 3~5 bytes access_code value (should be consistent
*								with “length”)
*								Note: Access_code configuration is determined by
*								algorithm, random configuration may influence
*								RF Rx/Tx performance.
*
*	@return	 	none
*/
extern void RF_AccessCodeSetting01 (unsigned char RF_PipeIdx,unsigned long long  RF_AccessCode);

/**
*	@brief	  	this function is to set access code of 2/3/4/5 channel 
*
*	@param[in]	RF_PipeIdx  	Set index number for access_code channel (only 2~5).
*	@param[in]	Prefix  Set 1-byte prefix of access_code.
*						Note:When this function is invoked, the
*						“RF_AccessCodeSetting01” should also be	invoked to set
*						access_code1 for channel 1.	Following is an example to
*						set access_code2 for channel 2.
*						//set access_code length as 5 bytes
*						RF_AccessCodeLengthSetting (5);
*						RF_AccessCodeSetting01 (1, 0x1122334455);
*						RF_AccessCodeSetting2345 (2, 0x66);
*						By the configuration above, the access_code value for
*						channel 2 (i.e. access_code2)is set as “0x1122334466”
*						(Former 4 bytes are higher 4 bytes of access_code1,
*						while the final byte is obtained from the
*						“AccessCodeSetting2345” function).	The “RF_AccessCodeSetting2345”
*						can only set the prefix for access_code(The prefix is the
*						lowest byte of access_code).For channel 2~5, the whole
*						access_code must be set via access_code1higher 4 bytes
*						of channel 1 and pefix.
*
*	@return	 	none
*/
extern void RF_AccessCodeSetting2345 (unsigned char  RF_PipeIdx,unsigned char  Prefix);

/**
*	@brief		this function is to enable/disable each access_code channel for
*				RF Rx terminal.
*
*	@param[in]	RF_RxPipeSel  	Bit0~bit5 correspond to channel 0~5, respectively.
*								0：Disable 1：Enable
*								If “enable” is set as 0x3f (i.e. 00111111),
*								all access_code channels (0~5) are enabled.
*
*	@return	 	none
*/
extern void RF_RxAccessCodeEnable (unsigned char RF_RxPipeSel);

/**
*	@brief	  	this function is to Set byte length for access_code.
*
*	@param[in]	RF_AccessCodeLength  	Optional range: 3~5
*										Note: The effect for 3-byte access_code is not good.
*
*	@return	 	none
*/
extern void RF_AccessCodeLengthSetting (unsigned char RF_AccessCodeLength);

/**
*	@brief	  	This function serves to switch to maxgain mode with better
*				Rx performance,	and will only take effect if it’s invoked after
*				the “RF_Init”.The “RF_Init” sets the mode as AGC mode by default.
*
*	@param[in]	length  	Optional range: 3~5
*							Note: The effect for 3-byte access_code is not good.
*
*	@return	 	none
*/
extern void RF_SetGainManualMax (void);

/**
*	@brief	  	This function serves to switch to AGC mode from maxgain mode,
*				and will only take effect if it’s invoked after the “RF_Init”.
*
*	@param[in]	none
*							
*
*	@return	 	none
*/
extern void RF_SetAgc (void);
/**
*	@brief	 This function is to update TP(two point),this value will affect
*			 RF performance
*			 it needs to use  before the function  "RF_TrxStateSet"
*
*	@param[in]	RF_Mode  	Set working mode for RF module.
*	@param[in]	RF_TPLow  	Tp value for lower frequency (2400Mhz)
*							range: 2M/250K : 0x40(+/-)10   1M :0x1d(+/-)10
*							If you set a value outside the range, you will be set to fail.
*	@param[in]	RF_TPHigh  	Tp value for higher frequency (2480Mhz)
*							range: 2M/250K : 0x39(+/-)10   1M :0x19(+/-)10
*							If you set a value outside the range, you will be set to fail.
*
*	@return	 	0 :set success; 
*              -1 :set failed
*/
extern int RF_UpdateTpValue(RF_ModeTypeDef RF_Mode ,unsigned  char RF_TPLow,unsigned  char RF_TPHigh);

/**
*	@brief	   This function is to update cap value to affect RF performance
*			   it needs to use after the function  "RF_Init"
*
*	@param[in] RF_Cap - cap value : <4:0> is cap value(0x00 - 0x1f)
*
*	@return	   none
*/
extern void RF_UpdateCapValue(unsigned  char RF_Cap);

/**
*	@brief	  	This function is turn off tx and rx
*   @param      none
*	@return	 	none
*/
extern void RF_SetTxRxOff (void);

/**
*	@brief	  	This function is to obtain the RSSI value of the current channel
*				Before using it, it is necessary to set the "RF_MODE_RX" by "RF_TrxStateSet"
*
*   @param      none
*	@return	 	RSSI value :  unit is dbm
*/
extern signed char RF_GetRssi(void);

/**
*	@brief	  	This function is to start energy detect of the current channel for zigbee mode
*				Before using it, it is necessary to set the "RF_MODE_RX" by "RF_TrxStateSet"
*   @param      none
*	@return	 	none
*/
extern void RF_EdDetect(void);

/**
*	@brief	  	This function is to stop energy detect and get energy detect value of
*				the current channel for zigbee mode.
*   @param      none
*	@return	 	ED:0x00~0xff
*
*/
extern unsigned char RF_StopEd(void);
/**
*	@brief	  	This function turns on power to the RF module
*   @param      none
*	@return	 	none
*
*/
extern int  RF_PowerDown(void);
/**
*	@brief	  	This function turns off power to the RF module
*   @param      none
*	@return	 	none
*
*/
extern int  RF_PowerOn(void);
extern unsigned int RF_FsmIsIdle(void);

/**
*	@brief	  	Check if packet data is received.
*
*	@return	 	0x00: RF Rx DMA is empty;
*				0x01: RF Rx DMA have received data.
*/
extern unsigned char  RF_Is_RxFinish(void);
/**
*	@brief	  	This function serves to clear the Rx IRQ flag bit.
*				After packet data is received, corresponding Rx IRQ flag bit
*				will be set as 1.By reading this flag bit, it can check whether
*				packet received is finished. After the check, it’s needed to
*				manually clear this flag bit so as to avoid misjudgment.
*   @param      none
*	@return	 	none
*/
extern void RF_ClearRxFlag (void);

void RF_Setting(RF_ModeTypeDef RF_Mode);
void rx_dma(volatile unsigned char *rx_addr);
void tx_close_auto(void);
void ble_1m(void);
void zigbee_fmt(void);
void nordic_1m(void);
void nordic_2m(void);
void ble_2m(void);

void txcyc1_manual_on(void);
void rx_auto(void);

void RF_Setting(RF_ModeTypeDef RF_Mode);
void RF_1M_Rx_Setting(volatile unsigned char *buff);
void RF_1M_Tx_Setting(void);
void RF_Nordic_1M_TX_Setting(void);
void RF_Nordic_1M_Rx_Setting(volatile unsigned char *buff);
void RF_Nordic_2M_Tx_Setting(void);
void RF_Nordic_2M_Rx_Setting(volatile unsigned char *buff);
void RF_Zigbee_TX_Setting(void);
void RF_Zigbee_Rx_Setting(volatile unsigned char *buff);
void RF_2M_Tx_Setting(void);
void RF_2M_Rx_Setting(volatile unsigned char *buff);

unsigned char TwoPoint_Calibration(RF_ModeTypeDef mode, unsigned char chn);
#endif
