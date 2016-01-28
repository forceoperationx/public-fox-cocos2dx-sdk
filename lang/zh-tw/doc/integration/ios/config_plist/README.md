## SDK設定的詳細

在plist裡追加必要的設定讓SDK發揮作用。新建「AppAdForce.plist」這樣一個Property List文件放到項目的任意一個地方，並輸入下面的Key和Value。

在任意地點點擊右鍵→選擇「New File...」

![SDK設定01](./img01.png)

「Property List」を選択。

![SDK設定02](./img02.png)

變更成「AppAdForce.plist」這個名稱、點擊Create按鈕。

![SDK設定03](./img03.png)

選擇新建的Property List文件，用右鍵打開菜單，選擇Add Row」

![SDK設定04](./img04.png)

設定各個Key和Value。

![SDK設定05](./img05.png)

設定的Key和Value如下。

<table>
<tr>
  <th>Key</th>
  <th>Type</th>
  <th>Value</th>
</tr>
<tr>
  <td>APP_ID</td>
  <td>String</td>
  <td>請將由Force Operation X管理者通知的數值輸入。</td>
</tr>
<tr>
  <td>SERVER_URL</td>
  <td>String</td>
  <td>請將由Force Operation X管理者通知的數值輸入。</td>
</tr>
<tr>
  <td>APP_SALT</td>
  <td>String</td>
  <td>請將由Force Operation X管理者通知的數值輸入。</td>
</tr>
<tr>
  <td>APP_OPTIONS</td>
  <td>String</td>
  <td>請空白。</td>
</tr>
<tr>
  <td>CONVERSION_MODE</td>
  <td>String</td>
  <td>1</td>
</tr>
<tr>
  <td>ANALYTICS_APP_KEY</td>
  <td>String</td>
  <td>請將由Force Operation X管理者通知的數值輸入。<br />不利用流量分析的場合沒有必要設定</td>
</tr>
</table>

[AppAdForce.plist範例](/lang/zh-tw/doc/integration/ios/config_plist/AppAdForce.plist)

---
[iOS TOP](../README.md)
