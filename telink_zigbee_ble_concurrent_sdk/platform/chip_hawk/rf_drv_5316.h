/********************************************************************************************************
 * @file     rf_drv_5316.h
 *
 * @brief    RF driver for hawk
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
#ifndef _RF_DRV_H_
#define _RF_DRV_H_
#include "bsp.h"
#include "../../proj/common/types.h"
/**
 *  ble
 */
#define		RF_BLE_PACKET_LENGTH_OK(p)			(p[0] == (p[5]&0x3f)+13)
#define		RF_BLE_PACKET_CRC_OK(p)				((p[p[0]+3] & 0x01) == 0)
/**
 *  Zigbee
 */
//#define		RF_ZIGBEE_PACKET_LENGTH_OK(p)	    (p[0]  == p[4]+9)
//#define		RF_ZIGBEE_PACKET_CRC_OK(p)	    	((p[p[0]+3] & 0x51) == 0x10)
/**
 *  Nordic
 */
#define		RF_NORDIC_PACKET_LENGTH_OK(p)	    (p[0]  == [p[12]&0x3F]+13)
#define		RF_NORDIC_PACKET_CRC_OK(p)	    	((p[p[0]+3] & 0x51) == 0x10)

#define ZB_PHY_MAX_PACKET_SIZE			127
#define		RF_PACKET_LENGTH_OK(p)		((p[0] == p[12]+13)&&p[0]<=(ZB_PHY_MAX_PACKET_SIZE+13))
#define		RF_PACKET_CRC_OK(p)			((p[p[0]+3] & 0x51) == 0x10)
/**
 *  @brief Timestamp is stored on the before of CRC value
 */
#define 	RF_GET_TIMESTAMP(p)    			( p[p[0]] | (p[p[0]+1]<<8) | (p[p[0]+2]<<16) )
#define 	RF_GET_PKT_RSSI(p)    			(p[4])

#define RF_TxFinishClearFlag()		 reg_rf_irq_status |= FLD_RF_IRQ_TX
#define RF_RxFinishClearFlag()		 reg_rf_irq_status |= FLD_RF_IRQ_RX
#define RF_TxFinish()				 (reg_rf_irq_status & FLD_RF_IRQ_TX)
////////////External Crystal Type///////////////////
enum{
	XTAL_24M_RF_BLE_1m_MODE 		= 0x01,
	XTAL_24M_RF_BLE_2m_MODE 		= 0x02,
	XTAL_24M_RF_ZIGBEE_250K_MODE 	= 0x04,
	XTAL_24M_RF_NORDIC_1M_MODE	 	= 0x08,
	XTAL_24M_RF_NORDIC_2M_MODE	 	= 0x10,
	XTAL_24M_RF_LE_500K_MODE		= 0x20,
	XTAL_24M_RF_LE_125K_MODE		= 0x40,

 	XTAL_24M    = XTAL_24M_RF_NORDIC_1M_MODE,
};

#define IS_RF_BLE_1M_MODE(mode)				( (mode) & 0x01)
#define IS_RF_BLE_2M_MODE(mode)				( (mode) & 0x02)
#define IS_RF_ZIGBEE_250K_MODE(mode)		( (mode) & 0x04)
#define IS_RF_NORDIC_1M_MODE(mode)			( (mode) & 0x08)
#define IS_RF_NORDIC_2M_MODE(mode)			( (mode) & 0x10)
#define IS_RF_LE_500K_MODE(mode)			( (mode) & 0x20)
#define IS_RF_LE_125K_MODE(mode)			( (mode) & 0x40)



#ifndef	CRYSTAL_TYPE
#define CRYSTAL_TYPE		XTAL_24M
#endif

#define RF_CHN_AUTO_CAP 	0xff00
#define RF_CHN_TABLE 		0x8000

#define RF_SET_TX_MANAUL		1
#define RF_SET_RX_MANAUL		2
#define RF_SET_AUTO				4

