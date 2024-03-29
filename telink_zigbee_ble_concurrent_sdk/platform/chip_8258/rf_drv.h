/********************************************************************************************************
 * @file	rf_drv.h
 *
 * @brief	This is the header file for B85
 *
 * @author	Driver Group
 * @date	2018
 *
 * @par     Copyright (c) 2018, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
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
#ifndef _RF_DRV_H_
#define _RF_DRV_H_

#include "bit.h"
#include "bsp.h"
#include "flash.h"
#include "register.h"
#include "analog.h"

#define RF_CHN_TABLE 		0x8000



/**
 *  @brief  Define RF mode
 */
typedef enum {
	 RF_MODE_BLE_2M =    		BIT(0),
	 RF_MODE_BLE_1M = 			BIT(1),
    RF_MODE_BLE_1M_NO_PN   =    BIT(2),
	RF_MODE_ZIGBEE_250K    =    BIT(3),
    RF_MODE_LR_S2_500K     =    BIT(4),
    RF_MODE_LR_S8_125K     =    BIT(5),
    RF_MODE_PRIVATE_250K   =    BIT(6),
    RF_MODE_PRIVATE_500K   =    BIT(7),
    RF_MODE_PRIVATE_1M     =    BIT(8),
    RF_MODE_PRIVATE_2M     =    BIT(9),
    RF_MODE_BLE_2M_NO_PN   =    BIT(10),
} RF_ModeTypeDef;


//extern  RF_ModeTypeDef g_RFMode;

typedef enum {
    RF_MODE_TX = 0,
    RF_MODE_RX = 1,
    RF_MODE_AUTO = 2,
    RF_MODE_OFF = 3
} RF_StatusTypeDef;


#if 0
typedef enum {
 /*VBAT*/
 RF_POWER_P10p46dBm,
 RF_POWER_P10p29dBm,
 RF_POWER_P10p01dBm,
 RF_POWER_P9p81dBm,
 RF_POWER_P9p48dBm,
 RF_POWER_P9p24dBm,
 RF_POWER_P8p97dBm,
 RF_POWER_P8p73dBm,
 RF_POWER_P8p44dBm,
 RF_POWER_P8p13dBm,
 RF_POWER_P7p79dBm,
 RF_POWER_P7p41dBm,
 RF_POWER_P7p02dBm,
 RF_POWER_P6p60dBm,
 RF_POWER_P6p14dBm,
 RF_POWER_P5p65dBm,
 RF_POWER_P5p13dBm,
 RF_POWER_P4p57dBm,
 RF_POWER_P3p94dBm,
 RF_POWER_P3p23dBm,
 /*VANT*/
 RF_POWER_P3p01dBm,
 RF_POWER_P2p81dBm,
 RF_POWER_P2p61dBm,
 RF_POWER_P2p39dBm,
 RF_POWER_P1p99dBm,
 RF_POWER_P1p73dBm,
 RF_POWER_P1p45dBm,
 RF_POWER_P1p17dBm,
 RF_POWER_P0p90dBm,
 RF_POWER_P0p58dBm,
 RF_POWER_P0p04dBm,
 RF_POWER_N0p14dBm,
 RF_POWER_N0p97dBm,
 RF_POWER_N1p42dBm,
 RF_POWER_N1p89dBm,
 RF_POWER_N2p48dBm,
 RF_POWER_N3p03dBm,
 RF_POWER_N3p61dBm,
 RF_POWER_N4p26dBm,
 RF_POWER_N5p03dBm,
 RF_POWER_N5p81dBm,
 RF_POWER_N6p67dBm,
 RF_POWER_N7p65dBm,
 RF_POWER_N8p65dBm,
 RF_POWER_N9p89dBm,
 RF_POWER_N11p4dBm,
 RF_POWER_N13p29dBm,
 RF_POWER_N15p88dBm,
 RF_POWER_N19p27dBm,
 RF_POWER_N25p18dBm,
} RF_PowerTypeDef;
#endif

