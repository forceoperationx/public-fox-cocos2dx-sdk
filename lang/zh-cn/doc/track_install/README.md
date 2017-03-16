[TOP](../../README.md)　>　Install计测详情

---

# Install计测详情

使用`trackInstall`方法可以进行Install计测。使用Cookie计测的情况时会弹跳出外部浏览器。此时，外部浏览器的迁移网页可以通过`trackInstall`的引数中指定计测选项来实现。<br>

编辑项目中的源代码，在APP启动时弹跳画面的AppDelegate:applicationDidFinishLaunching:方法等，APP启动时必定执行的位置，来按以下内容来做编码安装。

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

// 添加成果通知代码
CYZCCFox::trackInstall();
```

> 若不指定option参数将会跳转到默认页面，跳转页面的URL可以在F.O.X管理界面中进行自由设置。


想要指定跳转目的地URL或想在APP中自动生成URL时，请指定option参数。

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

CYZCCFoxTrackOption option;
option.redirectUrl = "http://yoursite.com";
option.buid = "USER_ID";
option.onInstalComplete = CC_CALLBACK_0(SampleClass::onInstallComplete, this);
CYZCCFox::trackInstall(option);

...

void SampleClass::onInstallComplete()
{
	CCLOG("Install Completed!!!!!!!!!!!!");
}
```

> ・CYZCCFoxTrackOption的buid中可以传递广告主终端ID。

> ・CYZCCFoxTrackOption的onInstalComplete中通过传递回调方法，可以在SDK通信完成时执行回调方法。

> ・通过设置CYZCCFoxTrackOption的optout为true，可以使optout有效。默认值为false。

> ※ 作为启动后的立即处理功能，必须在sendConversion做编码安装。登录ID等用户行为的数字无法作为参数来传递。

> 【注意】
`trackInstall`在没有特殊理由的情况下，请在启动APP时调用的`AppDelegate:applicationDidFinishLaunching`中执行。在其他位置执行可能会导致安装数无法正确计测。
APP启动时调用的`AppDelegate:applicationDidFinishLaunching`内中未编码安装的状态下实行安装成果型广告时，必须向广告代理店或媒体单位进行说明。未正确进行计测就开始安装成果型广告，可能会产生超过计测安装数的广告费用。


---
[TOP](../../README.md)
