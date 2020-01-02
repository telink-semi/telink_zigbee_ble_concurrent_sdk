/********************************************************************************************************
 * @file     zdo_internal.h
 *
 * @brief	 APIs used in the internal ZDO layer
 *
 * @author
 * @date     June. 10, 2017
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

#include "tl_common.h"
#include "../nwk/includes/nwk.h"
#include "zdo_api.h"



void zdo_nwk_candidateAssociateJoinStart(nlme_nwkDisc_cnf_t *arg);
/**
   Number of times device failes to send packet to the parent before rejoin
*/

#define			ZDO_NWK_MANAGER_MAX_SCAN_DURATION			5

#define			ZDO_NWK_MANAGER_CHANNEL_CHANGE				0xfe

#define			ZDO_NWK_MANAGER_ATTRIBUTES_CHANGE			0xff



typedef enum{
	ZDO_MGMT_NWK_REJOIN				= BIT(0),
	ZDO_MGMT_NWK_DEVICE_ANNOUNCE_TX	= BIT(1),
	ZDO_MGMT_NWK_KEY_SWITCH_TX		= BIT(2),
	ZDO_MGMT_NWK_STARTED			= BIT(3),	//Indicate NWK connection success
	ZDO_MGMT_NWK_SECURITY_EN		= BIT(4),
	ZDO_MGMT_REJOIN_DEFAULTCH		= BIT(5),
	ZDO_MGMT_LEAVE					= BIT(6),
}zdo_mgmt_flags;


typedef struct{
	//The address of the target for the binding
	u16	binding_target_addr;

	/*The IEEE address of the device
	generating the request.*/
	addrExt_t	src_ext_addr;

	/*The endpoint on the device generating
	the request.*/
	u8	src_endpoint;

	/*ProfileID which is to be matched
	between two End_Device_Bind_req
	received at the ZigBee Coordinator
	within the timeout value pre-configured
	in the ZigBee Coordinator.*/
	u16	profile_id;

	//  u8	num_in_clusters;

	//u16	in_cluster_lst[];

	//u8	num_out_clusters;

	//u16	out_cluster_lst[];
} zdo_edBindReqStack_t;

typedef struct{
	u8	*in_cluster_lst;
	u8	*out_cluster_lst;
	u8	num_in_clusters;
	u8	num_out_clusters;
} zdo_edBindReqPayloadStack_t;


#define		ZDO_EDBINDREQ_GETSRCEP(addr)			(*(((u8 *)addr)+9))

/****************************************************
 * Internal use for generating
 */
typedef struct
{
	ev_time_event_t 		*authCheckTimer;
	ev_time_event_t 		*synWithParentTimer;

	ev_time_event_t 		*nwkDiscReqTimerEvt;
	ev_time_event_t 		*rejoinBackffTimerEvt;

	void					*authCheckCnfBuffer;

	u16 					rejoinBackoffInterval;
	u16 					rejoinBackoffCnt;

	u16						total_transactions;
	u16						fail_transactions;

	u8						nwk_discovery_cnt:4;
	u8						nwk_rejoinScan_cnt:4;
	u8						link_failure_cnt;
	u8						pollCnt;
	u8						status_ind_cnt: 4;
	bool					resend_annce: 1;
	bool					zdp_data_req_busy: 1;
	bool					update_device_req_busy: 1;
	bool					update_device_req_pending: 1;
	bool					bad_link;
	u8						transaction_sn;
	u8						mgmt_leave_seq;
	u16						mgmt_leave_short_addr;
} zdo_nwk_manager_t;
extern zdo_nwk_manager_t g_zdo_nwk_manager;


/*****************************************
 * Internal use for ED scan result report to the remote device
 */
typedef struct
{
	//scan channel page
	u32	scan_channels;
	//scan duration
	u8	scan_duration;
	//scan count
	u8	scan_count;
	//remote device address which sent update req
	u16	dst_addr;
	//transaction sequence number
	u8	tsn;
}zdo_nwk_update_req_t;


typedef enum{
	SHORT_GROUPADDR_NODSTENDPOINT = 0x01,
	LONG_EXADDR_DSTENDPOINT = 0x03
}bind_req_dst_addr_mode;


