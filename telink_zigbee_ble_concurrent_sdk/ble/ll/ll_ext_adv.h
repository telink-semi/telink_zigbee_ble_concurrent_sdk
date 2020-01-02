/********************************************************************************************************
 * @file     ll_ext_adv.h
 *
 * @brief    for TLSR chips
 *
 * @author	 public@telink-semi.com;
 * @date     Feb. 1, 2018
 *
 * @par      Copyright (c) Telink Semiconductor (Shanghai) Co., Ltd.
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

#ifndef LL_ADV_EXT_H_
#define LL_ADV_EXT_H_


#include "../ble_common.h"
#include "../blt_config.h"
#include "../hci/hci_const.h"
#include "../hci/hci_event.h"
#include "../hci/hci_cmd.h"
#include "../ll/ll_adv.h"
#include "../ll/ll_encrypt.h"
#include "../ll/ll_init.h"
#include "../ll/ll_master.h"
#include "../ll/ll_pm.h"
#include "../ll/ll_scan.h"
#include "../ll/ll_slave.h"
#include "../ll/ll_whitelist.h"


#include "../../proj/tl_common.h"
//#include "drivers.h"


#define	INVALID_ADVHD_FLAG										0xFF


#define AUX_ADV_FEA			BIT(0)
#define PER_ADV_FEA			BIT(1)

typedef enum{
	LE_CODED_S2 = 2,
	LE_CODED_S8 = 8,
}le_coding_ind_t;

#define BLE_LL_EXT_ADV_ADVA_BIT         (0)
#define BLE_LL_EXT_ADV_TARGETA_BIT      (1)
#define BLE_LL_EXT_ADV_RFU_BIT          (2)
#define BLE_LL_EXT_ADV_DATA_INFO_BIT    (3)
#define BLE_LL_EXT_ADV_AUX_PTR_BIT      (4)
#define BLE_LL_EXT_ADV_SYNC_INFO_BIT    (5)
#define BLE_LL_EXT_ADV_TX_POWER_BIT     (6)

#define BLE_LL_EXT_ADV_ADVA_SIZE        (6)
#define BLE_LL_EXT_ADV_TARGETA_SIZE     (6)
#define BLE_LL_EXT_ADV_DATA_INFO_SIZE   (2)
#define BLE_LL_EXT_ADV_AUX_PTR_SIZE     (3)
#define BLE_LL_EXT_ADV_SYNC_INFO_SIZE   (18)
#define BLE_LL_EXT_ADV_TX_POWER_SIZE    (1)

#define BLE_LL_EXT_ADV_MODE_NON_CONN    (0x00)
#define BLE_LL_EXT_ADV_MODE_CONN        (0x01)
#define BLE_LL_EXT_ADV_MODE_SCAN        (0x02)








/* Advertising_Handle */
#define ADV_HANDLE_0											0x00
#define ADV_HANDLE_1											0x01
#define ADV_HANDLE_2											0x02
#define ADV_HANDLE_3											0x03




/* Advertising Event Properties
 * See the Core_v5.0(Vol 2/Part E/7.8.53 & Vol 6/Part B/4.4.2/Table 4.1) for more information
*/
#define BLE_EXT_ADV_PROP_CONNECTABLE							(0x0001)
#define BLE_EXT_ADV_PROP_SCANNABLE     							(0x0002)
#define BLE_EXT_ADV_PROP_CONNECTABLE_SCANNABLE					(0x0003) // BLE_EXT_ADV_PROP_CONNECTABLE | BLE_EXT_ADV_PROP_SCANNABLE
#define BLE_EXT_ADV_PROP_DIRECTED  							    (0x0004)
#define BLE_EXT_ADV_PROP_HD_DIRECTED     						(0x0008)
#define BLE_EXT_ADV_PROP_LEGACY          						(0x0010)
#define BLE_EXT_ADV_PROP_ANON_ADV       		 				(0x0020)
#define BLE_EXT_ADV_PROP_INC_TX_PWR      						(0x0040)

