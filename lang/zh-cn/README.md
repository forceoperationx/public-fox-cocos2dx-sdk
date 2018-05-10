# 什么是Force Operation X

Force Operation X (下面简称F.O.X)是一款基于智能手机的，用来最大改善广告效果的综合解决方案平台。除了对APP下载量和网络用户操作的基本计测外，还能基于手机用户行为特性采用独自效果计测基準，实现了企业宣传推广时费用与效果比的最大改善。

在这个文档里，详细讲解了基于智能手机平台优化广告效果的F.O.X SDK的导入步骤。

## 目录

* **[1. 安装](#install_sdk)**
	* [SDK下载](https://github.com/cyber-z/public-fox-cocos2dx-sdk/releases)
	* [Cocos2d-x Plugin的导入步骤](./doc/integration/README.md)
	* [iOS项目设置](./doc/integration/ios/README.md)
	* [Android项目设置](./doc/integration/android/README.md)
	* [更新到最新版本](./doc/update/README.md)
* **[2. F.O.X SDK激活](#activate_sdk)**
* **[3. 执行Install计测](#tracking_install)**
	* [Install计测详细](./doc/track_install/README.md)
* **[4. APP内事件计测](#tracking_event)**
	* [session(启动)事件计测](#track_session)
	*	[其他APP内事件计测](#track_other_event)
	* [事件计测详细](./doc/track_events/README.md)
* **[5. 最后的注意事项](#trouble_shooting)**

## 什么是F.O.X SDK

将F.O.X SDK导入APP之后，能够实现以下功能。

* **Install计测**

能够计测不同广告带来的安装数量。

* **LTV计测**

可以计测不同广告来源的Life Time Value。主要的成果地点为会员注册、新手引导完成、付费等。能够分别监测各广告的登录率、付费率以及付费金额。

* **流量分析**

比较自然流入和广告流入带来的安装。能够计测App的启动次数和唯一用户数(DAU/MAU)、留存率等。

<div id="install_sdk"></div>

## 1. 导入

请从以下页面中下载最新稳定版(Latest release)SDK。

[SDK发布页面](https://github.com/cyber-z/public-fox-cocos2dx-sdk/releases)

APP中已经导入SDK的场合，请参考[更新到最新版本](./doc/update/README.md)。

下载并解压SDK「FOX_COCOS2DX_SDK_&lt;version&gt;.zip」，并导入至APP项目中。

[Cocos2d-x Plugin的导入方法](./doc/integration/README.md)

### 各OS毎の設定

* [iOS项目设置](./doc/integration/ios/README.md)
* [Android项目设置](./doc/integration/android/README.md)

### SDK说明

将F.O.X SDK导入APP之后，能够实现以下功能。

|处理|必须|概要|
|:------:|:------:|:------|
|Install计测|必须|APP启动时会自动跳转浏览器，通过Cookie计测进行广告效果测定。<br>可以计测成果CV数、CVR等。<br>方法名：CYZCCFox::trackInstall();|
|事件计测|任意|在任意成果地点进行成果通知，能够计测不同广告的付费数和登录会员数。<br>可以计测付费金额、注销数等。<br>方法名：CYZCCFox::trackEvent(event);|
|session计测|任意|APP启动时及从后台恢复时进行启动测定。<br>可以计测APP启动数、活跃用户数(DAU)、留存率等。<br>方法名：CYZCCFox::trackSession();|

> Force Operation X SDK Cocos2d-x plugin作为连结原生SDK的封装来编码实现的。导入SDK时，需要plugin和iOS及Android的原生SDK。

<div id="activate_sdk"></div>

## 2. 激活F.O.X SDK

为激活F.O.X SDK，需将`CYZCCFoxConfig`书写在AppDelegate的`applicationDidFinishLaunching`内。

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

bool AppDelegate::applicationDidFinishLaunching() {
...
	CYZCCFoxConfig config;
	config.appId_android = "发行的Android APP ID";
	config.salt_android = "发行的Android APP的APP_SALT";
	config.appKey_android = "发行的Android APP的APP_KEY";
	config.appId_ios = "发行的iOS APP ID";
	config.salt_ios = "发行的iOS APP的APP_SALT";
	config.appKey_ios = "发行的iOS APP的APP_KEY";

#ifdef DEBUG
	config.debugMode = true;
#endif
	CYZCCFox::init(config);
...
```

> ※ `debugMode`为true时，能够输出调试日志。

### 2.1 线下模式
开启线下模式功能，可停止F.O.X SDK的所有监测行为。

设定config.offlineMode设定为OfflineModeType::OFFLINE来开启线下模式，设定为为OfflineModeType::ONLINE来关闭线下模式（未设定时默认关闭线下模式）。

- 在开发期间，如不想将数据发送到F.O.X，或者希望按照投放地域停止计测的时候，可以利用这个功能。
- 根据用户许可来设定线下模式是否开启时，请确保在用户许可之后执行activate()。(activate()需要在App每次启动时去执行)
- 自动计测的代码实装方式不适用于线下模式。请按手动计测来实装代码。
- 设定将保持生效至App被删除。

```c
{
  ...
  // 线下模式的设定
  config.offlineMode = OfflineModeType::OFFLINE;
  Fox.activate(config);
}
```

<div id="tracking_install"></div>

## 3. 执行Install计测

进行首次启动的Install计测，可以计测广告效果。首次启动APP时，启动浏览器，参照广告点击时的Cookie信息进行成果计测。

为使首次启动APP时自动弹跳出浏览器，需在`AppDelegate:applicationDidFinishLaunching:`方法等这样的APP启动时肯定调用的地点添加效果计测处理。


添加成果通知代码
```cpp
#include "CYZCCFox.h"

using namespace fox;
...

CYZCCFox::trackInstall();
```

* [Install计测详细](./doc/track_install/README.md)


<div id="tracking_event"></div>

## 4. APP内事件计测

<div id="track_session"></div>

### session（启动）事件计测

可以计测自然流入和广告流入的安装数对比、APP启动次数和唯一用户人数（DAU/MAU)、留存率等。如不需要流量分析，可以忽略本项的安装。<br><br>
APP启动时或从后台恢复时添加session计测代码。无需该计测时，可以忽略本项。<br>

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

CYZCCFox::trackSession();
```

<div id="track_other_event"></div>

### 其他的APP内事件计测

在会员注册，完成新手引导，付费等任意成果地点执行事件计测，能够测定流入源广告的LTV。<br>
无需事件计测时，可以忽略本项。<br>
成果在APP内部产生的情况，请在成果处理的地方进行按下面的方式来编码安装。<br>

**[新手引导事件计测案例]**
```cpp
#include "CYZCCFox.h"

using namespace fox;
...

int ltvId = 成果地点ID;
const char* eventName = "_tutorial_comp";
CYZCCFoxEvent* e = new CYZCCFoxEvent(eventName, ltvId);
CYZCCFox::trackEvent(e);
```

> 成果地点ID(必须)：请输入管理者通知通知的值。

> 进行事件计测时，需指定识别成果地点的成果地点ID。<br>`CYZCCFoxEvent`类的构造函数的参数中请指定事件名称和发行的成果地点ID。

**[付费事件计测案例]**
```cpp
#include "CYZCCFox.h"

using namespace fox;
...

int ltvId = 成果地点ID;
const char* eventName = "_purchase";
CYZCCFoxEvent* e = new CYZCCFoxEvent(eventName, ltvId);
e->buid = "garhira";
e->sku = "purchase item";
e->price = 100.0;
e->currency = "JPY";
CYZCCFox::trackEvent(e);
```

> currency中请指定[ISO 4217](http://ja.wikipedia.org/wiki/ISO_4217)定义的货币代码。

* [事件计测详细](./doc/track_events/README.md)

<div id="trouble_shooting"></div>

# 5. 最后需确认内容（常见问题集）

### 5.1 未设置URL SCHEME 进行发布时无法从浏览器跳转至APP

进行Cookie计测时启动浏览器以后，必须使用URL scheme跳转回到APP画面。
此时需要设置独自的URL scheme，未设置scheme就上线发布时会导致无法正常迁移。

### 5.2 URL SCHEME中含有大写字母时，无法正常跳转APP。

根据运行环境，会出现因为URL SCHEME 的大小写字母不能判定而导致URL SCHEME 无法正常迁移的情况。请将URL SCHEME 全部设置为小写英文或数字或小数点。

### 5.3 F.O.X中监测到的App安装数会大于APP商城里监测的安装数

F.O.X结合多种方式来检查终端是否有重复安装。如果设置为不进行重复检查时，同一终端的再次安装会被F.O.X判定为新的安装。针对android版，为提高重复排查的精确度，请进行如下设置。

* [导入Google Play Services SDK来使用广告ID](./doc/integration/android/google_play_services/README.md)

* [利用外部储存优化重复排除](./doc/integration/android/external_storage/README.md)

* [使用自动备份功能 Android M](./doc/integration/android/auto_backup/README.md)

---
[TOP MENU](/README.md)
