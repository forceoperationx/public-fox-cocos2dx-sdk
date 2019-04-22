[TOP](../../../README.md)　>　[Cocos2d-x plugin导入步骤](../README.md)　>　Android项目设置

---

# Android项目设置

* **[1. 导入](#install_sdk)**
* **[2. 权限设置](#permission)**
* **[3. Install Referrer计测设置](#install_referrer)**
* **[4. 流失唤回广告计测设置](#reengagement)**
* **[5. 使用ProGuard](#proguard)**
* **[6. 其他](#other)**

<div id="install_sdk"></div>

## 1. 导入

### 1.1 Cocos2d-x plugin导入

解压「FOX_Cocos2dx_SDK_&lt;version&gt;.zip」，进行以下操作。

* 将以下文件复制到Classes
  * CYZCCFox.h
  * CYZCCFoxEvent.h
  * CYZCCFoxTypes.h
  * Android目录下所有文件


* 更改项目内的jni/Android.mk设置，将上述文件设为编译对象<br>

请根据开发环境来配置CYZCCFox.cpp的JniHelper.h的include路径（以下为案例）

```cpp
#include <iostrem>
#include “cocos2d.h”
#include “CYZCCFox.h”
#include “../android/jni/JniHelper.h”
```

### 1.2 导入到Android Studio项目

APP为Android Studio内编译的场合，通过gradle进行安装，解压FOX_COCOS2DX_SDK_&lt;version&gt;.zip后，不需要其中FOX_Android_SDK_&lt;VERSION&gt;的类库。<br>
请在项目的build.gradle中添加以下设置。

```
repositories {
    maven {
        url "https://github.com/forceoperationx/public-fox-android-sdk/raw/master/mavenRepo"
    }
}

dependencies {
    compile 'co.cyberz.fox:track-core:4.0.0'
    compile 'co.cyberz.fox.support:track-cocos2dx:1.0.0'
}
```


### 1.3 导入到Eclipse项目

将下载的SDK「FOX_COCOS2DX_SDK_&lt;version&gt;.zip」在OS上展开。<br>
「FOX_Android_SDK_&lt;version&gt;/libs」文件中捆绑的以下两个文件移动至Eclipse项目的`libs`文件夹中。

|文件名|必须|概要|
|:------:|:------:|:------|
|FOX_Android_SDK_&lt;VERSION&gt;.jar|必须|Android原生SDK。可以计测普通成果・LTV成果・访问解析。|
|FOX_Android_SDK_Support_Cocos2dx_&lt;VERSION&gt;.jar|必须|原生SDK的捆绑类库|

<div id="permission"></div>

## 2. 权限设置

F.O.X SDK可以使用以下三种权限。
&lt;Manifest&gt;标签中添加以下权限的设置。

```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
```

权限|Protection Level|必须|概要
:---|:---:|:---:|:---
INTERNET|Normal|必須|F.O.X SDK是进行通信的必要条件。
READ_EXTERNAL_STORAGE|Dangerous|任意|使用外部储存来优化排重功能时必须设定。(※1)
WRITE_EXTERNAL_STORAGE|Dangerous|任意|使用外部储存来优化排重功能时必须设定。(※1)

> ※1 从Android M开始使用ProtectionLevel被指定为`dangerous`权限的功能时，需要获得用户许可。具体请参考[利用外部储存优化排除重复设置](/lang/ja/doc/integration/android/external_storage/README.md)。


<div id="install_referrer"></div>

## 3. Install Referrer计测设置
使用install referrer进行Install计测时，需将以下设置添加至&lt;application&gt;标签中。

```xml
<receiver android:name="co.cyberz.fox.FoxInstallReceiver" android:exported="true">
	<intent-filter>
		<action android:name="com.android.vending.INSTALL_REFERRER" />
	</intent-filter>
</receiver>
```

"com.android.vending.INSTALL_REFERRER"的receiver类已经被定义的情况下，请参照[让两种INSTALL_REFERRER RECEIVER共存的设置](/lang/ja/doc/integration/android/install_referrer/README.md)。

<div id="reengagement"></div>

## 4. 流失唤回广告计测设置

为进行流失唤回广告计测（计测经由自定义URL SCHEME的启动行为），将所需设置添加在&lt;application&gt;标签中。

流失唤回广告计测通过自定义URL SCHEME调用Activity的方式来进行计测。
这里的自定义URL SCHEME请区别于其他Activity中的值来设定。

[设置案例]

AndroidManifest.xml
```xml
<activity android:name="org.cocos2dx.cpp.AppActivity">
	<intent-filter>
		<action android:name="android.intent.action.VIEW" />
		<category android:name="android.intent.category.DEFAULT" />
		<category android:name="android.intent.category.BROWSABLE" />
		<data android:scheme="自定义URL scheme" />
	</intent-filter>
</activity>
```

Activity
```java
import co.cyberz.fox.Fox;

@Override
protected void onResume() {
	super.onResume();
	// 流失唤回广告计测
	Fox.trackDeeplinkLaunch(this);
}

@Override
protected void onNewIntent(Intent intent)
{
	super.onNewIntent(intent);
	setIntent(intent);
}
```

> 为进行流失唤回广告计测，所有设置了URL scheme的Activity的`onResume()`中必须执行`trackDeeplinkLaunch`方法。

<div id="proguard"></div>

## 5. 使用ProGuard

使用Proguard进行APP代码混淆时，为排除F.O.X SDK的method方法，请添加以下设置。

```
-keepattributes *Annotation*
-keep class co.cyberz.** { *; }
-keep class com.google.android.gms.ads.identifier.* { *; }
-dontwarn co.cyberz.**
# 通过Gradle安装SDK时，不需要指定以下jar文件。
-libraryjars libs/AppAdForce.jar
```

另外，在已安装Google Play Service SDK 的情况下，请确认以下页面中是否已记述了keep指定。

[导入Google Play Services时的Proguard应对](https://developer.android.com/google/play-services/setup.html#Proguard)

<div id="other"></div>

## 6. 其他

* [导入Google Play Services SDK来使用广告ID](./google_play_services/README.md)

*	[AndroidManifest.xml 设置案例](./config_androidManifest/AndroidManifest.xml)

* [（任意）使用外部储存进行重复排查的设置](./external_storage/README.md)

* [（任意）Android M 自动备份功能](./auto_backup/README.md)


---

[返回](../README.md#android)

[TOP](../../../README.md)
