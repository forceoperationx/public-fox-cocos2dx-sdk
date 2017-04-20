[TOP](../../README.md)　>　更新到最新版本

---

# 最新到最新版本

希望在导入了旧版F.O.X SDK的APP中导入最新SDK时，请按照以下的顺序进行。

* [1. 删除旧版本所有文件](#remove_regacy)
* [2. 在项目中导入新版本文件](#install)
* [3. 从旧版本(不足4.0.0版)更新的执行方法](#update_implement)
* [4. 其他](#other)

<div id="remove_regacy"></div>
## 1. 删除旧版本所有文件

#### 1.1 Cocos2d-x plugin文件一览

|删除对象文件名称|对象OS|
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

#### 1.2 Android项目的删除对象文件

**[删除]**

* libs目录的FOX_Android_SDK_&lt;VERSION&gt;.jar
* AndroidManifest.xml中记述的下列meta-data(今后，都在代码里做设置)

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

#### 1.3 iOS XCode项目里的删除对象文件

**[删除]**

* AdManager.h
* AnalyticsManager.h
* Ltv.h
* Notify.h
* libAppAdForce.a
* AppAdForce.plist

<div id="install"></div>
## 2. 在项目中导入新版本文件

> 请确认[`Cocos2d-x plugin的导入步骤`](../integration/README.md)。

<div id="update_implement"></div>
## 3. 从旧版本(不足4.0.0版)更新的执行方法

|分类|`〜 3.3.0` 的编码安装|`4.0.0 〜` 的编码安装|
|:---:|:---|:---|
|激活|**[iOS]**<br>・AppAdForce.plist<br><br>**[Android]**<br>AndroidManifest.xml<br>&lt;meta-data&gt;<br>・APPADFORCE_APP_ID<br>・APPADFORCE_CRYPTO_SALT<br>・ANALYTICS_APP_KEY|CYZCCFoxConfig config;<br>config.appId_android = 发行的APP ID;<br>config.salt_android = "发行的APP_SALT";<br>	config.appKey_android = "发行的APP_KEY";<br>CYZCCFox::init(config);|
|Install计测|FoxPlugin::sendConversion(“default”);|CYZCCFox::trackInstall();|
|Install计测<br>(可选)|FoxPlugin::sendConversion(“http://yourhost.com/yourpage.html”, "USER_ID");|CYZCCFoxTrackOption option;<br>option.redirectUrl = "http://yoursite.com";<br>option.buid = "USER_ID";<br>CYZCCFox::trackInstall(option);|
|外部浏览器的事件计测|-|char* externalUrl = (char*)"http://yoursite.com/tagpage";<br>CYZCCFox::trackEventByBrowser(externalUrl);|
|session计测|FoxPlugin::sendStartSession();|CYZCCFox::trackSession();|
|事件计测|// 通过LTV计测进行事件计测<br>FoxPlugin::addParameter(CC_LTV_PARAM_PRICE, “9.99”);<br>FoxPlugin::addParameter(CC_LTV_PARAM_CURRENCY, “USD”);<br>FoxPlugin::addParameter(CC_LTV_PARAM_SKU, “purchase item”);<br>FoxPlugin::sendLtv(成果地点ID, "USER_ID");<br><br>// 通过流量分析进行事件计测<br>FoxPlugin::sendEvent("_purchase", null, null, "order id", “purchase item”, null, 9.99, 1, "USD");|int ltvId = 成果地点ID;<br>const char* eventName = "_purchase";<br>CYZCCFoxEvent* e = new CYZCCFoxEvent(eventName, ltvId);<br>e->buid = "USER_ID";<br>e->sku = "purchase item";<br>e->price = 9.99;<br>e->currency = "USD";<br>e->orderId = "order id"<br>CYZCCFox::trackEvent(e);|

> ※1 请注意，更新到4.0.0及以上版本时如果修改旧版本的事件名，将无法保留流量分析中到现在为止计测到的数据。

<div id="other"></div>
## 4. 其他

#### (Android) BroadcastReceiver多项指定

**[`〜 3.3.0` 的编码安装]**

```xml
<!-- receiver类指定F.O.X SDK的类 -->
<receiver
    android:name="jp.appAdForce.android.InstallReceiver"
    android:exported="true">
    <intent-filter>
        <action android:name="com.android.vending.INSTALL_REFERRER" />
    </intent-filter>
</receiver>

<!-- 用 F.O.X SDK调用其他receiver类时信息记录为meta-data -->
<meta-data
        android:name="APPADFORCE_FORWARD_RECEIVER"
        android:value="com.example.InstallReceiver" />
```

**[`4.0.0 〜` 的编码安装](../integration/android/install_referrer/README.md)**

```xml
<!-- receiver类指定F.O.X SDK的类 -->
<receiver
    android:name="co.cyberz.fox.FoxInstallReceiver"
    android:exported="true">
    <intent-filter>
        <action android:name="com.android.vending.INSTALL_REFERRER" />
    </intent-filter>
</receiver>

<!-- 将F.O.X SDK想要调用的其他receiver类的路径用|(分隔符号)分割开来做描述 -->
<meta-data
        android:name="APPADFORCE_FORWARD_RECEIVER"
        android:value="com.example.InstallReceiver1|com.example.InstallReceiver2|com.example.InstallReceiver3" />
```

---
[TOP](../../README.md)
