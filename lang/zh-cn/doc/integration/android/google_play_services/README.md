[TOP](../../../../README.md)　>　[Cocos2d-x plugin的导入步骤](../../README.md)　>　[Android项目设置](../README.md)　>　Google Play Services SDK导入

---

# 导入Google Play Services SDK来使用广告ID


## Google Play development program准则

Force Operation X Android SDK以Google Play development program 条约为准则。该SDK为了遵守条约，已经获取永久设备ID（IMEI、MAC adress以及AndroidID）的情况下将不会获取广告ID。2014年8月1日开始，Google Play Store上所有的更新以及发布新app时，以广告为目的的终端ID必须使用广告ID。为了遵守该条约，请执行以下步骤。


## Google Play Services SDK


为了能够使用广告ID，必须安装Google Play Services SDK。
APP中没有安装Google Play Services SDK的情况时，请按照以下页面的步骤做导入安装。

[Setting Up Google Play Services | Android Developers](https://developer.android.com/google/play-services/setup.html)


## 获取Google Play Services SDK

以下为2014年12月时的Google Play Services SDK导入方法。


未安装Google Play Services SDK的情况下，请从Android SDK Manager获取安装包。

* 启动Android SDK Manager。
* 勾选在Extras目录下的Google Play services，导入文件包。

![googlePlayServices01](./img01.png)

## 导入Google Play Services

获取Google Play Services的类库项目，请在项目属性选项中指定参照外部类库项目 ${ANDROID_SDK_PATH}/extras/google/google_play_services/libproject/google-play-services_lib。


## Google Play Services使用设置

#### 编辑AndroidManifest.xml

使用Google Play Services前需要将下列设置写入AndroidManifest.xml的<application>标签中。

```xml
<meta-data android:name="com.google.android.gms.version"
        android:value="@integer/google_play_services_version" />
```

#### Proguard设置

使用Proguard进行代码混淆时，请添加以下设置。

```
-keep class * extends java.util.ListResourceBundle {
    protected Object[][] getContents();
}

-keep public class com.google.android.gms.common.internal.safeparcel.SafeParcelable {
    public static final *** NULL;
}

-keepnames @com.google.android.gms.common.annotation.KeepName class *
-keepclassmembernames class * {
    @com.google.android.gms.common.annotation.KeepName *;
}

-keepnames class * implements android.os.Parcelable {
    public static final ** CREATOR;
}
```

---
[Android TOP](../README.md)

[TOP](../../../../README.md)
