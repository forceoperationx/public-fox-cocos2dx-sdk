# F.O.X SDK の削除確認方法
<div id="delete_unity"></div>

# Cocos-2dx

## ライブラリの削除

以下のF.O.XのSDKに含まれるファイルがある場合は削除してください。

[F.O.X Cocos2d-x SDK 4.X](https://github.com/forceoperationx/public-fox-cocos2dx-sdk/blob/4.x/lang/ja/doc/integration/README.md)

[F.O.X Cocos2d-x SDK 3.X](https://github.com/forceoperationx/public-fox-cocos2dx-sdk/blob/3.x/lang/ja/doc/integration/README.md)

### iOSの場合

以下のファイルがある場合は削除してください。

- `CYZFox.framework`
- `libFoxSdk.a` 
- `AdManager.h`
- `Ltv.h`
- `AnalyticsManager.h`

F.O.Xにて追加したフレームワークで他で利用していないものを削除してください

[iOSプロジェクトの設定 4.X](https://github.com/forceoperationx/public-fox-cocos2dx-sdk/blob/4.x/lang/ja/doc/integration/ios/README.md)

[iOSプロジェクトの設定 3.X](https://github.com/forceoperationx/public-fox-cocos2dx-sdk/blob/3.x/lang/ja/doc/integration/README.md)

### Androidの場合

`build.gradle`に以下の設定がある場合は削除してください。

#### F.O.X 4.X

```gradle
repositories {
    maven {
        url "https://github.com/forceoperationx/public-fox-android-sdk/raw/master/mavenRepo"
    }
}

dependencies {
    implementation 'co.cyberz.fox:track-core:{VERSION}'
}
```

```gradle
dependencies {
	implementation files('libs/foxtrack-core_{VERSION}.jar')
}
```

#### F.O.X 3.X

```gradle
repositories {
    maven {
        url "https://github.com/cyber-z/public-fox-android-sdk/raw/master/mavenRepo"
    }
}

dependencies {
    compile 'co.jp.cyberz.fox:sdk-android:X.X.X'
}
```

以下で追加した設定で不要なものを削除してください。

[Android プロジェクトの詳細設定 4.X](https://github.com/forceoperationx/public-fox-cocos2dx-sdk/blob/4.x/lang/ja/doc/integration/android/README.md)

[Androidプロジェクトの設定 3.X](https://github.com/forceoperationx/public-fox-cocos2dx-sdk/blob/3.x/lang/ja/doc/integration/android/README.md)

## コード/その他ファイル全体

F.O.Xでの計測のために追加したコードを削除してください。

また、コード/ファイル全体を対象に、以下の単語を検索し、含まれてる場合は適宜削除してください。
大文字小文字の区別なしで検索してください。

- `FOX`
- `F.O.X`
- `forceoperationx`
- `app-adforce`
- `appadforce`
- `cyberz`
- `cyber-z`
- `cyz`

