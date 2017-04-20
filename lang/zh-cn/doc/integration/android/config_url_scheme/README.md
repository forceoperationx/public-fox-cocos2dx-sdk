[TOP](../../../../README.md)　>　[Cocos2d-x plugin导入步骤](../../README.md)　>　[Android项目设置](../README.md)　>　URL scheme设置

---

# URL scheme设置

从外部启动APP时必须设置。在启动对象的<activity>标签中添加。
#### 例如用”smapleapp://”启动APP

```xml
<intent-filter>		<action android:name="android.intent.action.VIEW" />		<category android:name="android.intent.category.DEFAULT" />		<category android:name="android.intent.category.BROWSABLE" />		<data android:scheme="sampleapp" /></intent-filter>
```

#### 使用例

```xml
<activity
		android:name="com.example.aaa.MainActivity"
		android:label="@string/app_name" >
        <intent-filter>
        	<action android:name="android.intent.action.MAIN" />
        	<category android:name="android.intent.category.LAUNCHER" />
        </intent-filter>

        <!-- URLスscheme设置 （sampleapp://）  -->
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

[TOP](../../../../README.md)