#define	RF_TRX_MODE					0x80
#define	RF_TRX_OFF					0x45		//f02

#define RF_TRX_OFF_MANUAL_TX       	0x55        //f02
#define RF_TRX_OFF_MANUAL_RX       	0x65        //f02

#define	STOP_RF_STATE_MACHINE	( REG_ADDR8(0xf00) = 0x80 )


#define FRE_OFFSET 	0
#define FRE_STEP 	5
#define MAX_RF_CHANNEL  16

#define RF_CHANNEL_MAX			16
#define RF_CHANNEL_MASK			(RF_CHANNEL_MAX - 1)

//#define analog_write WriteAnalogReg
extern const unsigned char rf_chn[RF_CHANNEL_MAX];
extern unsigned char rfhw_tx_power;
extern unsigned char cap_tp[RF_CHANNEL_MAX];


enum {
	RF_POWER_11PdBm		= 0,  // 11
	RF_POWER_10m4PdBm	= 1,  // 10.4
	RF_POWER_9m8PdBm	= 2,  // 9.8
	RF_POWER_9m34PdBm	= 3,  // 9.34
	RF_POWER_8m5PdBm	= 4,  // 8.5
	RF_POWER_7m9PdBm	= 5,  // 7.9
	RF_POWER_7m3PdBm	= 6,  // 7.3
	RF_POWER_6m3PdBm	= 7,  // 6.3
	RF_POWER_5m4PdBm	= 8,  // 5.4
	RF_POWER_4m5PdBm	= 9,  // 4.5
	RF_POWER_3m5PdBm	= 10,  // 3.5
	RF_POWER_1m9PdBm	= 11,  // 1.9
	RF_POWER_1PdBm		= 12, // 1
	RF_POWER_0m28NdBm	= 13, // -0.28
	RF_POWER_1m9NdBm	= 14, // -1.9
	RF_POWER_3m5NdBm	= 15, // -3.5
	RF_POWER_5m5NdBm	= 16, // -5.5
	RF_POWER_6m8NdBm	= 17, // -6.8
	RF_POWER_8m23NdBm	= 18, // -8.23
	RF_POWER_9m1NdBm	= 19, // -9.1
	RF_POWER_11m8NdBm	= 20, // -11.8
	RF_POWER_13m1NdBm	= 21, // -13.1
	RF_POWER_14m5NdBm	= 22, // -14.5
	RF_POWER_15m3NdBm	= 23, // -15.3
	RF_POWER_17m75NdBm	= 24, // -17.75
	RF_POWER_19m8NdBm	= 25, // -19
	RF_POWER_20m3NdBm	= 26, // -20.3
};

extern int 	sar_adc_pwdn_en;
extern int	xtalType_rfMode;


extern void rf_drv_init (int xtal_type);
extern void rf_set_channel(signed char chn, unsigned short set);
extern void rf_rx_buff_set(u8* adr,int size,u8 PingpongEn);

static inline void rf_start_brx(void* addr, u32 tick)
{
//	write_reg32 (0x800f04, 0x56);						// tx_wait = 0; tx_settle = 86 us
	write_reg32 (0x800f28, 0x0fffffff);					// first timeout
//	write_reg32(0x800f18, tick);						// Setting schedule trigger time
	write_reg32(0x800f18, (tick - pm_systick_offset));
    write_reg8(0x800f16, read_reg8(0x800f16) | 0x04);	// Enable cmd_schedule mode
	write_reg8 (0x800f00, 0x82);						// ble rx
	write_reg16 (0x800c0c, (u16)((u32)addr));
}

static inline void rf_ble_tx_on ()
{
	write_reg8  (0x800f02, RF_TRX_OFF | BIT(4));	// TX enable
	write_reg32 (0x800f04, 0x38);
}

static inline void rf_ble_tx_done ()
{
	write_reg8  (0x800f02, RF_TRX_OFF);	// TX disable
	write_reg32 (0x800f04, 0x50);
}




#endif
