[TOP](../../README.md)　>　事件计测详细

---

# 事件计测详细

## 1. session计测

#### ＜Android 项目＞
Android的场合，可以按照以下内容通过java编码执行。<br>

为计测APP启动及后台恢复的数据，需在Activity中`onResume`方法中添加代码。

APP启动时的启动计测（MainActivity类的执行案例）
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

#### ＜iOS 项目＞
iOS的场合，必须进行以下设置。

APP启动地点的`applicationDidFinishLaunching`及`applicationWillEnterForeground`两者中进行以下描述。
（另外，前面讲到的Android上Java的Activity中，`onResume方法无法执行的情况`也需进行以下执行。）

> ※APP从后台恢复时，Activity中没有执行启动计测的话，将无法正确计测活跃用户。<br>
※如果在Java的`onResume()`和C++的`applicationWillEnterForeground`两者中都未执行`CYZFOX::trackSession()`的话，可能会导致一个用户被记录两次启动信息，请务必在其中之一执行。


## 2. trackEvent详细

通过使用trackEvent方法，可以计测各广告流入的付费金额和注册人数等。为进行计测，需在任意地点中添加执行LTV成果信息的代码。<br>

应该在成果产生后实行的脚本处理里编写代码。例如，会员注册及APP内付费后的付费计测中，注册・付费实行后，在回调中执行事件计测处理。<br>

成果在APP内部产生时，请在成果处理部中进行以下描述。

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

CYZCCFoxEvent* e = new CYZCCFoxEvent("事件名称", LTV成果地点ID)
CYZCCFox::trackEvent(e);
```

> 成果地点ID(必须)：请输入由管理员通知的值。
APP内部的成果中，可以包含广告主终端ID（会员ID等），以这些为该基准进行成果计测。LTV成果中希望绑定广告主终端ID时请进行以下编码。
```cpp
#include "CYZCCFox.h"

using namespace fox;
...

CYZCCFoxEvent* e = new CYZCCFoxEvent("事件名", LTV成果地点ID)
e->buid = "USER_ID";	// 广告主终端ID
CYZCCFox::trackEvent(e);

```

> 成果地点ID(必须)：由管理员通知。请输入该值。广告主终端ID(任意)：广告主管理的独特标识符（会员ID等）。可以设置64字符以内半角英数字。APP内计测时可以进行参数。

```cpp
int ltvId = 191;	// LTV成果地点ID
const char* eventName = "_tutorial_comp";	// 事件名称
CYZCCFoxEvent* e = new CYZCCFoxEvent(eventName, ltvId);
e->buid = "USER_ID";	// 广告主终端ID
e->addParam("date", "2016-06-17");	// 任意Key/Value
e->addParam("gender", "female");
CYZCCFox::trackEvent(e);
```

> `addParam`方法中可以添加任意Key/Value。此时，Key値中请不要在参数名前面使用下划线符号（"_"）。另外，不能使用半角英数字以外的字符。

以下为可以指定的参数。

|**型**|**参数名**|**概要**|
|:---:|:---|:---|
|char|buid|设置Buid|
|double|price|设置金额|
|char|currency|设置货币|
|char|sku|设置sku|
|char|value|设置value|
|char|orderId|设置orderId|
|uint|quantity|设置quantity|
|map|extraInfo|任意参数的Key/Value|
|Document|eventInfo|设置eventInfo|

> currency中请指定[ISO 4217](http://ja.wikipedia.org/wiki/ISO_4217)定义的货币代码。

## 3. 使用标签进行事件计测

在页面上发生会员注册及商品购买等行为时，可以使用img标签来进行事件计测。<br>
从APP启动外部浏览器，在外部浏览器中表示的页面里进行标签计测时，请使用`trackEventByBrowser`方法启动外部浏览器。参数中请用字符串来设定外部浏览器显示的URL。<br>

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

// 标签设置页面URL
const char* externalUrl = "http://yoursite.com/tagpage";
CYZCCFox::trackEventByBrowser(externalUrl);
```



---
[TOP](../../README.md)
