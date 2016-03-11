# Cocos2d-xプラグインの導入手順

* [iOS](./README.md#ios)
* [Android](./README.md#android)

## iOS

### SDKの展開

ダウンロードしたSDK「FOX_Cocos2dx_SDK_<version>.zip」をOS上に展開します。Classesフォルダ内に同梱されているファイルは以下の通りです。

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

> ※1 iOS9より初回起動時のブラウザ起動からアプリに戻る際に、ダイアログが出力されます。 F.O.X SDKではiOS9からリリースされた新しいWebView形式である “SFSafariViewController”を初回起動時に起動させ計測を行います。`FoxReengagePlugin`は内部でSFSafariViewControllerの制御を行うために必要となりますので、アプリがiOS9をサポートしている場合は必須となります。

以下のファイル群が、iOSのネイティブSDKとなっており「FOX_iOS_SDK_<version>」フォルダに同梱されています。

ファイル名|必須|概要
:--------|:-------------:|:--------:
AdManager.h|必須|ヘッダファイル。広告の効果測定を行う。|
libAppAdForce.a|必須|ライブラリファイル。広告の効果測定を行う。|
Ltv.h|オプション|ヘッダファイル。LTV計測を行う。|
AnalyticsManager.h|オプション|ヘッダファイル。アクセス解析を行う。|
Notify.h|オプション|ヘッダファイル。Push通知を行う。

※「FOX_Cocos2dx\_SDK_&lt;version&gt;.zip」に「FOX_iOS\_SDK_&lt;version&gt;」フォルダが含まれていない場合は

SDKダウンロードサイトからFOX_iOS\_SDK_&lt;version&gt;.zipをダウンロードの上、ご使用ください。


### ライブラリの組み込み

* Xcodeのメニュー「File」→「Add Files to “XXX”」を選択
* Cocos2dxFox.h、Cocos2dxFox.mmを組み込んでください。Cocos2dxFox.cppはAndroid用ライブラリであるため、追加の必要はありません。
* プッシュ通知機能を使う場合は、FoxNotifyPlugin.h、FoxNotifyPlugin.mの2ファイルを組み込んでください。
* バンドルバージョン判定機能を使う場合は、FoxVersionDelegate.h、FoxVersionDelegate .mmとFoxVersionPlugin.h、FoxVersionPlugin.mmの計4ファイルを組み込んでください。
* iOS9をサポートする場合、またはリエンゲージメント計測を行う場合はFoxReengagePlugin.hとFoxReengagePlugin.mの2ファイルを組み込んでください。
* 「Copy items into destination group’s folder」にチェック

![インストール01](./ios/img01.png)

![インストール02](./ios/img02.png)

![インストール03](./ios/img03.png)

### プロジェクトの設定

[iOS SDKの詳細設定](./ios/README.md)

## Android

### SDKの展開

ダウンロードしたSDK「FOX_Cocos2dx_SDK_<version>.zip」をOS上に展開します。<br>
「FOX_Android_SDK_<version>」フォルダに同梱されている「AppAdForce.jar」を開発環境に導入します。次に、Eclipseプロジェクトへの導入手順について説明します。

|ファイル名|必須|概要|
|:------:|:------:|:------|
|AppAdForce.jar|必須|AndroidのネイティブSDK。通常成果・LTV成果・アクセス解析を計測することができます。|
|gcm.jar|オプション|プッシュ通知機能を利用する際に導入ください。|

※「FOX_Cocos2dx_SDK_<version>.zip」に「FOX_Android_SDK_<version>」フォルダが含まれていない場合はSDKダウンロードサイトからFOX_Android_SDK_<version>.zipをダウンロードの上、ご使用ください。

### Cocos2d-xプロジェクトのClassesへの導入

「FOX_Cocos2dx\_SDK_&lt;version&gt;.zip」を展開し、以下の操作を行います。

* Android/Classes配下のCocos2dxFox.hとCocos2dxFox.cppをプロジェクト配下のClassesへコピー
* プロジェクト内配下のjni/Android.mkにCocos2dxFox.cppファイルを追記し、ビルドの対象に含める<br>
　→ LOCAL_SRC_FILESにClasses/Cocos2dxFox.cppの指定を追加してください。
　
Cocos2dxFox.cppのJniHelper.hのincludeパスを開発環境に合わせる（以下はその例）

```cpp
#include <iostrem>
#inclued “cocos2d.h”
#include “Cocos2dxFox.h”
#include “../android/jni/JniHelper.h”
```

###	プロジェクトへの導入

既にアプリケーションにSDKが導入されている場合には、[最新バージョンへのアップデートについて](/lang/ja/doc/update/README.md)をご参照ください。

ダウンロードしたSDK「FOX_Android_SDK_<version>.zip」を展開し、「AppAdForce.jar」をアプリケーションのプロジェクトに組み込んでください。

* [Eclipseプロジェクトへの導入の方法](./android/ide/eclipse/README.md)
* [AndroidStudioプロジェクトへの導入の方法](./android/ide/android_studio/README.md)

### プロジェクトの設定

[Android SDKの詳細設定](./android/README.md)

---
[戻る](/lang/ja/doc/integration/README.md)

[TOP](/lang/ja/README.md)
