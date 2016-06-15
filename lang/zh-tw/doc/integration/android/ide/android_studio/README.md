### AndroidStudio項目的導入方法

將AppAdForce.jar添加到Android Studio項目的方法如下。

* 設定AppAdForce.jar到APP項目「libs」文件夾下。

![integration01](./img01.png)

打開APP的Module Directory裡的build.gradle，添加訪問AppAdForce.jar的路徑。

```
dependencies {
	compile files('libs/AppAdForce.jar')
}
```

![integration02](./img02.png)

---
[Android TOP](../../README.md)
