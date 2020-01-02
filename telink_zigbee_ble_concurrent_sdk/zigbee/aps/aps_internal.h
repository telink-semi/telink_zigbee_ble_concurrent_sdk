/********************************************************************************************************
 * @file     aps_internal.h
 *
 * @brief    File contains APS layer used define, macro and primitives
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

#define		APS_LAYER_DEBUG_EN						0
#define		APS_HANDLE_RANGE_MASK					0x3F//64

#define		NWK_DATA_INDICATION_PRIMITIVE_LEN		20

/********************************************************************************************
 * APS Frame Control Convert macro
 */

typedef enum{
	APS_FRAME_TYPE_DATA = 0,
	APS_FRAME_TYPE_CMD = BIT(0),
	APS_FRAME_TYPE_ACK = BIT(1),
	APS_FRAME_TYPE_RESERVED = BIT(0)|BIT(1),
	APS_DELIVERY_MODE_UNICAST = 0,
	APS_DELIVERY_MODE_BROADCAST = BIT(3),
	APS_DELIVERY_MODE_GROUP = BIT(2)|BIT(3),
	APS_ACK_DATA_FRAME = 0,
	APS_ACK_CMD_FRAME = BIT(4),
	APS_SECURITY_TYPE_ONE = 0,
	APS_SECURITY_TYPE_TWO = BIT(5),
	APS_ACK_NEED = BIT(6),
	APS_ACK_NONEED = 0,
	APS_EXTENDED_HEADER_PRESENT = BIT(7),
	APS_EXTENDED_HEADER_FALSE = 0,
}aps_frame_control_bits_values;



#define		APS_FRAME_TYPE_MASK						(BIT(0)|BIT(1))
#define		APS_FRAME_DELIVERY_MODE_MASK			(BIT(2)|BIT(3))
#define		APS_FRAME_ACK_MODE_MASK					(BIT(4))
#define		APS_FRAME_SECURITY_EN_MASK				(BIT(5))
#define		APS_FRAME_ACK_REQ_MASK					(BIT(6))
#define		APS_FRAME_EXTENDED_HEADER_MASK			(BIT(7))

//Frame type process
#define		APS_FRAME_TYPE_GET(h)						(h&APS_FRAME_TYPE_MASK)
#define		APS_FRAME_TYPE_IS_DATA(h)					((h&APS_FRAME_TYPE_MASK) == APS_FRAME_TYPE_DATA)
#define		APS_FRAME_TYPE_IS_CMD(h)					((h&APS_FRAME_TYPE_MASK) == APS_FRAME_TYPE_CMD)
#define		APS_FRAME_TYPE_IS_ACK(h)					((h&APS_FRAME_TYPE_MASK) == APS_FRAME_TYPE_ACK)
//frame type set
#define		APS_FRAME_TYPE_SET(h,t)							\
(														\
((h) &= (~APS_FRAME_TYPE_MASK)),						\
((h) |= (t))											\
)

//Delivery mode process
#define		APS_DELIVERY_MODE_GET(h)					(h&APS_FRAME_DELIVERY_MODE_MASK)

#define		APS_DELIVERY_MODE_SET(h,t)							\
(														\
((h) &= (~APS_FRAME_DELIVERY_MODE_MASK)),						\
((h) |= (t))											\
)
#define		APS_DELIVERY_MODE_IS_UNICAST(h)				((h&APS_FRAME_DELIVERY_MODE_MASK) == APS_DELIVERY_MODE_UNICAST)
#define		APS_DELIVERY_MODE_IS_BROADCAST(h)			((h&APS_FRAME_DELIVERY_MODE_MASK) == APS_DELIVERY_MODE_BROADCAST)
#define		APS_DELIVERY_MODE_IS_GROUP(h)				((h&APS_FRAME_DELIVERY_MODE_MASK) == APS_DELIVERY_MODE_GROUP)

//Ack format process
#define		APS_ACK_FORMAT_GET(h)						(h&APS_FRAME_ACK_MODE_MASK)
#define		APS_ACK_FORMAT_SET(h,t)							\
(														\
((h) &= (~APS_FRAME_ACK_MODE_MASK)),						\
((h) |= (t))											\
)
#define		APS_ACK_IS_DATA_FRAME(h)					((h&APS_FRAME_ACK_MODE_MASK) == APS_ACK_DATA_FRAME)
#define		APS_ACK_IS_CMD_FRAME(h)						((h&APS_FRAME_ACK_MODE_MASK) == APS_ACK_CMD_FRAME)

//Security process
#define		APS_SECURITY_GET(h)							(h&APS_FRAME_SECURITY_EN_MASK)
#define		APS_SECURITY_IS_TYPE_ONE(h)					((h&APS_FRAME_SECURITY_EN_MASK) == APS_SECURITY_TYPE_ONE)
#define		APS_SECURITY_IS_TYPE_TWO(h)					((h&APS_FRAME_SECURITY_EN_MASK) == APS_SECURITY_TYPE_TWO)
#define		APS_SECURITY_SET(h,t)							\
(														\
((h) &= (~APS_FRAME_SECURITY_EN_MASK)),						\
((h) |= (t))											\
)



