## 프레임 워크 설정에 대한 상세

빌드 대상 대상을 클릭하고 「Build Phases」→「Link Binary With Libraries」를 선택합니다. "+"버튼을 눌러 각 프레임 워크를 선택하십시오.

![프레임 워크 설정 01](https://github.com/cyber-z/public_fox_ios_sdk/raw/master/doc/config_framework/ja/img01.png)

다음 프레임 워크를 프로젝트에 연결하십시오.

<table>
<tr><th>프레임워크명</th><th>Status</th></tr>
<tr><td>AdSupport.framework</td><td>Optional</td></tr>
<tr><td>iAd.framework </td><td>Required</td></tr>
<tr><td>Security.framework </td><td>Required </td></tr>
<tr><td>StoreKit.framework </td><td>Required </td></tr>
<tr><td>SystemConfiguration.framework </td><td>Required </td></tr>
</table>

> AdSupport.framework은 iOS 6 이상에서 추가된 프레임 워크를 위해 앱을 iOS 5 이하에서도 작동시키는 (iOS Deployment Target을 5.1 이하로 설정) 경우에는 weak link를 실행하기 위해 "Optional"로 설정 하십시오.

![프레임 워크 설정 02](https://github.com/cyber-z/public_fox_ios_sdk/raw/master/doc/config_framework/ja/img02.png)


---
[TOP](../../README.md)
