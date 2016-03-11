# iOSプロジェクトの設定

## **Xcodeプロジェクトの設定**

### Xcodeプロジェクトの編集

パブリッシュされたXcodeプロジェクトを開き、編集します。

* **フレームワーク設定**

次のフレームワークをプロジェクトにリンクしてください。

<table>
<tr><th>フレームワーク名</th><th>Status</th></tr>
<tr><td>SafariServices.framework</td><td>Optional</td></tr>
<tr><td>AdSupport.framework</td><td>Optional</td></tr>
<tr><td>iAd.framework </td><td>Required</td></tr>
<tr><td>Security.framework </td><td>Required </td></tr>
<tr><td>StoreKit.framework </td><td>Required </td></tr>
</table>

> AdSupport.frameworkはiOS 6以降で追加されたフレームワークのため、アプリケーションをiOS 5以前でも動作させる(iOS Deployment Targetを5.1以下に設定する)場合にはweak linkを行うために”Optional”に設定してください。

> ※SafariServices.frameworkはiOS 9以降で追加されたフレームワークのため、アプリケーションをiOS 8以前でも動作させる(iOS Deployment Targetを8.4以下に設定する)場合にはweak linkを行うために”Optional”に設定してください。

![フレームワーク設定01](/lang/ja/doc/integration/ios/config_framework/img01.png)

[フレームワーク設定の詳細](/lang/ja/doc/integration/ios/config_framework/README.md)

* **SDK設定**

SDKの動作に必要な設定をplistに追加します。「AppAdForce.plist」というファイルをプロジェクトの任意の場所に作成し、次のキーと値を入力してください。

Key | Type | Value
:---: | :---: | :---
APP_ID | String | Force Operation X管理者より連絡しますので、その値を入力してください。
SERVER_URL | String | Force Operation X管理者より連絡しますので、その値を入力してください。
APP_SALT | String | Force Operation X管理者より連絡しますので、その値を入力してください。
APP_OPTIONS | String | 何も入力せず、空文字の状態にしてください。
CONVERSION_MODE | String | 1
ANALYTICS_APP_KEY | String | Force Operation X管理者より連絡しますので、その値を入力してください。<br />アクセス解析を利用しない場合は設定の必要はありません。

![フレームワーク設定01](/lang/ja/doc/integration/ios/config_plist/img05.png)

* **App Transport Securityについて**

iOS9より提供されたAppTransportSecurity(以下、ATS)を有効にしている場合、Info.plistに以下の設定を行いF.O.X SDKが行う通信先のドメインをATSの例外としてください。

キー | タイプ | 概要
:---: | :---: | :---
NSExceptionDomains|Dictionary|ATSの例外を指定するディクショナリー
指定ドメイン文字列|Dictionary|以下２つのドメインをキーで作成してください。<br>・app-adforce.jp<br>・forceoperationx.com
NSExceptionAllowsInsecureHTTPLoads|Boolean|YES を指定してくださいATSの例外とします。
NSIncludesSubdomains|Boolean|YES を指定しATSの例外設定をサブドメインにも適用させます。

![ATS設定](/lang/ja/doc/integration/ios/config_plist/img06.png)

[SDK設定の詳細](/lang/ja/doc/integration/ios/config_plist/README.md)

[AppAdForce.plistサンプル](/lang/ja/doc/integration/ios/config_plist/AppAdForce.plist)

**iOS9における導入の注意点**

> Cookie計測を実施する際に、iOS9ではSFSafariViewControllerが使用します。
F.O.X Unity SDK v2.16以降では、SFSafariViewController起動後の制御をFoxReengagePluginで行うため導入が必須となります。

> これまで外されていた場合には、本Unity SDKのunitypackageファイルに同梱のFoxReengagePluginをご導入ください。

### その他

* [管理画面上に登録したバンドルバージョンに応じた処理の振り分け](./check_version/README.md)

---
[戻る](/lang/ja/doc/integration/README.md)

[TOP](/lang/ja/README.md)
