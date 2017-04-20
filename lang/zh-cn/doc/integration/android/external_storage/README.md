[TOP](../../../../README.md)　>　[Cocos2d-x plugin导入步骤](../../README.md)　>　[Android项目设置](../README.md)　>　利用外部储存进行排除重复

---

## 利用外部储存进行排除重复

APP首次启动时，SDK生成的识别ID保存在本地储存或SD卡中，可以在APP再次安装时进行重复判定。

本设置为任意项目，但为了提高APP再次安装时重复检查的精度，建议使用。

### 权限设置

在AndroidManifest.xml的<manifest>的标签中添加读写外部储存必要的权限设置。

```xml
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" /><uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
```

如果设置了上述权限，ID识别文件会保存在以下路径。

```
Environment.getExternalStorageDirectory().getPath()可获取路径/APP的package名/__FOX_XUNIQ__
```

### （任意）保存目录及修改文件名

保存文件的目录名，一般为package名，在<application>标签下添加以下设置可以修改目录名以及文件名。

```xml
<meta-data android:name="APPADFORCE_ID_DIR" android:value="任意目录名" />
<meta-data android:name="APPADFORCE_ID_FILE" android:value="任意文件名" />
```

> 指定的目录名和文件名，会在
Environment.getExternalStorageDirectory().getPath()的返回值路径下创建出来。Environment.getExternalStorageDirectory().getPath()的返回值根据终端和OS版本的不同而有所差异。
> "APPADFORCE_ID_DIR"(任意目录名)，仅指定文件名时，会按APP的包(package)名来生成目录，并在该目录下保存文件。
> ※"APPADFORCE_ID_FILE"(任意文件名)，仅指定目录的情况时，会生成指定的目录名，并在该目录下保存为`__FOX_XUNIQ__`。
通常不需要设置。


### 设置案例

以下为AndroidManifest.xml的设置案例。

```xml
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" /><uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />

<application
	android:icon="@drawable/ic_launcher"
	android:label="@string/app_name" >

	<meta-data android:name="APPADFORCE_ID_DIR" android:value="fox_id_dir" />
	<meta-data android:name="APPADFORCE_ID_FILE" android:value="fox_id_file" />

</application>
```

在上述案例中，文件保存在以下路径。

```
用Environment.getExternalStorageDirectory().getPath()获取的路径/fox_id_dir/fox_id_file
```

### 停止使用外部储存

想要通过Force Operation X SDK停止访问外部储存时，请在AndroidManifest.xml中添加APPADFORCE_USE_EXTERNAL_STORAGE设置。
```xml
<meta-data android:name="APPADFORCE_USE_EXTERNAL_STORAGE" android:value="0" />
```

本项设置可以停止对外部储存的读写，但删除APP时会清空数据，可能导致无法进行准确测量。

### 关于Android M(6.0)的注意点

使用protectionLevel为dangerous等级的功能时，必须得到用户许可。 用户拒绝时，数据将无法保存在外部储存区域因此无法设置排除重复。上述中`READ_EXTERNAL_STORAGE`和`WRITE_EXTERNAL_STORAGE`也为dangerous，需获得用户许可。


* [编码安装参考](https://developer.android.com/training/permissions/requesting.html#perm-request)


---
[Android TOP](../README.md)

[TOP](../../../../README.md)
