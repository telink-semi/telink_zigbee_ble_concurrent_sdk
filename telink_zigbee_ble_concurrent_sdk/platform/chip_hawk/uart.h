/********************************************************************************************************
 * @file     uart.h
 *
 * @brief    This file provides set of functions to manage the UART interface
 *
 * @author   qiuwei.chen@telink-semi.com; junjun.chen@telink-semi.com;
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
#ifndef     uart_H
#define     uart_H
#include "./gpio.h"

#define UART_DMA_EN   1  // 1:uart DMA. 0: not DMA
/**
 *  @brief  Define parity type 
 */
typedef enum {
    PARITY_NONE = 0,
    PARITY_EVEN,
    PARITY_ODD,
} UART_ParityTypeDef;

/**
 *  @brief  Define the length of stop bit 
 */
typedef enum {
    STOP_BIT_ONE = 0,
    STOP_BIT_ONE_DOT_FIVE,
    STOP_BIT_TWO,
} UART_StopBitTypeDef;

/**
 *  @brief  Define UART RTS mode 
 */
typedef enum {
    UART_RTS_MODE_AUTO = 0,
    UART_RTS_MODE_MANUAL,
} UART_RTSModeTypeDef;

/**
 * define the macro that configures pin port for UART interface
 */

typedef enum {
	UART_PIN_GPIOA34 = 0,        //
	UART_PIN_GPIOB45,			//
	UART_PIN_GPIOC45,			//
} UART_PinTypeDef;

//enum{
//	PA7_UART_RX_EN = BIT(7),
//};
/** 
 *define the macro that configures pin port for UART interface 
 */ 
//enum{
//	PB2_UART_TX_EN = BIT(2),
//	PB3_UART_RX_EN = BIT(3),
//};

/** 
 *define the macro that configures pin port for UART interface 
 */ 
//enum{
//	PC2_UART_TX_EN = BIT(2),
//	PC3_UART_RX_EN = BIT(3),
//};
/**
 * @brief     This function resets the UART module.
 * @param[in] none
 * @return    none
 */
extern void UART_Reset(void );

extern void UART_PinSelect(UART_PinTypeDef PinGrp);

/**
 * @brief      This function initializes the UART module.
 * @param[in]  BaudRate - the selected baudrate for UART interface
 * @param[in]  Parity - selected parity type for UART interface
 * @param[in]  StopBit - selected length of stop bit for UART interface
 * @return     none
 */
extern void UART_Init(unsigned int BaudRate, UART_ParityTypeDef Parity, UART_StopBitTypeDef StopBit);

/**
 * @brief     enable uart DMA mode
 * @param[in] none
 * @return    none
 */
extern void UART_DmaInit(void);

/**
 * @brief     config the irq of uart tx and rx
 * @param[in] rx_irq_en - 1:enable rx irq. 0:disable rx irq
 * @param[in] tx_irq_en - 1:enable tx irq. 0:disable tx irq
 * @return    none
 */
extern void UART_NDmaIrqInit(unsigned char rx_irq_en,unsigned char tx_irq_en);
/**
 * @brief     uart send data function with not DMA method.
 *            variable uart_TxIndex,it must cycle the four registers 0x90 0x91 0x92 0x93 for the design of SOC.
 *            so we need variable to remember the index.
 * @param[in] uartData - the data to be send.
 * @return    none
 */
extern void UART_NDmaSendByte(unsigned char uartData);

/**
 * @brief     config the number level setting the irq bit of status register 0x9d
 *            ie 0x9d[3].
 *            If the cnt register value(0x9c[0,3]) larger or equal than the value of 0x99[0,3]
 *            or the cnt register value(0x9c[4,7]) less or equal than the value of 0x99[4,7],
 *            it will set the irq bit of status register 0x9d, ie 0x9d[3]
 * @param[in] rx_level - receive level value. ie 0x99[0,3]
 * @param[in] tx_level - transmit level value.ie 0x99[4,7]
 * @return    none
 */
extern void UART_NDmaIrqTrigLevel(unsigned char rx_level, unsigned char tx_level);

/**
 * @brief     get the status of uart irq.
 * @param[in] none
 * @return    0: not uart irq ;
 *            not 0: indicate tx or rx irq
 */
extern unsigned char UART_NDmaIrqGet(void);

/**
 * @brief     uart send data function, this  function tell the DMA to get data from the RAM and start
 *            the DMA transmission
 * @param[in] Addr - pointer to the buffer containing data need to send
 * @return    1: send success ;
 *            0: DMA busy
 */
extern volatile unsigned char UART_Send(unsigned char* Addr);

/**
 * @brief     data receive buffer initiate function. DMA would move received uart data to the address space,
 *            uart packet length needs to be no larger than (recBuffLen - 4).
 * @param[in] RecvAddr - pointer to the receiving buffer
 * @param[in] RecvBufLen - length in byte of the receiving buffer
 * @return    none
 */
extern void UART_RecBuffInit(unsigned char *RecvAddr, unsigned short RecvBufLen);

/**
 * @brief     This function determines whether parity error occurs once a packet arrives.
 * @param[in] none
 * @return    1: parity error ;
 *            0: no parity error
 */
extern unsigned char UART_IsParityError(void);

/**
 * @brief     This function clears parity error status once when it occurs.
 * @param[in] none
 * @return    none
 */
extern void UART_ClearParityError(void);

/**
 * @brief     UART hardware flow control configuration. Configure RTS pin.
 * @param[in] Enable - enable or disable RTS function.
 * @param[in] Mode - set the mode of RTS(auto or manual).
 * @param[in] Thresh - threshold of trig RTS pin's level toggle(only for auto mode), 
 *                     it means the number of bytes that has arrived in Rx buf.
 * @param[in] Invert - whether invert the output of RTS pin(only for auto mode)
 * @return    none
 */
extern void UART_RTSCfg(unsigned char Enable, UART_RTSModeTypeDef Mode, unsigned char Thresh, unsigned char Invert);

/**
 * @brief     This function sets the RTS pin's level manually
 * @param[in] Polarity - set the output of RTS pin(only for manual mode)
 * @return    none
 */
extern void UART_RTSLvlSet(unsigned char Polarity);

/**
 * @brief      UART hardware flow control configuration. Configure CTS pin.
 * @param[in]  Enable - enable or disable CTS function.
 * @param[in]  Select - when CTS's input equals to select, tx will be stopped
 * @return     none
 */
extern void UART_CTSCfg(unsigned char Enable, unsigned char Select);

#endif
