## 利用外部存儲設定重複排除（任意）

將APP初次啟動時，SDK生成的識別ID會保存在本地存儲和外部存儲（SD卡）裡，在APP再安裝時能做重複判定。
雖然本設定並非必須，但為了提高再安裝APP時的重複監測精度，推薦安裝。

### permission的設定

在<manifest>tag裡追加對外部存儲的文件讀寫所需要的Permission設定。

```xml
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
```

如果設定了上述Permission，識別ID文件將被保存在下面的路徑。

```
用Environment.getExternalStorageDirectory().getPath()取得的路徑/APP的Package名/__FOX_XUNIQ__
```

### （任意）變更保存目錄和文件名

默認使用Package名作為用於保存文件的目錄名，也可以改變為任意的目錄名和文件名。當然也可以選擇不保存文件。
如果需要控制識別ID保存的路徑，需要在&lt;application&gt;tag裏添加如下的設定。


```xml
<meta-data android:name="APPADFORCE_ID_DIR" android:value="任意的目錄名" />
<meta-data android:name="APPADFORCE_ID_FILE" android:value="任意的文件名" />
```

> 指定的任意的目錄名和文件名，會在Environment.getExternalStorageDirectory().getPath()返回路徑值的下面生成。在不同的設備或系統版本中Envrionment.getExternalStorageDirectory().getPath()的返回值不總是一樣的。<br>

> 沒有指定”APPADFORCE_ID_DIR”（任意的目錄名），只指定了文件名的話，會自動創建APP的Package名的目錄，在目錄下按指定名文件保存。<br>

> 沒有指定”APPADFORCE_ID_FILE”（任意的文件名），只指定了目錄名的話，在指定的目錄下會創建以”__FOX_XUNIQ__”為名的文件。通常不需要設定。


### 設定範例

下面記述了AndroidManifest.xml設定範例。

```xml
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />

<application
	android:icon="@drawable/ic_launcher"
	android:label="@string/app_name" >

	<meta-data android:name="APPADFORCE_ID_DIR" android:value="fox_id_dir" />
	<meta-data android:name="APPADFORCE_ID_FILE" android:value="fox_id_file" />

</application>

```

在上面的例子裡，保存文件的路徑如下：

```
用Environment.getExternalStorageDirectory().getPath()能夠取得的路徑是/fox_id_dir/fox_id_file
```

### 停止使用外部存儲

如果希望Force Operation X SDK停止訪問外部存儲，請在AndroidManifest.xml裡追加APPADFORCE_USE_EXTERNAL_STORAGE的設定。

```xml
<meta-data android:name="APPADFORCE_USE_EXTERNAL_STORAGE" android:value="0" />
```

通過這個設定可以停止紀錄到外部存儲，但因為刪除APP會初始化數據，將無法進行正確的Install計測。

### Android M(6.0)的注意事項

為了利用ProtectionLevel設定為`dangerous`權限的機能，需要獲得用戶許可。如果用戶不許可，數據無法保存到存儲領域，進而無法利用重複排除設定。
前面說到的READ_EXTERNAL_STORAGE和WRITE_EXTERNAL_STORAGE的級別也屬於dangerous，需要做實際安裝來獲得用戶許可。

* [安裝參考](https://developer.android.com/training/permissions/requesting.html#perm-request)

---
[Android TOP](../README.md)
