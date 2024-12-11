/********************************************************************************************************
 * @file    private.h
 *
 * @brief   This is the header file for private
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
#pragma once

#define PRIVATE_FEAT	0

void private_zclReadRspCmdHandler(u16 clusterId, zclReadRspCmd_t *pReadRspCmd);
void private_zclAddGroupCmdHandler(u8 endpoint, u16 srcAddr, u16 groupId);
status_t private_sceneReqHandler(zclIncomingAddrInfo_t *pAddrInfo, u8 cmdId, void *cmdPayload);
