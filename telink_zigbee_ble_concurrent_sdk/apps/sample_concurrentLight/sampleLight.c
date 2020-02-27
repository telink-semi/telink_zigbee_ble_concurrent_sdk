/********************************************************************************************************
 * @file     sampleLight.c
 *
 * @brief    HA Router
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

#if (__PROJECT_TL_CONCURRENT_LIGHT__)

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zb_api.h"
#include "zcl_include.h"
#include "bdb.h"
#include "ota.h"
#include "gp.h"
#include "sampleLight.h"
#include "sampleLightCtrl.h"
#include "app_ui.h"
#if ZBHCI_EN
#include "zbhci.h"
#endif
#if ZB_TEST_ENABLE
#include "../../zigbee/testcase/test_profile.h"
#endif

/**********************************************************************
 * LOCAL CONSTANTS
 */


/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * GLOBAL VARIABLES
 */
app_ctx_t gLightCtx;


#ifdef ZCL_OTA
extern ota_callBack_t sampleLight_otaCb;

//running code firmware information
ota_preamble_t sampleLight_otaInfo = {
		.fileVer = CURRENT_FILE_VERSION,
		.imageType = IMAGE_TYPE,
		.manufaurerCode = TELINK_MANUFACTURER_CODE,
};
#endif

extern void bdb_zdoStartDevCnf(void* startDevCnf);
//void DevAnnounceIndCB(void *arg);

//Must declare the application call back function which used by ZDO layer
const zdo_appIndCb_t appCbLst = {
		bdb_zdoStartDevCnf,//start device cnf cb
		NULL,//reset cnf cb
		NULL,//NULL,//device announce indication cb
		sampleLight_leaveIndHandler,//leave ind cb
		sampleLight_leaveCnfHandler,//leave cnf cb
		NULL,//nwk update ind cb
		NULL,//permit join ind cb
		NULL,//nlme sync cnf cb
};


/**
 *  @brief Definition for bdb commissioning setting
 */
bdb_commissionSetting_t g_bdbCommissionSetting = {
	.linkKey.tcLinkKey.keyType = SS_GLOBAL_LINK_KEY,
	.linkKey.tcLinkKey.key = (u8 *)tcLinkKeyCentralDefault,       		//can use unique link key stored in NV

	.linkKey.distributeLinkKey.keyType = MASTER_KEY,
	.linkKey.distributeLinkKey.key = (u8 *)linkKeyDistributedMaster,  	//use linkKeyDistributedCertification before testing

	.linkKey.touchLinkKey.keyType = MASTER_KEY,
	.linkKey.touchLinkKey.key = (u8 *)touchLinkKeyMaster,   			//use touchLinkKeyCertification before testing

#if TOUCHLINK_SUPPORT
	.touchlinkEnable = 1,												/* enable touch-link */
#else
	.touchlinkEnable = 0,												/* disable touch-link */
#endif
	.touchlinkChannel = DEFAULT_CHANNEL, 								/* touch-link default operation channel for target */
	.touchlinkLqiThreshold = 0xf0,			   							/* threshold for touch-link scan req/resp command */
};

/**********************************************************************
 * LOCAL VARIABLES
 */
ev_time_event_t *sampleLightAttrsStoreTimerEvt = NULL;

#if DUAL_MODE
#if DUAL_MODE_HW_BOOT
void dualModeDisable(void)
{
	u8 dualModeEnable = 0;
	flash_read(CFG_TELINK_DUAL_MODE_ENABLE, 1, (u8 *)&dualModeEnable);
	if(dualModeEnable == 0x5a){
		dualModeEnable = 0;
		flash_write(CFG_TELINK_DUAL_MODE_ENABLE, 1, (u8 *)&dualModeEnable);
	}
}

bool isDualModeEnable(void)
{
	u8 dualModeEnable = 0;
	flash_read(CFG_TELINK_DUAL_MODE_ENABLE, 1, (u8 *)&dualModeEnable);

	return (dualModeEnable == 0x5a) ? TRUE : FALSE;
}

