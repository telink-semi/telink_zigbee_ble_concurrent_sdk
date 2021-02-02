## V1.5.4

### Bugs
*  buffer free issue while doing join(data request confirmation occurs after associate confirmation)

### Feautures
* add ble master demo

### BREAKING CHANGES
* None

### Bugs
* 入网过程中buffer释放异常(当data request confirm在associate confirmation之后产生)

### Feautures
* 添加ble master用例

### BREAKING CHANGES
* 无

## V1.5.3

### Bugs
*  system timer interrupt has still run even if ble is idle.
*  call ble_task_restart/ble_task_stop in zigbee mode, the interupt mask will be cleared
*  buffer free issue while doing join

### Feautures
* add ble master functoinality
* add ble scan during ADV 

### BREAKING CHANGES
* None

### Bugs
* ble处于idle时，system timer中断仍然工作
* zigbee模式下调用task_restart/ble_task_stop， 导致rf中断mask位被清除
* 入网过程中buffer释放异常

### Feautures
* 添加ble master功能
* ble ADV状态添加scan功能

### BREAKING CHANGES
* 无

## V1.5.2

### Bugs
*  add usb_dp_pullup_en in lib/libdrivers_8258.a, or compile error while enable "ZBHCI_USB_CDC"， now usb cdc works
*  system ram exception will occur if the "ZB_BUF_POOL_NUM" or“APS_BINDING_TABLE_NUM”is modified in sdk
*  nib.ieeeAddress didn't set after touch link，so that the address information is wrong when doing binding
*  binding address table shouldn't be updated after group binding 

###Feautures
* mac retry number controlled by mac-pib.frameRetryNum
* update for following tc policy for ZC
* use "various" instead of "define" for some settings
* add aps_group.c ro open source code

### BREAKING CHANGES
* None

### Bugs
* 在lib/libdrivers_8258.a里，添加“usb_dp_pullup_en“函数，否则打开”ZBHCI_USB_CDC"编译出错，CDC可工作
* SDK里修改"ZB_BUF_POOL_NUM" or“APS_BINDING_TABLE_NUM”会导致内存异常
* touchlink结束后，nib.ieeeAddress没有正确赋值，导致绑定时地址出现异常。
* 组绑定后，绑定地址表不应该更新

###Feautures
* mac重传由mac-pib.frameRetryNum控制
* ZC 遵循tc policy
* 宏改为变量，可有用户配置
* 开源 aps_group.c

### BREAKING CHANGES
* 无


## V1.5.1

### Bugs
* Ble/Zigbee use different RF Tx Power(zb: 10dBm, ble: 3dBm),  the Tx Power should be set back while doing mode switch

### BREAKING CHANGES
* None

### Bugs
* Ble/Zigbee使用不同的Rf Tx power(zb: 10dBm, ble: 3dBm); 模式切换时，tx power应该设回相应的值

### BREAKING CHANGES
* 无



## V1.5.0

### Features
* remove bindlist when forget dev
* enable Green Power for Route/Coordinator 
* update the formula for converting the rssi to Lqi
* make the timeout of transport key can be configurable

### Bug Fixes
* fix the bug that the parent neighbor table can't been updated when the parent node is changed after orphan 
  joining is done
* Fix mac ack timeout issue
* Scene table store/restore issue

### BREAKING CHANGES
* None

### Features
* 设备离网，bindList清除
* 对于Route/Coordinator，使能Green Power
* 更新rssi转化到Lqi的折算公式
* 入网时tranport key超时时间可由用户层控制

### Bug Fixes
* 修复终端节点orphan join回连时父节点的neighbor table没有有效更新的问题。
* mac ack回复慢的问题
* scene table保存、恢复的问题

### BREAKING CHANGES
* 无