/*******************************************************************************************************************
 * @brief	This function would be called when device startup complete, e.g. by zdo_nlme_join_confirm, zdo_nlme_join_done,
 * 			zdo_nlme_network_discovery_confirm_cb and zdo_permit_join_confirm. If status is success, may store NWK info to
 * 			the flash.
 *
 * @param	param: buffer address of the packet
 *
 * @return	none
 */

void zdo_startup_complete(void *arg);

#ifdef ZB_SECURITY
/**********************************************************************************************************
 * @brief	Authentication check call back interface. If secure required and after 2 seconds, the state still un-secured,
 * 			this function would be called.
 *
 * @param	none
 *
 * @return	none
 */

s32 zdo_auth_check_timer_cb(void *arg);
#endif

/*****************************************************************************
 * @brief	Interface rise mgmt_flas
 *
 * @param	f: see enum zdo_mgmt_flags
 */
void zdo_mgmt_flag_rise(zdo_mgmt_flags f);

/**********************************************************************************
 * @brief	Interface to clear the mgmt_flas
 *
 * @param	f: see enum zdo_mgmt_flags
 */
void zdo_mgmt_flag_clr(zdo_mgmt_flags f);

/**********************************************************************************
 * @brief	Interface to check whether the flag has been polled or not
 *
 * @param	f: see enum zdo_mgmt_flags
 *
 * @return	TRUE: flag polled, otherwise FALSE
 */
bool zdo_mgmt_flag_check(zdo_mgmt_flags f);

/********************************************************************************************************
 * @brief	zdo_mgmt_nwk_update_req cmd send interface
 *
 * @param	br: ZDO MGMT network update request strut
 * 			zzr: ZDO ZDP request strut
 *
 * @return	ZDO_SUCCESS OR ZDO_INSUFFICIENT_SPACE when TX packet runout
 */

zdo_status_t zdo_mgmt_nwk_update_req(zdo_mgmt_nwk_update_req_t *br, zdo_zdp_req_t *zzr);


/*****************************************************************************************************
 * @brief	This interface check the leave complete cmd, and restore the NWK layer pending list
 *
 * @param	zbuff: buffer address of the data packet
 *
 * @return	ZDO_SUCCESS/ZDO_FAIL
 */
void zdo_leave_complete_process(void *buf, u8 st);
void zdo_mgmt_nwk_leave(u8 rejoin, nlme_leave_cnf_t *lc);


/*************************************************************************************
 * @brief	Unbinding request function, invoke from external applications to send a Unbind_req message
 *
 * @param	zdo_bind_req_t - info of binding request
 * 			zzr - zdo zdp request struct used internal, should specify dst addr, addr mode and cb function
 */
zdo_status_t zdo_unbind_req(zdo_edBindReq_user_t *ubr, zdo_zdp_req_t *zzr);


zdo_status_t zdo_bind_unbind_req(zdo_bind_req_t *br, zdo_zdp_req_t *zzr, bool bind);


/********************************************************************************************************
 * @brief	The End_Device_Bind_req is generated from a Local Device wishing to perform
			End Device Bind with a Remote Device. The End_Device_Bind_req is generated,
			typically based on some user action like a button press. The destination addressing
			on this command shall be unicast, and the destination address shall be that of the
			ZigBee Coordinator.
 *
 * @param	req: zdo_end_device_bind_req_t request strut
 * 			zzr: ZDO ZDP request strut
 *
 * @return	none
 */
zdo_status_t zdo_end_device_bind_req(zdo_edBindReq_user_t *req,zdo_zdp_req_t *zzr);


zdo_status_t zdo_txBufInit(u8 **txBuf,u8 **zdu, u8 reqLen);


void af_epDescInit(void);

s32 zdo_change_channel_cb(void *arg);

s32 zdoMgmtLeaveCmdProcessCb(void *arg, u8 seqNo, u16 shortAddr);

/****************************************************************************************************************
 * @brief	Interface used to send out leave response message after successfully leave the network
 *
 * @param	buf: packet address of the leave req
 * 			status: leave status
 *
 * @return	none
 */
void zdo_mgmt_leave_resp_send(void *buf, u8 status, u8 seqNum, u16 dstAddr);

void zdo_start_ed_scan(u8 *buf);

