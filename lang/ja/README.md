# Force Operation Xとは

Force Operation X (以下F.O.X)は、スマートフォンにおける広告効果最適化のためのトータルソリューションプラットフォームです。アプリケーションのダウンロード、ウェブ上でのユーザーアクションの計測はもちろん、スマートフォンユーザーの行動特性に基づいた独自の効果計測基準の元、企業のプロモーションにおける費用対効果を最大化することができます。

本ドキュメントでは、スマートフォンアプリケーションにおける広告効果最大化のためのF.O.X SDK導入手順について説明します。

## 目次

* **[1. インストール](#install_sdk)**
	* [SDKダウンロード](https://github.com/cyber-z/public-fox-cocos2dx-sdk/releases)
	* [Cocos2d-x プラグインの導入方法](./doc/integration/README.md)
	* [iOSプロジェクトの設定](./doc/integration/ios/README.md)
	* [Androidプロジェクトの設定](./doc/integration/android/README.md)
* **[2. インストール計測の実装](#tracking_install)**
	* [sendConversionの詳細](./doc/send_conversion/README.md)
* **[3. LTV計測の実装](#tracking_ltv)**
	* [sendLtvConversionの詳細](./doc/send_ltv_conversion/README.md)
* **[4. アクセス解析の実装](#tracking_analytics)**
	* [アクセス解析によるイベント計測](./doc/analytics_event/README.md)
* **[5. 広告配信機能](#fox_trade)**
	* [広告配信機能の詳細](./doc/fox_trade/README.md)
* **[6. 疎通テストの実施](#integration_test)**
* **[7. その他機能の実装](#other_function)**
	* [プッシュ通知の実装](./doc/notify/README.md)
* **[8. 最後に必ずご確認ください](#trouble_shooting)**

## F.O.X SDKとは

F.O.X SDKをアプリケーションに導入することで、以下の機能を実現します。

* **インストール計測**

広告流入別にインストール数を計測することができます。

* **LTV計測**

流入元広告別にLife Time Valueを計測します。主な成果地点としては、会員登録、チュートリアル突破、課金などがあります。各広告別に登録率、課金率や課金額などを計測することができます。

* **アクセス解析**

自然流入と広告流入のインストール比較。アプリケーションの起動数やユニークユーザー数(DAU/MAU)。継続率等を計測することができます。

* **プッシュ通知**

F.O.Xで計測された情報を使い、ユーザーに対してプッシュ通知を行うことができます。例えば、特定の広告から流入したユーザーに対してメッセージを送ることができます。

* **広告配信**

アプリ内に相互集客広告を表示させることができます。尚、広告表示が不要の場合には、本項目の実装を省略できます。


<div id="install_sdk"></div>
## 1. インストール

以下のページより最新のSDKをダウンロードしてください。

[SDKリリースページ](https://github.com/cyber-z/public-fox-cocos2dx-sdk/releases)

既にアプリケーションにSDKが導入されている場合には、[最新バージョンへのアップデートについて](./doc/update/README.md)をご参照ください。

ダウンロードしたSDK「FOX_UnityPlugin_<version>.zip」を展開し、アプリケーションのプロジェクトに組み込んでください。

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


<div id="tracking_install"></div>
## 2. インストール計測の実装

初回起動のインストール計測を実装することで、広告の効果測定を行うことができます。初回起動時に、ブラウザを起動し、広告クリック時に付与されたCookieの情報を照合することで、成果の計測を行います。

初回起動時にブラウザを起動するために、`AppDelegate:applicationDidFinishLaunching:`メソッド等、アプリケーションの起動時に必ず呼ばれる箇所に効果測定用の処理を追加します。

ヘッダファイルをインクルード
```cpp
#include "Cocos2dxFox.h"
```

成果通知のコードを追加
```cpp
FoxPlugin::sendConversion(“default”);
```

sendConversionメソッドの引数には、通常は上記の通り"default"という文字列をそのまま指定してください。

> iOS9より初回起動時のブラウザ起動からアプリに戻る際に、ダイアログが出力されます。 F.O.X SDKではiOS9からリリースされた新しいWebView形式である “SFSafariViewController”を初回起動時に起動させ計測することで、ダイアログ表示によるユーザービリティの低下を防止することが出来ます。

* [sendConversionの詳細](./doc/send_conversion/README.md)


<div id="tracking_ltv"></div>
## 3. LTV計測の実装

LTV計測により、広告流入別の課金金額や入会数などを計測することができます。計測のために、任意の地点にLTV成果通信を行うコードを追加します。

ソースの編集は、成果が上がった後に実行されるスクリプトに処理を記述します。例えば、会員登録やアプリ内課金後の課金計測では、登録・課金処理実行後のコールバック内にLTV計測処理を記述します。

成果がアプリ内部で発生する場合、成果処理部に以下のように記述してください。

ヘッダをインクルード
```cpp
#include “Cocos2dxFox.h”
```
成果を記述
```cpp
FoxPlugin::sendLtv(成果地点ID);
```

> 成果地点ID(必須)：管理者より連絡します。その値を入力してください。
※Android Cocos2dx SDK v2.10.4g以前の海外版/グローバル版SDK (バージョン末尾が u しくは g)からSDKをアップデートをする場合、必ず「v2.10.4g以前からのアップデート手順」の手順を追加してください。


* [sendLtvConversionの詳細](./doc/send_ltv_conversion/README.md)


<div id="tracking_analytics"></div>
## 4. アクセス解析

アクセス解析を導入することで、自然流入・広告流入別の起動数、アクティブユーザー数(DAU/MAU)や継続率を計測することができます。アクセス解析では、アプリケーションが起動、もしくはバックグラウンドから復帰する際にセッション計測を行うコードを追加します。不要の場合には、本項目の実装を省略できます。

#### ＜Android プロジェクト＞
Androidの場合、以下の設定が必要です。

アプリケーションの起動及び、バックグラウンドからの復帰を計測するために、Activityの`onResume`メソッドにコードを追加します。

アプリケーション起動時の起動計測（MainActivityクラスへの実装例）
```java
import jp.appAdForce.android.AnalyticsManager;

public class MainActivity extends Activity {

		@Override
		protected void onResume() {
            super.onResume();
            AnalyticsManager.sendStartSession(this);
		}
}
```

#### ＜iPhone プロジェクト＞
iPhoneの場合、以下の設定が必要です。

アプリ起動地点の`applicationDidFinishLaunching`および`applicationWillEnterForeground`の両方に、以下のように記述してください。
（また、前述のAndroidにおけるJavaのActivity上で、`onResumeメソッドに実装出来ない場合`にも以下の実装を行います。）


```cpp
#include “Cocos2dxFox.h”

---

FoxPlugin::sendStartSession();
```

> ※アプリケーションがバックグラウンドから復帰した際に、そのActivityに起動計測の実装がされていない場合など、正確なアクティブユーザー数が計測できなくなります。<br>
※JavaのonResume()とC++のapplicationWillEnterForegroundの両方でsendStartSession()が実行されていた場合、１ユーザーから２重にアプリ起動情報が送信されるため必ずどちらかで実装してください。


[アクセス解析によるイベント計測](./doc/analytics_event/README.md)

<div id="fox_trade"></div>
## 5. 広告配信機能

本機能を利用することで相互集客広告を表示させることができます。
尚、広告表示が不要の場合には、本項目の実装を省略できます。
表示する広告の種類は以下の２つとなります。

* バナー広告
* インタースティシャル広告

### 5.1 バナー広告表示の実装

表示させるタイミングでDLCoBannerインストタンスを生成し、showメソッドを実行します。<br>
実行すると、現在表示されている画面上にバナーが表示されます。

Sample.h
```cpp
#include "DLCoBanner.h"

class Sample
{
...
    DLCoBanner* dlb;
};
```

Sample.cpp
```cpp
#include "Sample.h"

Fox::DLCoBanner* dlb;

// 画面上部に表示する
void Sample::showBannerTop(Ref* pSender)
{

// バナーを表示するタイミングで以下の処理を実行
	int position = 0;
	char* placementId = ((char*)"広告表示ID");
	dlb = new DLCoBanner(placementId, position);
	dlb->show();
}

// バナー広告を閉じる
void Samle::hideBanner(Ref* pSender)
{
    dlb->hide();
}
```

> DLCoBannerコンストラクタの第一引数には管理者より発行される広告表示IDを指定してください。

> DLCoBannerコンストラクタの第二引数にはバナー広告の表示位置オプションを指定します。<br>
　・`AdPosition.TOP` : 画面上部の中心に配置<br>
　・`DLC_POSITION_TOP` : 画面上部中心に配置<br>
　・`DLC_POSITION_BOTTOM` : 画面下部中心に配置<br>
　・`DLC_POSITION_TOP_LEFT` : 画面上部左に配置<br>
　・`DLC_POSITION_TOP_RIGHT` : 画面上部右に配置<br>
　・`DLC_POSITION_BOTTOM_LEFT` : 画面下部左に配置<br>
　・`DLC_POSITION_BOTTOM_RIGHT` : 画面下部右に配置

[広告配信機能の詳細](./doc/fox_trade/README.md)

### 5.2 インタースティシャル広告表示の実装

インタースティシャル広告の表示対象となる画面にてDahliaInterstitialAdsインスタンスを生成し、showメソッドを実装してください。

Sample.h
```cpp
#include "DLCoInterstitial.h"

class Sample
{
...
    DLCoInterstitial* dli;
};
```

Sample.cpp
```cpp
#include "Sample.h"

// インタースティシャル広告の表示
void Sample::showInterstitial(Ref* pSender)
{
    char* placementId = ((char*)"広告表示ID");
    DLCoInterstitial* dli = new DLCoInterstitial(placementId);
    dli->show();
}
```

> DLCoInterstitialコンストラクタの引数には管理者より発行される広告表示IDを指定してください。

[広告配信機能の詳細](./doc/fox_trade/README.md)


<div id="integration_test"></div>
## 6. 疎通テストの実施

マーケットへの申請までに、Force Operation Xを導入した状態で十分にテストを行い、アプリケーションの動作に問題がないことを確認してください。

効果測定テストの手順については、管理者よりご連絡いたしますのでその手順に従いテストを実施してください。

成果のための通信は、起動後に一度のみ行わるため、二回目以降の起動では通信が発生しません。続けて効果測定テストを行いたい場合には、アプリケーションをアンインストールし、再度インストールから行ってください。

* **テスト手順**

SDKが正常に導入されていることを確認するためのテスト手順は以下の通りです。
ProGuardを掛けてリリースを行う場合、必ずProGuardを掛けた状態でテストの実施をお願い致します。

1. テスト用端末にテストアプリがインストールされている場合には、アンインストール
2. テスト用端末の「設定」→「Safari」→「Cookieとデータを消去」によりCookieを削除
3. 弊社より発行したテスト用URLをクリック<br>
   ※ テスト用URLは必ずOSに設定されているデフォルトブラウザでリクエストされるようにしてください。
デフォルトブラウザとは、URLをクリックした際に自動で起動するブラウザのことです。
メールアプリやQRコードアプリを利用され、そのアプリ内WebViewで遷移した場合には計測できません。
4. マーケットへリダイレクト<br>
   ※ テストURLの場合には、遷移先がなくエラーダイアログが表示される場合がありますが、問題ありません。
5. テスト用端末にテストアプリをインストール
6. アプリを起動、ブラウザが起動<br>
   ※ ここでブラウザが起動しない場合には、正常に設定が行われていません。
設定を見直していただき、問題が見当たらない場合には弊社へご連絡ください。
7. LTV地点まで画面遷移
8. アプリを終了し、バックグラウンドからも削除
9. 再度アプリを起動
10. 弊社へ3,6,7,9の時間をお伝えください。正常に計測が行われているか確認致します。
11. 弊社側の確認にて問題がなければテスト完了となります。


<div id="other_function"></div>
# 7. その他機能の実装

* [プッシュ通知の実装](./doc/notify/README.md)


<div id="trouble_shooting"></div>
# 8. 最後に必ずご確認ください（これまで発生したトラブル集）

### URLスキームの設定がされずリリースされたためブラウザからアプリに遷移ができない

Cookie計測を行いブラウザを起動した場合には、URLスキームを利用してアプリケーションに遷移します。

この際、独自のURLスキームが設定されている必要があります。


### URLスキームに大文字が含まれ、正常にアプリに遷移されない

環境によって、URLスキームの大文字小文字が判別されないことにより正常にURLスキームの遷移が行えない場合があります。

URLスキームは全て小文字で設定を行ってください。


### F.O.Xで確認できるインストール数の値がマーケットの数字より大きい

F.O.Xではいくつかの方式を組み合わせて端末の重複インストール検知を行っています。重複検知が行えない設定では、同一端末で再インストールされる度にF.O.Xは新規のインストールと判定してしまいます。重複検知の精度を向上するために、以下の設定を行ってください。

* [広告IDを利用するためのGoogle Play Services SDKの導入](./doc/integration/android/google_play_services/README.md)
* [（オプション）外部ストレージを利用した重複排除設定](./doc/integration/android/external_storage/README.md)
* [Android M(6.0) オートバックアップ機能の利用](./doc/integration/android/auto_backup/README.md)

---
[TOP MENU](/README.md)
