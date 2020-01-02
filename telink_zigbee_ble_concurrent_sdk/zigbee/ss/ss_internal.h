/********************************************************************************************************
 * @file     ss_internal.h
 *
 * @brief	 internal APIs and constructs for security service
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
#ifndef SS_INTERNAL_H
#define	SS_INTERNAL_H

#include "tl_common.h"
#include "../include/tl_config.h"
#include "security_service.h"


#define			DEBUG_ENDECRYPT			0

typedef enum {
	SS_STANDARD_DEV_SECURED_REJOIN = 0,
	SS_STANDARD_DEV_UNSECURED_JOIN = 1,
	SS_DEV_LEFT = 2,
	SS_STANDARD_DEV_TC_REJOIN = 3//0x04 ~ 0x07 reserved
}ss_apsmeUpdateDevstatus_e;



//Value of nwk packets counter which triggered nwk key switch
#define				SS_SECUR_NWK_COUNTER_LIMIT				(((u32)~0) - 128)
//Parameters for APSME-TRANSPORT-KEY.indication primitive

typedef struct{
	addrExt_t			srcAddr;
	u8					keyType;
	u8					key[CCM_KEY_SIZE];
	union{
		u8				keySeqNum;
		addrExt_t		partnerAddr;
	};
}ss_apsme_txKeyInd_t;

typedef struct{
	u8					cmdId;
	u8					stKeyType;//standard key type
	addrExt_t			srcAddr;
	u8					iniVerifyKeyHashVal[16];
}ss_verifyKeyFrame_t;


typedef struct{
	addrExt_t			dstAddr;
	u8					keyType;
}ss_verifyKeyReq_t;

typedef struct{
	u8					cmdId;
	u8					st;
	u8					stKeyType;//standard key type
	addrExt_t			dstAddr;
}ss_confirmKeyFrame_t;



typedef struct{
	u8					cmdId;
	u8					reqKeyType;//02/04
	addrExt_t			partnerAddr;//if application key, this field should be included
}ss_requestKeyFrame_t;


typedef struct{
	addrExt_t			dstAddr;
	u8					reqKeyType;//02/04
	addrExt_t			partnerAddr;//if application key, this field should be included
}ss_requestKeyReq_t;

//APSME-REMOVE-DEVICE.request primitive parameters structure
typedef struct
{
	addrExt_t	parent_address;
	addrExt_t	child_address;
}ss_apsme_remove_device_req_t;


/***************************************************************************
 * transport-key commands pay-load
 */
//If the key type field is set to 0 or 4, the key descriptor field shall be formatted as follow
typedef struct{
	u8				cmdId;
	u8				keyType;
	u8				key[16];
	addrExt_t		destAddr;
	addrExt_t		srcAddr;
}ss_apsTcLinkKey_t;



//If the key type field is set to 1, 5 or 6, this field shall be formatted as follow
typedef struct{
	u8				cmdId;
	u8				keyType;
	u8				key[16];
	u8				seqNum;
	addrExt_t		destAddr;
	addrExt_t		srcAddr;
}ss_apsNwkKey_t;
#define		SS_APSTXKEY_MAXPAYLOAD			sizeof(ss_apsNwkKey_t)
//If the key type field is set to 2 or 3, this field shall be formatted as follow
typedef struct{
	u8				cmdId;
	u8				keyType;
	u8				key[16];
	addrExt_t		partnerAddr;
	u8				initiatorFlag;
}ss_apsAppLinkKey_t;


/**
   Parameter for APSME-UPDATE-DEVICE.request
 */
typedef struct{
	//The extended 64-bit address of the device
	//that shall be sent the update information.
	addrExt_t dstAddr;
	/*The extended 64-bit address of the device
	whose status is being updated.*/
	addrExt_t devAddr;

	u16    devShortAddr;
	u8     status;
}ss_apsmeDevUpdateReq_t;


typedef struct{
	/*The extended 64-bit address of the
	device originating the update-device
	command.*/
	addrExt_t 						srcAddr;
	/*The extended 64-bit address of the device
	whose status is being updated.*/
	addrExt_t 						devAddr;

	u16								devShortAddr;
	ss_apsmeUpdateDevstatus_e		status;
}ss_apsmeDevUpdateInd_t;
/***************************************************************************
 * update device commands pay-load
 */
