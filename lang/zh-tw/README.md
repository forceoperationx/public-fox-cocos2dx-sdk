# Force Operation X是什麼

Force Operation X (下面簡稱F.O.X)是基於智慧手機的，用來最大改善廣告效果的綜合解決方案平台。除了對APP下載量和網絡用戶操作的基本計測外，還能基於手機用戶行為特性採用獨自效果計測基準，實現了企業宣傳推廣时費用与效果比的最大改善。

在這個文檔裡，詳細講解了基於智慧手機平台優化廣告效果的F.O.X SDK的導入步驟。

## 目次

* **[1. 導入](#install_sdk)**
	* [SDK下載](https://github.com/cyber-z/public-fox-cocos2dx-sdk/releases)
	* [Cocos2d-x插件的導入方法](./doc/integration/README.md)
  * [iOS項目的設定](./doc/integration/ios/README.md)
  * [Android項目的設定](./doc/integration/android/README.md)
* **[2. Install計測的安裝](#tracking_install)**
	* [sendConversion的詳細](./doc/send_conversion/README.md)
* **[3. LTV計測的安裝](#tracking_ltv)**
	* [sendLtvConversion的詳細](./doc/send_ltv_conversion/README.md)
* **[4. 流量分析的安裝](#tracking_analytics)**
	* [依靠流量分析進行Event計測](./doc/analytics_event/README.md)
* **[5. 廣告投放功能](#fox_trade)**
	* [広告配信機能の詳細](./doc/fox_trade/README.md)
* **[6. 進行疏通測試](#integration_test)**
* **[7. 最後請務必確認](#trouble_shooting)**

## F.O.X SDK是什麼

在APP中導入F.O.X，可以實現如下功能

* **Install計測**

能夠按不同的廣告流入來計測安裝數。

* **LTV計測**

按不同的廣告流入来計測Life Time Value。作為主要的成果地點，有會員登錄，教程突破，消费等。能夠按照不同廣告来監測登錄率，消費率和消費額等。

* **流量分析**

自然流入和廣告流入的APP安裝數比較。能夠計測APP的啟動數，唯一用戶數(DAU/MAU)，持續率等。

* **廣告投放**

能夠在APP內部表示互動推廣廣告。如果不需要顯示該廣告，可以省略本章節的安裝。

<div id="install_sdk"></div>
## 1. 導入

請從下面的頁面來下載最新的SDK。

[SDK發布頁面](https://github.com/cyber-z/public-fox-cocos2dx-sdk/releases)

請展開下載的SDK「FOX_UnityPlugin_<version>.zip」並導入到APP的項目裡。

[Cocos2d-x 插件的導入方法](./doc/integration/README.md)

### 不同OS的設定

* [iOS項目的設定](./doc/integration/ios/README.md)
* [Android項目的設定](./doc/integration/android/README.md)

### SDK式樣

在APP中導入F.O.X，可以實現如下功能。

|處理|必須|概要|
|:------:|:------:|:------|
|Install計測|必須|啟動時，透過瀏覽器的啟動、Cookie計測手法，進行廣告效果測量。能夠測量啟動數、CVR等等。Method名稱：sendConversion|
|LTV計測|任意|在任意的成果地點進行成果通知，進行廣告別的消費數和入會員數測量。能夠測量消費金額、退出會員數等等。Method名稱：sendLtv|
|流量分析|任意|計測APP啟動和從Background恢復時的啟動。能夠啟動啟動數、活躍用戶數(DAU)、持續率。Method名稱：sendStartSession|

> Force Operation X SDK Cocos2d-x plugin是為了連接Native版本的SDK而做的wrapper，所以為了正確的導入SDK，需要iOS或Android的Native版本的SDK

<div id="tracking_install"></div>
## 2. Install計測的安裝

導入初次啟動的Install計測，就能夠監測廣告效果。初次啟動時，啟動瀏覽器，對照在點擊廣告時所被賦予的Cookie資訊，進行成果計測。

在初次啟動時為了啟動瀏覽器，`AppDelegate:applicationDidFinishLaunching:` method等，追加效果測定用的處理到APP啟動時一定會被喚出的地方。

Include header file.
```cpp
#include "Cocos2dxFox.h"
```

追加成果通知Code
```cpp
FoxPlugin::sendConversion(“default”);
```

在sendConversion方法的參數裡，通常請完全按上面那樣指定"default"這個字符串。

> 另外，在iOS9環境初回啟動時，從瀏覽器啟動到返回APP的時候，會跳出對話框。
在F.O.X SDK裡，從iOS9開始提供新WebView形式，在初回啟動時使用這個新形式的“SFSafariViewController”來計測的話，可以禁止彈出對話框來提高用戶體驗。

* [sendConversion的詳細](./doc/send_conversion/README.md)

<div id="tracking_ltv"></div>
## 3. LTV計測的安裝

透過LTV計測，能夠計測廣告流入別的消費金額和加入會員數等。為了計測，須在任意地點添加进行LTV成果通信的代码。

在成果到達後執行的程式中加入SDK的處理程式。譬如說，會員登錄和APP內消費後的消費計測，是將LTV計測處理記述在登錄、消費處理實行後的回調方法內。

如果成果發生在APP內部，請如同以下記述在成果處理裡面。

Include header。
```cpp
#include “Cocos2dxFox.h”
```
記述成果
```cpp
FoxPlugin::sendLtv(成果地点ID);
```

> 成果地點ID(必須)：請輸入由管理員所告知的數值。
＊如果更新的是Android Cocos2dx SDK v2.10.4g及以前的海外版/世界版SDK(版本號末尾是u或g)，請按「v2.10.4g及以前版本的更新步驟」來執行。

* [sendLtvConversion的詳細](./doc/send_ltv_conversion/README.md)

<div id="tracking_analytics"></div>
## 4. 流量分析的安裝

導入流量分析，能夠計測自然流入和廣告流入的安裝數，APP的啟動數，唯一用戶數(DAU/MAU)，持續率等。流量分析會在APP啟動、或從後台恢復時，追加進行Session計測的代碼。如果不做流量分析，可以省略本項目的安裝。

#### ＜Android 項目＞
Android需要進行如下設定。

為了計測APP的啟動和從後台的恢復，追加代碼到Activity的onResume()方法。
APP啟動時的啟動計測（對於MainActivity class的安裝範例）。

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

#### ＜iPhone 項目＞
iPhone需要進行以下設定。

按照下面那樣添加在APP啟動地點`applicationDidFinishLaunching`和`applicationWillEnterForeground`。
（另外，在前面基於Android環境Java的Activity上，如果不能實際安裝`onResume`就進行如下的安裝。）

```cpp
#include “Cocos2dxFox.h”

---

FoxPlugin::sendStartSession();
```

> ※APP在從後台恢復時，如果此Activity沒有安裝啟動計測，將無法計測正確的活躍用戶。
※在Java的onResume()和C++のapplicationWillEnterForeground執行sendStartSession()的話，一個用戶會同時送出雙重的APP啟動資訊，請確保只在其中一個地方導入SDK的處理。

[依靠流量分析進行Event計測](./doc/analytics_event/README.md)

<div id="fox_trade"></div>
## 5. 廣告投放機能

能夠在APP內部表示相互推廣獲得客源的廣告。
如果不需要顯示該廣告，可以省略本章節的安裝。
可以顯示的廣告種類有以下兩種。

* 橫幅廣告（Banner Ad）
* 插播廣告（Interstitial Ad）

### 5.1 橫幅廣告表示的安裝

請在希望表示的時候生成DLCoBanner實例，並安裝show方法。
安裝後，橫幅廣告會在現在表示的畫面上顯示出來。

Sample.cpp
```cpp
#include "DLCoBanner.h"

Fox::DLCoBanner* dlb;

// 表示在畫面上部
void Sample::showBannerTop(Ref* pSender)
{
// 在表示橫幅廣告的時機進行如下處理
	int position = DLC_POSITION_TOP;
	char* placementId = ((char*)"廣告表示ID");
	dlb = new DLCoBanner(placementId, position);
	dlb->show();
}

// 關閉橫幅廣告
void Samle::hideBanner(Ref* pSender)
{
    dlb->hide();
}
```

> 在DLCoBanner構造函數的第一個參數裡指定由管理員發行的廣告表示ID。

> 在DLCoBanner構造函數的第二個參數裡指定橫幅廣告的表示位置option。<br>
　・`DLC_POSITION_TOP` : 配置到畫面上部中心<br>
　・`DLC_POSITION_BOTTOM` : 配置到畫面下部中心<br>
　・`DLC_POSITION_TOP_LEFT` : 配置到畫面上部左側<br>
　・`DLC_POSITION_TOP_RIGHT` : 配置到畫面上部右側<br>
　・`DLC_POSITION_BOTTOM_LEFT` : 配置到畫面下部左側<br>
　・`DLC_POSITION_BOTTOM_RIGHT` : 配置到畫面下部右側

[廣告投放機能的詳細](./doc/fox_trade/README.md)

### 5.2 插播廣告表示的安裝

請在插播廣告表示對象的畫面裡生成下面的DahliaInterstitialAds實例，並安裝show方法。

Sample.cpp
```cpp
#include "DLCoInterstitial.h"

// 插播廣告的表示
void Sample::showInterstitial(Ref* pSender)
{
    char* placementId = ((char*)"広告表示ID");
    DLCoInterstitial* dli = new DLCoInterstitial(placementId);
    dli->show();
}
```

> 請在DLCoInterstitial構造函數的參數裡指定管理員發行的廣告表示ID。

[廣告投放機能的詳細](./doc/fox_trade/README.md)

<div id="integration_test"></div>
## 6. 進行疏通測試

在APP上架申請以前，在導入SDK的狀態請做充分的測試，以確保APP的動作沒有問題。
請按照管理員會通知的測試步驟進行測試。
由於在啟動後只發生一次Install計測的通信，如果想要再次進行Install計測的話，請卸載APP再次安裝

**測試步驟**

1. 如果測試用的設備已安裝APP，請先卸載掉APP
1. 透過測試用設備的「設定」→「Safari」→「Cookie和數據消除」刪除Cookie
1. 複製鄙司發行的測試用URL，粘貼到默認瀏覽器（標準瀏覽器）的URL欄裡進行訪問。<br />
＊請一定在OS設定的默認瀏覽器裡使用測試URL來發出請求。點擊URL彈出的瀏覽器就是默認瀏覽器。郵件APP或QR碼讀取APP等這些APP內部會用WebView發生的畫面跳轉是無法計測的。
1. 畫面移轉到Market<br />
＊使用測試URL，可能會因為沒有設定跳轉目的地而彈出錯誤對話框，這個不影響測試。
1. 在測試終端上安裝測試APP<br />
1. 啟動APP，瀏覽器啟動<br />
＊若流覽器無法啟動，說明沒有正常設定。重新設定後，若仍無法發現問題，請與弊司聯繫。
1. 把畫面移轉到LTV地點<br />
＊如果登錄了LTV地點執行此步驟
1. 結束並從後台關閉APP<br />
1. 再次啟動APP<br />
1. 請告訴鄙司3，6，7，9的時間。在鄙司這邊會確認是否正常被計測。
1. 待鄙司確認沒有問題的時候，測試算正式完成。

<div id="trouble_shooting"></div>
# 7. 最後請務必確認（到現在發生過的問題集）

### 7.1. 未設定URL Scheme發布的APP引起無法從瀏覽器跳轉到APP

為了進行Cookie計測，在啟動外部瀏覽器以後，要利用URL Scheme跳轉到APP來返回到原來的畫面。
這時有必要設定獨自的URL Scheme，未設定URL Scheme發布的APP將無法正常跳轉。

### 7.2. URL Scheme裡包含了大寫字母，無法正常跳轉回APP

由於環境的不同，可能無法判別URL Scheme裡的大小寫字母，進而引起不能正常跳轉。
因此URL Scheme請全部使用小寫字母來設定。

### 7.3. 由於設定的URL Scheme與其他APP的相同，導致了從瀏覽器跳轉到了其他APP

在iOS裡，如果設定同一個URL Scheme到多個APP，啟動哪個APP是不確定的。因此設定URL Scheme的時候，請使用唯一的有一定複雜度的字符串。

### 7.4. 用F.O.X計測的Install數值比Market計測的數值要大

F.O.X使用了多種方式來監測終端的重複安裝。倘若設定了不進行重複監測，在相同終端再安裝時F.O.X會判定為新的安裝。為了提高重複監測的精度，請進行如下設定。

* [導入Google Play Services SDK來使用廣告ID](./doc/integration/android/google_play_services/README.md)
* [利用外部存儲設定重複排除](./doc/integration/android/external_storage/README.md)
* [Android M(6.0) 利用自動備份功能](./doc/integration/android/auto_backup/README.md)

---
[TOP MENU](/README.md)
