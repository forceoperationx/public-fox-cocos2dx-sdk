# URLスキームの設定

アプリを外部から起動する際に必須となります。起動させる対象となる<activity>タグ内に追加します。
#### 例 ”smapleapp://”でアプリを起動させる

	<intent-filter>		<action android:name="android.intent.action.VIEW" />		<category android:name="android.intent.category.DEFAULT" />		<category android:name="android.intent.category.BROWSABLE" />		<data android:scheme="sampleapp" />	</intent-filter>

#### 使用例

	<activity
    	android:name="com.example.aaa.MainActivity"
        android:label="@string/app_name" >
        <intent-filter>
        	<action android:name="android.intent.action.MAIN" />
        	<category android:name="android.intent.category.LAUNCHER" />
        </intent-filter>

        <!-- URLスキームの設定 （sampleapp://）  -->
        <intent-filter>
        	<action android:name="android.intent.action.VIEW" />
            <category android:name="android.intent.category.DEFAULT" />
            <category android:name="android.intent.category.BROWSABLE" />
            <data android:scheme="sampleapp" />
        </intent-filter>
	</activity>