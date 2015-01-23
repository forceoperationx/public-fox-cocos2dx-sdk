# プッシュ通知の実装

F.O.Xのプッシュ通知では、広告流入元別にユーザーのセグメントを分けてプッシュ通知を配信することが可能です。F.O.Xのプッシュ通知機能を使用しない場合は、本設定の必要はありません。


## iOS用の設定

iOSではAPNsというAppleのサーバを経由して、プッシュ通知を各端末に送信します。通知にはAppleから発行されるトークンを利用して、プッシュ通知を送信します。まず、Notify.h、libNotify.aをインポートします。実装では、起動時に実行されるスクリプトで、以下のメソッドを呼び出します。必ずsendConversionメソッドが呼ばれた後に呼ばれるように実装してください。	FoxPlugin::notifyManager();このメソッドは、初回起動時にAppleにデバイストークンを問い合わせにいき、F.O.Xへ登録するというメソッドです。そのデバイストークンを用いて、F.O.Xからプッシュ通知を送信します。※ Androidとプッシュ通知を併用する場合は、章末の実装例を参考に実装ください。
#### iOSでF.O.X以外のプッシュ通知機能を共存させる場合

FoxNotifyPlugin.mを編集してご利用ください。（46行目あたり）・devicetokenを受け取った際の処理	void didRegisterForRemoteNotificationsWithDeviceToken(id self, SEL _cmd, id application, id devToken)	{    	if ([self respondsToSelector:@selector(application:registerDevToken:)])	    {    	    [self application:application registerDevToken:devToken];    	}    		[[Notify sharedManager] manageDevToken:devToken];    		// devtoken取得後の処理をここに記載してください。	}

## Android用の設定

Androidでも同じように、Googleのサーバを経由して、プッシュ通知を送信します。
通知には、Googleから発行されるトークンを利用します。


### パーミッションの設定

下記のように、プッシュ通知を受け取るために必要なパーミッションの設定を\<manifest\>タグ内に追加してください。<br>
既にGCMもしくはC2DM用のパーミッションを記述済の場合は必要ありません。


	<uses-permission android:name="android.permission.WAKE_LOCK" />
	<uses-permission android:name="アプリのパッケージ名.permission.C2D_MESSAGE" />
	<permission android:name="アプリのパッケージ名.permission.C2D_MESSAGE" android:protectionLevel="signature" />
	<uses-permission android:name="com.google.android.c2dm.permission.RECEIVE" />


### プッシュ通知用レシーバーの設定

下記のように、プッシュ通知を受け取るために必要なレシーバーの設定を\<application\>タグ内に追加してください。<br>
既にGCMもしくはC2DM用のレシーバーを記述済の場合は、Receiverを以下のように変更してください。


	<receiver android:name="jp.appAdForce.android.NotifyReceiver"
		android:permission="com.google.android.c2dm.permission.SEND">
		<intent-filter>
			<action android:name="com.google.android.c2dm.intent.RECEIVE" />
			<action android:name="com.google.android.c2dm.intent.REGISTRATION" />
			<category android:name="アプリのパッケージ名" />
		</intent-filter>
	</receiver>


### 複数のレシーバーを共存させる場合

AndroidManifest.xmlではレシーバーを一つしか選択できません。アプリケーションが複数のレシーバー（複数のPush通知機能サービス）を必要とする場合の解決案としての実装手順を以下に説明します。Force Operation Xのレシーバークラスが共存させたいレシーバークラスのonReceive()、もしくはonMessage(),onRegistered()を呼び出します。AndroidManifest.xmlに導入するレシーバークラスをmeta-dataに追加します。<br>以下の例は、追加するレシーバークラスが”com.example.NotifyReceiver”の場合です。

	<meta-data android:name="APPADFORCE_NOTIFY_RECEIVER"
			   android:value="com.example.NotifyReceiver" />



### メソッドの呼び出し

実装では、起動時に実行されるスクリプト中で、以下のメソッドを呼び出します。

	// XXXXXXはGCMのProjectNumberを指定します
	FoxPlugin::notifyManager(XXXXXX);

### Project Number, API KEYの作り方

1. Googleアカウントで[http://cloud.google.com/console](http://cloud.google.com/console)にアクセスします。
2. アクセスすると、TOPにProject Numberが示されています。
3. API&authにアクセスします。
4. Google Cloud Messaging for Android のSTATUSをONにします。
5. Registered appsから「REGISTER APP」ボタンを押します。
6. NAMEには適当な名前を入れ、Web Applicationを選択し、Registerを押します。
7. Server Keyを押下し、API KEYを取得します。

### iOSと併用する場合の実装例

iOSとAndroidの両方でプッシュ通知を実装する際は、以下の例のようにOS別に実行

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)		// iOS		FoxPlugin::notifyManager();	#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)		// Android	   FoxPlugin::notifyManager(XXXXXX);	#endif

### 遷移機能

F.O.X管理画面において、設定したURL先、或いはURLスキームの該当先へプッシュ通知開封時に遷移します。


