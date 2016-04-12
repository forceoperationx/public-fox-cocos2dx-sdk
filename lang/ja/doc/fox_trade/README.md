# - F.O.X Trade Cocos2d-x Integration Guide -

## 1. 環境設定

### 1.1 Android

本SDKの組み込みにはlibsの`FOX_Android_SDK_3.0.jar`と別途`GooglePlayServices`が必須となります。<br>
組み込み対象のアプリにはGooglePlayServicesをご導入の上、AdvertisingIDを取得出来る状態が必須となっております。

**ライブラリの導入**

zipファイルを解凍し、以下のファイルを下記に従ってコピーしてください。

|コピーするファイル|コピー先|
|:---|:---|
|FOX_Android_SDK_{VERSION}/libs/FOX_Android_SDK_{VERSION}.jar|Androidプロジェクトのlibsフォルダ|
|Classes/Trade/DLCoBanner.h|Classes|
|Classes/Trade/DLCoInterstitial.h|Classes|
|Classes/Android/全てのファイル|Classes|

**[Gradleでビルドする場合のGooglePlayServicesのdependenciesの設定]**
```
compile 'com.google.android.gms:play-services-ads:8.3.0'
```

**[Eclipseでビルドする場合のGooglePlayServicesの設定]**

以下のライブラリプロジェクトをプロジェクトにインポートします。
```
{android_sdk}/extras/google/google_play_services/libproject/google-play-services_lib
```
> 詳細は[Goolge Developers](https://developers.google.com/android/guides/setup)をご確認ください。

#### AndroidManifest.xmlの設定

**[パーミッションの設定]**

広告配信機能は`INTERNET`・`ACCESS_NETWORK_STATE`の２つのパーミッションが必須ととなります。

```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
```

**[Activityの追加]**

インタースティシャル広告を表示する際に必須となるActivityとなります。<br>
以下、そのままコピーしてご設定ください。

```xml
<activity
    android:name="co.cyberz.dahlia.DahliaActivity"
    android:theme="@android:style/Theme.Translucent" />
```

**[meta-dataの設定]**

* `{アプリID}`は案件開始時に弊社より発行させて頂くIDとなります。
広告表示に必須となります。
* `com.google.android.gms.version`はGooglePlayServicesを利用するために必須となります。

```xml
<meta-data
    android:name="APPADFORCE_APP_ID"
    android:value="{アプリID}" />
<meta-data
    android:name="com.google.android.gms.version"
    android:value="@integer/google_play_services_version" />
```

### 1.2 iOS

**ライブラリの導入**

zipファイルを解凍し、以下のファイルをXcodeプロジェクトに導入してください。

|導入するファイル|
|:---|
|Classes/iOS/全てのファイル|
|Classes/Trade/DLCoBanner.h|
|Classes/Trade/DLCoInterstitial.h|
|Classes/Trade/iOS/全てのファイル|

**必要なframework**
* UIKit.framework
* Foundation.framework
* Security.framework
* SystemConfiguration.framework
* AdSupport.framework

**2.3 plist設定ファイル**
__ファイル名__

`AppAdForce.plist`

__設定項目__
* `APP_ID` 値は案件開始時に弊社より発行させて頂くIDとなります。
広告表示に必須となります。

## 2. API

### DLCoBanner

|返り値型|メソッド|詳細|
|:---:|:---|:---|
|-|BannerView ( String placementId, int position )<br><br>`placementID` : 広告表示ID (管理者より発行されます)<br><br>`position` : 表示位置|コンストラクター|
|void|show ( )<br><br>`placementID` : 広告表示ID (管理者より発行されます)|バナー広告を表示します。|
|void|hide ( )|表示したバナー広告を閉じます。|
|-|position : <br>`AdPosition.TOP` : 画面上部の中心に配置<br>`DLC_POSITION_TOP` : 画面上部中心に配置<br>`DLC_POSITION_BOTTOM` : 画面下部中心に配置<br>`DLC_POSITION_TOP_LEFT` : 画面上部左に配置<br>`DLC_POSITION_TOP_RIGHT` : 画面上部右に配置<br>`DLC_POSITION_BOTTOM_LEFT` : 画面下部左に配置<br>`DLC_POSITION_BOTTOM_RIGHT` : 画面下部右に配置|表示位置コンスタント|

### DLCoInterstitial

|返り値型|メソッド|詳細|
|:---:|:---|:---|
|-|Interstitial ( String placementId )<br><br>`placementID` : 広告表示ID (管理者より発行されます)|コンストラクター|
|void|show ( )|インタースティシャル広告を表示します。|


## 3. 実装サンプル

### 3.1 バナー広告

表示させるタイミングでDLCoBannerインストタンスを生成し、showメソッドを実行します。

Sample.h
```cpp
#include "DLCoBanner.h"

class Sample
{
...

    DLCoBanner* dlb;

};
```

Sample.cpp
```cpp
#include "Sample.h"

Fox::DLCoBanner* dlb;

// 画面上部に表示する
void Sample::showBannerTop(Ref* pSender)
{
    int position = dlb->DLC_POSITION_TOP_RIGHT;
    char* placementId = ((char*)"広告表示ID");
    dlb = new DLCoBanner(placementId, position);
    dlb->onCocosAdSuccess = CC_CALLBACK_0(Sample::onBannerSuccess, this);
    dlb->onCocosAdFailed = CC_CALLBACK_0(Sample::onBannerFailed, this);
    dlb->show();
}

// バナー広告を閉じる
void Sample::hideBanner(Ref* pSender)
{
    dlb->hide();
}

// 広告表示の成功時に呼ばれるメソッド
void Sample::onBannerSuccess()
{
    CCLOG("Show banner Success!");
}

// 広告表示の失敗時に呼ばれるメソッド
void Sample::onBannerFailed()
{
    CCLOG("Show banner Failed. Orz");
}


```

### 3.1 インタースティシャル広告

表示させるタイミングでDLCoInterstitialインスタンスを生成し、showメソッドを実行します。

Sample.h
```cpp
#include "DLCoInterstitial.h"

class Sample
{
...

    DLCoInterstitial* dli;

};
```

Sample.cpp
```cpp
#include "Sample.h"

// インタースティシャル広告の表示
void Sample::showInterstitial(Ref* pSender)
{
    char* placementId = ((char*)"広告表示ID");
    DLCoInterstitial* di = new DLCoInterstitial(placementId);
    di->onCocosAdSuccess = CC_CALLBACK_0(Sample::onBannerSuccess, this);
    di->onCocosAdFailed = CC_CALLBACK_0(Sample::onBannerFailed, this);
    di->onCocosAdExit = CC_CALLBACK_0(Sample::onBannerClosed, this);
    di->show();
}

// バナー削除
void Sample::onBannerClosed()
{
    CCLOG("Banner is Closed.");
}
```

---
[トップ](/lang/ja/README.md)
