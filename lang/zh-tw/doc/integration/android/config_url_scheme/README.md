# URL Scheme的設定

從外部啟動APP時必須設定。添加到啟動對象的&lt;activity&gt;標簽內。

#### 例如 用”smapleapp://”來啟動APP

```xml
<intent-filter>
		<action android:name="android.intent.action.VIEW" />
		<category android:name="android.intent.category.DEFAULT" />
		<category android:name="android.intent.category.BROWSABLE" />
		<data android:scheme="sampleapp" />
</intent-filter>
```

#### 使用範例

```xml
<activity
		android:name="com.example.aaa.MainActivity"
		android:label="@string/app_name" >
        <intent-filter>
        	<action android:name="android.intent.action.MAIN" />
        	<category android:name="android.intent.category.LAUNCHER" />
        </intent-filter>

        <!-- URL Scheme （sampleapp://）  -->
        <intent-filter>
        	<action android:name="android.intent.action.VIEW" />
            <category android:name="android.intent.category.DEFAULT" />
            <category android:name="android.intent.category.BROWSABLE" />
            <data android:scheme="sampleapp" />
        </intent-filter>
</activity>
```

---
[Android TOP](../README.md)