void dualModeRecovery(void)
{
	u32 value = 0xffffffff;
	flash_read(CFG_TELINK_SIG_MESH_CRC, 4, (u8 *)&value);

	if(isDualModeEnable() && (value != 0xffffffff)){
		u32 crcValue = 0xffffffff;
		u32 addressOffset = 0;

		flash_erase(0);

		for(u8 i = 0; i < (FLASH_SECTOR_SIZE /FLASH_PAGE_SIZE ); i++){
			u8 buf[FLASH_PAGE_SIZE] = {0};
			flash_read(CFG_TELINK_SIG_MESH_CODE_4K + addressOffset, FLASH_PAGE_SIZE, buf);
			crcValue = xcrc32(buf, FLASH_PAGE_SIZE, crcValue);
			if(addressOffset == 0){
				buf[8] = 0xff;
			}
			flash_write(addressOffset, FLASH_PAGE_SIZE, buf);
			addressOffset += FLASH_PAGE_SIZE;
		}

		if(crcValue == value){
			u8 flashInfo = 0x4b;
			flash_write((0 + 8), 1, &flashInfo);//enable boot-up flag

			u32 sdkType = TYPE_DUAL_MODE_RECOVER;
			flash_erase(CFG_TELINK_SDK_TYPE);
			flash_write(CFG_TELINK_SDK_TYPE, 4, (u8 *)&sdkType);
		}
	}
}
#elif DUAL_MODE_SW_BOOT
void dualModeRecovery(void){
	u32 sdkType = TYPE_DUAL_MODE_RECOVER;
	flash_erase(CFG_TELINK_SDK_TYPE);
	flash_write(CFG_TELINK_SDK_TYPE, 4, (u8 *)&sdkType);
}
#endif

volatile u8 T_dualModeSwInfo[8] = {0};
void dualModeInit(void)
{
    u32 sdkType = 0;
    u32 zigbeeSdkType = TYPE_TLK_ZIGBEE;

    T_dualModeSwInfo[0]++;

    flash_read(CFG_TELINK_SDK_TYPE, 4, (u8 *)&sdkType);
    if(sdkType != TYPE_TLK_ZIGBEE){
    	T_dualModeSwInfo[1]++;
    	//Store SDK type.
		if(sdkType == 0xFFFFFFFF){
			flash_write(CFG_TELINK_SDK_TYPE, 4, (u8 *)&zigbeeSdkType);
		}else{
			nv_resetAll();
			flash_erase(CFG_TELINK_SDK_TYPE);
			flash_write(CFG_TELINK_SDK_TYPE, 4, (u8 *)&zigbeeSdkType);
		}
		T_dualModeSwInfo[2]++;

#if DUAL_MODE_HW_BOOT
		if(!isDualModeEnable()){
			return;
		}

		T_dualModeSwInfo[3]++;
		u8 flashInfo = 0;
		flash_read(0 + 8, 1, &flashInfo);
		if((flashInfo != 0x4b) && (flashInfo != 0xff)){
			T_dualModeSwInfo[4]++;
			//Store SIG Mesh Code.
			flash_erase(CFG_TELINK_SIG_MESH_CODE_4K);

			u32 crcValue = 0xffffffff;
			u32 addressOffset = 0;
			u8 buf[FLASH_PAGE_SIZE] = {0};
			for(u8 i = 0; i < (FLASH_SECTOR_SIZE /FLASH_PAGE_SIZE ); i++){
				memset((u8 *)buf, 0, FLASH_PAGE_SIZE);
				flash_read(addressOffset, FLASH_PAGE_SIZE, buf);
				crcValue = xcrc32(buf, FLASH_PAGE_SIZE, crcValue);
				flash_write(CFG_TELINK_SIG_MESH_CODE_4K + addressOffset, FLASH_PAGE_SIZE, buf);
				addressOffset += FLASH_PAGE_SIZE;
			}

			flash_write(CFG_TELINK_SIG_MESH_CRC, 4, (u8 *)&crcValue);
		}
#endif
    }else{
    	//do nothing.
    }
}
#endif



/**********************************************************************
 * FUNCTIONS
 */

/*********************************************************************
 * @fn      stack_init
 *
 * @brief   This function initialize the ZigBee stack and related profile. If HA/ZLL profile is
 *          enabled in this application, related cluster should be registered here.
 *
 * @param   None
 *
 * @return  None
 */
void stack_init(void)
{
#if DUAL_MODE
	dualModeInit();
#endif

	/* Initialize ZB stack */
	zb_init();

	/* Register stack CB */
    zb_zdoCbRegister((zdo_appIndCb_t *)&appCbLst);
}

/*********************************************************************
 * @fn      user_app_init
 *
 * @brief   This function initialize the application(Endpoint) information for this node.
 *
 * @param   None
 *
 * @return  None
 */
