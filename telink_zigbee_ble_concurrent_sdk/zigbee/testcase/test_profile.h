/********************************************************************************************************
 * @file     test_profile.h
 *
 * @brief	 the configuration header file of zigbee profile
 *
 * @author
 * @date     May. 27, 2017
 *
 * @par      Copyright (c) 2017, Telink Semiconductor (Shanghai) Co., Ltd.
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


#define TEST_PROFILE_ID												0x7F01	//test profile ID
#define TEST_PROFILE_EP												240		//test profile endpoint number (hardcoded)

#define DEV_ID_TEST_DRIVER											0x0000
#define DEV_ID_DUT													0xAAAA
#define DEV_ID_FULL_DUT												0xFFFF

#define TEST_CLUSTER_ID_TRANSMIT_COUNTED_PACKETS					0x0001
#define TEST_CLUSTER_ID_RESET_PACKET_CNT							0x0002
#define TEST_CLUSTER_ID_RETRIEVE_PACKET_CNT							0x0003
#define TEST_CLUSTER_ID_PACKET_CNT_RSP								0x0004
#define TEST_CLUSTER_ID_BUFFER_TEST_REQ								0x001C
#define TEST_CLUSTER_ID_BUFFER_TEST_GROUP_REQ						0x001D
#define TEST_CLUSTER_ID_BUFFER_TEST_RSP								0x0054
#define TEST_CLUSTER_ID_BUFFER_TEST_GROUP_RSP						0x0055
#define TEST_CLUSTER_ID_ROUTE_DISC_REQ								0x1000
#define TEST_CLUSTER_ID_ROUTE_DISC_RSP								0x1001
#define TEST_CLUSTER_ID_FREE_FROM_REQ								0xA0A8
#define TEST_CLUSTER_ID_FREE_FROM_RSP								0xE000
#define TEST_CLUSTER_ID_FREE_FROM_NO_DATA_RSP						0xE001
#define TEST_CLUSTER_ID_BROADCAST_REQ								0xF000
#define TEST_CLUSTER_ID_BROADCAST_TO_ALL_DEV_RSP					0xF001
#define TEST_CLUSTER_ID_BROADCAST_TO_ALL_RX_ON_WHEN_IDLE_DEV_RSP	0xF00A
#define TEST_CLUSTER_ID_BROADCAST_TO_ALL_ROUTERS_AND_COORD_RSP		0xF00E




/**
   Buffer test request
 */
typedef enum
{
	BUFFER_TEST_SHORT_ADDR_MODE,
	BUFFER_TEST_GROUP_ADDR_MODE,
	BUFFER_TEST_ADDR_NONE_MODE
}bufferTest_addrMode_t;

typedef struct
{
	u16	clusterId;
	u16	dstAddr;//destination short address
	u8	len;  //length (in bytes) of the packet
	u8	srcEp;
	u8	dstEp;
	bufferTest_addrMode_t	addrMode;
}bufferTestReq_t;

/**
   Transmit buffer test response
*/
typedef struct
{
	u16 clusterId;
	u16	dstAddr;
	u8	len;  //Length (in bytes) of the packet
	u8	status;//Status of the response
	u8	srcEp;
	u8	dstEp;
}bufferTestResp_t;

typedef struct
{
	u16	shortAddr;	//the short address of the destination
	u16	overallSendPacketNum;//the count of packets to send to the destination
	u8	len;		//length of the packet(including octet seq counter and octet seq)
	u8	intervalIn10Ms;//the interval in a unit of 10ms, the valid range from 10ms (1) to 1s (100)
}countedPacketTxReq_t;

typedef struct{
	u16 sendIndex;
	u16 sendPacketNum;
	u16	dstAddr;
	u8	sendLen;
	u8	handle;
}countedPacketTxRecord_t;

typedef struct
{
	u8	len;//precedes the octet seq counter and the octet seq
	u16	seqCounter;//Packet seq cnt during execution of the test
	u8	octetSeq[];
}countedPacketsTx_frame;


void testProfileInit(void);
void bufferTestReqSend(bufferTest_addrMode_t addrMode, u16 dstAddr);
void transmitCountedPackets(countedPacketTxReq_t *pReq);



#if 0

