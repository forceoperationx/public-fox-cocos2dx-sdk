[TOP](../../README.md)　>　イベント計測の詳細

---

# イベント計測の詳細

## 1. セッション計測

#### ＜Android プロジェクト＞
Androidの場合、以下のようにjavaによる実装も可能です。<br>

アプリケーションの起動及び、バックグラウンドからの復帰を計測するために、Activityの`onResume`メソッドにコードを追加します。

アプリケーション起動時の起動計測（MainActivityクラスへの実装例）
```java
import co.cyberz.fox.Fox;

public class MainActivity extends Activity {

		@Override
		protected void onResume() {
            super.onResume();
            Fox.trackSession();
		}
}
```

#### ＜iOS プロジェクト＞
iOSの場合、以下の設定が必要です。

アプリ起動地点の`applicationDidFinishLaunching`および`applicationWillEnterForeground`の両方に、以下のように記述してください。
（また、前述のAndroidにおけるJavaのActivity上で、`onResumeメソッドに実装出来ない場合`にも以下の実装を行います。）

> ※アプリケーションがバックグラウンドから復帰した際に、そのActivityに起動計測の実装がされていない場合など、正確なアクティブユーザー数が計測できなくなります。<br>
※Javaの`onResume()`とC++の`applicationWillEnterForeground`の両方で`CYZFOX::trackSession()`が実行されていた場合、１ユーザーから２重にアプリ起動情報が送信されるため必ずどちらかで実装してください。


## 2. trackEventの詳細

trackEventメソッドを利用することで、広告流入別の課金金額や入会数などを計測することができます。計測のために、任意の地点にLTV成果通信を行うコードを追加します。<br>

ソースの編集は、成果が上がった後に実行されるスクリプトに処理を記述します。例えば、会員登録やアプリ内課金後の課金計測では、登録・課金処理実行後のコールバック内にイベント計測処理を記述します。<br>

成果がアプリ内部で発生する場合、成果処理部に以下のように記述してください。

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

CYZCCFoxEvent* e = new CYZCCFoxEvent("イベント名", LTV成果地点ID)
CYZCCFox::trackEvent(e);
```

> 成果地点ID(必須)：管理者より連絡します。その値を入力してください。
アプリ内部の成果に、広告主端末ID（会員IDなど）を含める事ができ、これを基準とした成果計測が行えます。LTV成果に広告主端末IDを付与したい場合は以下のように記述してください。
```cpp
#include "CYZCCFox.h"

using namespace fox;
...

CYZCCFoxEvent* e = new CYZCCFoxEvent("イベント名", LTV成果地点ID)
e->buid = "USER_ID";	// 広告主端末ID
CYZCCFox::trackEvent(e);

```

> 成果地点ID(必須)：管理者より連絡します。その値を入力してください。広告主端末ID(オプション)：広告主様が管理しているユニークな識別子（会員IDなど）です。指定できる値は64文字以内の半角英数字です。アプリ内計測時には、パラメータをオプションとして設定する事が可能です。

```cpp
int ltvId = 191;	// LTV成果地点ID
const char* eventName = "_tutorial_comp";	// イベント名
CYZCCFoxEvent* e = new CYZCCFoxEvent(eventName, ltvId);
e->buid = "USER_ID";	// 広告主端末ID
e->addParam("date", "2016-06-17");	// 任意のKey/Value
e->addParam("gender", "female");
CYZCCFox::trackEvent(e);
```

> `addParam`メソッドで任意のKey/Valueを追加することが可能です。その場合、Key値にアンダースコア（"_"）をパラメータ名の先頭に記述しないでください。また、半角英数字以外は使用できません。

指定できるパラメータは次の通りです。

|**型**|**パラメータ名**|**概要**|
|:---:|:---|:---|
|char|buid|Buidをセット|
|double|price|金額をセット|
|char|currency|通貨をセット|
|char|sku|skuをセット|
|char|value|valueをセット|
|char|orderId|orderIdをセット|
|uint|quantity|quantityをセット|
|map|extraInfo|任意パラメータのKey/Value|
|Document|eventInfo|eventInfoをセット|

> currencyには[ISO 4217](http://ja.wikipedia.org/wiki/ISO_4217)で定義された通貨コードを指定してください。

## 3. タグを利用したイベント計測について

会員登録や商品購入等がWebページで行われる場合に、imgタグを利用してイベント計測を利用することができます。<br>
アプリケーションから外部ブラウザを起動し、外部ブラウザで表示したWebページでタグ計測を行う場合は、`trackEventByBrowser`メソッドを利用して外部ブラウザを起動してください。引数には、外部ブラウザで表示するURLを文字列で指定します。<br>

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

// タグ設置ページURL
const char* externalUrl = "http://yoursite.com/tagpage";
CYZCCFox::trackEventByBrowser(externalUrl);
```



---
[TOP](../../README.md)
