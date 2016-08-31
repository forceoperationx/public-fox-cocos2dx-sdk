### Android Studioプロジェクトへの導入

Android StudioプロジェクトへFOX_Android_SDK_&lt;version&gt;.jarを追加する方法は以下の通りです。

* アプリケーションプロジェクトの「libs」フォルダー配下にFOX_Android_SDK_&lt;version&gt;.jarを配置します。


![integration01](./img01.png)

アプリケーションのモジュールディレクトリにあるbuild.gradleを開き、FOX_Android_SDK_&lt;version&gt;.jarへのパスを追記します。

```
dependencies {
	compile files('libs/FOX_Android_SDK_<version>.jar')
}
```

![integration02](./img02.png)

---
[Android TOP](/lang/ja/doc/integration/android/README.md)

[TOP](/lang/ja/README.md)