typedef struct{
	u8							cmdId;

	addrExt_t					devExtAddr;

	u8							devShortAddr_l;
	u8							devShortAddr_h;

	ss_apsmeUpdateDevstatus_e	status;
}ss_apsDevUpdate_frame_t;


/***************************************************************************
 * remove device commands pay-load
 */
typedef struct{
	u8					cmdId;
	addrExt_t			targetExtAddr;
}ss_apsDevRemoveFrame_t;

/***************************************************************************
 * Request key cmd pay-load
 */
typedef struct{
	u8					cmdID;
	u8					keyType;
	addrExt_t			partnerExtAddr;
}ss_apsKeyReq_frame_t;

typedef struct{
	addrExt_t			dstAddr;
	u8					reqKeyType;
	addrExt_t			partnerExtAddr;
}ss_apsKeyReq_t;




/***************************************************************************
 * Switch key cmd pay-load
 */
typedef struct{
	u8			apsCmdID;
	u8			seqNum;
}ss_apsKeySwitch_frame_t;


typedef struct{
	u8			securityLevel:3;
	u8			keyIdentifer:2;
	u8			extendedNonce:1;
	u8			reserved:2;
	u32    		frameCnt;
}ss_apsEncryAuxCommonHdr_t;

/**
   Auxiliary frame header (4.5.1) for APS frame encrypted by NWK key

   Extended nonce subfield set to 0 (4.4.1.1).
   source_address absent, key_seq_number exists.
 */
typedef struct{
	u8			securityLevel:3;
	u8			keyIdentifer:2;
	u8			extendedNonce:1;
	u8			reserved:2;
	u32    		frameCnt;
	u8     		keySeqNum;
}ss_apsEncryByNwkKeyAuxHdr_t;


//Auxiliary frame header (4.5.1) for NWK frame and NWK key

//Extended nonce subfield set to 1 (4.3.1.1).
//source_address amd key_seq_number exist.

typedef struct{
	u8			securityLevel:3;
	u8			keyIdentifer:2;
	u8			extendedNonce:1;
	u8			reserved:2;

	/*The counter field is used to provide frame freshness and to prevent processing of
	duplicate frames.*/
	u32			frameCnt;

	/*  The source address field shall only be present when the extended nonce sub-field
	of the security control field is 1. When present, the source address field shall
	indicate the extended 64-bit address of the device responsible for securing the
	frame.*/
	addrExt_t	srcAddr;

	/*  The key sequence number field shall only be present when the key identifier subfield
	of the security control field is 1 (that is, a network key). When present, the
	key sequence number field shall indicate the key sequence number of the network
	key used to secure the frame.*/
	u8			keySeqNum;

}ss_apsNwkAuxFrameHdr_t;

/**
   Auxiliary frame header (4.5.1) for APS frame encrypted by Data key

   Extended nonce subfield set to 0 (4.4.1.1).
   source_address and key_seq_number are absent.
 */
typedef struct{
	u8			securityLevel:3;
	u8			keyIdentifer:2;
	u8			extendedNonce:1;
	u8			reserved:2;
	u32    		frameCnt;
}ss_apsEncryByDataKeyAuxHdr_t;


typedef struct{
	u8				securityLevel:3;
	u8				keyIdentifer:2;
	u8				extendedNonce:1;
	u8				reserved:2;
	u32    			frameCnt;
	addrExt_t		srcAddr;
}ss_apsEncryByDataKeyAuxHdrWithNonce_t;




#define			SS_CLR_SECURITY_LEVEL(d)					((*(u8 *)(d)) &= 0xf8)


#define			SS_SET_SECURITY_LEVEL(d,t)					\
	(														\
			(*(u8 *)(d) &= 0xf8),							\
			(*(u8 *)(d) |= t)								\
	)


//CCM nonce (see 4.5.2.2)

typedef struct{
	addrExt_t		srcAddr;
	u32				frameCnt;
	u8				secureCtrl;
}ss_securityCcmNonce_t;

#define	SS_TUNNELEDAUXFRAME_LEN			13
#define	SS_TUNNELEDEXTRA_LEN			11
/***************************************************************************
 * Tunnel cmd pay-load
 */

