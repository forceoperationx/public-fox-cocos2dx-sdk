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
ANALYTICS_SERVER_URL  | String | 請將由Force Operation X管理者通知的數值輸入。<br />不利用流量分析的場合沒有必要設定


![Framework設定01](/lang/zh-tw/doc/integration/ios/config_plist/img05.png)

[SDK設定的詳細](/lang/zh-tw/doc/integration/ios/config_plist/README.md)

[AppAdForce.plist例子](/lang/zh-tw/doc/integration/ios/config_plist/AppAdForce.plist)

---
[TOP](/lang/zh-tw/README.md)
