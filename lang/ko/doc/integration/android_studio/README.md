### Android Studio 프로젝트에 도입

Android Studio 프로젝트에 FOX_Android_SDK_&lt;version&gt;.jar을 추가하는 방법은 다음과 같습니다.

* 앱 프로젝트 「libs」폴더 아래에 FOX_Android_SDK_&lt;version&gt;.jar을 배치합니다.


![integration01](./img01.png)

앱의 모듈 디렉토리에있는 build.gradle을 열고 FOX_Android_SDK_&lt;version&gt;.jar에 경로를 추가합니다.

```
dependencies {
	compile files('libs/FOX_Android_SDK_<version>.jar')
}
```

![integration02](./img02.png))

---
[TOP](/lang/ko/README.md)
