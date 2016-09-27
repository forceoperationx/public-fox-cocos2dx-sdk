# Force Operation Xとは

Force Operation X (以下F.O.X)は、スマートフォンにおける広告効果最適化のためのトータルソリューションプラットフォームです。アプリケーションのダウンロード、ウェブ上でのユーザーアクションの計測はもちろん、スマートフォンユーザーの行動特性に基づいた独自の効果計測基準の元、企業のプロモーションにおける費用対効果を最大化することができます。

本ドキュメントでは、スマートフォンアプリケーションにおける広告効果最大化のためのF.O.X SDK導入手順について説明します。

## 目次

* **[1. インストール](#install_sdk)**
	* [SDKダウンロード](https://github.com/cyber-z/public-fox-cocos2dx-sdk/releases)
	* [Cocos2d-x プラグインの導入手順](./doc/integration/README.md)
	* [iOSプロジェクトの設定](./doc/integration/ios/README.md)
	* [Androidプロジェクトの設定](./doc/integration/android/README.md)
	* [最新バージョンへのマイグレーションについて](./doc/update/README.md)
* **[2. F.O.X SDKのアクティベーション](#activate_sdk)**
* **[3. インストール計測の実装](#tracking_install)**
	* [インストール計測の詳細](./doc/track_install/README.md)
* **[4. アプリ内イベントの計測](#tracking_event)**
	* [セッション(起動)イベントの計測](#track_session)
	*	[その他アプリ内イベントの計測](#track_other_event)
	* [イベント計測の詳細](./doc/track_events/README.md)
* **[5. 最後に必ずご確認ください](#trouble_shooting)**

## F.O.X SDKとは

F.O.X SDKをアプリケーションに導入することで、以下の機能を実現します。

* **インストール計測**

広告流入別にインストール数を計測することができます。

* **LTV計測**

流入元広告別にLife Time Valueを計測します。主な成果地点としては、会員登録、チュートリアル突破、課金などがあります。各広告別に登録率、課金率や課金額などを計測することができます。

* **アクセス解析**

自然流入と広告流入のインストール比較。アプリケーションの起動数やユニークユーザー数(DAU/MAU)。継続率等を計測することができます。

<div id="install_sdk"></div>
## 1. インストール

以下のページより最新のSDKをダウンロードしてください。

[SDKリリースページ](https://github.com/cyber-z/public-fox-cocos2dx-sdk/releases)

既にアプリケーションにSDKが導入されている場合には、[最新バージョンへのマイグレーションについて](./doc/update/README.md)をご参照ください。

ダウンロードしたSDK「FOX_COCOS2DX_SDK_&lt;version&gt;.zip」を展開し、アプリケーションのプロジェクトに組み込んでください。

[Cocos2d-x プラグインの導入方法](./doc/integration/README.md)

### 各OS毎の設定

* [iOSプロジェクトの設定](./doc/integration/ios/README.md)
* [Androidプロジェクトの設定](./doc/integration/android/README.md)

### SDK仕様

F.O.X SDKをアプリケーションに導入することで、以下の機能を実現します。

|処理|必須|概要|
|:------:|:------:|:------|
|インストール計測|必須|起動時はブラウザが起動し、Cookie計測により広告効果測定を行います。<br>コンバージョン数、CVRなどを測定することができます。<br>メソッド名：sendConversion|
|LTV計測|オプション|任意の成果地点で成果通知を行い、広告別の課金数や入会数の計測を行います。<br>課金金額、退会数などを測定することができます。<br>メソッド名：sendLtv|
|アクセス解析|オプション|アプリの起動時およびバックグラウンドからの復帰時の起動計測を行います。<br>起動数、アクティブユーザー数(DAU)、継続率などを測定することができます。<br>メソッド名：sendStartSession|

> Force Operation X SDK Cocos2d-x プラグインは、ネイティブ版SDKへのブリッジを行うラッパーとして実装しています。SDK導入には、プラグインと、iOS及びAndroidのネイティブ版SDKが必要となります。_

<div id="activate_sdk"></div>
## 2. F.O.X SDKのアクティベーション

F.O.X SDKのアクティベーションを行うため、`CYZCCFoxConfig`をAppDelegateの`applicationDidFinishLaunching`内に記述します。

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

bool AppDelegate::applicationDidFinishLaunching() {
...
	CYZCCFoxConfig config;
	config.appId_android = 発行されたアプリID;
	config.salt_android = "発行されたAPP_SALT";
	config.appKey_android = "発行されたAPP_KEY";
	config.debugMode = 1;
	CYZCCFox::init(config);
...
```

> ※ `debugMode`は1にするとデバッグ用ログを出力することが可能となります。

<div id="tracking_install"></div>
## 3. インストール計測の実装

初回起動のインストール計測を実装することで、広告の効果測定を行うことができます。初回起動時に、ブラウザを起動し、広告クリック時に付与されたCookieの情報を照合することで、成果の計測を行います。

初回起動時にブラウザを起動するために、`AppDelegate:applicationDidFinishLaunching:`メソッド等、アプリケーションの起動時に必ず呼ばれる箇所に効果測定用の処理を追加します。


成果通知のコードを追加
```cpp
#include "CYZCCFox.h"

using namespace fox;
...

CYZCCFox::trackInstall();
```

* [インストール計測の詳細](./doc/track_install/README.md)


<div id="tracking_event"></div>
## 4. アプリ内イベントの計測

<div id="track_session"></div>
### セッション(起動)イベントの計測

自然流入と広告流入のインストール数比較、アプリケーションの起動数やユニークユーザー数(DAU/MAU)、継続率等を計測することができます。アクセス解析が不要の場合には、本項目の実装を省略できます。<br><br>
アプリケーションが起動、もしくはバックグラウンドから復帰する際にセッション計測を行うコードを追加します。不要の場合には、本項目の実装を省略できます。<br>

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

CYZCCFox::trackSession();
```

<div id="track_other_event"></div>
### その他アプリ内イベントの計測

会員登録、チュートリアル突破、課金など任意の成果地点にイベント計測を実装することで、流入元広告のLTVを測定することができます。<br>
イベント計測が不要の場合には、本項目の実装を省略できます。<br>
成果がアプリ内部で発生する場合、成果処理部に以下のように記述してください。<br>

**[チュートリアルイベントの計測例]**
```cpp
#include "CYZCCFox.h"

using namespace fox;
...

int ltvId = 成果地点ID;
char* eventName = (char*)"_tutorial_comp";
CYZCCFoxEvent* e = new CYZCCFoxEvent(eventName, ltvId);
CYZCCFox::trackEvent(e);
```

> 成果地点ID(必須)：管理者より連絡します。その値を入力してください。

> イベント計測を行うためには、各成果地点を識別する`成果地点ID`を指定する必要があります。<br>`CYZCCFoxEvent`クラスのコンストラクタの引数にイベント名と発行された成果地点IDを指定してください。

**[課金イベントの計測例]**
```cpp
#include "CYZCCFox.h"

using namespace fox;
...

int ltvId = 成果地点ID;
char* eventName = (char*)"_purchase";
CYZCCFoxEvent* e = new CYZCCFoxEvent(eventName, ltvId);
e->buid = "garhira";
e->sku = "purchase item";
e->price = 100.0;
e->currency = "JPY";
CYZCCFox::trackEvent(e);
```

> currencyの指定には[ISO 4217](http://ja.wikipedia.org/wiki/ISO_4217)で定義された通過コードを指定してください。

* [イベント計測の詳細](./doc/track_events/README.md)

<div id="trouble_shooting"></div>
# 5. 最後に必ずご確認ください（これまで発生したトラブル集）

### 5.1 URLスキームの設定がされずリリースされたためブラウザからアプリに遷移ができない

Cookie計測を行いブラウザを起動した場合には、URLスキームを利用してアプリケーションに遷移します。

この際、独自のURLスキームが設定されている必要があります。


### 5.2 URLスキームに大文字が含まれ、正常にアプリに遷移されない

環境によって、URLスキームの大文字小文字が判別されないことにより正常にURLスキームの遷移が行えない場合があります。

URLスキームは全て小文字で設定を行ってください。


### 5.3 F.O.Xで確認できるインストール数の値がマーケットの数字より大きい

F.O.Xではいくつかの方式を組み合わせて端末の重複インストール検知を行っています。重複検知が行えない設定では、同一端末で再インストールされる度にF.O.Xは新規のインストールと判定してしまいます。重複検知の精度を向上するために、以下の設定を行ってください。

---
[TOP MENU](/README.md)
