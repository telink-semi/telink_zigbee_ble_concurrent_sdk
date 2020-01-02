/********************************************************************************************************
 * @file     nwk_internal.h
 *
 * @brief	 Network layer internals
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
#ifndef NWK_INTERNAL_H
#define NWK_INTERNAL_H 1

#include "tl_common.h"
#include "nwk_neighbor.h"
#include "nwk.h"


/***************************************************************************
* @brief	this parameter shows a acceptable energy level on channel
*/
#define ZB_NWK_CHANNEL_ACCEPT_LEVEL 60

/***************************************************************************
* @brief	MWK tx pending table size
*/
#define PENDING_TABLE_NUM		16


/***************************************************************************
* @brief	NWK Mesh route stuff: route discovery table size
*/
#define ROUTE_DISC_TABLE_NUM	16

/***************************************************************************
* @brief	The number of OctetDurations, on the originator of a multicast
* 			route request, between receiving a route reply and sending a
* 			message to validate the route.
*/
#define NWK_WAIT_BEFORE_VALIDATION	(0x500 / 1000)//s

/***************************************************************************
* @brief	The number of OctetDurations until a route discovery expires
*/
#define NWK_ROUTE_DISCOVERY_TIME	(0x2710 / 1000)//s

/***************************************************************************
* @brief	The number of times the first broadcast route request command
*/
#define MWK_INITIAL_RREQ_RETRIES 	3

/***************************************************************************
* @brief	The number of times the broadcast transmission of a route request
* 			command frame is retries on relay by an intermediate ZigBee router
* 			or ZigBee coordinator
*/
#define NWK_RREQ_RETRIES	2

/***************************************************************************
* @brief	The number of OctetDurations between retries of a broadcast route request command
*/
#define NWK_RREQ_RETRY_INTERVAL		0xFE//ms


#define NWK_MIN_RREQ_JITTER			2//ms

#define NWK_MAX_RREQ_JITTER			128//ms




#define NWK_DATA_PENDIND_TIMEOUT	60//s



/***************************************************************************
* @brief	Calculate path cost from LQI
*/
#define NWK_LQI_TO_PATH_COST(lqi, path_cost) do                       \
{                                                                     \
    u8 i = 0;                               		                  \
    while ( 32*(i+1) < lqi )                                          \
    {                                                                 \
      i++;                                                            \
    }                                                                 \
    path_cost = (7 - i) ? (7 - i) : 1;                                \
} while (0)


extern tl_zb_normal_neighbor_entry_t *g_nbEntyBackup;

extern nwk_txDataPendEntry_t g_txDataPendTab[];


#ifdef ZB_NWK_DISTRIBUTED_ADDRESS_ASSIGN

u16 tl_zbNwkDistributeAddrCskipGet(u8 depth);

#else
  //#error Implement Stochastic address assign mechanism
#endif /* ZB_NWK_DISTRIBUTED_ADDRESS_ASSIGN */



/**
   zb_nwk_leave_handler
   @param param - buffer with scan result
 */
void tl_zbNwkRejoinScanConfirm(void *arg) ;


/**
   zb_nlme_rejoin_response_timeout

   @param param - buffer
   @return nothing
 */
s32 tl_zbNlmeRejoinRespTimeoutCb(void *arg);



/**
   tl_zbNwkNlmeOrphanScanConfirm
   @param param - buffer

 */
void tl_zbNwkNlmeOrphanScanConfirm(void *arg);

void tl_zbNwkNlmeNwkDiscConfirm(void *arg);

void tl_zbNwkNibInit(u8 coldReset);

void tl_zbNwkRemoveParentFromPotentialParents(tl_zb_addition_neighbor_entry_t *parent);

void tl_zbNwkPanidConflictProcess(void *arg);



void nwkMsgSendCb(void *arg);

void keepaliveMsgSendStop(void);

void tl_zbNwkRejoinRespTimeoutStart(void);
void tl_zbNwkRejoinRespTimeoutStop(void);

