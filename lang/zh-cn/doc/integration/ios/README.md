[TOP](../../../README.md)　>　[Cocos2d-x plugin的导入步骤](../../README.md)　>　iOS项目设置

---

# iOS项目设置

## **Xcode项目设置**

打开发布的Xcode项目进行编辑。

### 1. F.O.X SDK原生架构(Framework)导入

下载并解压`CYZFox_iOS_static_<version>.zip`，将`CYZFox.framework`文件接入Xcode项目。

### 2. 其他架构设置

请将以下架构接入项目。

架构名 | Status
:--- | :---:
AdSupport.framework|任意
Security.framework|必须
SystemConfiguration.framework|必须
WebKit.framework|必须


### 3. 添加Plugin source

将下载的SDK`FOX_COCOS2DX_SDK_<version>.zip`在OS上打开。请将Classes文件夹内下列iOS的source文件添加在Xcode项目中。

文件名|概要
:---|:---
CYZCCFox.h|API的定义
CYZCCFoxEvent.h|追踪事件的定义
CYZCCFoxTypes.h|回调函数的定义
iOS/CYZCCFox.mm|原生API的封装
iOS/CYZCCFoxEvent.mm|原生追踪事件的封装
iOS/CYZCCFoxIOSUtility.mm|Util方法
iOS/CYZFoxAppDelegateSwizzling.m|protocol`AppDelegate`的`application:openURL:sourceApplication:`和`application:openURL:options`的动态重写定义


### 4. 关于App Transport Security

从F.O.X SDK ver4.0.0开始，底层全部都基于HTTPS协议进行通信，不需要做额外的对应。

---
[返回](../README.md#ios)

[TOP](../../../README.md)
