[TOP](../../../README.md)　>　[Cocos2d-xプラグインの導入手順](../README.md)　>　Androidプロジェクトの設定

---

# Androidプロジェクトの設定

* **[インストール](#install_sdk)**
* **[パーミッションの設定](#permission)**
* **[インストールリファラ計測の設定](#install_referrer)**
* **[リエンゲージメント計測の設定](#reengagement)**
* **[¥ProGuardを利用する場合](#proguard)**
* **[インストール計測完了のコールバックを受け取る（オプション機能）](#receive_callback)**
* **[その他](#other)**

<div id="install_sdk"></div>

## インストール

### Cocos2d-xプラグインの導入

「FOX_Cocos2dx_SDK_&lt;version&gt;.zip」を展開し、以下の操作を行います。

* 以下のファイルをClassesへコピー
  * CYZCCFox.h
  * CYZCCFoxEvent.h
  * CYZCCFoxTypes.h
  * Androidディレクトリ配下の全ファイル


* プロジェクト内配下のjni/Android.mkの設定を変更し、上記のファイルをビルドの対象に含める<br>

CYZCCFox.cppのJniHelper.hのincludeパスを開発環境に合わせる（以下はその例）

```cpp
#include <iostrem>
#include “cocos2d.h”
#include “CYZCCFox.h”
#include “../android/jni/JniHelper.h”
```

### Android Studioプロジェクトへの導入

アプリをAndroid Studioでビルドしている場合は、gradle経由でインストールできるため、FOX_COCOS2DX_SDK_&lt;version&gt;.zipを展開した中の、FOX_Android_SDK_&lt;VERSION&gt;のライブラリは不要となります。<br>
以下の設定をプロジェクトのbuild.gradleに追加してください。

```
repositories {
    maven {
        url "https://github.com/cyber-z/public-fox-android-sdk/raw/master/mavenRepo"
    }
}

dependencies {
    compile 'co.cyberz.fox:track-core:4.1.1'
    compile 'co.cyberz.fox.support:track-cocos2dx:1.0.1'
}
```


### Eclipseプロジェクトへの導入

ダウンロードしたSDK「FOX_COCOS2DX_SDK_&lt;version&gt;.zip」をOS上に展開します。<br>
「FOX_Android_SDK_&lt;version&gt;/libs」フォルダに同梱されている以下２ファイルをEclipseプロジェクトの`libsフォルダ`に移動させます。

|ファイル名|必須|概要|
|:------:|:------:|:------|
|FOX_Android_SDK_&lt;VERSION&gt;.jar|必須|AndroidのネイティブSDK。通常成果・LTV成果・アクセス解析を計測することができます。|
|FOX_Android_SDK_Support_Cocos2dx_&lt;VERSION&gt;.jar|必須|ネイティブSDK用のラッパーライブラリ|

<div id="permission"></div>

## パーミッションの設定

F.O.X SDKでは下記3つのパーミッションを利用します。
&lt;Manifest&gt;タグ内に次のパーミッションの設定を追加します。

```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
```

パーミッション|Protection Level|必須|概要
:---|:---:|:---:|:---
INTERNET|Normal|必須|F.O.X SDKが通信を行うために必要となります。
READ_EXTERNAL_STORAGE|Dangerous|任意|ストレージを利用した重複排除機能向上に必要となります。(※1)
WRITE_EXTERNAL_STORAGE|Dangerous|任意|ストレージを利用した重複排除機能向上に必要となります。(※1)

> ※1 Android MよりProtectionLevelが`dangerous`に指定されているパーミッションを必要とする機能を利用するには、ユーザーの許可が必要になります。詳細は[外部ストレージを利用した重複排除設定](/lang/ja/doc/integration/android/external_storage/README.md)をご確認ください。


<div id="install_referrer"></div>

## インストールリファラ計測の設定
インストールリファラーを用いたインストール計測を行うために下記の設定を&lt;application&gt;タグに追加します。

```xml
<receiver android:name="co.cyberz.fox.FoxInstallReceiver" android:exported="true">
	<intent-filter>
		<action android:name="com.android.vending.INSTALL_REFERRER" />
	</intent-filter>
</receiver>
```

既に"com.android.vending.INSTALL_REFERRER"に対するレシーバークラスが定義されている場合には、[二つのINSTALL_REFERRERレシーバーを共存させる場合の設定](/lang/ja/doc/integration/android/install_referrer/README.md)をご参照ください。

<div id="reengagement"></div>

## リエンゲージメント計測の設定

リエンゲージメント計測（カスタムURLスキーム経由の起動を計測）するために必要な設定を&lt;application&gt;タグ内に追記します。

リエンゲージメント計測はカスタムURLスキームでActivityが呼び出されることで計測を行います。
ここでのカスタムURLスキームは他のActivityに設定しているものとは異なる値を設定してください。

[設定例]

AndroidManifest.xml
```xml
<activity android:name="org.cocos2dx.cpp.AppActivity">
	<intent-filter>
		<action android:name="android.intent.action.MAIN"/>

		<category android:name="android.intent.category.LAUNCHER"/>
	</intent-filter>

	<intent-filter>
		<action android:name="android.intent.action.VIEW" />

		<category android:name="android.intent.category.DEFAULT" />
		<category android:name="android.intent.category.BROWSABLE" />

		<data android:scheme="カスタム URLスキーム" />
	</intent-filter>
</activity>
```

AppActivity
```java
import co.cyberz.fox.Fox;

@Override
protected void onResume() {
	super.onResume();
	// リエンゲージメント計測
	Fox.trackDeeplinkLaunch(this);
}

@Override
protected void onNewIntent(Intent intent)
{
	super.onNewIntent(intent);
	setIntent(intent);
}
```

> リエンゲージメント広告の計測をするためには、`URLスキームが設定されている全てのActivity`のonResume()に`trackDeeplinkLaunch`メソッドが実装されてある必要があります。



<div id="proguard"></div>

## ProGuardを利用する場合

ProGuard を利用してアプリケーションの難読化を行う際は F.O.X SDK のメソッドが対象とならないよう、以下の設定 を追加してください。

```
-keepattributes *Annotation*
-keep class co.cyberz.** { *; }
-keep class com.google.android.gms.ads.identifier.* { *; }
-dontwarn co.cyberz.**
# Gradle経由でSDKをインストールしている場合、下記jarファイルの指定は不要です。
-libraryjars libs/AppAdForce.jar
```

また、Google Play Service SDK を導入されている場合は、以下のぺージに記載されている keep 指定が記述されているかご確認ください。

[Google Play Services導入時のProguard対応](https://developer.android.com/google/play-services/setup.html#Proguard)

<div id="other"></div>


<div id="receive_callback"></div>

## インストール計測完了のコールバックを受け取る（オプション機能）

[![F.O.X](http://img.shields.io/badge/F.O.X%20SDK-4.1.1%20〜-blue.svg?style=flat)](https://github.com/cyber-z/public-fox-android-sdk/releases/tag/4.1.1)

オプション機能として、インストール計測完了のコールバックをアプリ側で受け取ることが可能です（コールバックが必要ない場合は実装不要です）。<br>
組み込んでいるAndroidネイティブSDKがバージョン4.1.1以降においてインストール計測完了のコールバックを受け取る場合には<br>
以下のように必ず`"アプリ起動時に最初に呼ばれるActivity"`(メインのアクティビティ)の onResume に Fox.trackDeeplinkLaunch メソッドを実装してください。`但し、[前項](#reengagement)の実装が行われている場合には不要です。`

```java

	@Override
	protected void onResume()
	{
		super.onResume();
		// FOX
		Fox.trackDeeplinkLaunch(this);
	}
```

> ※ アプリのインストール計測をCookie計測で行っている場合は、ブラウザからカスタムURLスキームでアプリに戻る際のActivityのonResumeに`Fox.trackDeeplinkLaunch`を実装してください。

> ※ 本実装が行われていない場合、C++側にインストール計測完了が通知されません。

## その他

* [広告IDを利用するためのGoogle Play Services SDKの導入](./google_play_services/README.md)

*	[AndroidManifest.xml 設定サンプル](./config_androidManifest/AndroidManifest.xml)

* [（オプション）外部ストレージを利用した重複排除設定](./external_storage/README.md)

* [（オプション）Android M オートバックアップ機能の利用](./auto_backup/README.md)


---

[戻る](../README.md#android)

[TOP](../../../README.md)