void nwkTxDataPendTabInit(void);
void nwkBrcTransTabInit(void);
void nwkRouteDiscTabInit(void);
void nwkRoutingTabInit(void);

void nwk_fwdPacket(void *arg, nwk_hdr_t *hdr, u8 *nsdu, u8 nsduLen);

void tl_zbNwkBeaconPayloadUpdate(void);

void nwkRoutingTabEntryDstDel(u16 dstAddr);

void tl_zbNwkInterPanDataReq(void *arg);

tl_zb_addition_neighbor_entry_t *AdditionNeighborEntryGetFromExtPanId(extPANId_t extPanId);

tl_zb_normal_neighbor_entry_t *tl_zbNeighborTableSearchFromAddrmapIdx(u16 addrMapIdx);

tl_zb_normal_neighbor_entry_t *tl_zbNeighborTabSearchForChildEndDev(tl_zb_normal_neighbor_entry_t *curEntry);

void tl_zbNwkReigsterPollCb(edpollIndication2APS cb);

void tl_zbNwkUnreigsterPollCb(void );

void tl_zbNwkSendRejoinRespCmd(void *arg, nwk_hdr_t *pNwkHdr, nwkCmd_t *pRejoinRespCmd, bool indirect, u8 handle);

void nwkTxDataPendTabEntryClear(nwk_txDataPendEntry_t *entry);

void *nwkTxDataCachePacketCopy(void *srcBuf);

void nwk_tx(void *arg, nwk_hdr_t *hdr, u16 dstAddr, bool indirect, u8 *nsdu, u8 nsduLen);

void nwkNldeDataCnf(void *arg, u8 status, u8 handle);

void nwkReportCmdSend(void *arg, nwk_hdr_t *pNwkHdr, nwkCmd_t *pNwkReportCmd, u8 handle);

void nwkReportCmdHandler(void *arg, nwkCmd_t *pNwkReportCmd);

bool tl_zbNwkPanidConflictDetect(u16 pid, extPANId_t epid);

void tl_zbNwkPanidConflictSetPanidStart(void);

//Nwk routing
nwk_routingTabEntry_t *nwkRoutingTabEntryCreate(u16 dstAddr);

void nwkRoutingTabEntryClear(nwk_routingTabEntry_t *entry);

void nwkRouteRecTabEntryDstDel(u16 dstAddr);

nwk_routeRecordTabEntry_t *nwkRouteRecTabEntryCreat(u16 nwkAddr, nwkCmd_t *pRouteRecordCmd);

nwk_routeRecordTabEntry_t *nwkRouteRecTabEntryFind(u16 nwkAddr);

void nwkRoutingTabEntryInactiveSet(u16 nebAddr);


nwk_routingTabEntry_t *nwkRoutingTabEntryDstFind(u16 dstAddr);

nwk_routingTabEntry_t *nwkRoutingTabEntryFind(u16 shortAddr);

nwk_routingTabEntry_t *nwkRoutingTabEntryDstActiveGet(u16 dstAddr);

nwk_routingTabEntry_t *nwkRoutingTabEntryNextHopActiveGet(u16 shortAddr);

void nwkSrcRouteRequiredClear(u16 dstAddr);

zb_nwk_status_t nwkSourceRoutePacketRelayFilter(nwk_hdr_t *hdr);

tl_zb_normal_neighbor_entry_t *tl_zbNeighborTabSearchForRouter(tl_zb_normal_neighbor_entry_t *curEntry);

void nwkRouteMaintenance(nwk_hdr_t *hdr, u16 neighborAddr);

u16 nwkSrcRouteReplayNextHop(nwk_hdr_t *hdr);

nwk_routingTabEntry_t *nwkRoutingTabGetNextHop(nwk_hdr_t *hdr);

nwk_routeDiscEntry_t *nwkRouteDiscEntryDstFind(u16 dstAddr);

zb_nwk_status_t nwkTxDataRouteDiscStart(nwk_hdr_t *hdr);

void nwkRouteRecordInitiation(u16 srcAddr, u16 dstAddr);

