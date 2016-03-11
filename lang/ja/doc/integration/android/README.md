# Androidプロジェクトの設定

Android 用の設定は Unity プロジェクト上で行うことができます。Unity プロジェクトに組み込まれた
AndroidManifest.xml を編集します。プロジェクトに AndroidManifest.xml が存在しない場合は、 「Plugins/Android/AndroidManifest-sample.xml」を「AndroidManifest.xml」にリネームしてご利用ください。


## パーミッションの設定

F.O.X SDKでは下記4つのパーミッションを利用します。
&lt;Manifest&gt;タグ内に次のパーミッションの設定を追加します。

```xml
<uses-permission android:name="android.permission.INTERNET" />
<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
```

パーミッション|Protection Level|必須|概要
:---|:---:|:---:|:---
INTERNET|Normal|必須|F.O.X SDKが通信を行うために必要となります。
ACCESS_NETWORK_STATE|Normal|必須|F.O.X SDKが通信可能かを確認するために必要となります。
READ_EXTERNAL_STORAGE|Dangerous|任意|ストレージを利用した重複排除機能向上に必要となります。(※1)
WRITE_EXTERNAL_STORAGE|Dangerous|任意|ストレージを利用した重複排除機能向上に必要となります。(※1)

> ※1 Android MよりProtectionLevelが`dangerous`に指定されているパーミッションを必要とする機能を利用するには、ユーザーの許可が必要になります。詳細は[外部ストレージを利用した重複排除設定](/lang/ja/doc/integration/android/external_storage/README.md)をご確認ください。


## メタデータの設定

SDKの実行に必要な情報を<application>タグ内に追加します。

```xml
<meta-data
	android:name="APPADFORCE_APP_ID"
	android:value="Force Operation X管理者より連絡しますので、その値を入力してください。" />
<meta-data
	android:name="APPADFORCE_SERVER_URL"
	android:value="Force Operation X管理者より連絡しますので、その値を入力してください。" />
<meta-data
	android:name="APPADFORCE_CRYPTO_SALT"
	android:value="Force Operation X管理者より連絡しますので、その値を入力してください。" />
<meta-data
	android:name="ANALYTICS_APP_KEY"
	android:value="Force Operation X管理者より連絡しますので、その値を入力してください。" />
```

設定するキーとバリューは以下の通りです。

|パラメータ名|必須|概要|
|:------|:------|:------|
|APPADFORCE_APP_ID|必須|Force Operation X管理者より連絡しますので、その値を入力してください。|
|APPADFORCE_SERVER_URL|必須|Force Operation X管理者より連絡しますので、その値を入力してください。|
|APPADFORCE_CRYPTO_SALT|必須|Force Operation X管理者より連絡しますので、その値を入力してください。|
|ANALYTICS_APP_KEY|必須|Force Operation X管理者より連絡しますので、その値を入力してください。|


## インストールリファラ計測の設定
インストールリファラーを用いたインストール計測を行うために下記の設定を&lt;application&gt;タグに追加します。

```xml
<receiver android:name="jp.appAdForce.android.InstallReceiver" android:exported="true">
	<intent-filter>
		<action android:name="com.android.vending.INSTALL_REFERRER" />
	</intent-filter>
</receiver>
```

既に"com.android.vending.INSTALL_REFERRER"に対するレシーバークラスが定義されている場合には、[二つのINSTALL_REFERRERレシーバーを共存させる場合の設定](/lang/ja/doc/integration/android/install_referrer/README.md)をご参照ください。


## リエンゲージメント計測の設定

リエンゲージメント計測（カスタムURLスキーム経由の起動を計測）するために必要な設定を&lt;application&gt;タグ内に追記します。

リエンゲージメント計測はカスタムURLスキームでActivityが呼び出されることで計測を行います。
ここでのカスタムURLスキームは他のActivityに設定しているものとは異なる値を設定してください。

[設定例]

AndroidManifest.xml
```xml
<activity android:name="org.cocos2dx.cpp.AppActivity">
	<intent-filter>
		<action android:name="android.intent.action.VIEW" />
		<category android:name="android.intent.category.DEFAULT" />
		<category android:name="android.intent.category.BROWSABLE" />
		<data android:scheme="カスタム URL スキーム" />
	</intent-filter>
</activity>
```

Activity
```java
import jp.appAdForce.android.AdManager;

@Override
protected void onResume() {
	super.onResume();
	AdManager ad = new AdManager(this);
	ad.sendReengageConversion(getIntent());
}
```

URLスキームで起動されるActivityのlaunchModeが"singleTask"または"singleInstance"の場合は、URLスキーム経由でパラメータを受け取るために`onNewIntent`メソッドをoverrideし、以下のように`setIntent`メソッドをコールしてください。

```java
@Override
protected void onNewIntent(Intent intent)
{
	super.onNewIntent(intent);
	setIntent(intent);
}
```

> リエンゲージメント広告の計測をするためには、`URLスキームが設定されている全てのActivity`のonResume()に`sendReengageConversion`メソッドが実装されてある必要があります。


## その他

* [広告IDを利用するためのGoogle Play Services SDKの導入](/lang/ja/doc/integration/android/google_play_services/README.md)

* [AndroidManifest.xml 設定サンプル](/lang/ja/doc/integration/android/config_android_manifest/AndroidManifest.xml)

* [（オプション）外部ストレージを利用した重複排除設定](/lang/ja/doc/integration/android/external_storage/README.md)

* [（オプション）Android M オートバックアップ機能の利用](/lang/ja/doc/integration/android/auto_backup/README.md)


## ProGuardを利用する場合

ProGuard を利用してアプリケーションの難読化を行う際は F.O.X SDK のメソッドが対象とならないよう、以下の設定 を追加してください。

```
-keepattributes *Annotation*

-libraryjars libs/AppAdForce.jar
-keep interface jp.appAdForce.** { *; }
-keep class jp.appAdForce.** { *; }
-keep class jp.co.dimage.** { *; }
-keep class com.google.android.gms.ads.identifier.* { *; }
-dontwarn jp.appAdForce.android.**
-dontwarn jp.co.dimage.**
-dontwarn jp.co.cyberz.fox.**
-dontwarn com.adobe.fre.**
-dontwarn com.ansca.**
-dontwarn com.naef.jnlua.**
```

また、Google Play Service SDK を導入されている場合は、以下のぺージに記載されている keep 指定が記述されているかご確認ください。

[Google Play Services導入時のProguard対応](https://developer.android.com/google/play-services/setup.html#Proguard)


---
[TOP](/lang/ja/README.md)