/**
 *  @brief  Define power list of RF
 */
typedef enum {
	 /*VBAT*/
	 RF_POWER_P10p46dBm = 63, //  10.46 dbm
	 RF_POWER_P10p29dBm = 61, //  10.29 dbm
	 RF_POWER_P10p01dBm = 58, //  10.01 dbm
	 RF_POWER_P9p81dBm  = 56, //   9.81 dbm
	 RF_POWER_P9p48dBm  = 53, //   9.48 dbm
	 RF_POWER_P9p24dBm  = 51, //   9.24 dbm
	 RF_POWER_P8p97dBm  = 49, //   8.97 dbm
	 RF_POWER_P8p73dBm  = 47, //   8.73 dbm
	 RF_POWER_P8p44dBm  = 45, //   8.44 dbm
	 RF_POWER_P8p13dBm  = 43, //   8.13 dbm
	 RF_POWER_P7p79dBm  = 41, //   7.79 dbm
	 RF_POWER_P7p41dBm  = 39, //   7.41 dbm
	 RF_POWER_P7p02dBm  = 37, //   7.02 dbm
	 RF_POWER_P6p60dBm  = 35, //   6.60 dbm
	 RF_POWER_P6p14dBm  = 33, //   6.14 dbm
	 RF_POWER_P5p65dBm  = 31, //   5.65 dbm
	 RF_POWER_P5p13dBm  = 29, //   5.13 dbm
	 RF_POWER_P4p57dBm  = 27, //   4.57 dbm
	 RF_POWER_P3p94dBm  = 25, //   3.94 dbm
	 RF_POWER_P3p23dBm  = 23, //   3.23 dbm
	 /*VANT*/
	 RF_POWER_P3p01dBm  = BIT(7) | 63,   //   3.01 dbm
	 RF_POWER_P2p81dBm  = BIT(7) | 61,   //   2.81 dbm
	 RF_POWER_P2p61dBm  = BIT(7) | 59,   //   2.61 dbm
	 RF_POWER_P2p39dBm  = BIT(7) | 57,   //   2.39 dbm
	 RF_POWER_P1p99dBm  = BIT(7) | 54,   //   1.99 dbm
	 RF_POWER_P1p73dBm  = BIT(7) | 52,   //   1.73 dbm
	 RF_POWER_P1p45dBm  = BIT(7) | 50,   //   1.45 dbm
	 RF_POWER_P1p17dBm  = BIT(7) | 48,   //   1.17 dbm
	 RF_POWER_P0p90dBm  = BIT(7) | 46,   //   0.90 dbm
	 RF_POWER_P0p58dBm  = BIT(7) | 44,   //   0.58 dbm
	 RF_POWER_P0p04dBm  = BIT(7) | 41,   //   0.04 dbm
	 RF_POWER_N0p14dBm  = BIT(7) | 40,   //  -0.14 dbm
	 RF_POWER_N0p97dBm  = BIT(7) | 36,   //  -0.97 dbm
	 RF_POWER_N1p42dBm  = BIT(7) | 34,   //  -1.42 dbm
	 RF_POWER_N1p89dBm  = BIT(7) | 32,   //  -1.89 dbm
	 RF_POWER_N2p48dBm  = BIT(7) | 30,   //  -2.48 dbm
	 RF_POWER_N3p03dBm  = BIT(7) | 28,   //  -3.03 dbm
	 RF_POWER_N3p61dBm  = BIT(7) | 26,   //  -3.61 dbm
	 RF_POWER_N4p26dBm  = BIT(7) | 24,   //  -4.26 dbm
	 RF_POWER_N5p03dBm  = BIT(7) | 22,   //  -5.03 dbm
	 RF_POWER_N5p81dBm  = BIT(7) | 20,   //  -5.81 dbm
	 RF_POWER_N6p67dBm  = BIT(7) | 18,   //  -6.67 dbm
	 RF_POWER_N7p65dBm  = BIT(7) | 16,   //  -7.65 dbm
	 RF_POWER_N8p65dBm  = BIT(7) | 14,   //  -8.65 dbm
	 RF_POWER_N9p89dBm  = BIT(7) | 12,   //  -9.89 dbm
	 RF_POWER_N11p4dBm  = BIT(7) | 10,   //  -11.4 dbm
	 RF_POWER_N13p29dBm = BIT(7) | 8,   //  -13.29 dbm
	 RF_POWER_N15p88dBm = BIT(7) | 6,   //  -15.88 dbm
	 RF_POWER_N19p27dBm = BIT(7) | 4,   //  -19.27 dbm
	 RF_POWER_N25p18dBm = BIT(7) | 2,   //  -25.18 dbm

	 RF_POWER_N30dBm    = 0xff,         //  -30 dbm
	 RF_POWER_N50dBm    = BIT(7) | 0,   //  -50 dbm

} RF_PowerTypeDef;