//Brc
zb_nwk_status_t nwkBrcTimerStart(void *arg, nwk_hdr_t *hdr, u8 *nsdu, u8 nsduLen);

void nwkBrcTransTabEntryClear(nwk_brcTransRecordEntry_t *entry);

nwk_brcTransRecordEntry_t *nwkBrcTransEntryFind(u16 srcAddr, u8 seqNum);

void nwkBrcMsgAddSender(nwk_brcTransRecordEntry_t *entry, u16 macSrcAddr);

bool nwkBrcCheckDevMatch(u16 dstAddr);

nwk_brcTransRecordEntry_t *nwkBrcTransEntryCreate(nwk_txDataPendEntry_t *pEntry, u16 srcAddr, u8 seqNum);

void nwkBrcMsgAllEndDevStart(nwk_brcTransRecordEntry_t *entry);

void nwkBrcMsgPassiveAckTimeoutStart(nwk_brcTransRecordEntry_t *entry);


//tx pending
nwk_txDataPendEntry_t *nwkTxDataPendTabEntryFind(u16 srcAddr, u8 seqNum);

nwk_txDataPendEntry_t *nwkTxDataPendTabEntryRtDiscFind(u16 dstAddr, u8 routeReqId);

nwk_txDataPendEntry_t *nwkTxDataPendTabEntryAdd(void *arg, nwk_hdr_t *hdr, u8 *nsdu, u8 nsduLen);

//leave
void nwkLeaveCnfDeliver(void *arg, u8 status, extAddr_t extAddr);

void nwkLeaveReqSend(void *arg, nwk_hdr_t *hdr, nwkCmd_t *leaveCmd, u8 handle);

//join
void tl_zbMcpsRejoinRespCnfHandler(void *arg, u8 status, u16 dstAddr);

//fromation
void tl_zbNwkFormationEdScanConfirm(void *arg);

void tl_zbNwkFormationActiveScanConfirm(void *arg);

//end device timeout
void nwkEndDevTimeoutReqCnfHandler(void *arg);
void nwkEndDevTimeoutRspCnfHandler(void *arg);

//nwk command handler
void tl_zbNwkNetworkUpdateCmdHandler(void *arg, nwk_hdr_t *hdr, nwkCmd_t *pNwkUpdateCmd);

void tl_zbNwkRejoinRespCmdHandler(void *arg, nwk_hdr_t *pNwkHdr, nwkCmd_t *pRejoinRspCmd);

void tl_zbNwkLeaveReqCmdHandler(void *arg, nwk_hdr_t *pNwkHdr, nwkCmd_t *pNwkLeaveCmd);

void tl_zbNwkStatusCmdHandler(void *arg, nwk_hdr_t *hdr, nwkCmd_t *nwkStatusCmd);

void nwkEndDevTimeoutReqCmdHandler(void *arg, nwk_hdr_t *hdr, nwkCmd_t *pEndDevTimeoutReqCmd);

void nwkEndDevTimeoutRspCmdHandler(void *arg, nwk_hdr_t *hdr, nwkCmd_t *pEndDevTimeoutRspCmd);

void tl_zbNwkReportCmdHandler(void *arg, nwk_hdr_t *hdr, nwkCmd_t *nwkReportCmd);

void tl_zbNwkLinkStatusCmdHandler(void *arg, nwk_hdr_t *pNwkHdr, nwkCmd_t *pLinkStatusCmd);

void tl_zbNwkRejoinReqCmdHandler(void *arg, nwk_hdr_t *pNwkHdr, nwkCmd_t *pRejoinReqCmd);

void nwkRouteRecordCmdHandler(void *arg, nwk_hdr_t *hdr, nwkCmd_t *pRouteRecordCmd);

void nwkRouteReplyCmdHandler(void *arg, nwk_hdr_t *hdr, nwkCmd_t *pRouteReplyCmd);

void nwkRouteReqCmdHandler(void *arg, nwk_hdr_t *hdr, nwkCmd_t *pRouteReqCmd);

#endif /* NWK_INTERNAL_H */
