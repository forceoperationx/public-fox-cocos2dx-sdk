## （任意）登錄到管理畫面的BundleVersion相對應的不同處理

通過登錄在F.O.X管理畫面裡的版本和執行中APP的版本做比較，能夠依照版本是否一致來執行不同處理。
F.O.X可以利用這個機能來實現控制發布版本和測試版本做不同處理，或者只在測試版本裡才執行某些特定處理等任務。
使用本機能不需要安裝。

此外，F.O.X裡使用的BundleVersion相當於CFBundleShortVersionString的值。

為實現對BundleVersion來做相應的處理，需要利用`checkVersionWithDelegate()`方法。
服務器會接收和處理BundleVersion的查詢，一收到結果就會調用didLoadVersion()。請安裝Delegate方法didLoadVersion()。
調用didLoadVersion()時，能夠判別管理畫面裡登錄的BundleVersion和運行APP的BundelVersion是否一致。一致的場合返回YES，不一致的場合返回NO。

下面是這個機能的安裝例子。調用CheckVersionDelegate()方法在服務器做查詢。

```cs
FoxPlugin.setListenerGameObject(this.gameObject.name);
FoxPlugin.checkVersionWithDelegate();
```

安裝Delegate方法didLoadVersion()。

```cs
public void didLoadVersion(string result)
{
	// 記述了不一致的場合(例如測試中的Version)的處理。
	if (result=="NO") {
		....
	}
}
```

> 用這個方法在F.O.X服務器做查詢，為了減輕負荷，一個用戶每個版本最大5回。超過5回將不能在服務器做查詢，或者說didLoadVersion()不被調用。如果更新了BundleVersion可以在服務器再做5回查詢。

---
[iOS TOP](../README.md)
