## Framework設定的詳細

點擊編譯對象，「Build Phases」→選擇「Link Binary With Libraries」。點擊「＋」按鈕，請選擇各Framework。

![Framework設定01](./img01.png)

請把下面的Framework追加到開發項目裡。

<table>
<tr><th>Framework名</th><th>Status</th></tr>
<tr><td>AdSupport.framework</td><td>Optional</td></tr>
<tr><td>iAd.framework </td><td>Required</td></tr>
<tr><td>Security.framework </td><td>Required </td></tr>
<tr><td>StoreKit.framework </td><td>Required </td></tr>
<tr><td>SystemConfiguration.framework </td><td>Required </td></tr>
</table>

![Framework設定02](./img02.png)

---
[iOS TOP](../README.md)
