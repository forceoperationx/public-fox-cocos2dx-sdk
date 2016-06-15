# 廣告投放機能

## 1. 環境設定環境設定

### 1.1 Android

為了導入本SDK，除了`FOX_Android_SDK_3.0.jar`以外還需要導入`GooglePlayServices`<br>
在導入對象APP裡需要導入`GooglePlayServices`來達到取得AdvertisingID的狀態。

**類庫的導入**

請解壓zip文件，遵照下面的格式來拷貝下面的文件。

|拷貝文件|拷貝目的地|
|:---|:---|
|FOX_Android_SDK_{VERSION}/libs/FOX_Android_SDK_{VERSION}.jar|Android項目的libs目錄|
|Classes/Trade/DLCoBanner.h|Classes|
|Classes/Trade/DLCoInterstitial.h|Classes|
|Classes/Trade/Android/\*.\* (全部的文件)|Classes|

**[使用Gradle開發時GooglePlayServicesのdependencies的設定]**
```
compile 'com.google.android.gms:play-services-ads:8.3.0'
```

**[使用Eclipse開發時GooglePlayServices的設定]**

在項目裡導入下面的類庫項目。
```
{android_sdk}/extras/google/google_play_services/libproject/google-play-services_lib
```
> 詳細請確認[Goolge Developers](https://developers.google.com/android/guides/setup)。

#### AndroidManifest.xml的設定

**[permission的設定]**

廣告投放機能需要`INTERNET`和`ACCESS_NETWORK_STATE`這兩個permission。

```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
```

**[Activity的追加]**

表示插播廣告時必須使用Activity。<br>
請按下面那樣原封不動地拷貝和設定。

```xml
<activity
    android:name="co.cyberz.dahlia.DahliaActivity"
    android:theme="@android:style/Theme.Translucent" />
```

**[meta-data的設定]**

* `{APP ID}`是案件開始時由鄙公司發行的ID。是廣告表示必需的。
* `com.google.android.gms.version`是為了利用GooglePlayServices所必需的。

```xml
<meta-data
    android:name="APPADFORCE_APP_ID"
    android:value="{APP ID}" />
<meta-data
    android:name="com.google.android.gms.version"
    android:value="@integer/google_play_services_version" />
```

### 1.2 iOS

**類庫的導入**

請解壓zip文件，並導入下面的文件到Xcode項目裡。

|導入文件|
|:---|
|Classes/iOS/全部的文件|
|Classes/Trade/DLCoBanner.h|
|Classes/Trade/DLCoInterstitial.h|
|Classes/Trade/iOS/\*.\* (全部的文件)|

**必要的framework**
* UIKit.framework
* Foundation.framework
* Security.framework
* SystemConfiguration.framework
* AdSupport.framework

**2.3 plist設定文件**
__文件名__

`AppAdForce.plist`

__設定項目__
* `APP_ID` 的值是案件開始時由敝社發行的ID，是廣告表示必需的。

## 2. API

### DLCoBanner

|返回值類型|方法|詳細|
|:---:|:---|:---|
|-|BannerView ( String placementId, int position )<br>`placementID` : 廣告表示ID (管理員發行)<br>`position` : 表示位置|構造函數|
|void|show ( )<br>`placementID` : 廣告表示ID (管理員發行)|表示橫幅廣告。|
|void|hide ( )|關閉表示的橫幅廣告。|
|-|position : <br>　`DLC_POSITION_TOP` : 配置到畫面上部中心<br>　`DLC_POSITION_BOTTOM` : 配置到畫面下部中心<br>　`DLC_POSITION_TOP_LEFT` : 配置到畫面上部左側<br>　`DLC_POSITION_TOP_RIGHT` : 配置到畫面上部右側<br>　`DLC_POSITION_BOTTOM_LEFT` : 配置到畫面下部左側<br>　`DLC_POSITION_BOTTOM_RIGHT` : 配置到畫面下部右側|表示位置定數|

### DLCoInterstitial

|返回值類型|方法|詳細|
|:---:|:---|:---|
|-|Interstitial ( String placementId )<br><br>`placementID` : 廣告表示ID (管理員發行)|構造函數|
|void|show ( )|表示插播廣告。|


## 3. 安裝範例

### 3.1 橫幅廣告

請在希望表示的時候生成DLCoBanner實例，並安裝show方法。

Sample.cpp
```cpp
#include "DLCoBanner.h"

Fox::DLCoBanner* dlb;

// 表示在畫面上部
void Sample::showBannerTop(Ref* pSender)
{
    int position = DLC_POSITION_TOP_RIGHT;
    char* placementId = ((char*)"広告表示ID");
    dlb = new DLCoBanner(placementId, position);
    dlb->onCocosAdSuccess = CC_CALLBACK_0(Sample::onBannerSuccess, this);
    dlb->onCocosAdFailed = CC_CALLBACK_0(Sample::onBannerFailed, this);
    dlb->show();
}

// 關閉橫幅廣告
void Sample::hideBanner(Ref* pSender)
{
    dlb->hide();
}

// 廣告表示成功時調用的方法
void Sample::onBannerSuccess()
{
    CCLOG("Show banner Success!");
}

// 廣告表示失敗時調用的方法
void Sample::onBannerFailed()
{
    CCLOG("Show banner Failed. Orz");
}


```

### 3.1 插播廣告

請在插播廣告表示對象的畫面裡生成下面的DLCoInterstitial實例，並安裝show方法。

Sample.cpp
```cpp
#include "DLCoInterstitial.h"

// 插播廣告的表示
void Sample::showInterstitial(Ref* pSender)
{
    char* placementId = ((char*)"広告表示ID");
    DLCoInterstitial* di = new DLCoInterstitial(placementId);
    di->onCocosAdSuccess = CC_CALLBACK_0(Sample::onBannerSuccess, this);
    di->onCocosAdFailed = CC_CALLBACK_0(Sample::onBannerFailed, this);
    di->onCocosAdExit = CC_CALLBACK_0(Sample::onBannerClosed, this);
    di->show();
}

// 橫幅的刪除
void Sample::onBannerClosed()
{
    CCLOG("Banner is Closed.");
}
```

---
[Top](/lang/zh-tw/README.md)