#define		RF_PACKET_LENGTH_OK(p)		(p[0] == p[5]+13)//BLE
#define		RF_PACKET_CRC_OK(p)			((p[p[0]+3] & 0x01) == 0x0)//BLE

#define		RF_BLE_PACKET_LENGTH_OK(p)			( *((unsigned int*)p) == p[5]+13)
#define		RF_BLE_PACKET_CRC_OK(p)				((p[*((unsigned int*)p) + 3] & 0x01) == 0x0)

#define    RF_ZIGBEE_PACKET_LENGTH_OK(p)    (p[0]  == p[4]+9)//zigbee
#define    RF_ZIGBEE_PACKET_CRC_OK(p)       ((p[p[0]+3] & 0x51) == 0x10)//zigbee
#define    RF_ZIGBEE_PACKET_RSSI_GET(p)     (p[p[0]+2])
#define    RF_ZIGBEE_PACKET_TIMESTAMP_GET(p)           (p[p[0]-4] | (p[p[0]-3]<<8) | (p[p[0]-2]<<16) | (p[p[0]-1]<<24))
#define    RF_ZIGBEE_PACKET_PAYLOAD_LENGTH_GET(p)      (p[4])

#define    RF_TPLL_PACKET_LENGTH_OK(p)              	(p[0] == (p[4] & 0x3f) + 11)
#define    RF_TPLL_PACKET_CRC_OK(p)                 	((p[p[0]+3] & 0x01) == 0x00)
#define    RF_TPLL_PACKET_RSSI_GET(p)               	(p[p[0]+2])
#define    RF_SB_PACKET_PAYLOAD_LENGTH_GET(p)      		(p[0] - 10)
#define    RF_SB_PACKET_CRC_OK(p)                  		((p[p[0]+3] & 0x01) == 0x00)
#define    RF_SB_PACKET_CRC_GET(p)                 		((p[p[0]-8]<<8) + p[p[0]-7]) //Note: here assume that the MSByte of CRC is received first
#define    RF_SB_PACKET_RSSI_GET(p)                		(p[p[0]+2])
#define    RF_TPLL_PACKET_TIMESTAMP_GET(p)         	 	(p[p[0]-4] | (p[p[0]-3]<<8) | (p[p[0]-2]<<16) | (p[p[0]-1]<<24))
#define    RF_SB_PACKET_TIMESTAMP_GET(p)           		(p[p[0]-4] | (p[p[0]-3]<<8) | (p[p[0]-2]<<16) | (p[p[0]-1]<<24))


static inline void rf_ble_tx_on ()
{
	write_reg8  (0x800f02, 0x45 | BIT(4));	// TX enable
	write_reg32 (0x800f04, 0x38);
}

static inline void rf_ble_tx_done ()
{
	write_reg8  (0x800f02, 0x45);	// TX enable
	write_reg32 (0x800f04, 0x50);
}

void rf_update_tp_value (unsigned char tp0, unsigned char tp1);


/////////////////////  RF BaseBand ///////////////////////////////
static inline void reset_baseband(void)
{
	REG_ADDR8(0x61) = BIT(0);		//reset baseband
	REG_ADDR8(0x61) = 0;			//release reset signal
}

