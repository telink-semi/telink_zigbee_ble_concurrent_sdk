/********************************************************************************************************
 * @file     mac_internal.h
 *
 * @brief    some Apis used by MAC layer only
 *
 * @author
 * @date     Dec. 1, 2016
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
#ifndef MAC_INTERNAL_INCLUDED
#define MAC_INTERNAL_INCLUDED 1

#include "tl_common.h"
#include "tl_zb_mac.h"


/*! \addtogroup ZB_MAC */
/*! @{ */



//MAC internal Handles
typedef enum{
	MAC_HANDLE_MIN = 0xDF,
	MAC_HANDLE_ASSOCIATION_REQ,
	MAC_HANDLE_ASSOCIATION_RSP,
	MAC_HANDLE_DISASSOCIATION_NOTIFY,
	MAC_HANDLE_BEACON,
	MAC_HANDLE_BEACON_REQ,
	MAC_HANDLE_COORDINATOR_REALIGNMENT,
	MAC_HANDLE_DEVICESTART_REQ_CMD,
	MAC_HANDLE_PANIDCONFLICT_CMD,
	MAC_HANDLE_PULL_FROM_UPLAYER,
	MAC_HANDLE_PULL_ASSOCIATION,
	MAC_HANDLE_ORPHAN_NOTIFICATION
}mac_handle_e;

/**
 realignment command format
*/
typedef struct{
	u8 cmdId;
	u16 panId;
	u16 coordShortAddr;
	u8 logicalChannel;
	u16 shortAddr;
	u8  channelPage;
} zb_coord_realignment_cmd_t;



u8 zb_mac_check_security(zb_buf_t *data_buf);

typedef struct{
	void *pdu;
	u8	pduLen;
}mac_dataSend_t;

void tl_zbMacReset(void);

mac_sts_t tl_zbMacTx(void *buf, void *pdu, u8 pduLen, bool needAck);

u8 tl_zbMacMlmeDataRequestSend(zb_mlme_data_req_cmd_t *params);

u8 tl_zbMacPendindDataPush(zb_mac_pending_trans_t *pend_data, u8 type);

void tl_zbMacIndirectDataTimerCancel(void);

void tl_zbMacBeaconRequestCb(void *arg) ;

void tl_zbMacMlmeDataRequestCb(zb_mac_raw_frame_t *arg);

u8 tl_zbMacMlmeCoordRealignmentCmdSend(bool is_broadcast, addrExt_t orphaned_dev_ext_addr,
                                     	 	 	 	 u16 orphaned_dev_short_addr, void *arg);

void tl_zbMacActiveScanListAdd(void *arg);

void tl_zbMacOrphanScanStatusUpdate(void);

void tl_zbMacParamsUpdate(void *arg);

u8 tl_zbMacCommStatusSend(void *buf, u8 status);

u8 tl_zbMacMlmeDataRequestCmdSend(zb_mlme_data_req_cmd_t *pReq, void *arg, u8 handle);


void tl_zbMacAssociateRespReceived(u8 status);

void tl_zbMaxTxConfirmCb(void *arg, u8 status);

/*
 * callback when receive primitive from upper layer(NWK layer...)
 *
 * */
void tl_zbMacStartRequestHandler(void *arg);
void tl_zbMacMcpsDataRequestHandler(void *arg);
void tl_zbMacAssociateRequestHandler(void *arg);
void tl_zbMacAssociateResponseHandler(void *arg);

void tl_zbMacDisassociateRequestHandler(void *arg);
void tl_zbMacOrphanResponseHandler(void *arg);
void tl_zbMacPollRequestHandler(void *arg);
void tl_zbMacResetRequestHandler(void *arg);
void tl_zbMacScanRequestHandler(void *arg);

void tl_zbMlmeCmdDisassociateNotifyRecvd(zb_mac_raw_frame_t *pData, tl_zb_mac_mhr_t *mHdr, u8 mhrLen);

/*
 * callback when receive indication primitive from PHY layer
 *
 * */
void tl_zbPhyIndication(zb_mac_raw_frame_t *buf, tl_zb_mac_mhr_t *macHdr, u8 macHdrLen);
void tl_zbPhyMldeIndication(zb_mac_raw_frame_t *pData, tl_zb_mac_mhr_t *macHdr, u8 macHdrLen);
void tl_zbPhyMlmeIndicate(zb_mac_raw_frame_t *pData, tl_zb_mac_mhr_t *macHdr, u8 macHdrLen);

mac_sts_t macDataPending(void *arg, addr_t dstAddr);

void tl_zbMacAssociateRequestStatusCheck(void *arg, u8 status);
void tl_zbMacDisassociateNotifyCmdConfirm(void *arg, u8 status);
void tl_zbMacDataRequestStatusCheck(void *arg, u8 status);
void tl_zbMacStartReqConfirm(void *arg, u8 status);
void tl_zbMacCmdPanIdConflictNotifySendCheck(void *arg, u8 status);
void tl_zbMacMlmeBeaconSendConfirm(void *arg, u8 status);
void tl_zbMacOrphanResponseStatusCheck(void *arg, u8 status);


/*! @} */

#endif
