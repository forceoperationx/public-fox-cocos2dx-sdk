# Cocos2d-x插件的導入步驟

* [iOS](./README.md#ios)
* [Android](./README.md#android)

## iOS

### SDK的展開

將下載的SDK「FOX_Cocos2dx_SDK_&lt;version&gt;.zip」在OS上展開。被一起打包在Classes文件夾裡的文件如下。

文件名|必須|概要
:--------|:-------------:|:--------:
Cocos2dxFox.h|必須|頭文件。為從Cocos2d-x使用SDK做的封裝
Cocos2dxFox.mm|	iOS専用	|類庫文件。在iOS環境為從Cocos2d-x使用F.O.X SDK做的封裝
Cocos2dxFox.cpp|Android専用|類庫文件。在Android環境為從Cocos2d-x使用F.O.X SDK做的封裝
FoxVersionPlugin.h|任意|類庫文件。為從Cocos2d-x控制BundleVersion做的封裝
FoxVersionDelegate.m|任意|類庫文件。為從Cocos2d-x控制BundleVersion做的封裝|
FoxVersionPlugin.h|任意|類庫文件。為從Cocos2d-x控制BundleVersion做的封裝|
FoxVersionPlugin.m|任意|類庫文件。為從Cocos2d-x控制BundleVersion做的封裝|
FoxReengagePlugin.h|必須|頭文件。為從Cocos2d-x進行經由URL Scheme的啟動計測做的封裝(※1)|
FoxReengagePlugin.m|必須|類庫文件。為從Cocos2d-x進行經由URL Scheme的啟動計測做的封裝(※1)|

上面的文件是封裝文件，須和Native SDK結合起來進行安裝。

> ※從iOS9開始，從初回啟動時的瀏覽器啟動到返回APP的時候，會彈出對話框。F.O.X SDK從iOS9開始發布了新的WebView形式，在初回啟動時啟動這個新形式的“SFSafariViewController”來進行計測。在內部控制SFSafariViewController需要`FoxReengagePlugin`，所以若是支持iOS9的APP請務必導入。

以下文件群是iOS的Native SDK，被一同包裝在「FOX_iOS_SDK_&lt;version&gt;」文件夾裡。

文件名|必須|概要
:--------|:-------------:|:--------:
AdManager.h|必須|頭文件。進行廣告的效果測定。|
libAppAdForce.a|必須|類庫文件。進行廣告的效果測定。|
Ltv.h|任意|頭文件。進行LTV計測。|
AnalyticsManager.h|任意|頭文件。進行流量分析。|

※如果「FOX_iOS\_SDK_&lt;version&gt;」文件夾沒有包含在「FOX_Cocos2dx\_SDK_&lt;version&gt;.zip」裡
請從SDK下載網站下載FOX_iOS_SDK_&lt;version&gt;.zip來使用。

### 類庫的導入

* Xcode的菜單「File」→選擇「Add Files to “XXX”」
* 請導入Cocos2dxFox.h、Cocos2dxFox.mm。Cocos2dxFox.cpp是Android用的類庫文件，所以不需要追加。
* 如果使用BundleVersion判定功能，請導入FoxVersionDelegate.h、FoxVersionDelegate .mm和FoxVersionPlugin.h、FoxVersionPlugin.mm這4個文件。
* 請導入FoxReengagePlugin.hとFoxReengagePlugin.m兩個文件。
* 選中「Copy items into destination group’s folder」



![安裝01](./ios/img01.png)

![安裝02](./ios/img02.png)

![安裝03](./ios/img03.png)

### 項目設定

[iOS SDK的詳細設定](./ios/README.md)

## Android

### SDK展開

將下載的SDK「FOX_Cocos2dx_SDK_&lt;version&gt;.zip」在OS上展開。<br>並將同樣包在「FOX_Android_SDK_&lt;version&gt;」文件夾裡的「AppAdForce.jar」導入到開發環境。接下來說明針對Eclipse project的導入步驟。

|文件名|必須|概要|
|:------:|:------:|:------|
|AppAdForce.jar|必須|Android的Native SDK。能夠計測通常成果・LTV成果・流量分析。|

※如果「FOX_Cocos2dx_SDK_&lt;version&gt;.zip」裡不包含「FOX_Android_SDK_&lt;version&gt;」文件夾，請從SDK下載頁面下載FOX_Android_SDK_&lt;version&gt;.zip後使用。

### 導入到Cocos2d-x project的Classes

展開「FOX_Cocos2dx\_SDK_&lt;version&gt;.zip」，進行以下操作。

* 將Android/Classes之下的Cocos2dxFox.h和Cocos2dxFox.cpp複製到project之下的Classes裡
* 將Cocos2dxFox.cpp文件添加到project project內之下的jni/Android.mk，包含build的對象<br>
→請把Classes/Cocos2dxFox.cpp的指定添加到LOCAL_SRC_FILES裡。

將Cocos2dxFox.cpp的JniHelper.h的include路徑對應到開發環境（以下為範例）

```cpp
#include <iostrem>
#inclued “cocos2d.h”
#include “Cocos2dxFox.h”
#include “../android/jni/JniHelper.h”
```

###	導入到項目

展開下載的SDK「FOX_Android_SDK_&lt;version&gt;.zip」，請把「AppAdForce.jar」導入到APP的項目裡。

* [Eclipse項目的導入方法](./android/ide/eclipse/README.md)
* [AndroidStudio項目的導入方法](./android/ide/android_studio/README.md)

### 項目設定

[Android SDK的詳細設定](./android/README.md)

---
[TOP](/lang/zh-tw/README.md)