//ACK require process
#define		APS_NEED_ACK_GET(h)								(h&APS_FRAME_ACK_REQ_MASK)
#define		APS_ACK_SET(h,t)							\
(														\
((h) &= (~APS_FRAME_ACK_REQ_MASK)),						\
((h) |= (t))											\
)

#define		APS_NEED_ACK(h)									((h&APS_FRAME_ACK_REQ_MASK) == APS_ACK_NEED)
#define		APS_NONEED_ACK(h)								((h&APS_FRAME_ACK_REQ_MASK) == APS_ACK_NONEED)

//Extended header process
#define		APS_EXTHDR_PRESENT_GET(h)						(h&APS_FRAME_EXTENDED_HEADER_MASK)
#define		APS_EXTENDED_HEADER_IS_PRESENT(h)				((h&APS_FRAME_EXTENDED_HEADER_MASK) == APS_EXTENDED_HEADER_PRESENT)

//1s aps duplicate check timer
#define			APS_DUP_CHECK_TIMEOUT							ZB_MILLISECONDS_TO_BEACON_INTERVAL(1000)
//The maximum number of retries allowed after a transmission failure.
#define			APS_MAX_FRAME_RETRIES							3

#define			APS_ACK_EXPIRY									2//seconds

typedef enum{
	APS_CMD_SKKE_1 = 1,
	APS_CMD_SKKE_2,
	APS_CMD_SKKE_3,
	APS_CMD_SKKE_4,
	APS_CMD_TRANSPORT_KEY,
	APS_CMD_UPDATE_DEVICE,
	APS_CMD_REMOVE_DEVICE,//APS Secure required
	APS_CMD_REQUEST_KEY,
	APS_CMD_SWITCH_KEY,
	APS_CMD_EA_INIT_CHLNG,//10
	APS_CMD_EA_RSP_CHLNG,
	APS_CMD_EA_INIT_MAC_DATA,
	APS_CMD_EA_RSP_MAC_DATA,
	APS_CMD_TUNNEL,
	APS_CMD_VERIFY_KEY,
	APS_CMD_CONFIRM_KEY,//APS Secure required
	APS_CMD_RESERVED
}aps_cmd_id;

typedef struct{
	u8 frame_type;
	u8 delivery_mode;
	u8 ack_format;
	u8 security;
	u8 ack_req;
	u8 ext_hdr;
}aps_fc_field_t;

typedef struct{
	u8					aps_hdr_len;
	u8					fc;
	u8					aps_counter;
	u8					src_endpoint;

	u16					src_addr;
	union{
		u8					dst_endpoint;
		u16					group_addr;
	};

	u16					clusterid;
	u16					profileid;
	aps_fc_field_t		fct;
}aps_header_t;


typedef struct{
	aps_address_t 		aps_addr;
	aps_dst_addr_mode	dst_addr_mode;
}bind_dst_list;

typedef struct{
	u8 *txData;
	bind_dst_list list[8];
	u8 txCnt;
	u8 totalCnt;
}bind_dst_list_tbl;

typedef struct{
	u8							fc;
	u8							aps_counter;
}aps_cmd_pkt_header_t;

typedef struct{
	aps_cmd_pkt_header_t		cmd_h;
	u8							aps_command_id;
	u8							aps_payload[1];
}aps_cmd_frame_t;

typedef struct{
	u8			*txBuf;
	u8			*adu;


	union{
		u16			dstShortAddr;
		addrExt_t	dstExtAddr;
	};
	zb_addr_mode_t	addrM;
	u8				aduLen;
	bool			secure;
	bool			secureNwkLayer;
	u8				ackReq;
}aps_cmd_send_t;

#define		APS_GET_PARSED_HDR(zbuf)				(aps_header_t *)(NWK_DATA_INDICATION_PRIMITIVE_LEN + ((void *)zbuf))

void aps_command_handle(void *p);
void aps_process_group_addressed_packet(void *p);
/*********************************************************************************************************
 * @brief	Parse the APS header info from the received APS Frame from NWK layer
 *
 * @param	aps_frame: start address of the APS frame
 * 			aps_hdr: buffer to hold parsed info
 * @return	length of header
 */
u8 aps_hdr_parse(u8 *aps_frame, aps_header_t *aps_hdr);
aps_status_t aps_search_dst_from_bind_tbl(aps_data_req_t *apsreq, bind_dst_list_tbl *bindList);

u8 aps_bindingTblExist(u16 index);
void aps_me_init(void);

void aps_cmd_send(aps_cmd_send_t *p, u8 handle);

aps_status_t aps_txBufInit(u8 **txBuf,u8 **adu, u8 reqLen);


/***********************************************************************************************************
 * @brief	Interface to receive APS layer indication data
 *
 * @param	*p: recived packet
 *
 * @return	none
 */

void af_aps_data_entry(void *p);

