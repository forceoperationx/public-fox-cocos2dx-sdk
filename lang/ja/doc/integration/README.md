[TOP](../../README.md)　>　Cocos2d-xプラグインの導入手順

---

# Cocos2d-xプラグインの導入手順

* [1. 共通](#common)
* [2. iOS](./README.md#ios)
* [3. Android](./README.md#android)


<div id="common"></div>
## 1. 共通

### 1.1 SDKの展開

ダウンロードしたSDK「FOX_COCOS2DX_SDK_&lt;version&gt;.zip」をOS上に展開します。Classesフォルダ内に同梱されているファイルは以下の通りです。

```
[Classes]　// C++,Objective-C++のラッパーコード格納ディレクトリ
　　┗━ CYZCCFox.h
　　┗━ CYZCCFoxEvent.h
　　┗━ CYZCCFoxTypes.h
　　┗━ [iOS]  // -----------------------------------  iOS用ラッパーコード
　　┃　  ┗━ CYZCCFox.mm
　　┃　  ┗━ CYZCCFoxEvent.mm
　　┃　  ┗━ CYZCCFoxIOSUtility.mm
　　┃　  ┗━ CYZFoxAppDelegateSwizzling.m
　　┗━ [Android]  // -------------------------------  Android用ラッパーコード
　　 　  ┗━ co_cyberz_fox_cocos2dx_wrapper_Fox.h
　　 　  ┗━ co_cyberz_fox_cocos2dx_wrapper_Fox.cpp
　　 　  ┗━ CYZCCFoxEvent.cpp
　　 　  ┗━ CYZCCFoxTrack.cpp
　　 　  ┗━ FoxNativeTrackListener.h
　　 　  ┗━ FoxNativeTrackListener.cpp
　　 　  ┗━ util
　　 　 　　  ┗━ CYZCCFoxUtil.h
　　 　 　　  ┗━ CYZCCFoxUtil.cpp

[CYZFox_iOS_static_<VERSION>]  // ---------------------  iOSネイティブSDK
　　┗━ CYZFox.framework

[FOX_Android_SDK_<VERSION>]  // -------------------  AndroidネイティブSDK
　　┗━ [libs]
　　　　　┗━ FOX_Android_SDK_<VERSION>.jar
　　　　　┗━ FOX_Android_SDK_Support_Cocos2dx_<VERSION>.jar
```


<div id="ios"></div>
## 2. iOS

> **[iOS SDKの詳細設定](./ios/README.md)**

<div id="android"></div>
## 3. Android

> **[Android SDKの詳細設定](./android/README.md)**

---
[TOP](../../README.md)
