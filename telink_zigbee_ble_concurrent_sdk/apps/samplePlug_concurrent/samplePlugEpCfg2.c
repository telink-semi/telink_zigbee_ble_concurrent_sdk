/********************************************************************************************************
 * @file    samplePlugEpCfg2.c
 *
 * @brief   This is the source file for samplePlugEpCfg2
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *******************************************************************************************************/
#if (__PROJECT_TL_PLUG__)

/**********************************************************************
 * INCLUDES
 */
#include "tl_common.h"
#include "zcl_include.h"
#include "samplePlug.h"

#if PLUG_EP_2_SUPPORT
/**********************************************************************
 * LOCAL CONSTANTS
 */
#ifndef ZCL_BASIC_MFG_NAME_2
#define ZCL_BASIC_MFG_NAME_2     		{6,'T','E','L','I','N','K'}
#endif
#ifndef ZCL_BASIC_MODEL_ID_2
#define ZCL_BASIC_MODEL_ID_2	   		{5,'T','L','S','R','9'}
#endif
#ifndef ZCL_BASIC_SW_BUILD_ID_2
#define ZCL_BASIC_SW_BUILD_ID_2     	{10,'0','1','2','2','0','5','2','0','1','7'}
#endif

#define COLOR_TEMPERATURE_PHYSICAL_MIN_2	0x00FA//4000K
#define COLOR_TEMPERATURE_PHYSICAL_MAX_2	0x01C6//2200K
#define COLOR_TEMPERATURE_DEFAULT_2			0x0176//2700K


/**********************************************************************
 * TYPEDEFS
 */


/**********************************************************************
 * GLOBAL VARIABLES
 */
/**
 *  @brief Definition for Incoming cluster / Sever Cluster
 */
const u16 sampleLight_inClusterList_2[] =
{
	ZCL_CLUSTER_GEN_BASIC,
	ZCL_CLUSTER_GEN_IDENTIFY,
#ifdef ZCL_GROUP
	ZCL_CLUSTER_GEN_GROUPS,
#endif
#ifdef ZCL_SCENE
	ZCL_CLUSTER_GEN_SCENES,
#endif
#ifdef ZCL_ON_OFF
	ZCL_CLUSTER_GEN_ON_OFF,
#endif
#ifdef ZCL_LEVEL_CTRL
	ZCL_CLUSTER_GEN_LEVEL_CONTROL,
#endif
#ifdef ZCL_LIGHT_COLOR_CONTROL
	ZCL_CLUSTER_LIGHTING_COLOR_CONTROL,
#endif
#ifdef ZCL_WWAH
	ZCL_CLUSTER_WWAH,
#endif
};

/**
 *  @brief Definition for Outgoing cluster / Client Cluster
 */
const u16 sampleLight_outClusterList_2[] =
{
#ifdef ZCL_OTA
    ZCL_CLUSTER_OTA,
#endif
};

/**
 *  @brief Definition for Server cluster number and Client cluster number
 */
#define SAMPLELIGHT_IN_CLUSTER_NUM_2		(sizeof(sampleLight_inClusterList_2)/sizeof(sampleLight_inClusterList_2[0]))
#define SAMPLELIGHT_OUT_CLUSTER_NUM_2		(sizeof(sampleLight_outClusterList_2)/sizeof(sampleLight_outClusterList_2[0]))

/**
 *  @brief Definition for simple description for HA profile
 */
const af_simple_descriptor_t sampleLight_simpleDesc_2 =
{
	HA_PROFILE_ID,                      		/* Application profile identifier */
#ifdef ZCL_LIGHT_COLOR_CONTROL
	HA_DEV_COLOR_DIMMABLE_LIGHT,
#else
	#ifdef ZCL_LEVEL_CTRL
		HA_DEV_DIMMABLE_LIGHT,              	/* Application device identifier */
	#else
		HA_DEV_ONOFF_LIGHT,						/* Application device identifier */
	#endif
#endif
	SAMPLE_LIGHT_ENDPOINT_2,              		/* Endpoint */
	1,                                  		/* Application device version */
	0,											/* Reserved */
	SAMPLELIGHT_IN_CLUSTER_NUM_2,           	/* Application input cluster count */
	SAMPLELIGHT_OUT_CLUSTER_NUM_2,          	/* Application output cluster count */
	(u16 *)sampleLight_inClusterList_2,    		/* Application input cluster list */
	(u16 *)sampleLight_outClusterList_2,   		/* Application output cluster list */
};

