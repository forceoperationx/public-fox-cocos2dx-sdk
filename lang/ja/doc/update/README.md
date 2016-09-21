[TOP](../../README.md)　>　最新バージョンへのマイグレーションについて

---

# 最新バージョンへのマイグレーションについて

以前のF.O.X SDKが導入されたアプリに最新のSDKを導入する際に必要な手順は以下の通りです。

* [1. 以前のバージョンのファイルを全て削除](#remove_regacy)
* [2. 最新バージョンのファイルをプロジェクトにインストール](#install)
* [3. 旧バージョン(4.0.0未満)からの実装方法を更新](#update_implement)
* [4. その他](#other)

<div id="remove_regacy"></div>
## 1. 以前のバージョンのファイルを全て削除

#### 1.1 Cocos2d-xプラグインファイル一覧

|削除対象ファイル名|対象OS|
|:---:|:---:|
|Cocos2dxFox.h|共通|
|Cocos2dxFox.cpp|Android|
|Cocos2dxFox.mm|iOS|
|FoxNotifyPlugin.h|iOS|
|FoxNotifyPlugin.m|iOS|
|FoxReengagePlugin.h|iOS|
|FoxReengagePlugin.m|iOS|
|FoxVersionDelegate.h|iOS|
|FoxVersionDelegate.mm|iOS|
|FoxVersionPlugin.h|iOS|
|FoxVersionPlugin.mm|iOS|

#### 1.2 Androidプロジェクトの削除対象ファイル

**[削除]**

* libsディレクトリのFOX_Android_SDK_&lt;VERSION&gt;.jar
* AndroidManifest.xmlに記述していた以下のmeta-data(今後、コード上での設定となります)

```xml
<meta-data
    android:name="APPADFORCE_APP_ID"
    android:value="1234" />
<meta-data
    android:name="APPADFORCE_SERVER_URL"
    android:value="XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" />
<meta-data
    android:name="APPADFORCE_CRYPTO_SALT"
    android:value="YYYYYYYYYYYYYYYYYYYYYYYYYY" />
<meta-data
    android:name="ANALYTICS_APP_KEY"
    android:value="ZZZZZZZZZZZZZZZZZZZZZZZZZZ" />
```

#### 1.3 iOS XCodeプロジェクトの削除対象ファイル

**[削除]**

* AdManager.h
* AnalyticsManager.h
* Ltv.h
* Notify.h
* libAppAdForce.a
* AppAdForce.plist

<div id="install"></div>
## 2. 最新バージョンのファイルをプロジェクトにインストール

> [`Cocos2d-xプラグインの導入手順`](../integration/README.md)をご確認ください。

<div id="update_implement"></div>
## 3. 旧バージョン(4.0.0未満)からの実装方法を更新

|種別|`〜 3.3.0` の実装|`4.0.0 〜` の実装|
|:---:|:---|:---|
|アクティベーション|**[iOS]**<br>・AppAdForce.plist<br><br>**[Android]**<br>AndroidManifest.xml<br>&lt;meta-data&gt;<br>・APPADFORCE_APP_ID<br>・APPADFORCE_CRYPTO_SALT<br>・ANALYTICS_APP_KEY|CYZCCFoxConfig config;<br>config.appId_android = 発行されたアプリID;<br>config.salt_android = "発行されたAPP_SALT";<br>	config.appKey_android = "発行されたAPP_KEY";<br>CYZCCFox::init(config);|
|インストール計測|FoxPlugin::sendConversion(“default”);|CYZCCFox::trackInstall();|
|インストール計測<br>(オプション付)|FoxPlugin::sendConversion(“http://yourhost.com/yourpage.html”, "USER_ID");|CYZCCFoxTrackOption option;<br>option.redirectUrl = "http://yoursite.com";<br>option.buid = "USER_ID";<br>CYZCCFox::trackInstall(option);|
|外部ブラウザでイベント計測|-|char* externalUrl = (char*)"http://yoursite.com/tagpage";<br>CYZCCFox::trackEventByBrowser(externalUrl);|
|セッション計測|FoxPlugin::sendStartSession();|CYZCCFox::trackSession();|
|イベント計測|// LTV計測によるイベント計測<br>FoxPlugin::addParameter(CC_LTV_PARAM_PRICE, “9.99”);<br>FoxPlugin::addParameter(CC_LTV_PARAM_CURRENCY, “USD”);<br>FoxPlugin::addParameter(CC_LTV_PARAM_SKU, “purchase item”);<br>FoxPlugin::sendLtv(成果地点ID, "USER_ID");<br><br>// アクセス解析によるイベント計測<br>FoxPlugin::sendEvent("_purchase", null, null, "order id", “purchase item”, null, 9.99, 1, "USD");|int ltvId = 成果地点ID;<br>char* eventName = (char*)"_purchase";<br>CYZCCFoxEvent* e = new CYZCCFoxEvent(eventName, ltvId);<br>e->buid = "USER_ID";<br>e->sku = "purchase item";<br>e->price = 9.99;<br>e->currency = "USD";<br>e->orderId = "order id"<br>CYZCCFox::trackEvent(e);|

> ※1 バージョン4.0.0以降にマイグレーションする際、これまで旧バージョンで指定していたイベント名を変更してしまうと、アクセス解析にて計測してきた集計データが引き継がれなくなりますのでご注意ください。

<div id="other"></div>
## 4. その他

#### (Android) BroadcastReceiverの複数指定

**[`〜 3.3.0` の実装]**

```xml
<!-- レシーバークラスはF.O.X SDKのクラスを指定 -->
<receiver
    android:name="jp.appAdForce.android.InstallReceiver"
    android:exported="true">
    <intent-filter>
        <action android:name="com.android.vending.INSTALL_REFERRER" />
    </intent-filter>
</receiver>

<!-- F.O.X SDKから呼び出したい他のレシーバークラス情報をmeta-dataとして記述 -->
<meta-data
        android:name="APPADFORCE_FORWARD_RECEIVER"
        android:value="com.example.InstallReceiver" />
```

**[`4.0.0 〜` の実装](../integration/android/install_referrer/README.md)**

```xml
<!-- レシーバークラスはF.O.X SDKのクラスを指定します -->
<receiver
    android:name="co.cyberz.fox.FoxInstallReceiver"
    android:exported="true">
    <intent-filter>
        <action android:name="com.android.vending.INSTALL_REFERRER" />
    </intent-filter>
</receiver>

<!-- F.O.X SDKから呼び出したい他のレシーバークラスのパスを|(パイプ)区切りで記述します -->
<meta-data
        android:name="APPADFORCE_FORWARD_RECEIVER"
        android:value="com.example.InstallReceiver1|com.example.InstallReceiver2|com.example.InstallReceiver3" />
```

---
[TOP](../../README.md)
