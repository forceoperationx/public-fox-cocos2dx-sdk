## 최신 버전으로 업데이트 정보

이전 버전의 F.O.X SDK가 도입된 앱에 대한 최신 버전의 F.O.X SDK를 도입하는데 필요한 단계를 설명합니다.

1. 이전 버전의 파일이 프로젝트에 포함되어 있으면 모두 삭제합니다
2. 최신 버전의 파일을 프로젝트에 추가합니다
3. iOS의 경우 Xcode의 「Product」→「Clean」을 실행

F.O.X iOS SDK v2.12 이상에서는 라이브러리 파일은 libAppAdForce.a만 제공됩니다. v2.11 이전은 개별적으로 분리된 라이브러리는 모든 libAppAdForce.a에 포함됩니다. 업데이트시 아래의 파일이 포함되어있는 경우에는 모두 삭제하십시오.

* libLtv.a
* libAnalytics.a
* libNotify.a


v2.14부터 Android에서는 광고 ID에 대응하고 있습니다.
광고 ID를 취득하는 경우는 「[광고 ID를 이용하기위한 Google Play Services SDK의 도입](../google_play_services/README.md)」를 확인하십시오.

또한 v2.14부터 Engagement계측 기능이 추가되어 있습니다.
Engagement측정을 실시하는 iOS 앱의 경우는 FoxReengagePlugin.m/h를 프로젝트에 추가하십시오.Android 앱의 경우는 「Engagement 계측 구현」을 확인하고 구현합니다.

SDK 업데이트 후에는 반드시 효과 측정 테스트를 실시하고 계측 및 앱의 작동에 문제가 없음을 확인하십시오.
또한 Engagement측정을 실시하는 경우는 Engagement측정을 위한 테스트를 실시해야합니다.