void user_app_init(void)
{
	af_nodeDescManuCodeUpdate(TELINK_MANUFACTURER_CODE);

    /* Initialize ZCL layer */
	/* Register Incoming ZCL Foundation command/response messages */
    zcl_init(sampleLight_zclProcessIncomingMsg);

	/* Register endPoint */
	af_endpointRegister(SAMPLE_LIGHT_ENDPOINT, (af_simple_descriptor_t *)&sampleLight_simpleDesc, zcl_rx_handler, NULL);

#if AF_TEST_ENABLE
	/* A sample of AF data handler. */
	af_endpointRegister(SAMPLE_TEST_ENDPOINT, (af_simple_descriptor_t *)&sampleTestDesc, afTest_rx_handler, afTest_dataSendConfirm);
#endif

	/* Initialize or restore attributes, this must before 'zcl_register()' */
	zcl_sampleLightAttrsInit();
	zcl_reportingTabInit();

	/* Register ZCL specific cluster information */
	zcl_register(SAMPLE_LIGHT_ENDPOINT, SAMPLELIGHT_CB_CLUSTER_NUM, g_sampleLightClusterList);

#ifdef ZCL_GREEN_POWER
	/* Initialize GP */
	gp_init();
#endif

#ifdef ZCL_OTA
	/* Initialize OTA */
    ota_init(OTA_TYPE_CLIENT, (af_simple_descriptor_t *)&sampleLight_simpleDesc, &sampleLight_otaInfo, &sampleLight_otaCb);
#endif
}



s32 sampleLightAttrsStoreTimerCb(void *arg)
{
	zcl_onOffAttr_save();
	zcl_levelAttr_save();
	zcl_colorCtrlAttr_save();

	sampleLightAttrsStoreTimerEvt = NULL;
	return -1;
}

void sampleLightAttrsStoreTimerStart(void)
{
	if(sampleLightAttrsStoreTimerEvt){
		ev_on_timer(sampleLightAttrsStoreTimerEvt, 200 * 1000);
	}else{
		sampleLightAttrsStoreTimerEvt = TL_ZB_TIMER_SCHEDULE(sampleLightAttrsStoreTimerCb, NULL, 200 * 1000);
	}
}

void sampleLightAttrsChk(void)
{
	if(gLightCtx.lightAttrsChanged){
		gLightCtx.lightAttrsChanged = FALSE;
		if(zb_isDeviceJoinedNwk()){
			sampleLightAttrsStoreTimerStart();
		}
	}
}

void report_handler(void)
{
	if(zb_isDeviceJoinedNwk()){
		if(zcl_reportingEntryActiveNumGet()){
			u16 second = 1;//TODO: fix me

			reportNoMinLimit();

			//start report timer
			reportAttrTimerStart(second);
		}else{
			//stop report timer
			reportAttrTimerStop();
		}
	}
}

void app_task(void)
{
	app_key_handler();
	if(BDB_STATE_GET() == BDB_STATE_IDLE){
		localPermitJoinState();
		report_handler();

#if 0/* NOTE: If set to '1', the latest status of lighting will be stored. */
		sampleLightAttrsChk();
#endif
	}
}

static void sampleLightSysException(void)
{
	zcl_onOffAttr_save();
	zcl_levelAttr_save();
	zcl_colorCtrlAttr_save();

	SYSTEM_RESET();
}

void factoryRst_init(void)
{
	gLightCtx.powerCntFacRst = 0;
	if(factory_reset_handle()){
		gLightCtx.powerCntFacRst = 1;
	}
}

void factoryRst_task(void)
{
	if(BDB_STATE_GET() == BDB_STATE_IDLE){
		if(gLightCtx.powerCntFacRst){
			gLightCtx.powerCntFacRst = 0;
			gLightCtx.powerCntFacRst2SigMesh = 1;

			factory_reset();
		}else{
			factory_reset_cnt_check();
		}
	}
}

/*********************************************************************
 * @fn      user_init
 *
 * @brief   User level initialization code.
 *
 * @param   None
 *
 * @return  None
 */
void user_init(void)
{
#if USB_PRINTF_MODE
	/* Enable USB Port*/
	gpio_set_func(GPIO_PA5, AS_USB);
	gpio_set_func(GPIO_PA6, AS_USB);
	usb_dp_pullup_en(TRUE);
#endif

	/* Initialize LEDs*/
	led_init();
	hwLight_init();

	/* Power up counter check */
	factoryRst_init();

	/* Initialize Stack */
	stack_init();

	/* Initialize user application */
	user_app_init();

	/* Register except handler for test */
	sys_exceptHandlerRegister(sampleLightSysException);

	/* Adjust light state to default attributes*/
	light_adjust();

	/* User's Task */
#if ZBHCI_EN
	zbhciInit();
	ev_on_poll(EV_POLL_HCI, zbhciTask);
#endif

	ev_on_poll(EV_POLL_FACTORY_RST, factoryRst_task);
	ev_on_poll(EV_POLL_IDLE, app_task);

    /* Read the pre-insatll code from NV */
    zb_pre_install_code_load(&g_bdbCommissionSetting.linkKey, &gLightCtx.linkKey);

    /* Set default reporting configuration */
    u8 reportableChange = 0x00;
    bdb_defaultReportingCfg(SAMPLE_LIGHT_ENDPOINT, HA_PROFILE_ID, ZCL_CLUSTER_GEN_ON_OFF, ZCL_ATTRID_ONOFF,
    						0x0000, 0x003c, (u8 *)&reportableChange);

    /* Initialize BDB */
	bdb_init((af_simple_descriptor_t *)&sampleLight_simpleDesc, &g_bdbCommissionSetting, &g_zbDemoBdbCb, 1);
}


