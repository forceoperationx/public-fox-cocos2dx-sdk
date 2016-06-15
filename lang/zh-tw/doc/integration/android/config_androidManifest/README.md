## AndroidManifest.xml meta-data 選項詳細

|參數名|必須|概要|
|:------|:------|:------|
|APPADFORCE_APP_ID|必須|請輸入Force Operation X管理員告知的值。|
|APPADFORCE_SERVER_URL|必須|請輸入Force Operation X管理員告知的值。|
|APPADFORCE_CRYPTO_SALT|必須|請輸入Force Operation X管理員告知的值。|
|ANALYTICS_APP_KEY|必須|請輸入Force Operation X管理員告知的值。|
|APPADFORCE_ID_DIR|任意|使用內(外)部存儲時，能夠指定任意的保存目錄名。<br>沒有指定的時候，會用PACKAGE名生成目錄。|
|APPADFORCE_ID_FILE|任意|使用內(外)部存儲時，能夠指定任意的保存識別子文件名。<br>沒有指定的時候，會用”__FOX_XUNIQ__”生成文件。|
|APPADFORCE_USE_EXTERNAL_STORAGE|任意|設定為0的時候，不會保存在內(外)部存儲裡。|

#### 利用內部和外部存儲實現重複排除
將APP初次啟動時，SDK生成的識別ID會保存在本地存儲和外部存儲（SD card）裡，在APP再安裝時能做重複判定。在<manifest>tag裡追加對外部存儲的文件讀寫所需要的Permission設定。雖然本設定並非必須，但為了提高再安裝APP時的重複監測精度，推薦設定。

	<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
	<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />

根據上面設定的PERMISSION，識別ID文件會自動保存在下面默認路徑裡

	Environment.getExternalStorageDirectory().getPath()/APP的PACKAGE名/__FOX_XUNIQ__

	<默認保存路徑的範例>

	　(※根據終端或OS版本會有差異。)
	/mnt/shell/emulated/0/APP的PACKAGE名/__FOX_XUNIQ__

默認使用Package名作為用於保存文件的目錄名，也可以改變為任意的目錄名和文件名。當然也可以選擇不保存文件。
如果需要控制識別ID保存的路徑，需要在&lt;application&gt;tag裏添加如下的設定。通常是不需要設定的。<br>
指定的任意目錄名或文件名，會生成在Environment.getExternalStorageDirectory().getPath()的返回值的路徑下面。


	<meta-data android:name="APPADFORCE_ID_DIR" android:value="任意的目錄名" />
	<meta-data android:name="APPADFORCE_ID_FILE" android:value="任意的文件名" />

<設定範例>

	<meta-data android:name="APPADFORCE_ID_DIR" android:value="fox_id_dir" />
	<meta-data android:name="APPADFORCE_ID_FILE" android:value="fox_id_file" />

<默認保存路徑的範例>

　(※根據終端或OS版本會有差異。)

	/mnt/shell/emulated/0/APP的PACKAGE名/__FOX_XUNIQ__

> 指定的任意的目錄名和文件名，會在Environment.getExternalStorageDirectory().getPath()返回路徑值的下面生成。在不同的設備或系統版本中Envrionment.getExternalStorageDirectory().getPath()的返回值不總是一樣的。<br>

> 沒有指定”APPADFORCE_ID_DIR”（任意的目錄名），只指定了文件名的話，會自動創建APP的Package名的目錄，在目錄下按指定名文件保存。<br>

> 沒有指定”APPADFORCE_ID_FILE”（任意的文件名），只指定了目錄名的話，在指定的目錄下會創建以”__XUNIQ__”為名的文件。通常不需要設定。

####AndroidManifest.xml設定實例

	<?xml version="1.0" encoding="utf-8"?>
	<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    	package="com.example.aaa"
		android:versionCode="1"
		android:versionName="1.0" >

	    <uses-sdk
    	    android:minSdkVersion="8"
        	android:targetSdkVersion="16" />

	    <application
    	    android:allowBackup="true"
        	android:icon="@drawable/ic_launcher"
	        android:label="@string/app_name"
    	    android:theme="@style/AppTheme" >
        	<activity
            	android:name="com.example.aaa.MainActivity"
            	android:label="@string/app_name" >
            	<intent-filter>
                	<action android:name="android.intent.action.MAIN" />
                	<category android:name="android.intent.category.LAUNCHER" />
            	</intent-filter>

            	<!-- ① URL Scheme的設定 (sampleapp://)   -->
	            <intent-filter>
    	            <action android:name="android.intent.action.VIEW" />
        	        <category android:name="android.intent.category.DEFAULT" />
            	    <category android:name="android.intent.category.BROWSABLE" />
                	<data android:scheme="sampleapp" />
	            </intent-filter>
    	    </activity>

         	<!-- ② Install Referrer計測的receiver設定  -->
	         <receiver android:exported="true"　android:name="jp.appAdForce.android.InstallReceiver" >
    	        <intent-filter>
        	        <action android:name="com.android.vending.INSTALL_REFERRER" />
            	</intent-filter>
	        </receiver>

    	     <!-- ③ 必須: meta-data 的設定 -->
        	<meta-data android:name="APPADFORCE_APP_ID" android:value="123" />
	        <meta-data android:name="APPADFORCE_SERVER_URL" android:value="0123456" />
    	    <meta-data android:name="APPADFORCE_CRYPTO_SALT" android:value="abcdefg" />
        	<meta-data android:name="ANALYTICS_APP_KEY" android:value="xxxxxx" />

	        <!-- ④不使用内(外)部存儲保存功能的設定的範例 -->
    	    <meta-data android:name="APPADFORCE_USE_EXTERNAL_STORAGE" android:value="0" />

    	    <!-- ⑤利用GooglePlayServices取得AdvertisingID -->
	        <meta-data android:name="com.google.android.gms.version"
				android:value="@integer/google_play_services_version" />
    	</application>

    	<uses-permission android:name="android.permission.INTERNET" />
    	<uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
	</manifest>

①	URL Scheme的設定 → 用Web瀏覽器訪問sampleapp://，設定成讓MainActivity啟動<br>
②	Install Referrer計測的receiver設定<br>
③	必須meta-data的設定<br>
④	不使用内(外)部存儲保存功能的設定：ON
⑤	在項目裡導入GooglePlayServices類庫時需設定

---
[Android TOP](../README.md)
