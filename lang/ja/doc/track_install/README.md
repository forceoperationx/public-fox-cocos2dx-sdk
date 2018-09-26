[TOP](../../README.md)　>　インストール計測の詳細

---

# インストール計測の詳細

`trackInstall`メソッドを利用することで、インストール計測を行うことができます。Cookie計測を利用する場合には、外部ブラウザが起動されます。この際、外部ブラウザの遷移先を`trackInstall`の引数に計測オプションを指定することができます。<br>

プロジェクトのソースコードを編集し、アプリケーションの起動時に呼び出される画面のAppDelegate:applicationDidFinishLaunching:メソッド等、アプリケーションの起動時に必ず呼ばれる箇所に対して、次の通り実装を行ってください。

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

// 成果通知のコードを追加
CYZCCFox::trackInstall();
```

> オプションを指定しない場合では標準で用意されたページが表示されますが、遷移先のURLをF.O.X管理画面上で任意に設定することが可能です。


特定のURLヘ遷移させたい場合や、アプリケーションで動的にURLを生成したい場合には、オプションを指定します。

```cpp
#include "CYZCCFox.h"

using namespace fox;
...

CYZCCFoxTrackOption option;
option.redirectURL = "http://yoursite.com";
option.buid = "USER_ID";
option.onInstalComplete = CC_CALLBACK_0(SampleClass::onInstallComplete, this);
CYZCCFox::trackInstall(option);

...

void SampleClass::onInstallComplete()
{
	CCLOG("Install Completed!!!!!!!!!!!!");
}
```

> * CYZCCFoxTrackOptionのbuidに広告主端末IDを渡すことができます。

> * CYZCCFoxTrackOptionのonInstalCompleteにコールバックを渡すことで、SDKの通信が完了したタイミングでコールバックを受け取ることができます。<br>※ F.O.X Cocos2d-x SDK 4.0.1以降においてAndroidでコールバックを受け取るの場合、アプリ初回起動時に呼ばれるActivityを編集する必要があります。[]詳細はこちら](../integration/android/README.md#receive_callback)をご確認ください。

> * CYZCCFoxTrackOptionのoptoutをtrueにすることで、オプトアウトを有効にすることができます。デフォルトではfalseです。

> ※ sendConversionは起動直後の処理として実装される必要があるため、ログインIDなどのユーザーアクションが伴う値を引数として渡すことはできません。

> 【ご注意】
`trackInstall`は、特に理由がない限りはアプリケーションの起動時に呼び出される`AppDelegate:applicationDidFinishLaunching`内に実装してください。それ以外の箇所に実装された場合にはインストール数が正確に計測できない場合があります。
アプリケーションの起動時に呼び出される`AppDelegate:applicationDidFinishLaunching`内に実装していない状態でインストール成果型の広告を実施する際には、必ず広告代理店もしくは媒体社の担当にその旨を伝えてください。正確に計測が行えない状態でインストール成果型の広告を実施された際には、計測されたインストール数以上の広告費の支払いを求められる恐れがあります。


---
[TOP](../../README.md)