#define		TL_DEVICE_TESTDRIVER						0
#define		TL_DEVICE_DUT								0xaaaa
#define		TL_DEVICE_FFDUT								0xffff
#if COORDINATOR
#define		TL_TEST_PROFILE_ID							0x0103 //test profile ID
#define		TL_TEST_PROFILE_EP							1    //test profile endpoint number (hardcoded)
#define		TL_INCLUSTER1								0
#define		TL_INCLUSTER2								0x0070
#define		TL_INCLUSTER3								0x008c
#define		TL_INCLUSTER4								0x00c4
#define		TL_INCLUSTER5								0x00ff

#else
#define		TL_TEST_PROFILE_ID							0x7f01 //test profile ID
#define		TL_TEST_PROFILE_EP							240    //test profile endpoint number (hardcoded)
#endif

#define		TP_TX_COUNTED_PACKETS_CLID					0x0001
#define		TP_RESET_PACKET_CNT_CLID					0x0002
#define		TP_RETRIVE_PACKET_CNT_CLID					0x0003
#define		TP_PACKET_CNT_RSP_CLID						0x0004


#define		TP_BUFFER_TEST_REQUEST_CLID      			0x001C
#define		TP_BUFFER_TEST_GROUPREQ_CLID      			0x001D


#define		TP_BUFFER_TEST_RESPONSE_CLID     			0x0054
#define		TP_BUFFER_TEST_GROUPRSP_CLID     			0x0055

#define		TP_ROUTEDISCOVERY_REQ_CLID					0x1000
#define		TP_ROUTEDISCOVERY_RSP_CLID					0x1001

#define		TP_FREEFORM_REQ_CLID						0xa0a8
#define		TP_FREEFORM_RSP_CLID						0xe000
#define		TP_FREEFORM_NODATA_RSP_CLID					0xe001

#define		TP_BROADCAST_REQ_CLID						0xf000
#define		TP_BROADCAST_TO_ALLDEVICE_RSP_CLID			0xf001
#define		TP_BROADCAST_TO_ALLRXONDEVICE_RSP_CLID		0xf00a
#define		TP_BROADCAST_TO_ALLROUTERCOOR_RSP_CLID		0xf00e


#define		TP_TESTINCLUSTER1							0x00e0
#define		TP_TESTOUTCLUSTER1							0x0038
#define		TP_TESTOUTCLUSTER2							0x00a8


#define		TP_BUFFER_TEST_OK   						0x00 /* Successful buffer test */
#define		TP_BUFFER_TEST_FAIL 						0x01 /* Transmission failure on first attempt */
/**
   Buffer test request
 */
typedef enum{
	TEST_BUFFER_SEND_NORMAL,
	TEST_BUFFER_SEND_DSTADDR_EP_NOTPRESETNT,
	TEST_BUFFER_SEND_SHORT_GROUPADDR_NOEP
}testBuffer_deliveryMode_e;
typedef struct{
	u16	profileID;//Profile ID
	u16	dstAddr;//destination short address
	u8	len;  //< Length (in bytes) of the packet
	u8	srcEp;
	u8	dstEp;
	testBuffer_deliveryMode_e	deliveryMode;
	u16	groupAddr;//only present when deliveryModes set to group
}tl_bufferTestReq_t;

typedef struct{
	u8 len;
}tl_bufferTestReq_frame;


typedef struct{
	// the short address of the destination
	u16	shortAddr;
	//length of the packet(including octet seq counter and octet seq)
	u8	len;
	//the interval in a unit of 10ms, the valid range from 10ms (1) to 1s (100)
	u8	intervalIn10Ms;
	//the count of packets to send to the destination
	u16	overallSendPacketNum;
}tl_countedPacketTxReq_t;

typedef struct{
	//precedes the octet seq counter and the octet seq
	u8	len;
	//Packet seq cnt during execution of the test
	u16	seqCounter;
	u8	octetSeq[1];
}tl_countedPacketsTx_frame;


/**
   Transmit buffer test response
*/
typedef struct{
	u16		dstAddr;
	u8		len;  //Length (in bytes) of the packet
	u8		status;//Status of the response
	u8		srcEp;
	u8		dstEp;
}tl_bufferTestResp_t;

typedef struct{
	u8 len;
	u8 status;
}tl_bufferTestRspFrame_t;






void testBufferReq(void *p);
void testCountedPacketsTxReq(void *p);
void tl_af_add_ep(u8 ep);
#endif