#define		SS_TUNNELCMD_SETTARGETADDR(ptr,addr)		ZB_IEEE_ADDR_COPY((ptr - 13 - 2 - 8),addr)
#define		SS_TUNNELCMD_TARGETEXTADDR(ptr)				((ptr - EXT_ADDR_LEN))
typedef struct{
	u8			cmdId;//APS_CMD_TUNNEL

	/*The destination address field shall be the 64-bit extended address of the device
	that is to receive the tunneled command.*/
	addrExt_t	destExtAddr;
	//The tunneled APS header
	struct {
		u8 fc;
		u8	cnt;
	}aps_hdr;
	/*The tunneled auxiliary frame field shall be the auxiliary frame (see subclause
	4.5.1) used to encrypt the tunneled command. The auxiliary frame shall
	indicate that a link key was used and shall included the extended nonce field.*/
	ss_apsEncryByDataKeyAuxHdrWithNonce_t			tunneledAuxFrame;
}ss_apsTunnelCmd_frame_t;

typedef struct{
	addrExt_t srcAddr;
	addrExt_t devAddr;
	u16		devShortAddr;//if use parent = 0, device short address is the dst short address
	u8		useParent;
	u8		rejoinNwk;
	bool	secureRejoin;
}ss_zdoAuthReq_t;

/*************************************************************************************************************
 * @brief
 */

void ss_zdoApsmeTxKeyIndCb(void *p);
void ss_apsmeUpdateDevReq(void *p);
void ss_zdoChildAuthStart(void *p);
void ss_zdoCommissionChildAuthStart (void *p);
void ss_apsmeTxKeyReq(void *p);
void ss_apsmeEstablishKeyReq(void *p);


u8 ss_ccmDecryption(u8 *key, u8 *nonce, u8 nwkHdrLen, u8 *nwkHdr, u8 srcMsgLen, u8 *srcMsg);
u8 ss_ccmEncryption(u8 *key, u8 *nonce, u8 nwkHdrLen, u8 *nwkHdr, u8 srcMsgLen, u8 *srcMsg);
void ss_zdoSecureRejoin(void *arg);
void ss_apsSwitchKeyCmdHandle(u8 keySeqNum);
u8 tl_cryHashFunction(u8* input, u8 inputLen, u8 *output);
void ss_ttlMAC(u8 len, u8 *input, u8 *key, u8 *hashOut);
u8 ss_keyHash(u8 *padV, u8 *key, u8 *hashOut);
void ss_zdoUpdateDeviceIndicationHandle(void *p);
void ss_zdoRemoveDeviceInd(void *p);
void ss_apsmeVerifyKeyReq(void *p);
ss_dev_pair_set_t *ss_devKeyPairSearch(addrExt_t extAddr);
ss_dev_pair_set_t *ss_devKeyPairGet(addrExt_t extAddr);
bool ss_securityModeIsDistributed(void);
void ss_apsPassNwkKeyToED(u8 keyIndx);
ss_dev_pair_set_t *ss_freeDevKeyPairGet(void );
ss_dev_pair_set_t *ss_freeDevKeyPairGet(void );

u8 zdo_ssInfoKeyGet(void);

void ss_apsTxKeyCmdHandle(void *p);

void ss_apsConfirmKeyHandle(void *p);

void ss_apsKeyReqHandle(void *p);

void ss_apsVerifyKeyReqHandle(void *p);

void ss_apsDeviceUpdateCmdHandle(void *p);

void ss_apsDeviceRemoveCmdHandle(void *p);

void ss_apsTunnelCmdHandle(void *p);


u8 ss_apsEnAuxHdrFill(void *p, ss_apsNwkKey_t *q, aps_tx_options txopt);

void ss_zdoTcInit(void);

void ss_zdoNwkKeySwitch(u8 keySeqNum);

u8 *ss_zdoGetNwkKeyBySeqNum(u8 keySeqNum);

u8 ss_nwkDecryptFrame(void *p, u8 nwkHdrSize, u8 payloadLen, u8 *payloadAddr, nwk_hdr_t *nwkHdr, u8 lqi);

u8 ss_nwkSecureFrame(zb_buf_t *src, u8 nwkHdrAuxLen);

#endif