/* Basic */
zcl_basicAttr_t g_zcl_basicAttrs_2 =
{
	.zclVersion 	= 0x03,
	.appVersion 	= 0x00,
	.stackVersion 	= 0x02,
	.hwVersion		= 0x00,
	.manuName		= ZCL_BASIC_MFG_NAME_2,
	.modelId		= ZCL_BASIC_MODEL_ID_2,
	.powerSource	= POWER_SOURCE_MAINS_1_PHASE,
	.swBuildId		= ZCL_BASIC_SW_BUILD_ID_2,
	.deviceEnable	= TRUE,
};

const zclAttrInfo_t basic_attrTbl_2[] =
{
	{ ZCL_ATTRID_BASIC_ZCL_VER,      		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs_2.zclVersion},
	{ ZCL_ATTRID_BASIC_APP_VER,      		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs_2.appVersion},
	{ ZCL_ATTRID_BASIC_STACK_VER,    		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs_2.stackVersion},
	{ ZCL_ATTRID_BASIC_HW_VER,       		ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs_2.hwVersion},
	{ ZCL_ATTRID_BASIC_MFR_NAME,     		ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ,  						(u8*)g_zcl_basicAttrs_2.manuName},
	{ ZCL_ATTRID_BASIC_MODEL_ID,     		ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ,  						(u8*)g_zcl_basicAttrs_2.modelId},
	{ ZCL_ATTRID_BASIC_POWER_SOURCE, 		ZCL_DATA_TYPE_ENUM8,    ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs_2.powerSource},
	{ ZCL_ATTRID_BASIC_DEV_ENABLED,  		ZCL_DATA_TYPE_BOOLEAN,  ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)&g_zcl_basicAttrs_2.deviceEnable},
	{ ZCL_ATTRID_BASIC_SW_BUILD_ID,  		ZCL_DATA_TYPE_CHAR_STR, ACCESS_CONTROL_READ,  						(u8*)&g_zcl_basicAttrs_2.swBuildId},

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  						(u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_BASIC_ATTR_NUM_2	  sizeof(basic_attrTbl_2) / sizeof(zclAttrInfo_t)


/* Identify */
zcl_identifyAttr_t g_zcl_identifyAttrs_2 =
{
	.identifyTime	= 0x0000,
};

const zclAttrInfo_t identify_attrTbl_2[] =
{
	{ ZCL_ATTRID_IDENTIFY_TIME,  			ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)&g_zcl_identifyAttrs_2.identifyTime},

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  						(u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_IDENTIFY_ATTR_NUM_2	 sizeof(identify_attrTbl_2) / sizeof(zclAttrInfo_t)

#ifdef ZCL_GROUP
/* Group */
zcl_groupAttr_t g_zcl_groupAttrs_2 =
{
	.nameSupport	= 0,
};

const zclAttrInfo_t group_attrTbl_2[] =
{
	{ ZCL_ATTRID_GROUP_NAME_SUPPORT,  		ZCL_DATA_TYPE_BITMAP8,  ACCESS_CONTROL_READ,  (u8*)&g_zcl_groupAttrs_2.nameSupport},

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  (u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_GROUP_ATTR_NUM_2	  sizeof(group_attrTbl_2) / sizeof(zclAttrInfo_t)
#endif

#ifdef ZCL_SCENE
/* Scene */
zcl_sceneAttr_t g_zcl_sceneAttrs_2 =
{
	.sceneCount		= 0,
	.currentScene	= 0,
	.currentGroup	= 0x0000,
	.sceneValid		= FALSE,
	.nameSupport	= 0,
};

const zclAttrInfo_t scene_attrTbl_2[] =
{
    { ZCL_ATTRID_SCENE_SCENE_COUNT,       	ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  (u8*)&g_zcl_sceneAttrs_2.sceneCount},
    { ZCL_ATTRID_SCENE_CURRENT_SCENE,     	ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ,  (u8*)&g_zcl_sceneAttrs_2.currentScene},
    { ZCL_ATTRID_SCENE_CURRENT_GROUP,     	ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ,  (u8*)&g_zcl_sceneAttrs_2.currentGroup},
    { ZCL_ATTRID_SCENE_SCENE_VALID,       	ZCL_DATA_TYPE_BOOLEAN,  ACCESS_CONTROL_READ,  (u8*)&g_zcl_sceneAttrs_2.sceneValid},
    { ZCL_ATTRID_SCENE_NAME_SUPPORT,      	ZCL_DATA_TYPE_BITMAP8,  ACCESS_CONTROL_READ,  (u8*)&g_zcl_sceneAttrs_2.nameSupport},

    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  (u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_SCENE_ATTR_NUM_2	 sizeof(scene_attrTbl_2) / sizeof(zclAttrInfo_t)
#endif

#ifdef ZCL_ON_OFF
/* On/Off */
zcl_onOffAttr_t g_zcl_onOffAttrs_2 =
{
	.onOff				= 0x00,
	.globalSceneControl	= 1,
	.onTime				= 0x0000,
	.offWaitTime		= 0x0000,
	.startUpOnOff 		= ZCL_START_UP_ONOFF_SET_ONOFF_TO_ON,
};

const zclAttrInfo_t onOff_attrTbl_2[] =
{
	{ ZCL_ATTRID_ONOFF,  					ZCL_DATA_TYPE_BOOLEAN,  ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE,  (u8*)&g_zcl_onOffAttrs_2.onOff},
	{ ZCL_ATTRID_GLOBAL_SCENE_CONTROL, 		ZCL_DATA_TYPE_BOOLEAN, 	ACCESS_CONTROL_READ, 							  (u8*)&g_zcl_onOffAttrs_2.globalSceneControl},
	{ ZCL_ATTRID_ON_TIME, 					ZCL_DATA_TYPE_UINT16, 	ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, 	  (u8*)&g_zcl_onOffAttrs_2.onTime},
	{ ZCL_ATTRID_OFF_WAIT_TIME, 			ZCL_DATA_TYPE_UINT16, 	ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, 	  (u8*)&g_zcl_onOffAttrs_2.offWaitTime},
	{ ZCL_ATTRID_START_UP_ONOFF, 			ZCL_DATA_TYPE_ENUM8, 	ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, 	  (u8*)&g_zcl_onOffAttrs_2.startUpOnOff},

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,  							  (u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_ONOFF_ATTR_NUM_2	 sizeof(onOff_attrTbl_2) / sizeof(zclAttrInfo_t)
#endif

#ifdef ZCL_LEVEL_CTRL
/* Level */
zcl_levelAttr_t g_zcl_levelAttrs_2 =
{
	.curLevel				= ZCL_LEVEL_ATTR_MAX_LEVEL,
	.remainingTime			= 0,
	.options				= 0,
	.minLevel				= ZCL_LEVEL_ATTR_MIN_LEVEL,
	.maxLevel				= ZCL_LEVEL_ATTR_MAX_LEVEL,
	.startUpCurrentLevel 	= ZCL_START_UP_CURRENT_LEVEL_TO_PREVIOUS,
};

const zclAttrInfo_t level_attrTbl_2[] =
{
	{ ZCL_ATTRID_LEVEL_CURRENT_LEVEL,  			ZCL_DATA_TYPE_UINT8,   ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_levelAttrs_2.curLevel},
	{ ZCL_ATTRID_LEVEL_REMAINING_TIME, 			ZCL_DATA_TYPE_UINT16,  ACCESS_CONTROL_READ,  							(u8*)&g_zcl_levelAttrs_2.remainingTime},
	{ ZCL_ATTRID_LEVEL_MIN_LEVEL,  				ZCL_DATA_TYPE_UINT8,   ACCESS_CONTROL_READ, 							(u8*)&g_zcl_levelAttrs_2.minLevel },
	{ ZCL_ATTRID_LEVEL_MAX_LEVEL,  				ZCL_DATA_TYPE_UINT8,   ACCESS_CONTROL_READ, 							(u8*)&g_zcl_levelAttrs_2.maxLevel },
	{ ZCL_ATTRID_LEVEL_OPTIONS,  				ZCL_DATA_TYPE_BITMAP8, ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, 		(u8*)&g_zcl_levelAttrs_2.options },
	{ ZCL_ATTRID_LEVEL_START_UP_CURRENT_LEVEL,  ZCL_DATA_TYPE_UINT8,   ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE,  	(u8*)&g_zcl_levelAttrs_2.startUpCurrentLevel},

	{ ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 		ZCL_DATA_TYPE_UINT16,  ACCESS_CONTROL_READ,  							(u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_LEVEL_ATTR_NUM_2	 sizeof(level_attrTbl_2) / sizeof(zclAttrInfo_t)
#endif

#ifdef ZCL_LIGHT_COLOR_CONTROL
/* Color Control */
zcl_lightColorCtrlAttr_t g_zcl_colorCtrlAttrs_2 =
{
#if COLOR_RGB_SUPPORT && COLOR_CCT_SUPPORT
	.colorCapabilities				= ZCL_COLOR_CAPABILITIES_BIT_HUE_SATURATION |
									  ZCL_COLOR_CAPABILITIES_BIT_X_Y_ATTRIBUTES |
									  ZCL_COLOR_CAPABILITIES_BIT_COLOR_TEMPERATURE,
	.colorMode						= ZCL_COLOR_MODE_CURRENT_X_Y,
	.enhancedColorMode				= ZCL_COLOR_MODE_CURRENT_X_Y,
#elif COLOR_RGB_SUPPORT
	.colorCapabilities				= ZCL_COLOR_CAPABILITIES_BIT_HUE_SATURATION |
									  ZCL_COLOR_CAPABILITIES_BIT_X_Y_ATTRIBUTES,
	.colorMode						= ZCL_COLOR_MODE_CURRENT_X_Y,
	.enhancedColorMode				= ZCL_COLOR_MODE_CURRENT_X_Y,
#elif COLOR_CCT_SUPPORT
	.colorCapabilities				= ZCL_COLOR_CAPABILITIES_BIT_COLOR_TEMPERATURE,
	.colorMode						= ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS,
	.enhancedColorMode				= ZCL_COLOR_MODE_COLOR_TEMPERATURE_MIREDS,
#endif
	.options						= 0,
	.numOfPrimaries					= 0,
#if COLOR_RGB_SUPPORT
	.currentX 						= 0x753f,
	.currentY						= 0x68f6,

	.currentHue						= 0x18,
	.currentSaturation				= 0xc9,
#if COLOR_LOOP_SUPPORT
	.colorLoopActive				= 0x00,
	.colorLoopDirection				= 0x00,
	.colorLoopTime					= 0x0019,
	.colorLoopStartEnhancedHue		= 0x2300,
	.colorLoopStoredEnhancedHue		= 0x0000,
#endif//COLOR_LOOP_SUPPORT
#endif
#if COLOR_CCT_SUPPORT
	.colorTemperatureMireds			= COLOR_TEMPERATURE_DEFAULT_2,//COLOR_TEMPERATURE_PHYSICAL_MAX_2,
	.colorTempPhysicalMinMireds		= COLOR_TEMPERATURE_PHYSICAL_MIN_2,
	.colorTempPhysicalMaxMireds 	= COLOR_TEMPERATURE_PHYSICAL_MAX_2,
	.coupleColorTempToLevelMinMireds = COLOR_TEMPERATURE_PHYSICAL_MIN_2,
	.startUpColorTemperatureMireds 	= ZCL_START_UP_COLOR_TEMPERATURE_MIREDS_TO_PREVIOUS,
#endif
};

const zclAttrInfo_t lightColorCtrl_attrTbl_2[] =
{
    { ZCL_ATTRID_COLOR_MODE,              				ZCL_DATA_TYPE_ENUM8,   	ACCESS_CONTROL_READ,     					(u8*)&g_zcl_colorCtrlAttrs_2.colorMode },
    { ZCL_ATTRID_COLOR_OPTIONS,           				ZCL_DATA_TYPE_BITMAP8, 	ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE, (u8*)&g_zcl_colorCtrlAttrs_2.options },
    { ZCL_ATTRID_ENHANCED_COLOR_MODE,     				ZCL_DATA_TYPE_ENUM8,   	ACCESS_CONTROL_READ,     					(u8*)&g_zcl_colorCtrlAttrs_2.enhancedColorMode },
    { ZCL_ATTRID_COLOR_CAPABILITIES,       				ZCL_DATA_TYPE_BITMAP16, ACCESS_CONTROL_READ,     					(u8*)&g_zcl_colorCtrlAttrs_2.colorCapabilities },
    { ZCL_ATTRID_NUMBER_OF_PRIMARIES,     				ZCL_DATA_TYPE_UINT8,   	ACCESS_CONTROL_READ,     					(u8*)&g_zcl_colorCtrlAttrs_2.numOfPrimaries },
#if COLOR_RGB_SUPPORT
    { ZCL_ATTRID_CURRENT_X,             				ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_colorCtrlAttrs_2.currentX },
    { ZCL_ATTRID_CURRENT_Y,      						ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_colorCtrlAttrs_2.currentY },
    { ZCL_ATTRID_CURRENT_HUE,             				ZCL_DATA_TYPE_UINT8,   	ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_colorCtrlAttrs_2.currentHue },
    { ZCL_ATTRID_CURRENT_SATURATION,      				ZCL_DATA_TYPE_UINT8,   	ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_colorCtrlAttrs_2.currentSaturation },
#if COLOR_LOOP_SUPPORT
    { ZCL_ATTRID_COLOR_LOOP_ACTIVE,       				ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ, 							 (u8*)&g_zcl_colorCtrlAttrs_2.colorLoopActive },
    { ZCL_ATTRID_COLOR_LOOP_DIRECTION,    				ZCL_DATA_TYPE_UINT8,    ACCESS_CONTROL_READ, 							 (u8*)&g_zcl_colorCtrlAttrs_2.colorLoopDirection },
    { ZCL_ATTRID_COLOR_LOOP_TIME,         				ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ, 							 (u8*)&g_zcl_colorCtrlAttrs_2.colorLoopTime },
    { ZCL_ATTRID_COLOR_LOOP_START_ENHANCED_HUE,   		ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ,     						 (u8*)&g_zcl_colorCtrlAttrs_2.colorLoopStartEnhancedHue },
    { ZCL_ATTRID_COLOR_LOOP_STORED_ENHANCED_HUE,  		ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ,     						 (u8*)&g_zcl_colorCtrlAttrs_2.colorLoopStoredEnhancedHue },
#endif//COLOR_LOOP_SUPPORT
#endif
#if COLOR_CCT_SUPPORT
    { ZCL_ATTRID_COLOR_TEMPERATURE_MIREDS,				ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ | ACCESS_CONTROL_REPORTABLE, (u8*)&g_zcl_colorCtrlAttrs_2.colorTemperatureMireds },
    { ZCL_ATTRID_COLOR_TEMP_PHYSICAL_MIN_MIREDS,  		ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,     						 (u8*)&g_zcl_colorCtrlAttrs_2.colorTempPhysicalMinMireds },
    { ZCL_ATTRID_COLOR_TEMP_PHYSICAL_MAX_MIREDS,  		ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,     						 (u8*)&g_zcl_colorCtrlAttrs_2.colorTempPhysicalMaxMireds },
	{ ZCL_ATTRID_COUPLE_COLOR_TEMP_TO_LEVEL_MIN_MIREDS, ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ,     						 (u8*)&g_zcl_colorCtrlAttrs_2.coupleColorTempToLevelMinMireds },
    { ZCL_ATTRID_START_UP_COLOR_TEMPERATURE_MIREDS, 	ZCL_DATA_TYPE_UINT16,  	ACCESS_CONTROL_READ | ACCESS_CONTROL_WRITE,      (u8*)&g_zcl_colorCtrlAttrs_2.startUpColorTemperatureMireds },
#endif
    { ZCL_ATTRID_GLOBAL_CLUSTER_REVISION, 				ZCL_DATA_TYPE_UINT16,   ACCESS_CONTROL_READ,  							 (u8*)&zcl_attr_global_clusterRevision},
};

#define ZCL_COLOR_ATTR_NUM_2	 sizeof(lightColorCtrl_attrTbl_2) / sizeof(zclAttrInfo_t)
#endif

/**
 *  @brief Definition for simple light ZCL specific cluster
 */
const zcl_specClusterInfo_t g_sampleLightClusterList_2[] =
{
	{ZCL_CLUSTER_GEN_BASIC,				 MANUFACTURER_CODE_NONE, 	ZCL_BASIC_ATTR_NUM_2, 		basic_attrTbl_2,  			zcl_basic_register,			 sampleLight_basicCb},
	{ZCL_CLUSTER_GEN_IDENTIFY,			 MANUFACTURER_CODE_NONE, 	ZCL_IDENTIFY_ATTR_NUM_2,	identify_attrTbl_2,			zcl_identify_register,		 sampleLight_identifyCb},
#ifdef ZCL_GROUP
	{ZCL_CLUSTER_GEN_GROUPS,			 MANUFACTURER_CODE_NONE, 	ZCL_GROUP_ATTR_NUM_2, 		group_attrTbl_2,  			zcl_group_register,			 sampleLight_groupCb},
#endif
#ifdef ZCL_SCENE
	{ZCL_CLUSTER_GEN_SCENES,			 MANUFACTURER_CODE_NONE, 	ZCL_SCENE_ATTR_NUM_2,		scene_attrTbl_2,			zcl_scene_register,			 sampleLight_sceneCb},
#endif
#ifdef ZCL_ON_OFF
	{ZCL_CLUSTER_GEN_ON_OFF,			 MANUFACTURER_CODE_NONE, 	ZCL_ONOFF_ATTR_NUM_2,		onOff_attrTbl_2,			zcl_onOff_register,			 sampleLight_onOffCb},
#endif
#ifdef ZCL_LEVEL_CTRL
	{ZCL_CLUSTER_GEN_LEVEL_CONTROL,		 MANUFACTURER_CODE_NONE, 	ZCL_LEVEL_ATTR_NUM_2,		level_attrTbl_2,			zcl_level_register,			 sampleLight_levelCb},
#endif
#ifdef ZCL_LIGHT_COLOR_CONTROL
	{ZCL_CLUSTER_LIGHTING_COLOR_CONTROL, MANUFACTURER_CODE_NONE, 	ZCL_COLOR_ATTR_NUM_2,		lightColorCtrl_attrTbl_2,	zcl_lightColorCtrl_register, sampleLight_colorCtrlCb},
#endif
};

u8 SAMPLELIGHT_CB_CLUSTER_NUM_2 = (sizeof(g_sampleLightClusterList_2)/sizeof(g_sampleLightClusterList_2[0]));


/**********************************************************************
 * FUNCTIONS
 */


/*********************************************************************
 * @fn      zcl_onOffAttr_save_2
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_onOffAttr_save_2(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_ON_OFF
#if NV_ENABLE
	bool needSave = FALSE;
	zcl_nv_onOff_t zcl_nv_onOff_2;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_ON_OFF_2, sizeof(zcl_nv_onOff_t), (u8*)&zcl_nv_onOff_2);

	if(st == NV_SUCC){
		if((zcl_nv_onOff_2.onOff != g_zcl_onOffAttrs_2.onOff) ||
		   (zcl_nv_onOff_2.startUpOnOff != g_zcl_onOffAttrs_2.startUpOnOff)){
			needSave = TRUE;
		}
	}else if(st == NV_ITEM_NOT_FOUND){
		needSave = TRUE;
	}

	if(needSave){
		zcl_nv_onOff_2.onOff = g_zcl_onOffAttrs_2.onOff;
		zcl_nv_onOff_2.startUpOnOff = g_zcl_onOffAttrs_2.startUpOnOff;

		printf("ep 2: onoff = %x, startUp = %x\n", zcl_nv_onOff_2.onOff, zcl_nv_onOff_2.startUpOnOff);

		st = nv_flashWriteNew(1, NV_MODULE_ZCL, NV_ITEM_ZCL_ON_OFF_2, sizeof(zcl_nv_onOff_t), (u8*)&zcl_nv_onOff_2);
	}
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_onOffAttr_restore_2
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_onOffAttr_restore_2(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_ON_OFF
#if NV_ENABLE
	zcl_nv_onOff_t zcl_nv_onOff_2;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_ON_OFF_2, sizeof(zcl_nv_onOff_t), (u8*)&zcl_nv_onOff_2);

	if(st == NV_SUCC){
		g_zcl_onOffAttrs_2.onOff = zcl_nv_onOff_2.onOff;
		g_zcl_onOffAttrs_2.startUpOnOff = zcl_nv_onOff_2.startUpOnOff;
	}
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_levelAttr_save_2
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_levelAttr_save_2(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_LEVEL_CTRL
#if NV_ENABLE
	bool needSave = FALSE;
	zcl_nv_level_t zcl_nv_level_2;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_LEVEL_2, sizeof(zcl_nv_level_t), (u8*)&zcl_nv_level_2);

	if(st == NV_SUCC){
		if((zcl_nv_level_2.curLevel != g_zcl_levelAttrs_2.curLevel) ||
		   (zcl_nv_level_2.startUpCurLevel != g_zcl_levelAttrs_2.startUpCurrentLevel)){
			needSave = TRUE;
		}
	}else if(st == NV_ITEM_NOT_FOUND){
		needSave = TRUE;
	}

	if(needSave){
		zcl_nv_level_2.curLevel = g_zcl_levelAttrs_2.curLevel;
		zcl_nv_level_2.startUpCurLevel = g_zcl_levelAttrs_2.startUpCurrentLevel;

		st = nv_flashWriteNew(1, NV_MODULE_ZCL, NV_ITEM_ZCL_LEVEL_2, sizeof(zcl_nv_level_t), (u8*)&zcl_nv_level_2);
	}
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_levelAttr_restore_2
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_levelAttr_restore_2(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_LEVEL_CTRL
#if NV_ENABLE
	zcl_nv_level_t zcl_nv_level_2;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_LEVEL_2, sizeof(zcl_nv_level_t), (u8*)&zcl_nv_level_2);

	if(st == NV_SUCC){
		g_zcl_levelAttrs_2.curLevel = zcl_nv_level_2.curLevel;
		g_zcl_levelAttrs_2.startUpCurrentLevel = zcl_nv_level_2.startUpCurLevel;
	}
#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_colorCtrlAttr_save_2
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_colorCtrlAttr_save_2(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_LIGHT_COLOR_CONTROL
#if NV_ENABLE
	bool needSave = FALSE;
	zcl_nv_colorCtrl_t zcl_nv_colorCtrl_2;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_COLOR_CTRL_2, sizeof(zcl_nv_colorCtrl_t), (u8*)&zcl_nv_colorCtrl_2);

	if(st == NV_SUCC){
		if((zcl_nv_colorCtrl_2.currentHue != g_zcl_colorCtrlAttrs_2.currentHue) ||
		   (zcl_nv_colorCtrl_2.currentSaturation != g_zcl_colorCtrlAttrs_2.currentSaturation) ||
		   (zcl_nv_colorCtrl_2.currentX != g_zcl_colorCtrlAttrs_2.currentX) ||
		   (zcl_nv_colorCtrl_2.currentY != g_zcl_colorCtrlAttrs_2.currentY) ||
		   (zcl_nv_colorCtrl_2.colorTemperatureMireds != g_zcl_colorCtrlAttrs_2.colorTemperatureMireds) ||
		   (zcl_nv_colorCtrl_2.startUpColorTemperatureMireds != g_zcl_colorCtrlAttrs_2.startUpColorTemperatureMireds)){
			needSave = TRUE;
		}
	}else if(st == NV_ITEM_NOT_FOUND){
		needSave = TRUE;
	}

	if(needSave){
		zcl_nv_colorCtrl_2.currentHue = g_zcl_colorCtrlAttrs_2.currentHue;
		zcl_nv_colorCtrl_2.currentSaturation = g_zcl_colorCtrlAttrs_2.currentSaturation;
		zcl_nv_colorCtrl_2.currentX = g_zcl_colorCtrlAttrs_2.currentX;
		zcl_nv_colorCtrl_2.currentY = g_zcl_colorCtrlAttrs_2.currentY;
		zcl_nv_colorCtrl_2.colorTemperatureMireds = g_zcl_colorCtrlAttrs_2.colorTemperatureMireds;
		zcl_nv_colorCtrl_2.startUpColorTemperatureMireds = g_zcl_colorCtrlAttrs_2.startUpColorTemperatureMireds;
		zcl_nv_colorCtrl_2.colorMode = g_zcl_colorCtrlAttrs_2.colorMode;
		zcl_nv_colorCtrl_2.enhancedColorMode = g_zcl_colorCtrlAttrs_2.enhancedColorMode;

		st = nv_flashWriteNew(1, NV_MODULE_ZCL, NV_ITEM_ZCL_COLOR_CTRL_2, sizeof(zcl_nv_colorCtrl_t), (u8*)&zcl_nv_colorCtrl_2);
	}

#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_colorCtrlAttr_restore_2
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
nv_sts_t zcl_colorCtrlAttr_restore_2(void)
{
	nv_sts_t st = NV_SUCC;

#ifdef ZCL_LIGHT_COLOR_CONTROL
#if NV_ENABLE
	zcl_nv_colorCtrl_t zcl_nv_colorCtrl_2;

	st = nv_flashReadNew(1, NV_MODULE_ZCL,  NV_ITEM_ZCL_COLOR_CTRL_2, sizeof(zcl_nv_colorCtrl_t), (u8*)&zcl_nv_colorCtrl_2);
	if(st == NV_SUCC){
		g_zcl_colorCtrlAttrs_2.colorMode = zcl_nv_colorCtrl_2.colorMode;
		g_zcl_colorCtrlAttrs_2.enhancedColorMode = zcl_nv_colorCtrl_2.enhancedColorMode;
		g_zcl_colorCtrlAttrs_2.currentHue = zcl_nv_colorCtrl_2.currentHue;
		g_zcl_colorCtrlAttrs_2.currentSaturation = zcl_nv_colorCtrl_2.currentSaturation;
		g_zcl_colorCtrlAttrs_2.currentX = zcl_nv_colorCtrl_2.currentX;
		g_zcl_colorCtrlAttrs_2.currentY = zcl_nv_colorCtrl_2.currentY;
		g_zcl_colorCtrlAttrs_2.colorTemperatureMireds = zcl_nv_colorCtrl_2.colorTemperatureMireds;
		g_zcl_colorCtrlAttrs_2.startUpColorTemperatureMireds = zcl_nv_colorCtrl_2.startUpColorTemperatureMireds;
	}

#else
	st = NV_ENABLE_PROTECT_ERROR;
#endif
#endif

	return st;
}

/*********************************************************************
 * @fn      zcl_sampleLightAttrsInit
 *
 * @brief
 *
 * @param   None
 *
 * @return
 */
void zcl_sampleLightAttrsInit_2(void)
{
	zcl_onOffAttr_restore_2();
	zcl_levelAttr_restore_2();
	zcl_colorCtrlAttr_restore_2();
}
#endif

#endif	/* __PROJECT_TL_PLUG__ */
