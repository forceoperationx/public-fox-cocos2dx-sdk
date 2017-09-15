### Android Studioプロジェクトへの導入

Android StudioプロジェクトへFOX_Android_SDK_&lt;version&gt;.jarとFOX_Android_SDK_Cocos2dx.jarを追加する方法は以下の通りです。

* アプリケーションプロジェクトの「libs」フォルダー配下にFOX_Android_SDK_&lt;version&gt;.jarとFOX_Android_SDK_Cocos2dx.jarを配置します。


![integration01](./img01.png)

アプリケーションのモジュールディレクトリにあるbuild.gradleを開き、FOX_Android_SDK_&lt;version&gt;.jarとFOX_Android_SDK_Cocos2dx.jarへのパスを追記します。

```
dependencies {
	compile files('libs/FOX_Android_SDK_<version>.jar')
	compile files('libs/FOX_Android_SDK_Cocos2dx.jar')
}
```

![integration02](./img02.png)

---
[Android TOP](/lang/ja/doc/integration/android/README.md)

[TOP](/lang/ja/README.md)
