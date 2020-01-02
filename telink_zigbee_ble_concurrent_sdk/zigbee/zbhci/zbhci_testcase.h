/********************************************************************************************************
 * @file     zbhciFroTestCase.h
 *
 * @brief	 zbhci header file for test case
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
#ifndef ZBHCIFORTESTCASE_H
#define	ZBHCIFORTESTCASE_H

#include "tl_common.h"

/** Macro to send a log message to the host machine
 *  First byte of the message is the level (0-7).
 *  Remainder of message is char buffer containing ascii message
 */

/****************************************************************************/
/***        Type Definitions                                              ***/
/****************************************************************************/

enum{
	NETWORK_START_FORMATION  = 	0x0,
	NETWORK_START_JOIN ,
};

enum{
	TEST_PARAM_APS_LAYER_SECURITY = 0x01,
	TEST_PARAM_PARENT_ADDRESS,
	TEST_PARAM_NWKKEY_CHANGE,
	TEST_PARAM_NWKKEY_SWITCH,
	TEST_PARAM_TC_REJOIN,
	TEST_PARAM_NWK_LEAVE_REQ,
	TEST_PARAM_NETWORK_START,
	TEST_PARAM_NODE_ACCESS,
	TEST_PARAM_CHILD_ADDR_ASSIGN,
	TEST_PARAM_STACK_REVISION,
	TEST_PARAM_NWK_LAYER_SECURITY,   //0x0b
	TEST_PARAM_NWK_OUTGOING_FRAME_COUNT,
	TEST_PARAM_PROTOCOL_VERSION,
	TEST_PARAM_TX_POWER_SET = 0x10,
	TEST_PARAM_EPID_REJOIN,
	TEST_PARAM_PAN_ID_CONFLICT_DETECTION_ENABLE,
	TEST_PARAM_POLL_DETECTION_ENABLE,
	TEST_PARAM_MANY_TO_ONE_NEXT_HOP_SET,
	TEST_PARAM_POLL_RATE_SET,
	TEST_PARAM_NEIGHBOR_LQI_SET,
	TEST_PARAM_END_DEV_KEEPALIVE_STOP,
};