static inline void reset_sn_nesn(void)
{
	REG_ADDR8(0xf01) =  0x01;
}

static inline unsigned char is_rf_receiving_pkt(void)
{
	//if the value of [5:4] of the reg_0x448 is 0b10 or 0b10, it means that the RF is in the receiving packet phase.(confirmed by junwen)
	return (((read_reg8(0x448)>>5)& 1) == 1);
}


static inline void 	tx_settle_adjust(unsigned short txstl_us)
{
	REG_ADDR16(0xf04) = txstl_us;  //adjust TX settle time
}

static inline void rf_set_tx_pipe (unsigned char pipe)
{
	write_reg8 (0x800f15, 0xf0 | pipe);
}

static inline void rf_set_ble_crc (unsigned char *p)
{
	write_reg32 (0x800424, p[0] | (p[1]<<8) | (p[2]<<16));
}

static inline void rf_set_ble_crc_value (unsigned int crc)
{
	write_reg32 (0x800424, crc);
}

static inline void rf_set_ble_crc_adv ()
{
	write_reg32 (0x800424, 0x555555);
}

static inline void rf_set_ble_access_code (unsigned char *p)
{
	write_reg32 (0x800408, p[3] | (p[2]<<8) | (p[1]<<16) | (p[0]<<24));
}

static inline void rf_set_ble_access_code_value (unsigned int ac)
{
	write_reg32 (0x800408, ac);
}


static inline void rf_set_ble_access_code_adv (void)
{
	write_reg32 (0x800408, 0xd6be898e);
}
static inline void rf_access_code_comm (unsigned int acc)
{
	write_reg32 (0x800408, acc);
	write_reg8 (0x800405, read_reg8(0x405)|0x80);
}

static inline unsigned int rf_access_code_16to32 (unsigned short code)
{
	unsigned int r = 0;
	for (int i=0; i<16; i++) {
		r = r << 2;
		r |= code & BIT(i) ? 1 : 2;
	}
	return r;
}

static inline unsigned short rf_access_code_32to16 (unsigned int code)
{
	unsigned short r = 0;
	for (int i=0; i<16; i++) {
		r = r << 1;

		r |= (code & BIT(i*2)) ? 1 : 0;

	}
	return r;
}

static inline void rf_reset_sn (void)
{
	write_reg8  (0x800f01, 0x3f);
	write_reg8  (0x800f01, 0x00);
}

void rf_set_power_level_index (RF_PowerTypeDef level);     //@@@

void 	rf_drv_init (RF_ModeTypeDef rf_mode);   				//@@@

void	rf_set_channel (signed char chn, unsigned short set);

void 	rf_set_ble_channel (signed char chn_num);

//manual mode
static inline void rf_set_rxmode (void)
{
    write_reg8 (0x800428, 0x80 | BIT(0));	// rx enable
    write_reg8 (0x800f02, 0x45 | BIT(5));		// RX enable
}

static inline void rf_set_txmode (void)
{
	write_reg8  (0x800f02, 0x45 | BIT(4));	// TX enable
}

//maunal mode off
static inline void rf_set_tx_rx_off(void)
{
	write_reg8 (0x800f16, 0x29);
	write_reg8 (0x800428, 0x80);	// rx disable
	write_reg8 (0x800f02, 0x45);	// reset tx/rx state machine
}
//auto mode off
static inline void rf_set_tx_rx_off_auto_mode(void)
{
 write_reg8 (0xf00, 0x80);
}
//auto
static inline void rf_stop_trx (void)
{
	write_reg8  (0x800f00, 0x80);			// stop
}

void	rf_send_packet (void* addr);

void  rf_rx_buffer_set(unsigned char *  RF_RxAddr, int size, unsigned char  PingpongEn);
void  rf_pn_disable();

void  rf_rx_cfg(int size, unsigned char  PingpongEn);

void rf_start_btx (void* addr, unsigned int tick);
void rf_start_brx  (void* addr, unsigned int tick);

