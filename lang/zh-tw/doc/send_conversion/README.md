## sendConversionの詳細

利用`sendConversion:`方法能夠進行Install計測。如果使用Cookie計測手法，外部瀏覽器將被啟動。這個時候，可以把外部瀏覽器的跳轉目的地用字符串形式指定到`sendConversion:`的參數裡。<br>
從iOS9開始，從初回啟動時的瀏覽器啟動到返回APP的時候，會彈出對話框。F.O.X SDK從iOS9開始發布了新的WebView形式，在初回啟動時啟動這個新形式的“SFSafariViewController”來進行計測。这样有效防止了因弹出对话框带来的用户体验下降。

編輯項目的源代碼，對於APP啟動時調用畫面的`AppDelegate:applicationDidFinishLaunching:`方法等，請按下面那样来安装在APP啟動時肯定處理的地方。

```cpp
#include "Cocos2dxFox.h"

// 添加成果通知的代碼
FoxPlugin::sendConversion(“default”);
```

通常在sendConversion的參數裡像上面那樣輸入@"default"。默認是顯示準備好的標準頁面，可以在F.O.X管理畫面裡任意設定跳轉目標頁面的URL。

想要跳轉至特定URL，或者想用APP動態生成URL的時候，請設定URL字符串。

```cpp
	FoxPlugin::sendConversion(“http://yourhost.com/yourpage.html”);
```

可以在sendConversion方法的第二個參數裡傳遞廣告主終端ID。比如，希望把用户ID和SDK生成的UUID结合起来管理时可以使用这个参数。

```cpp
	FoxPlugin::sendConversion("default", "your unique id");
```

> ※ 作為剛啟動後的處理需要實際安裝`sendConversion`，像登錄ID這樣的用戶行為相伴的值無法通過參數傳遞。

> 【注意事项】
沒有特別的理由請將`sendConversion`安裝在APP啟動時調用的`AppDelegate:applicationDidFinishLaunching`方法裡。安裝在別的地點可能無法正確計測安裝數。
在沒有安裝`AppDelegate:applicationDidFinishLaunching`的狀態下投放安裝成果型廣告的時候，請一定事先通知廣告代理店或者媒體負責人。不能正常計測的狀態下投放安裝成果型廣告，可能被要求支付超過計測安裝數的廣告費用。

---
[TOP](../../README.md)