typedef enum{
  ADV_EVT_PROP_LEGACY_CONNECTABLE_SCANNABLE_UNDIRECTED 				       	= 0x0013,		//  0001 0011'b 	ADV_IND
  ADV_EVT_PROP_LEGACY_CONNECTABLE_UNDIRECTED_LOW_DUTY 				       	= 0x0015,		//  0001 0101'b		ADV_DIRECT_IND(low duty cycle)
  ADV_EVT_PROP_LEGACY_CONNECTABLE_UNDIRECTED_HIGH_DUTY 	 				    = 0x001D,		//  0001 1101'b		ADV_DIRECT_IND(high duty cycle)
  ADV_EVT_PROP_LEGACY_SCANNABLE_UNDIRECTED 							       	= 0x0012,		//  0001 0010'b		ADV_SCAN_IND
  ADV_EVT_PROP_LEGACY_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED				= 0x0010,		//  0001 0000'b		ADV_NONCONN_IND


  ADV_EVT_PROP_EXTENDED_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED    	    = 0x0000,		//  0000 0000'b		ADV_EXT_IND + AUX_ADV_IND
  ADV_EVT_PROP_EXTENDED_CONNECTABLE_UNDIRECTED       				 	  	= 0x0001,		//  0000 0001'b		ADV_EXT_IND + AUX_ADV_IND
  ADV_EVT_PROP_EXTENDED_SCANNABLE_UNDIRECTED						        = 0x0002,		//  0000 0010'b		ADV_EXT_IND + AUX_ADV_IND
  ADV_EVT_PROP_EXTENDED_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED_LOW_DUTY	= 0x0004,		//  0000 0100'b		ADV_EXT_IND + AUX_ADV_IND
  ADV_EVT_PROP_EXTENDED_CONNECTABLE_DIRECTED_LOW_DUTY       				= 0x0005,		//  0000 0101'b		ADV_EXT_IND + AUX_ADV_IND
  ADV_EVT_PROP_EXTENDED_SCANNABLE_DIRECTED_LOW_DUTY						    = 0x0006,		//  0000 0110'b		ADV_EXT_IND + AUX_ADV_IND


  ADV_EVT_PROP_EXTENDED_MASK_ANONYMOUS_ADV 		= 0x0020,  //if this mask on(only extended ADV event can mask it), anonymous advertising
  ADV_EVT_PROP_EXTENDED_MASK_TX_POWER_INCLUDE	= 0x0040,  //if this mask on(only extended ADV event can mask it), TX power include

}adv_event_prop_t;

#if 0
#define BLE_EXT_ADV_PROP_LEGACY_IND      (0x0013)
#define BLE_EXT_ADV_PROP_LEGACY_LD_DIR   (0x0015)
#define BLE_EXT_ADV_PROP_LEGACY_HD_DIR   (0x001d)
#define BLE_EXT_ADV_PROP_LEGACY_SCAN     (0x0012)
#define BLE_EXT_ADV_PROP_LEGACY_NONCONN  (0x0010)
#define BLE_EXT_ADV_PROP_MASK			 (0x7F)
#endif





#if 1
my_fifo_t			adv_sets;
u8					adv_sets_b[];

my_fifo_t			adv_pkts;
u8					adv_pkts_b[];

my_fifo_t			scan_rsps;
u8					scan_rsps_b[];




typedef struct {
	u8 type   :4;
	u8 rfu1   :1;
	u8 chan_sel:1;
	u8 txAddr :1;
	u8 rxAddr :1;
}rf_extAdv_head_t;




typedef struct{
	u32 dma_len;

	rf_extAdv_head_t  header;	//RA(1)_TA(1)_CHSEL(1)_RFU(1)_TYPE(4)
	u8  rf_len;				//LEN(6)_RFU(2)
	u8	advA[6];			//address
	u8	data[31];			//0-31 byte
}rf_packet_pri_adv_t;
#define MAX_LENGTH_PRIMARY_ADV_PKT				44   //sizeof(rf_packet_pri_adv_t) = 43




#define ADV_DAT_LEN		254		//max
typedef struct{
	u32 dma_len;            //won't be a fixed number as previous, should adjust with the mouse package number
	rf_extAdv_head_t  header;	//RA(1)_TA(1)_CHSEL(1)_RFU(1)_TYPE(4)
	u8  rf_len;				//LEN(8)

	u8	ext_hdr_len		:6;
	u8	adv_mode		:2;
	u8	ext_hdr[ADV_DAT_LEN];		//no sync info & acad
}rf_packet_ext_adv_t;
#define MAX_LENGTH_SECOND_ADV_PKT				264   //sizeof(rf_packet_ext_adv_t) = 261




struct ext_adv_config{
	u8  ext_adv_en;		//universal switch for ext adv
	u8  adv_set_num;	//max num for supported adv sets, default 4
	void* adv_set_entry;		//point to adv_sets
};

typedef struct{
	u8 chn_ind		:6;
	u8 ca			:1;
	u8 off_unit		:1;
	u16 aux_off		:13;
	u16 aux_phy		:3;
} aux_ptr_t;







