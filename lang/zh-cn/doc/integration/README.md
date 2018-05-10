[TOP](../../README.md)　>　Cocos2d-x plugin的导入步骤

---

# Cocos2d-x plugin的导入步骤

* [1. 共通](#common)
* [2. iOS](./README.md#ios)
* [3. Android](./README.md#android)


<div id="common"></div>

## 1. 共通

### 1.1 SDK解压

将下载的SDK「FOX_COCOS2DX_SDK_&lt;version&gt;.zip」在OS上展开。Classes文件夹中含有以下文件。

```
[Classes]　// C++,Objective-C++封装代码目录结构
　　┗━ CYZCCFox.h
　　┗━ CYZCCFoxEvent.h
　　┗━ CYZCCFoxTypes.h
　　┗━ [iOS]  // -----------------------------------  iOS封装代码
　　┃　  ┗━ CYZCCFox.mm
　　┃　  ┗━ CYZCCFoxEvent.mm
　　┃　  ┗━ CYZCCFoxIOSUtility.mm
　　┃　  ┗━ CYZFoxAppDelegateSwizzling.m
　　┗━ [Android]  // -------------------------------  Android封装代码
　　 　  ┗━ co_cyberz_fox_cocos2dx_wrapper_Fox.h
　　 　  ┗━ co_cyberz_fox_cocos2dx_wrapper_Fox.cpp
　　 　  ┗━ CYZCCFoxEvent.cpp
　　 　  ┗━ CYZCCFoxTrack.cpp
　　 　  ┗━ FoxNativeTrackListener.h
　　 　  ┗━ FoxNativeTrackListener.cpp
　　 　  ┗━ util
　　 　 　　  ┗━ CYZCCFoxUtil.h
　　 　 　　  ┗━ CYZCCFoxUtil.cpp

[CYZFox_iOS_static_<VERSION>]  // ---------------------  iOS原生SDK
　　┗━ CYZFox.framework

[FOX_Android_SDK_<VERSION>]  // -------------------  Android原生SDK
　　┗━ [libs]
　　　　　┗━ FOX_Android_SDK_<VERSION>.jar
　　　　　┗━ FOX_Android_SDK_Support_Cocos2dx_<VERSION>.jar
```


<div id="ios"></div>

## 2. iOS

> **[iOS SDK详细设置](./ios/README.md)**

<div id="android"></div>
## 3. Android

> **[Android SDK详细设置](./android/README.md)**

---
[TOP](../../README.md)