void rf_start_stx  (void* addr, unsigned int tick);
void rf_start_srx  (unsigned int tick);

void rf_start_stx2rx  (void* addr, unsigned int tick);
void rf_start_srx2tx  (void* addr, unsigned int tick);

extern int rf_trx_state_set(RF_StatusTypeDef rf_status, signed char rf_channel);
extern RF_StatusTypeDef rf_trx_state_get(void);
extern void rf_tx_pkt(unsigned char *rf_txaddr);
static inline unsigned char rf_tx_finish(void)
{
    return (READ_REG8(0xf20) & BIT(1));
}

static inline void rf_tx_finish_clear_flag(void)
{
    WRITE_REG8(0xf20, 0x02);
}

/**
 *	@brief	  	This function serves to determine whether sending a packet of rf_tx_acc_code_select is finished
 *	@param[in]	none.
 *	@return	 	Yes: 1, NO: 0.
 */
static inline unsigned char rf_rx_finish(void)
{
    return ((read_reg8(0xf20) & BIT(0)) == 0x01);
}

static inline void rf_rx_finish_clear_flag(void)
{
    WRITE_REG8(0xf20, 0x01);
}

static inline void rf_rx_buffer_reconfig(unsigned short RF_RxAddr)
{
	reg_dma2_addr = (unsigned short)(RF_RxAddr);
}


extern void rf_acc_len_set(unsigned char len);
static inline unsigned char rf_acc_len_get(unsigned char len)
{
    return (READ_REG8(0x405) & 0x07); //access_byte_num[2:0]
}
extern void rf_acc_code_set(unsigned char pipe, const unsigned char *addr);
extern void rf_acc_code_get(unsigned char pipe, unsigned char *addr);
static inline void rf_rx_acc_code_enable(unsigned char pipe)
{
    WRITE_REG8(0x407, (READ_REG8(0x407)&0xc0) | pipe); //rx_access_code_chn_en
}
static inline void rf_tx_acc_code_select(unsigned char pipe)
{
    WRITE_REG8(0xf15, (READ_REG8(0xf15)&0xf8) | pipe); //Tx_Channel_man[2:0]
}

static inline void rf_fix_payload_len_set(int len)
{
    WRITE_REG8(0x404, READ_REG8(0x404)|0x03); //select private header mode
    WRITE_REG8(0x406, len);
}

static inline void rf_drv_cap(unsigned long addr)
{
	unsigned char cap = 0xff;
	flash_read_page(addr, 1, &cap);
	if(cap != 0xff){
		cap &= 0x3f;
		WriteAnalogReg(0x8a, (ReadAnalogReg(0x8a) & 0xc0) | cap);
	}
}

/**
 * @brief	  	This function serves to clear the TX/RX irq mask.
 * @param[in]   mask 	- RX/TX irq value.
 * @return	 	none.
 */
static inline void rf_clr_irq_mask(rf_irq_e mask)
{
	BM_CLR(reg_rf_irq_mask,mask);
}

/**
 * @brief	  	This function serves to clear the TX/RX irq mask.
 * @param[in]   mask 	- RX/TX irq value.
 * @return	 	none.
 */
static inline void rf_set_irq_mask(rf_irq_e mask)
{
	BM_SET(reg_rf_irq_mask,mask);
}

extern unsigned short crc16_ccitt_cal(unsigned char *input, unsigned int len, unsigned short init_val);
extern void rf_tx_500k_simulate_100k(unsigned char *preamble, unsigned char preamble_len,
                                     unsigned char *acc_code, unsigned char acc_len,
                                     unsigned char *payload, unsigned char pld_len,
                                     unsigned char *tx_buf, unsigned short crc_init);
extern signed char rf_rssi_get_154(void);
extern unsigned char rf_stop_ed_154(void);

void rf_ble_1m_param_init(void);

void ble_rf_drv_init (RF_ModeTypeDef rf_mode);


void rf_baseband_reset(void);

#endif