#if 0
//configure zigbee network
#define ZB_BLE_CI_CMD_CFG_SET_CHANNEL           0x0001
#define ZB_BLE_CI_CMD_CFG_SET_PANID             0x0002
#define ZB_BLE_CI_CMD_CFG_SET_SHORT_ADDR        0x0003 
#define ZB_BLE_CI_CMD_CFG_SET_EXT_PANID         0x0004
#define ZB_BLE_CI_CMD_CFG_SET_NWK_KEY           0x0005
#define ZB_BLE_CI_CMD_CFG_START_NWK             0x0006

//light control
#define ZB_BLE_CI_CMD_LIGHT_TOGGLE_BROADCAST    0x0010
#define ZB_BLE_CI_CMD_LIGHT_TOGGLE_UNICAST      0x0011
#define ZB_BLE_CI_CMD_LIGHT_TOGGLE_UNICAST_BY_SEQ 0x0012
//end

//data
#define ZB_BLE_CI_DATA_DEFAULT_CHANNEL          13
#define ZB_BLE_CI_DATA_DEFAULT_PANID            0xface
//end
extern u16 ChipId;
u8 zb_ble_ci_channel = ZB_BLE_CI_DATA_DEFAULT_CHANNEL;
u16 zb_ble_ci_panid = ZB_BLE_CI_DATA_DEFAULT_PANID;
u16 zb_ble_ci_short_addr = MAC_SHORT_ADDR_BROADCAST;
u8 zb_ble_ci_extPanId[8] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77};
u8 zb_ble_ci_nwkKey[16] = { 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89,
			  	  	  	0x9a, 0xab, 0xbc, 0xcd, 0xde, 0xef, 0xf0, 0x01};

u16 zb_ble_ci_cmd_light_toggle_dest_addr;

#define SAMPLE_SWITCH_ENDPOINT 0x01

//
typedef struct 
{
    unsigned char isActive;
    unsigned char seqNO;
    //unsigned char nwk_addr[2];
    unsigned short nwk_addr;
    unsigned char ieee_addr[8];
}device_list_node_t;

device_list_node_t device_list[16];

void init_device_list()
{
    int i;
    for(i=0;i<16;i++)
    {
        device_list[i].isActive = 0;
    }
}

void DevAnnounceIndCB(void *arg)
{
    static unsigned char sequence_number = 0;
    device_list_node_t *ptr = NULL;
    int i;
    
    zdo_device_annce_req_t *devAnnInd = (zdo_device_annce_req_t *)arg;
    for(i=0;i<16;i++)
    {
        if(device_list[i].isActive == 0)
        {
            ptr = &(device_list[i]);
            break;
        }
    }

    if(ptr == NULL)
    {
        return;
    }

    ptr->isActive = 1;
    ptr->seqNO = sequence_number;
    sequence_number++;
    //memcpy(ptr->nwk_addr, &devAnnInd->nwk_addr_local, 2);
    ptr->nwk_addr = devAnnInd->nwk_addr_local;
    memcpy(ptr->ieee_addr, devAnnInd->ieee_addr_local, 8);
}
//

//begin
void onoff_light_unicast(void * p)
{
			epInfo_t dstEpInfo;
			TL_SETSTRUCTCONTENT(dstEpInfo, 0);


			dstEpInfo.dstAddrMode = APS_SHORT_DSTADDR_WITHEP;
			dstEpInfo.dstEp = SAMPLE_SWITCH_ENDPOINT;

            
			dstEpInfo.dstAddr.shortAddr = zb_ble_ci_cmd_light_toggle_dest_addr;
            
            
            
			dstEpInfo.profileId = HA_PROFILE_ID;
			dstEpInfo.txOptions = APS_TX_OPT_ACK_TX;
			dstEpInfo.radius = 0;
            

			zcl_onOff_toggleCmd(SAMPLE_SWITCH_ENDPOINT, &dstEpInfo, FALSE);

}