//NOTE: this data structure must 4 bytes aligned
typedef struct
{
    u8		adv_handle;
    u8 		extAdv_en;
    u8 		adv_chn_mask;
    u8 		adv_filterPolicy;

    u8 		pri_phy;
    u8 		sec_phy;
	u8 		coding_ind;					//s2 or s8
    u8 		adv_sid;
    u8 		scan_req_noti_en;
    u8 		max_ext_adv_evt;
    u8 		ext_adv_evt;

//    u8 		periodicAdv_en;

	u16 	evt_props;
    u16 	maxLen_extAdv;			//for each ADV sets, this value can be different to save SRAM
    u16 	curLen_extAdv;
    u16 	maxLen_scanRsp;			//for each ADV sets, this value can be different to save SRAM
    u16 	curLen_scanRsp;
//	  u16 	maxLen_periodicAdv;
//	  u16 	curLen_periodicAdv;

	u16 	advInt_min;
	u16 	advInt_max;
	u16		advInt_use;


    u32		adv_event_tick;
	u32 	adv_begin_tick;				//24

//    u32		adv_intervalMin_tick;
//	  u32		adv_intervalMax_tick;
	u32 	adv_duration_tick;

	u8*		dat_extAdv;
	u8*		dat_scanRspData;                //Scan response data.
	u8*		dat_periodicAdv;

    rf_packet_pri_adv_t*		primary_adv;
	rf_packet_ext_adv_t*		secondary_adv;
//	rf_packet_ext_adv_t*		chain_adv;








	u8 own_addr_type;
	u8 peer_addr_type;
    u8 s_adv_max_skip;

    u8 adv_secondary_chan;


	u8 adv_tx_bit_map;				//ps: bit 0 for ext adv, 1 aux_ind, 2 chain_ind, 3 chain
	u8 adv_tx_bit;
	u8 adv_SetData_flag;

    s8 adv_tx_pow;





	u16 adi;
	u16 advInt_rand;				//16




	u32 	adv_interval;

	u32 	adv_rpa_timer;				//40
	u32 	s_adv_begin_tick;




	u8 own_addr[6];
    u8 peer_addr[6];

}ll_ext_adv_t;

#define MAX_LENGTH_ADV_CTRL				(sizeof(ll_ext_adv_t))   //sizeof(ll_ext_adv_t) =  ,  must 4 byte





typedef struct
{
    u8 		maxNum_advSets;
    u8		useNum_advSets;

    u8		last_advSet;
    u8		last_advHand;

    u8		T_SCAN_RSP_INTVL;


}ll_adv_mng_t;





#endif









/******************************************** User Interface  ********************************************************************/
ble_sts_t	blc_ll_setAdvRandomAddr(u8 advHandle, u8* rand_addr);


ble_sts_t 	blc_ll_setExtAdvParam(  u8 advHandle, 		 			adv_event_prop_t adv_evt_prop, u32 pri_advIntervalMin, u32 pri_advIntervalMax,
									u8 pri_advChnMap,	 			own_addr_type_t ownAddrType, 	u8 peerAddrType, 		u8  *peerAddr,
									adv_fp_type_t advFilterPolicy,  u8 adv_tx_pow,					u8 pri_adv_phy, 		u8 sec_adv_max_skip,
									u8 sec_adv_phy, 				u8 adv_sid, 					u8 scan_req_noti_en);
ble_sts_t	blc_ll_setExtAdvData(u8 advHandle, u8 operation, u8 fragment_prefer, u8 adv_dataLen, u8 *advdata);
ble_sts_t 	blc_ll_setExtScanRspData(u8 advHandle, u8 operation, u8 fragment_prefer, u8 scanRsp_dataLen, u8 *scanRspData);
ble_sts_t 	blc_ll_setExtAdvEnable_1(u8 extAdv_en, u8 sets_num, u8 advHandle, 	 u16 duration, 	  u8 max_extAdvEvt);
ble_sts_t	blc_ll_setExtAdvEnable_n(u8 extAdv_en, u8 sets_num, u8 *pData);

u16 	  	blc_ll_readMaxAdvDataLength(void);
u8		  	blc_ll_readNumberOfSupportedAdvSets(void);


ble_sts_t	blc_ll_setPeriodicAdvParam(u8 advHandle, u16 periodic_advIntervalMin, u16 periodic_advIntervalMax, u16 periodic_advProp);
ble_sts_t  	blc_ll_setPeriodicAdvData(u8 advHandle, u8 operation, u8 adv_dataLen, u8 *advdata);
ble_sts_t 	blc_ll_setPeriodicAdvEnable(u8 periodicAdv_en, u8 advHandle);





/****************************************** Stack Interface, user can not use!!! *************************************************/
ble_sts_t 	blc_hci_le_setExtAdvParam( hci_le_setExtAdvParam_cmdParam_t *para, u8 *pTxPower);

ble_sts_t 	blc_hci_le_setExtAdvEnable(u8 extAdv_en, u8 sets_num, u8 *pData);

ble_sts_t	blc_hci_le_removeAdvSet(u8 advHandle);
ble_sts_t	blc_hci_le_clearAdvSets(void);

int 		blt_send_ext_adv(ll_ext_adv_t*  cur_blta);
int  		blt_ext_adv_proc(void);
int 		blt_send_aux_adv(void);
u8 			blc_ll_findAvailableAdvSet(u8 advHandle);

#endif /* LL_ADV_EXT_H_ */