/** Serial link message types */
typedef enum
{
    ZBHCI_MSG_STATUS                                            =   0x8000,
    ZBHCI_MSG_LOG                                               =   0x8001,
    ZBHCI_MSG_DATA_INDICATION                                   =   0x8002,//Report received data to HOST

    ZBHCI_MSG_NODE_CLUSTER_LIST                                 =   0x8003,
    ZBHCI_MSG_NODE_ATTRIBUTE_LIST                               =   0x8004,
    ZBHCI_MSG_NODE_COMMAND_ID_LIST                              =   0x8005,
    ZBHCI_MSG_NODE_NON_FACTORY_NEW_RESTART                      =   0x8006,
    ZBHCI_MSG_NODE_FACTORY_NEW_RESTART                          =   0x0007,
	ZBHCI_MSG_MAC_PIB_SET										=   0x0008,
	ZBHCI_MSG_NWK_NIB_SET										=   0x0009,
	ZBHCI_MSG_APS_ATTR_SET										=   0x000a,
	ZBHCI_MSG_NETWORK_STATUS_GET_REQ							=   0x000b,
	ZBHCI_MSG_NETWORK_STATUS_GET_RESP							=   0x800b,
	ZBHCI_MSG_KEY_SET											=   0x000c,
	ZBHCI_MSG_MAC_PIB_GET_REQ									=   0x000d,
	ZBHCI_MSG_MAC_PIB_GET_RESP									=   0x800d,
	ZBHCI_MSG_TEST_PARAM_SET									=   0x000e,  //for test case
	ZBHCI_MSG_RX_ON_IDLE_SET									=	0x000f,//Add
    ZBHCI_MSG_GET_VERSION                                       =   0x0010,
    ZBHCI_MSG_VERSION_LIST                                      =   0x8010,

	//Device management(self-control) CMDs
	ZBHCI_MSG_RESET                                             =   0x0011,//Required
	ZBHCI_MSG_ERASE_PERSISTENT_DATA                             =   0x0012,//Required
	ZBHCI_MSG_ZLL_FACTORY_NEW                                   =   0x0013,

	ZBHCI_MSG_PERMIT_JOIN_ST_GET                                =   0x0014,
	ZBHCI_MSG_PERMIT_JOIN_ST_GET_RESPONSE                       =   0x8014,

	ZBHCI_MSG_ROUTE_REQUEST										=	0x0015,//Add
	ZBHCI_MSG_NWK_STATUS_CMD									=	0x0016,//Add

    ZBHCI_MSG_SET_EXT_PANID                                     =   0x0020,//Required
    ZBHCI_MSG_SET_CHANNELMASK                                   =   0x0021,//Required
    ZBHCI_MSG_SET_SECURITY                                      =   0x0022,//Required
    ZBHCI_MSG_SET_DEVICETYPE                                    =   0x0023,

    ZBHCI_MSG_START_NETWORK                                     =   0x0024,//Required
	ZBHCI_MSG_NETWORK_JOINED_FORMED                             =   0x8024,//Required

    ZBHCI_MSG_START_SCAN                                        =   0x0025,//Required
    ZBHCI_MSG_NETWORK_REMOVE_DEVICE                             =   0x0026,//Required
    ZBHCI_MSG_NETWORK_WHITELIST_ENABLE                          =   0x0027,

    ZBHCI_MSG_ADD_AUTHENTICATE_DEVICE                           =   0x0028,
	ZBHCI_MSG_AUTHENTICATE_DEVICE_RESPONSE                      =   0x8028,

    ZBHCI_MSG_OUTOFBAND_COMMISSIONING_DATA_REQ                  =   0x0029,
    ZBHCI_MSG_OUTOFBAND_COMMISSIONING_DATA_RSP                  =   0x8029,

    ZBHCI_MSG_UPDATE_AUTHENTICATE_DEVICE                        =   0x002A,

	//ZDO-APS Layer related functions
	ZBHCI_MSG_USER_DESC_SET                                     =   0x002B,
	ZBHCI_MSG_USER_DESC_NOTIFY                                  =   0x802B,
    ZBHCI_MSG_USER_DESC_REQ                                     =   0x002C,//Required
    ZBHCI_MSG_USER_DESC_RSP                                     =   0x802C,//Required
    ZBHCI_MSG_BIND                                              =   0x0030,//Required
    ZBHCI_MSG_BIND_RESPONSE                                     =   0x8030,//Required
    ZBHCI_MSG_UNBIND                                            =   0x0031,//Required
    ZBHCI_MSG_UNBIND_RESPONSE                                   =   0x8031,//Required
    ZBHCI_MSG_BIND_GROUP                                        =   0x0032,//Required
    ZBHCI_MSG_BIND_GROUP_RESPONSE                               =   0x8032,//Required
    ZBHCI_MSG_UNBIND_GROUP                                      =   0x0033,//Required
    ZBHCI_MSG_UNBIND_GROUP_RESPONSE                             =   0x8033,//Required
	ZBHCI_MSG_COMPLEX_DESCRIPTOR_REQUEST                        =   0x0034,
	ZBHCI_MSG_COMPLEX_DESCRIPTOR_RESPONSE                       =   0x8034,
	ZBHCI_MSG_UNBIND_ALL_GROUP                                      =   0x0035,
	ZBHCI_MSG_UNBIND_ALL_GROUP_RESP                                      =   0x8035,
    ZBHCI_MSG_NETWORK_ADDRESS_REQUEST                           =   0x0040,//Required
    ZBHCI_MSG_NETWORK_ADDRESS_RESPONSE                          =   0x8040,//Required
    ZBHCI_MSG_IEEE_ADDRESS_REQUEST                              =   0x0041,//Required
    ZBHCI_MSG_IEEE_ADDRESS_RESPONSE                             =   0x8041,//Required
    ZBHCI_MSG_NODE_DESCRIPTOR_REQUEST                           =   0x0042,//Required
    ZBHCI_MSG_NODE_DESCRIPTOR_RESPONSE                          =   0x8042,//Required
    ZBHCI_MSG_SIMPLE_DESCRIPTOR_REQUEST                         =   0x0043,//Required
    ZBHCI_MSG_SIMPLE_DESCRIPTOR_RESPONSE                        =   0x8043,//Required
    ZBHCI_MSG_POWER_DESCRIPTOR_REQUEST                          =   0x0044,//Required
    ZBHCI_MSG_POWER_DESCRIPTOR_RESPONSE                         =   0x8044,//Required
    ZBHCI_MSG_ACTIVE_ENDPOINT_REQUEST                           =   0x0045,//Required
    ZBHCI_MSG_ACTIVE_ENDPOINT_RESPONSE                          =   0x8045,//Required
    ZBHCI_MSG_MATCH_DESCRIPTOR_REQUEST                          =   0x0046,//Required
    ZBHCI_MSG_MATCH_DESCRIPTOR_RESPONSE                         =   0x8046,//Required
    ZBHCI_MSG_MANAGEMENT_LEAVE_REQUEST                          =   0x0047,//Required
    ZBHCI_MSG_MANAGEMENT_LEAVE_RESPONSE                         =   0x8047,//Required

    ZBHCI_MSG_LEAVE_INDICATION                                  =   0x8048,//Required
    ZBHCI_MSG_PERMIT_JOINING_REQUEST                            =   0x0049,//Required
    ZBHCI_MSG_PERMIT_JOINING_RESPONSE                           =   0x8049,//Required
    ZBHCI_MSG_MANAGEMENT_NETWORK_UPDATE_REQUEST                 =   0x004A,//Required
    ZBHCI_MSG_MANAGEMENT_NETWORK_UPDATE_RESPONSE                =   0x804A,//Required
    ZBHCI_MSG_SYSTEM_SERVER_DISCOVERY                           =   0x004B,//Required
    ZBHCI_MSG_SYSTEM_SERVER_DISCOVERY_RESPONSE                  =   0x804B,//Required
    ZBHCI_MSG_LEAVE_REQUEST                                     =   0x004C,//Required
    ZBHCI_MSG_DEVICE_ANNOUNCE                                   =   0x004D,//Required
    ZBHCI_MSG_MANAGEMENT_LQI_REQUEST                            =   0x004E,//Required
    ZBHCI_MSG_MANAGEMENT_LQI_RESPONSE                           =   0x804E,//Required
	ZBHCI_MSG_MANY_TO_ONE_ROUTE_REQUEST                         =   0x004F,


	//Cluster related CMDs
    /* Basic Cluster */
    ZBHCI_MSG_BASIC_RESET_TO_FACTORY_DEFAULTS                   =   0x0050,//Required
    ZBHCI_MSG_BASIC_RESET_TO_FACTORY_DEFAULTS_RESPONSE          =   0x8050,//Required

    /* Group Cluster */
    ZBHCI_MSG_ADD_GROUP                                         =   0x0060,//Required
    ZBHCI_MSG_ADD_GROUP_RESPONSE                                =   0x8060,//Required
    ZBHCI_MSG_VIEW_GROUP                                        =   0x0061,//Required
    ZBHCI_MSG_VIEW_GROUP_RESPONSE                               =   0x8061,//Required
    ZBHCI_MSG_GET_GROUP_MEMBERSHIP                              =   0x0062,//Required
    ZBHCI_MSG_GET_GROUP_MEMBERSHIP_RESPONSE                     =   0x8062,//Required
    ZBHCI_MSG_REMOVE_GROUP                                      =   0x0063,//Required
    ZBHCI_MSG_REMOVE_GROUP_RESPONSE                             =   0x8063,//Required
    ZBHCI_MSG_REMOVE_ALL_GROUPS                                 =   0x0064,//Required
    ZBHCI_MSG_ADD_GROUP_IF_IDENTIFY                             =   0x0065,//Required

    /* Identify Cluster */
    ZBHCI_MSG_IDENTIFY_SEND                                     =   0x0070,//Required
    ZBHCI_MSG_IDENTIFY_QUERY                                    =   0x0071,//Required
    ZBHCI_MSG_IDENTIFY_LOCAL_ACTIVE                             =   0x807a,//Required

    /* Level Cluster */
    ZBHCI_MSG_MOVE_TO_LEVEL                                     =   0x0080,//Required
    ZBHCI_MSG_MOVE_TO_LEVEL_ONOFF                               =   0x0081,//Required
    ZBHCI_MSG_MOVE_STEP                                         =   0x0082,//Required
    ZBHCI_MSG_MOVE_STOP_MOVE                                    =   0x0083,//Required
    ZBHCI_MSG_MOVE_STOP_ONOFF                                   =   0x0084,//Required

	/* On/Off Cluster */
	ZBHCI_MSG_ONOFF_NOEFFECTS                                   =   0x0092,//Required
	ZBHCI_MSG_ONOFF_TIMED                                       =   0x0093,//Required
	ZBHCI_MSG_ONOFF_EFFECTS                                     =   0x0094,//Required
	ZBHCI_MSG_ONOFF_UPDATE                                      =   0x8095,//Required

    /* Scenes Cluster */
    ZBHCI_MSG_VIEW_SCENE                                        =   0x00A0,//Required
    ZBHCI_MSG_VIEW_SCENE_RESPONSE                               =   0x80A0,//Required
    ZBHCI_MSG_ADD_SCENE                                         =   0x00A1,//Required
    ZBHCI_MSG_ADD_SCENE_RESPONSE                                =   0x80A1,//Required
    ZBHCI_MSG_REMOVE_SCENE                                      =   0x00A2,//Required
    ZBHCI_MSG_REMOVE_SCENE_RESPONSE                             =   0x80A2,//Required
    ZBHCI_MSG_REMOVE_ALL_SCENES                                 =   0x00A3,//Required
    ZBHCI_MSG_REMOVE_ALL_SCENES_RESPONSE                        =   0x80A3,//Required
    ZBHCI_MSG_STORE_SCENE                                       =   0x00A4,//Required
    ZBHCI_MSG_STORE_SCENE_RESPONSE                              =   0x80A4,//Required
    ZBHCI_MSG_RECALL_SCENE                                      =   0x00A5,//Required
    ZBHCI_MSG_SCENE_MEMBERSHIP_REQUEST                          =   0x00A6,//Required
    ZBHCI_MSG_SCENE_MEMBERSHIP_RESPONSE                         =   0x80A6,//Required

	 /* Scenes Cluster */
	ZBHCI_MSG_ADD_ENHANCED_SCENE                                =   0x00A7,
	ZBHCI_MSG_VIEW_ENHANCED_SCENE                               =   0x00A8,
	ZBHCI_MSG_COPY_SCENE                                        =   0x00A9,

    /* Colour Cluster */
    ZBHCI_MSG_MOVE_TO_HUE                                       =   0x00B0,
    ZBHCI_MSG_MOVE_HUE                                          =   0x00B1,
    ZBHCI_MSG_STEP_HUE                                          =   0x00B2,
    ZBHCI_MSG_MOVE_TO_SATURATION                                =   0x00B3,
    ZBHCI_MSG_MOVE_SATURATION                                   =   0x00B4,
    ZBHCI_MSG_STEP_SATURATION                                   =   0x00B5,
    ZBHCI_MSG_MOVE_TO_HUE_SATURATION                            =   0x00B6,
    ZBHCI_MSG_MOVE_TO_COLOUR                                    =   0x00B7,
    ZBHCI_MSG_MOVE_COLOUR                                       =   0x00B8,
    ZBHCI_MSG_STEP_COLOUR                                       =   0x00B9,
	ZBHCI_MSG_ENHANCED_MOVE_TO_HUE                              =   0x00BA,
	ZBHCI_MSG_ENHANCED_MOVE_HUE                                 =   0x00BB,
	ZBHCI_MSG_ENHANCED_STEP_HUE                                 =   0x00BC,
	ZBHCI_MSG_ENHANCED_MOVE_TO_HUE_SATURATION                   =   0x00BD,
	ZBHCI_MSG_COLOUR_LOOP_SET                                   =   0x00BE,
	ZBHCI_MSG_STOP_MOVE_STEP                                    =   0x00BF,
	ZBHCI_MSG_MOVE_TO_COLOUR_TEMPERATURE                        =   0x00C0,
	ZBHCI_MSG_MOVE_COLOUR_TEMPERATURE                           =   0x00C1,
	ZBHCI_MSG_STEP_COLOUR_TEMPERATURE                           =   0x00C2,

    /* ZLL Commands */
    /* Touchlink */
    ZBHCI_MSG_INITIATE_TOUCHLINK                                =   0x00D0,//Required
    ZBHCI_MSG_TOUCHLINK_STATUS                                  =   0x00D1,//Required
    ZBHCI_MSG_TOUCHLINK_FACTORY_RESET                           =   0x00D2,//Required
    /* Identify Cluster */
    ZBHCI_MSG_IDENTIFY_TRIGGER_EFFECT                           =   0x00E0,//Required

    /* Door Lock Cluster */
    ZBHCI_MSG_LOCK_UNLOCK_DOOR                                  =   0x00F0,

    /* ZHA Commands */
    ZBHCI_MSG_READ_ATTRIBUTE_REQUEST                             =  0x0100,
    ZBHCI_MSG_READ_ATTRIBUTE_RESPONSE                            =  0x8100,
    ZBHCI_MSG_DEFAULT_RESPONSE                                   =  0x8101,
    ZBHCI_MSG_REPORT_IND_ATTR_RESPONSE                           =  0x8102,
    ZBHCI_MSG_WRITE_ATTRIBUTE_REQUEST                            =  0x0110,
    ZBHCI_MSG_WRITE_ATTRIBUTE_RESPONSE                           =  0x8110,
    ZBHCI_MSG_CONFIG_REPORTING_REQUEST                           =  0x0120,
    ZBHCI_MSG_CONFIG_REPORTING_RESPONSE                          =  0x8120,
    ZBHCI_MSG_REPORT_ATTRIBUTES                                  =  0x8121,
    ZBHCI_MSG_READ_REPORT_CONFIG_REQUEST                         =  0x0122,
    ZBHCI_MSG_READ_REPORT_CONFIG_RESPONSE                        =  0x8122,
    ZBHCI_MSG_ATTRIBUTE_DISCOVERY_REQUEST                        =  0x0140,
    ZBHCI_MSG_ATTRIBUTE_DISCOVERY_RESPONSE                       =  0x8140,
    ZBHCI_MSG_ATTRIBUTE_EXT_DISCOVERY_REQUEST                    =  0x0141,
    ZBHCI_MSG_ATTRIBUTE_EXT_DISCOVERY_RESPONSE                   =  0x8141,
    ZBHCI_MSG_COMMAND_RECEIVED_DISCOVERY_REQUEST                 =  0x0150,
    ZBHCI_MSG_COMMAND_RECEIVED_DISCOVERY_INDIVIDUAL_RESPONSE     =  0x8150,
    ZBHCI_MSG_COMMAND_RECEIVED_DISCOVERY_RESPONSE                =  0x8151,
    ZBHCI_MSG_COMMAND_GENERATED_DISCOVERY_REQUEST                =  0x0160,
    ZBHCI_MSG_COMMAND_GENERATED_DISCOVERY_INDIVIDUAL_RESPONSE    =  0x8160,
    ZBHCI_MSG_COMMAND_GENERATED_DISCOVERY_RESPONSE               =  0x8161,

    ZBHCI_MSG_SAVE_PDM_RECORD                                    =  0x0200,
    ZBHCI_MSG_SAVE_PDM_RECORD_RESPONSE                           =  0x8200,
    ZBHCI_MSG_LOAD_PDM_RECORD_REQUEST                            =  0x0201,
    ZBHCI_MSG_LOAD_PDM_RECORD_RESPONSE                           =  0x8201,
    ZBHCI_MSG_DELETE_PDM_RECORD                                  =  0x0202,

    ZBHCI_MSG_PDM_HOST_AVAILABLE                                 =  0x0300,
    ZBHCI_MSG_ASC_LOG_MSG                                        =  0x0301,
    ZBHCI_MSG_ASC_LOG_MSG_RESPONSE                               =  0x8301,
    ZBHCI_MSG_PDM_HOST_AVAILABLE_RESPONSE                        =  0x8300,


    /* IAS Cluster */
    ZBHCI_MSG_SEND_IAS_ZONE_ENROLL_RSP                           =  0x0400,//Required
    ZBHCI_MSG_IAS_ZONE_STATUS_CHANGE_NOTIFY                      =  0x8401,//Required

    /* OTA Cluster */
    ZBHCI_MSG_LOAD_NEW_IMAGE                                     =  0x0500,//Required
    ZBHCI_MSG_BLOCK_REQUEST                                      =  0x8501,//Required
    ZBHCI_MSG_BLOCK_SEND                                         =  0x0502,//Required
    ZBHCI_MSG_UPGRADE_END_REQUEST                                =  0x8503,//Required
    ZBHCI_MSG_UPGRADE_END_RESPONSE                               =  0x0504,//Required
    ZBHCI_MSG_IMAGE_NOTIFY                                       =  0x0505,//Required
    ZBHCI_MSG_SEND_WAIT_FOR_DATA_PARAMS                          =  0x0506,//Required
    ZBHCI_MSG_SEND_RAW_APS_DATA_PACKET                          =   0x0530,//Required

    ZBHCI_MSG_NWK_RECOVERY_EXTRACT_REQ                           =  0x0600,
    ZBHCI_MSG_NWK_RECOVERY_EXTRACT_RSP                           =  0x8600,
    ZBHCI_MSG_NWK_RECOVERY_RESTORE_REQ                           =  0x0601,
    ZBHCI_MSG_NWK_RECOVERY_RESTORE_RSP                           =  0x8601,

    ZBHCI_MSG_TOUCHLINK_START									 =  0x0602,

    ZBHCI_MSG_ROUTE_DISCOVERY_CONFIRM                            =  0x8701,
    ZBHCI_MSG_APS_DATA_CONFIRM_FAILED                            =  0x8702,

	ZBHCI_MSG_AHI_DIO_SET_DIRECTION								= 0x0801,
	ZBHCI_MSG_AHI_DIO_SET_OUTPUT								= 0x0802,
	ZBHCI_MSG_AHI_DIO_READ_INPUT								= 0x0803,
	ZBHCI_MSG_AHI_DIO_READ_INPUT_RSP							= 0x8803,
	ZBHCI_MSG_AHI_SET_TX_POWER									= 0x0806,

	/* Test profile */
	ZBHCI_MSG_TEST_BUFFER_REQ_SEND								= 0x0901,
	ZBHCI_MSG_TEST_BUFFER_GROUP_REQ_SEND								= 0x0902,
	ZBHCI_MSG_TEST_BUFFER_RESET_PACKET_SEND								= 0x0903,
	ZBHCI_MSG_TEST_BUFFER_RERIEVE_PACKET_SEND					= 0x0904,
    /* test commands */
    ZBHCI_MSG_SEND_COUNTED_PACKET                               = 0x1000,
    ZBHCI_MSG_SEND_BEACON_REQ                                   = 0x1001,
    ZBHCI_MSG_DEL_DEV_KEYPAIR                                   = 0x1002,
    ZBHCI_MSG_BDB_FIND_BIND                                     = 0x1003,
    ZBHCI_MSG_MODIFY_DESC_PROFILE_ID                            = 0x1004,
    ZBHCI_MSG_MGMT_BIND_REQ                                     = 0x1005,
    ZBHCI_MSG_LEAVE_REQUEST_NEW                                 = 0x1006,
    ZBHCI_MSG_LEAVE_REQUEST_WITHOUT_LAST_OCTET                  = 0x1007,
    ZBHCI_MSG_LEAVE_REQUEST_FORCE_FORWARD                       = 0x1008,
    ZBHCI_MSG_SET_FORGET_DEV_FLAG                               = 0x1009,
} teSL_MsgType;