//end
void onoff_light_broadcast(void * p)
{
			epInfo_t dstEpInfo;
			TL_SETSTRUCTCONTENT(dstEpInfo, 0);


			dstEpInfo.dstAddrMode = APS_SHORT_DSTADDR_WITHEP;
			dstEpInfo.dstEp = SAMPLE_SWITCH_ENDPOINT;
            
			dstEpInfo.dstAddr.shortAddr = 0xfffc;
            
            
			dstEpInfo.profileId = HA_PROFILE_ID;
			dstEpInfo.txOptions = 0;//APS_TX_OPT_ACK_TX;
			dstEpInfo.radius = 0;
            

			zcl_onOff_toggleCmd(SAMPLE_SWITCH_ENDPOINT, &dstEpInfo, FALSE);

}
#endif

int zb_ble_ci_cmd_handler(u16 cmd_type , u8 * payload)
{
    
#if 0
    if(cmd_type == ZB_BLE_CI_CMD_CFG_SET_CHANNEL)
    {
        zb_ble_ci_channel = payload[0];
    }else if(cmd_type == ZB_BLE_CI_CMD_CFG_SET_PANID)
    {
        zb_ble_ci_panid = payload[0];
        zb_ble_ci_panid <<= 8;
        zb_ble_ci_panid |= payload[1];
    }else if(cmd_type == ZB_BLE_CI_CMD_CFG_SET_SHORT_ADDR)
    {
        zb_ble_ci_short_addr = payload[0];
        zb_ble_ci_short_addr <<= 8;
        zb_ble_ci_short_addr |= payload[1];
    }else if(cmd_type == ZB_BLE_CI_CMD_CFG_SET_EXT_PANID)
    {
        memcpy(zb_ble_ci_extPanId,payload,8);
    }else if(cmd_type == ZB_BLE_CI_CMD_CFG_SET_NWK_KEY)
    {
        memcpy(zb_ble_ci_nwkKey,payload,16);
    }else if(cmd_type == ZB_BLE_CI_CMD_CFG_START_NWK)
    {
        //
        
        //
        if(zb_ble_ci_short_addr == MAC_SHORT_ADDR_BROADCAST)
        {
            zb_joinAFixedNetwork(zb_ble_ci_channel,  zb_ble_ci_panid, ChipId, zb_ble_ci_extPanId, zb_ble_ci_nwkKey);
        }
        else
        {
            zb_joinAFixedNetwork(zb_ble_ci_channel,  zb_ble_ci_panid, zb_ble_ci_short_addr, zb_ble_ci_extPanId, zb_ble_ci_nwkKey);
        }
	    bdb_init((af_simple_descriptor_t *)&sampleLight_simpleDesc, &g_bdbCommissionSetting, &g_zbDemoBdbCb, 1);
        memcpy(ss_ib.trust_center_address, g_invalid_addr, EXT_ADDR_LEN);
    
    }else if(cmd_type == ZB_BLE_CI_CMD_LIGHT_TOGGLE_BROADCAST)
    {
        tl_zbTaskPost(onoff_light_broadcast, NULL);
    }else if(cmd_type == ZB_BLE_CI_CMD_LIGHT_TOGGLE_UNICAST)
    {
        zb_ble_ci_cmd_light_toggle_dest_addr = payload[0];
        zb_ble_ci_cmd_light_toggle_dest_addr <<= 8;
        zb_ble_ci_cmd_light_toggle_dest_addr |= payload[1];
        tl_zbTaskPost(onoff_light_unicast, NULL);
    }else if(cmd_type == ZB_BLE_CI_CMD_LIGHT_TOGGLE_UNICAST_BY_SEQ)
    {
        unsigned char seqNum = payload[0];
        int i;

        for(i = 0;i < 16;i++)
        {
            if((device_list[i].isActive)&&(device_list[i].seqNO == seqNum))
            {
                //zb_ble_ci_cmd_light_toggle_dest_addr = device_list[i].nwk_addr[0];
                //zb_ble_ci_cmd_light_toggle_dest_addr <<= 8;
                //zb_ble_ci_cmd_light_toggle_dest_addr |= device_list[i].nwk_addr[1];
                zb_ble_ci_cmd_light_toggle_dest_addr = device_list[i].nwk_addr;
                tl_zbTaskPost(onoff_light_unicast, NULL);
                break;
            }
        }
    }
#endif
}


/*********************************************************************
 * @fn      gpio_user_irq_handler
 *
 * @brief   GPIO interrupt handler.
 *
 * @param   None
 *
 * @return  None
 */
void gpio0_user_irq_handler(void)
{

}

#endif  /* __PROJECT_TL_DIMMABLE_LIGHT__ */

