[TOP](../../../README.md)　>　[Cocos2d-xプラグインの導入手順](../../README.md)　>　iOSプロジェクトの設定

---

# iOSプロジェクトの設定

## **Xcodeプロジェクトの設定**

パブリッシュされたXcodeプロジェクトを開き、編集します。

### 1. F.O.X SDKネーティブフレームワークの導入

ダウンロードした`CYZFox_iOS_static_<version>.zip`を解凍して、`CYZFox.framework`ファイルをXcodeプロジェクトにリンクしてください。

### 2. 他のフレームワークの設定

次のフレームワークをプロジェクトにリンクしてください。

フレームワーク名 | Status
:--- | :---:
AdSupport.framework|Optional
Security.framework|Required
SystemConfig.framework|Required


### 3. Pluginソースの追加

ダウンロードしたSDK`FOX_COCOS2DX_SDK_<version>.zip`をOS上に展開します。Classesフォルダ内に以下iOSに使われるソースファイルをXcodeプロジェクトに追加してください。

ファイル名|概要
:---|:---
CYZCCFox.h|APIの定義
CYZCCFoxEvent.h|トラッキングイベントの定義
CYZCCFoxTypes.h|コールバックファンクションの定義
iOS/CYZCCFox.mm|native APIのwrapper実装
iOS/CYZCCFoxEvent.mm|native トラッキングイベントのwrapper実装
iOS/CYZCCFoxIOSUtility.mm|utilメソッド
iOS/CYZCCFoxReengagePlugin.h|`appDelegate:openURL`のダイナミックオーバーライド定義
iOS/CYZCCFoxReengagePlugin.m|`appDelegate:openURL`のダイナミックオーバーライド実装


### 4. App Transport Securityについて

iOS9より提供されたAppTransportSecurity(以下、ATS)を有効にしている場合、Info.plistに以下の設定を行いF.O.X SDKが行う通信先のドメインをATSの例外としてください。

キー | タイプ | 概要
:---: | :---: | :---
`NSExceptionDomains`|Dictionary|ATSの例外を指定するディクショナリー
指定ドメイン文字列|Dictionary|以下２つのドメインをキーで作成してください。<br>・`app-adforce.jp`<br>・`forceoperationx.com`
`NSExceptionAllowsInsecureHTTPLoads`|Boolean|YES を指定してくださいATSの例外とします。
`NSIncludesSubdomains`|Boolean|YES を指定しATSの例外設定をサブドメインにも適用させます。

![ATS設定](./img_ats.png)

---
[戻る](../README.md#ios)

[TOP](../../../README.md)