typedef struct{
	u8			st;
	u8			shortAddrH;
	u8			shortAddrL;
	addrExt_t	extAddr;
	u8			channel;
}hci_nwkStartCnfMsg_t;

typedef struct{
	u8			shortAddrH;
	u8			shortAddrL;
	addrExt_t	extAddr;
	u8			mc;
}hci_devAnncMsg_t;

#define		MAX_MATCHRSP_LEN		5
typedef struct{
	u8	seq;
	u8	st;
	u8	shortAddrH;
	u8	shortAddrL;
	u8	matchLen;
	u8	matchRes[MAX_MATCHRSP_LEN];

}hci_matchRsp_t;

typedef struct{
	u8			shortAddrH;
	u8			shortAddrL;
	addrExt_t	extAddr;
	u8			mc;
}hci_leaveIndMsg_t;


#define			MAX_REQ_CLST_NUM			8
typedef struct{
	u8		sqn;
	u8		st;
	u8		nwkAddrH;
	u8		nwkAddrL;

	u8		msgLen;
	u8		ep;
	u8		profileIdH;
	u8		profileIdL;

	u8		deviceIdH;
	u8		deviceIdL;
	u8		appVer;

	u8		inputClstNum;
	u8		payload[MAX_REQ_CLST_NUM*4 + 1];
}hci_simpleDescRspMsg_t;


typedef struct{
	u8 linkKeyType;
	addrExt_t extAddr;
	u8 key[16];
}hci_LinkKeySetReq_t;

typedef struct{
	u8 key[16];
}hci_nwkKeySetReq_t;

typedef struct{
	u8 keyType;
	u8 length;
	u8 payLoad[1];
}hci_keySetReq_t;

#endif

