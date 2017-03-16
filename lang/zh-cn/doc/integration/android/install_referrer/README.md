[TOP](../../../../README.md)　>　[Cocos2d-x plugin的导入步骤](../../README.md)　>　[Android项目设置](../README.md)　>　设置多个INSTALL_REFERRER RECEIVER

---

## 使多个INSTALL_REFERRER RECEIVER共存的设置

"com.android.vending.INSTALL_REFERRER"对应的receiver类只能定义一个。

F.O.X之外的SDK等，已经定义"com.android.vending.INSTALL_REFERRER"对应的receiver类时，可以使用F.O.X SDK的receiver类，调用其他receiver类来实现共存。

请编辑AndroidManifest.xml，添加以下的设置。

```xml
<!-- receiver类指定F.O.X SDK的类-->
<receiver
	android:name="co.cyberz.fox.FoxInstallReceiver"
	android:exported="true">
	<intent-filter>
		<action android:name="com.android.vending.INSTALL_REFERRER" />
	</intent-filter>
</receiver>

<!-- 用F.O.X SDK调用其他receiver类时信息记录为meta-data -->
<meta-data
		android:name="APPADFORCE_FORWARD_RECEIVER"
		android:value="com.example.InstallReceiver1|com.example.InstallReceiver2|com.example.InstallReceiver3" />
```

> `APPADFORCE_FORWARD_RECEIVER`中指定的类请附上package。可以用`|`(竖线)隔开多个类。

> 使用Proguard时，`APPADFORCE_FORWARD_RECEIVER`中的类指定为-keep且不要更改类名称。<br>
请注意，如果成为Proguard的对象，F.O.X SDK将无法正常搜索类。


---
[Android TOP](../README.md)

[TOP](../../../../README.md)
