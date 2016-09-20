[TOP](../../../README.md)　>　[Cocos2d-xプラグインの導入手順](../README.md)　>　Androidプロジェクトの設定

---

# Androidプロジェクトの設定

## 1. パーミッションの設定

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



## 2. インストールリファラ計測の設定
インストールリファラーを用いたインストール計測を行うために下記の設定を&lt;application&gt;タグに追加します。

```xml
<receiver android:name="co.cyberz.fox.FoxInstallReceiver" android:exported="true">
	<intent-filter>
		<action android:name="com.android.vending.INSTALL_REFERRER" />
	</intent-filter>
</receiver>
```

既に"com.android.vending.INSTALL_REFERRER"に対するレシーバークラスが定義されている場合には、[二つのINSTALL_REFERRERレシーバーを共存させる場合の設定](/lang/ja/doc/integration/android/install_referrer/README.md)をご参照ください。


## 3. リエンゲージメント計測の設定

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


## 4. その他

* [広告IDを利用するためのGoogle Play Services SDKの導入](./google_play_services/README.md)

*	[AndroidManifest.xml 設定サンプル](./config_androidManifest/AndroidManifest.xml)

* [（オプション）外部ストレージを利用した重複排除設定](./external_storage/README.md)

* [（オプション）Android M オートバックアップ機能の利用](./auto_backup/README.md)


## 5. roGuardを利用する場合

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


---

[戻る](../../README.md)

[TOP](../../../README.md)
