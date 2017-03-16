[TOP](../../../../README.md)　>　[Cocos2d-xplugin导入步骤](../../README.md)　>　[Android项目设置](../README.md)　>　使用自动备份功能提高排重精度

---

# 使用自动备份功能提高排重精度

Android M(6.0)追加的自动备份功能可以提高排除重复的效果。本功能为任意选项。

## 适用条件

* 仅限从Android M的终端向Android M及以上的终端恢复备份数据。
* 备份时和恢复时，登录终端的Google账号必须为同一个。
* 传承数据时必须遵照下图那样，用户在终端将相关选项设置为有效。

![设置界面](./img01.png)

## 设置

　使用本功能时，必须根据APP的备份设置文件情况来进行设置。

> [设置参考](https://developer.android.com/training/backup/autosyncapi.html)

**[备份个别指定的APP数据]**

　请设置将以下文件包含在备份对象中。

```
<include domain="file" path="__ADMAGE_RANDOM_DEVICE_ID__" />
```

**[备份所有APP数据]**

　设置备份所有APP数据时，请移除以下文件。

```
<exclude domain="file" path="__ADMAGE_WEB_CONVERSION_COMPLETED__" />
<exclude domain="file" path="__ADMAGE_APP_CONVERSION_COMPLETED__" />
```

---
[Android TOP](../README.md)

[TOP](../../../../README.md)
