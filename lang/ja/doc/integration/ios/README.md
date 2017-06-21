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
SystemConfiguration.framework|Required
WebKit.framework|Required


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
iOS/CYZFoxAppDelegateSwizzling.m|protocol`AppDelegate`の`application:openURL:sourceApplication:`と`application:openURL:options`のダイナミックオーバーライド定義



### 4. App Transport Securityについて

F.O.X SDK ver4.0.0からは計測における全ての通信をHTTPSを利用して行うため、追加で対応を行う必要はありません。

---
[戻る](../README.md#ios)

[TOP](../../../README.md)
