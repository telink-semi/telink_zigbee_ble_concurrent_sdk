/********************************************************************************************************
 * @file     aps_stackUse.h
 *
 * @brief    File contains APS layer used interface
 *
 * @author
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
#pragma once

#include "tl_common.h"
#include "aps_api.h"
#include "../nwk/includes/nwk.h"

enum{
	APS_ATTR_CHANNEL_MASK = 0,
	APS_ATTR_USE_EPID,
	APS_ATTR_DESIGNATED_COORDINATOR,
	APS_ATTR_NONMENBER_RAIUS,
	PS_ATTT_USE_INSECURITY_JOIN,
	APS_ATTT_SECURITY_LEVEL,
	APS_ATTT_DISSECURITY,
	APS_ATTT_SENDTESTBUFREQ,
	APS_ONLYACCEPT_ENCRYPTEDCMD,
	APS_LEGACY_SUPPORT,
	APS_REMOVE_DEVICE,
	APS_ATTT_COUNTEDPACKETTX,
	APS_ATT_USESECURE_REJOIN,
	APS_ATT_JOINTONWK,
	APS_ADD_GROUP,
	APS_DELETE_GROUP,
	APS_DELETE_ALLGROUP,
	APS_BINDING_REQ,
	APS_DATA_REQUEST,
	APS_ADD_EP,
	APS_ATTT_DISNWKSECURITY,
	APS_ATT_PERMITJOIN_SET = 21,

};

typedef enum{
	APS_ZDO_ED_SCAN_MASK = 				BIT(0),
	APS_CHANNEL_MANAGER_ED_SCAN_MASK = 	BIT(1)
}aps_flag_e;

typedef enum{
	APX_TX_CACHE_STA_TODO,
	APX_TX_CACHE_STA_ADDR_REQ,
	APX_TX_CACHE_STA_TXING,
	APX_TX_CACHE_STA_WAITNIG_ACK,
	APX_TX_CACHE_STA_RETRY,
	APX_TX_CACHE_STA_DONE,
}aps_tx_chache_state_e;

typedef enum{
	APS_TX_EVENT_TX_TODO,
	APS_TX_EVENT_RETRY,
	APS_TX_EVENT_WAITING_ACK,
	APS_TX_EVENT_DONE,
}aps_tx_chache_evt_e;

#define APS_TX_CHCHE_NUM_MAX	12
typedef struct{
    union{
    	u16		  addr_short;
		addrExt_t addr_long;
	}dstAddr;

	u8	*payload;

    u8  dstAddrMode;
    u8  dstEndpoint;
	u8	ep;					//srcEp
	u8	handler;      		//real data handler

	u8	apsCount;     		//real data aps count
	u8	zdpSeqnoAddrReq;  	//the aps count for nwk address req
	u8	used:1;
	u8	addrReqNeed:1;
	u8	ackNeed:1;
	u8	interPAN:1;
	u8	state: 4;
	u8	retries;

	s8	apsAckWaitTimeOut;
	s8	apsAddrWaitTimeout;
	u8  resv[2];
}aps_tx_chache_list_t;

#define			APS_SET_ZDO_ED_SCAN_FLAG()					(aps_ib.aps_flags |= APS_ZDO_ED_SCAN_MASK )
#define			APS_CLEAR_ZDO_ED_SCAN_FLAG()				(aps_ib.aps_flags &= ~APS_ZDO_ED_SCAN_MASK )
#define			APS_GET_ZDO_ED_SCAN_FLAG()					(aps_ib.aps_flags & APS_ZDO_ED_SCAN_MASK )

#define			APS_SET_CHANNEL_MANAGER_ED_SCAN_FLAG()		(aps_ib.aps_flags |= APS_CHANNEL_MANAGER_ED_SCAN_MASK)
#define			APS_CLEAR_CHANNEL_MANAGER_ED_SCAN_FLAG()	(aps_ib.aps_flags &= ~APS_CHANNEL_MANAGER_ED_SCAN_MASK)
#define			APS_GET_CHANNEL_MANAGER_ED_SCAN_FLAG()		(aps_ib.aps_flags & APS_CHANNEL_MANAGER_ED_SCAN_MASK)


void aps_nwk_data_confirm_cb(void *p);
void aps_nwk_data_indication_cb(void *p);
void aps_route_discovery_confirm(void *p);

u8 aps_get_counter_value(void);
void aps_interPanDataIndCb(void *p);
bool aps_bindingTblMatched(u16 clusterID, u8 srcEp);

void aps_data_request(void *p);
void aps_conf(apsdeDataConf_t *pCnf);
aps_tx_chache_list_t *apsTxDataPost(bool ackNeed, bool addrReqNeed, bool interPAN, u8 *pdu, apsdeDataConf_t *pCnf);

void apsParentAnnceTimerStart(void);

aps_status_t aps_route_disc_req(nlme_routeDisc_req_t *pRouteDiscReq);

void apsCleanToStopSecondClock(void);
