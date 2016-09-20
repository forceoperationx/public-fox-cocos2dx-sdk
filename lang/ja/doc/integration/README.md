# Cocos2d-xプラグインの導入手順

* [1. iOS](./README.md#ios)
* [2. Android](./README.md#android)

<div id="ios"></div>
## 1. iOS

### 1.1 SDKの展開

ダウンロードしたSDK「FOX_COCOS2DX_SDK_&lt;version&gt;.zip」をOS上に展開します。Classesフォルダ内に同梱されているファイルは以下の通りです。

ファイル名|必須|概要
:--------|:-------------:|:--------:
Cocos2dxFox.h|必須|ヘッダファイル。Cocos2d-xからSDKを使用するためのラッパー
Cocos2dxFox.mm|	iOS専用	|ライブラリファイル。Cocos2d-xからFOX SDKを使用するためのiOS用のラッパー
Cocos2dxFox.cpp|Android専用|ライブラリファイル。Cocos2d-xからFOX SDKを使用するためのAndroid用のラッパー
FoxNotifyPlugin.m|オプション|ライブラリファイル。Cocos2d-xからPush通知を行うためのラッパー
FoxVersionPlugin.h|オプション|ヘッダファイル。Cocos2d-xからバンドルバージョンを制御するラッパー
FoxVersionDelegate.m|オプション|ライブラリファイル。Cocos2d-xからバンドルバージョンを制御するラッパー|
FoxVersionPlugin.h|オプション|ヘッダファイル。Cocos2d-xからバンドルバージョンを制御するラッパー|
FoxVersionPlugin.m|オプション|ライブラリファイル。Cocos2d-xからバンドルバージョンを制御するラッパー|
FoxReengagePlugin.h|必須|ヘッダファイル。Cocos2d-xからURLスキーム経由の起動計測を行うためのラッパー(※1)|
FoxReengagePlugin.m|必須|ライブラリファイル。Cocos2d-xからURLスキーム経由の起動計測を行うためのラッパー(※1)|

上記のファイルはラッパーですので、実装ファイルはネイティブSDKを組み合わせます。

以下のファイル群が、iOSのネイティブSDKとなっており「FOX_iOS_SDK_&lt;version&gt;」フォルダに同梱されています。

ファイル名|必須|概要
:--------|:-------------:|:--------:
AdManager.h|必須|ヘッダファイル。広告の効果測定を行う。|
libAppAdForce.a|必須|ライブラリファイル。広告の効果測定を行う。|
Ltv.h|オプション|ヘッダファイル。LTV計測を行う。|
AnalyticsManager.h|オプション|ヘッダファイル。アクセス解析を行う。|
Notify.h|オプション|ヘッダファイル。Push通知を行う。

※「FOX_COCOS2DX\_SDK_&lt;version&gt;.zip」に「FOX_iOS\_SDK_&lt;version&gt;」フォルダが含まれていない場合は

SDK[ダウンロードページ](https://github.com/cyber-z/public-fox-ios-sdk/releases)からFOX_iOS\_SDK_&lt;version&gt;.zipをダウンロードの上、ご使用ください。


### 1.2 ライブラリの組み込み

* Xcodeのメニュー「File」→「Add Files to “XXX”」を選択
* CYZCCFox.h, CYZCCFoxEvent.h, CYZCCFoxTypes.h, iOSディレクトリを組み込んでください。*.cppはAndroid用ライブラリであるため、追加の必要はありません。
* iOS9をサポートする場合、またはリエンゲージメント計測を行う場合はCYZCCFoxReengagePlugin.hとCYZCCFoxReengagePlugin.mの2ファイルを組み込んでください。
* 「Copy items into destination group’s folder」にチェック

![インストール01](./ios/img01.png)

![インストール02](./ios/img02.png)

![インストール03](./ios/img03.png)

### 1.3 プロジェクトの設定

[iOS SDKの詳細設定](./ios/README.md)

<div id="android"></div>
## 2. Android

### 2.1 Android Studioへの導入

F.O.X SDKモジュールをGradleを用いてインポートする場合、以下の設定をプロジェクトのbuild.gradleに追加してください。

```
repositories {
    maven {
        url "https://github.com/cyber-z/public-fox-android-sdk/raw/master/mavenRepo"
    }
}

dependencies {
    compile 'co.cyberz.fox:track-core:4.0.0'
    compile 'co.cyberz.fox.support:track-cocos2dx:1.0.0'
}
```


### 2.2 Eclipseプロジェクトへの導入

#### SDKの展開

ダウンロードしたSDK「FOX_COCOS2DX_SDK_&lt;version&gt;.zip」をOS上に展開します。<br>
「FOX_Android_SDK_&lt;version&gt;/libs」フォルダに同梱されている「`FOX_Android_SDK_<version>.jar`」を開発環境に導入します。次に、Eclipseプロジェクトへの導入手順について説明します。

|ファイル名|必須|概要|
|:------:|:------:|:------|
|FOX_Android_SDK_&lt;VERSION&gt;.jar|必須|AndroidのネイティブSDK。通常成果・LTV成果・アクセス解析を計測することができます。|
|FOX_Android_SDK_Support_Cocos2dx_&lt;VERSION&gt;.jar|必須|ネイティブSDK用のラッパーライブラリ|


### 2.3 Cocos2d-xプロジェクトのClassesへの導入

「FOX_Cocos2dx_SDK_&lt;version&gt;.zip」を展開し、以下の操作を行います。

* CYZCCFox.h, CYZCCFoxEvent.h, CYZCCFoxTypes.h, AndroidディレクトリをClassesへコピー
* プロジェクト内配下のjni/Android.mkの設定を変更し、上記のファイルをビルドの対象に含める
　
CYZCCFox.cppのJniHelper.hのincludeパスを開発環境に合わせる（以下はその例）

```cpp
#include <iostrem>
#include “cocos2d.h”
#include “Cocos2dxFox.h”
#include “../android/jni/JniHelper.h”
```

### 2.4 プロジェクトの設定

[Android SDKの詳細設定](./android/README.md)

---
[TOP](../../README.md)
