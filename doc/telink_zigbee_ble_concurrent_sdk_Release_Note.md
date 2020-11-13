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