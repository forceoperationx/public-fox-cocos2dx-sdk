## AndroidManifest.xml メタデータ オプション詳細

|パラメータ名|必須|概要|
|:------|:------|:------|
|APPADFORCE_APP_ID|必須|Force Operation X管理者より連絡しますので、その値を入力してください。|
|APPADFORCE_SERVER_URL|必須|Force Operation X管理者より連絡しますので、その値を入力してください。|
|APPADFORCE_CRYPTO_SALT|必須|Force Operation X管理者より連絡しますので、その値を入力してください。|
|ANALYTICS_APP_KEY|必須|Force Operation X管理者より連絡しますので、その値を入力してください。|
|APPADFORCE_ID_DIR|オプション|内(外)部ストレージを利用する際、任意の保存するディレクトリ名を指定できます。<br>未指定の場合、パッケージ名でディレクトリが作成されます。|
|APPADFORCE_ID_FILE|オプション|内(外)部ストレージを利用する際、任意の保存する識別子ファイル名を指定できます。<br>未指定の場合、”__FOX_XUNIQ__”でファイルが作成されます。|
|APPADFORCE_USE_EXTERNAL_STORAGE|オプション|0を指定した場合、内(外)部ストレージへの保存は実行しません。|

#### 内部及び外部ストレージを利用した重複排除
アプリケーションの初回起動時にSDKが生成した識別IDをローカルストレージまたはSDカードに保存することで、アプリケーション再インストール時に重複判定を行うことができます。外部ストレージへのファイル読み書きに必要なパーミッションの設定を<manifest>タグ内に追加します。本設定は必須ではありませんが、アプリケーションの再インストールにおける重複検知の精度が大きく向上するため、できる限り設定を行ってください。

	<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />	<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />上記パーミッションが設定されていることにより、自動で以下のデフォルトパスに識別IDファイルが保存されます。
	Environment.getExternalStorageDirectory().getPath()/アプリのパッケージ名/__FOX_XUNIQ__
<デフォルト保存されるパスの例>
　(※端末やOSバージョンによって異なります。)

	/mnt/shell/emulated/0/アプリのパッケージ名/__FOX_XUNIQ__

保存されるファイルのディレクトリ名は標準でパッケージ名で作成されますが、任意のディレクトリ名及びファイル名に変更することができます。また、本機能によりファイルが生成されることを抑制することが可能です。識別子ファイルの保存先をコントロールしたい場合には、<application>タグ内に以下設定を追加することができます。通常は設定の必要はありません。<br>
任意のディレクトリ名やファイル名を指定した場合でも、Environment.getExternalStorageDirectory().getPath()の返り値のパス配下に作成します。

	<meta-data android:name="APPADFORCE_ID_DIR" android:value="任意のディレクトリ名" />
	<meta-data android:name="APPADFORCE_ID_FILE" android:value="任意のファイル名" />

<設定例>

	<meta-data android:name="APPADFORCE_ID_DIR" android:value="fox_id_dir" />
	<meta-data android:name="APPADFORCE_ID_FILE" android:value="fox_id_file" />
	
<デフォルト保存されるパスの例>

　(※端末やOSバージョンによって異なります。)

	/mnt/shell/emulated/0/アプリのパッケージ名/__FOX_XUNIQ__

> ※ Environment.getExternalStorageDirectory().getPath()の返り値は端末やOSバージョンによって異なります。<br>
> ※ ”APPADFORCE_ID_DIR”(任意のディレクトリ名)を指定せず、任意のファイル名のみを指定した場合、アプリのパッケージ名のディレクトリが作成され、その配下に任意のファイル名で保存されます。<br>
> ※ ”APPADFORCE_ID_FILE”(任意のファイル名)を指定せず、任意のディレクトリ名のみを指定した場合、任意の名前でディレクトリが作成され、その配下に”__XUNIQ__”で保存されます。

####AndroidManifest.xmlの設定例

	<?xml version="1.0" encoding="utf-8"?>	<manifest xmlns:android="http://schemas.android.com/apk/res/android"    	package="com.example.aaa"		android:versionCode="1"		android:versionName="1.0" >	    <uses-sdk    	    android:minSdkVersion="8"        	android:targetSdkVersion="16" />	    <application    	    android:allowBackup="true"        	android:icon="@drawable/ic_launcher"	        android:label="@string/app_name"    	    android:theme="@style/AppTheme" >        	<activity            	android:name="com.example.aaa.MainActivity"            	android:label="@string/app_name" >            	<intent-filter>                	<action android:name="android.intent.action.MAIN" />                	<category android:name="android.intent.category.LAUNCHER" />            	</intent-filter>            	<!-- ① URLスキームの設定 （sampleapp://）  -->	            <intent-filter>    	            <action android:name="android.intent.action.VIEW" />        	        <category android:name="android.intent.category.DEFAULT" />            	    <category android:name="android.intent.category.BROWSABLE" />                	<data android:scheme="sampleapp" />	            </intent-filter>    	    </activity>                 	<!-- ② インストールリファラー計測のreceiver設定 -->	         <receiver android:exported="true"　android:name="jp.appAdForce.android.InstallReceiver" >    	        <intent-filter>        	        <action android:name="com.android.vending.INSTALL_REFERRER" />            	</intent-filter>	        </receiver>    	     <!-- ③ 必須meta-dataの設定 -->        	<meta-data android:name="APPADFORCE_APP_ID" android:value="123" />	        <meta-data android:name="APPADFORCE_SERVER_URL" android:value="0123456" />    	    <meta-data android:name="APPADFORCE_CRYPTO_SALT" android:value="abcdefg" />        	<meta-data android:name="ANALYTICS_APP_KEY" android:value="xxxxxx" />	        <!-- ④ストレージ保存機能を使わない場合の例 -->    	    <meta-data android:name="APPADFORCE_USE_EXTERNAL_STORAGE" android:value="0" />
    	    <!-- ⑤GooglePlayServicesを用いてAdvertisingIDを取得する場合 -->
	        <meta-data android:name="com.google.android.gms.version"
				android:value="@integer/google_play_services_version" />    	</application>        	<uses-permission android:name="android.permission.INTERNET" />    	<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />	</manifest>①	URLスキームの設定 → Webブラウザでsampleapp:// にアクセスでMainActivityが起動するよう設定<br>②	インストールリファラー計測のreceiver設定<br>
③	必須meta-dataの設定<br>
④	内(外)部ストレージ保存機能を使用しない設定：ON
⑤	プロジェクトにGooglePlayServicesライブラリを導入している場合に必ず設定
