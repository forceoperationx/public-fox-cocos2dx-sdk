## 외부 스토리지를 이용한 중복 제거 설정

앱을 처음 시작할 때 SDK가 생성한 식별 ID를 로컬 저장소 또는 SD 카드에 저장함으로써 앱 재설치시에 중복 판정을 할 수 있습니다.

이 설정은 필수는 아니지만 앱을 재설치의 중복 감지의 정확도가 크게 향상하기 위해 구현을 권장하고 있습니다.

### 권한 설정

외부 스토리지에 파일 읽기 및 쓰기에 필요한 권한 설정을 AndroidManifest.xml의<manifest> 태그내에 추가합니다.

```xml
<uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
<uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
```

위 권한이 설정되어있는 경우 다음의 경로에 식별ID 파일이 저장됩니다.

```java
Environment.getExternalStorageDirectory().getPath()에 얻을 수있는 경로/앱의 패키지명/__FOX_XUNIQ__
```

### (임의) 저장 디렉토리 및 파일명 변경

저장되는 파일의 디렉토리 이름은 표준에서는 패키지명으로 작성됩니다만 <application> 태그에 다음 설정을 추가하여 임의의 디렉토리 이름 및 파일 이름 변경 될 수 있습니다.

```xml
<meta-data android:name="APPADFORCE_ID_DIR" android:value="임의의 디렉토리명"/>
<meta-data android:name="APPADFORCE_ID_FILE" android:value="임의의 파일명"/>
```

> 임의의 디렉토리명이나 파일명을 지정한 경우에도 Environment.getExternalStorageDirectory ().getPath()의 반환 값의 경로 아래에 작성합니다. Environment.getExternalStorageDirectory().getPath()의 반환 값은 단말기와 OS 버전에 따라 다릅니다.
> "APPADFORCE_ID_DIR"(임의의 디렉토리명)을 지정하지 않고 임의의 파일명만 지정하면 앱의 패키지명의 디렉토리가 생성되고 그 아래에 임의의 파일명으로 저장됩니다.
> ※"APPADFORCE_ID_FILE"(임의의 파일명)을 지정하지 않고 임의의 디렉토리명만을 지정했을 경우, 임의의 이름으로 디렉토리가 생성되고 그 아래에 "__FOX_XUNIQ__"에 저장됩니다.
일반적으로 설정할 필요는 없습니다.


### 설정 예

AndroidManifest.xml의 설정예를 기재합니다.

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

위의 예제의 경우 저장되는 파일의 경로는 다음과 같습니다.

```java
Environment.getExternalStorageDirectory().getPath()에서 얻을 수있는 경로/fox_id_dir/fox_id_file
```

### 외부 스토리지 이용 정지

Force Operation X SDK를 사용하여 외부 저장 장치에 대한 액세스를 중지하려는 경우에는 AndroidManifest.xml에 APPADFORCE_USE_EXTERNAL_STORAG​​E 설정을 추가하십시오.

```xml
<meta-data android:name="APPADFORCE_USE_EXTERNAL_STORAGE" android:value="0" />
```

본 설정을함으로써 외부 스토리지에 대한 기록이 중지되지만 앱을 제거하면 데이터가 항상 초기화되기 때문에 정확한 설치 측정을 하지 않게됩니다.