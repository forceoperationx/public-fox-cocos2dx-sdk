# iOS項目的設定

## **Xcode項目的設定**

### Xcode項目的編輯

打開並編輯發行的Xcode項目。

* **Framework設定**

請把下面的Framework追加到開發項目裡。

<table>
<tr><th>Framework名</th><th>Status</th></tr>
<tr><td>SafariServices.framework</td><td>Optional</td></tr>
<tr><td>AdSupport.framework</td><td>Optional</td></tr>
<tr><td>iAd.framework </td><td>Required</td></tr>
<tr><td>Security.framework </td><td>Required </td></tr>
<tr><td>StoreKit.framework </td><td>Required </td></tr>
</table>

> ※SafariServices.framework是在iOS 9之後被追加的Framework，如果要讓APP在iOS 8之前版本也能運行（將iOS Deployment Target設定為8.4以下），為了設定為weak link，請修改設置為”Optional”

![Framework設定01](/lang/zh-tw/doc/integration/ios/config_framework/img01.png)

[Framework設定的詳細](/lang/zh-tw/doc/integration/ios/config_framework/README.md)

* **SDK設定**

追加必要的設定到plist裡讓SDK發揮作用。新建「AppAdForce.plist」這樣一個Property List文件放到項目的任意一個地方，並輸入下面的Key和Value。

Key | Type | Value
:---: | :---: | :---
APP_ID | String | 請將由Force Operation X管理者通知的數值輸入。
SERVER_URL | String | 請將由Force Operation X管理者通知的數值輸入。
APP_SALT | String | 請將由Force Operation X管理者通知的數值輸入。
APP_OPTIONS | String | 請空白。
CONVERSION_MODE | String | 請輸入1
ANALYTICS_APP_KEY | String | 請將由Force Operation X管理者通知的數值輸入。<br />不利用流量分析的場合沒有必要設定


![Framework設定01](/lang/zh-tw/doc/integration/ios/config_plist/img05.png)

* **關於App Transport Security**

由iOS9提供的AppTransportSecurity(下面稱做ATS)設定為有效的時候、請在Info.plist裡做如下設定，把F.O.X SDK使用的通信域名設置為ATS的例外。

Key | Type | 概要
:---: | :---: | :---
NSExceptionDomains|Dictionary|指定ATS例外的dictionary
指定的域名字符串|Dictionary|請把下面兩個域名做成Key。<br>・app-adforce.jp<br>・forceoperationx.com
NSExceptionAllowsInsecureHTTPLoads|Boolean|請指定成YES，設置成ATS的例外。
NSIncludesSubdomains|Boolean|指定成YES，把ATS的例外設定也適用到子域名。

![ATS設定](/lang/zh-tw/doc/integration/ios/config_plist/img06.png)

[SDK設定的詳細](/lang/zh-tw/doc/integration/ios/config_plist/README.md)

[AppAdForce.plist例子](/lang/zh-tw/doc/integration/ios/config_plist/AppAdForce.plist)


**在iOS9環境導入的注意點**

> Cookie計測を実施する際に、iOS9ではSFSafariViewControllerが使用します。 F.O.X Unity SDK v2.16以降では、SFSafariViewController起動後の制御をFoxReengagePluginで行うため導入が必須となります。
> 進行Cookie計測的時候，在iOS9環境裡使用SFSafariViewController。
F.O.X Unity SDK v2.16及以後版本，是靠FoxReengagePlugin做SFSafariViewController啟動後的控制，所以必須導入。

> これまで外されていた場合には、本Unity SDKのunitypackageファイルに同梱のFoxReengagePluginをご導入ください。
> 如果到此都沒有安裝，請導入同捆的FoxReengagePlugin到這個Unity SDK的unitypackage文件裡。

### 其他

* [登錄到管理畫面的BundleVersion相對應的不同處理](./check_version/README.md)

---
[TOP](/lang/zh-tw/README.md)
