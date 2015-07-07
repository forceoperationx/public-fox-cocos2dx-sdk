# URL스키마의 설정

앱을 외부에서부터 기동할 때 필수입니다. 기동하는 대상이되는<activity>태그안에 추가합니다.
#### 예 ”smapleapp://”에서 앱을 기동시킴

```xml:
	<intent-filter>
		<action android:name="android.intent.action.VIEW" />
		<category android:name="android.intent.category.DEFAULT" />
		<category android:name="android.intent.category.BROWSABLE" />
		<data android:scheme="sampleapp" />
	</intent-filter>
```

#### 사용예

```xml:
	<activity
    	android:name="com.example.aaa.MainActivity"
        android:label="@string/app_name" >
        <intent-filter>
        	<action android:name="android.intent.action.MAIN" />
        	<category android:name="android.intent.category.LAUNCHER" />
        </intent-filter>

        <!-- URL스키마의 설정 （sampleapp://）  -->
        <intent-filter>
        	<action android:name="android.intent.action.VIEW" />
            <category android:name="android.intent.category.DEFAULT" />
            <category android:name="android.intent.category.BROWSABLE" />
            <data android:scheme="sampleapp" />
        </intent-filter>
	</activity>
```