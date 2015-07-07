## sendConversion 상세

sendConversion 메소드를 이용하여 설치 측정을 할 수 있습니다. Cookie 측정을 이용하는 경우에는 외부 브라우저가 시작됩니다. 이 때 외부 브라우저의 링크를 sendConversion의 인수에 URL문자열을 지정할 수 있습니다.

프로젝트의 소스 코드를 편집하고 응용 프로그램이 시작될 때 호출되는 화면의 AppDelegate:applicationDidFinishLaunching:메소드 같은 앱을 기동할 때 반드시 불리는 곳에 대해 다음과 같이 구현을해야합니다.

> 【주의】
sendConversion는 특별한 이유가없는 한 앱이 시작될 때 호출되는 AppDelegate:applicationDidFinishLaunching에 구현하십시오. 그 외에 구현된 경우에는 설치 횟수가 정확하게 측정되지 않을 수 있습니다.
앱이 시작될 때 호출되는 AppDelegate:applicationDidFinishLaunching 안에 구현하지 않은 상태에서 설치 성과형의 광고를 실시하는 경우에는 반드시 광고 대행사 또는 매체사의 담당자에게 그 사실을 알려주십시오. 정확하게 측정 할 수없는 상태에서 설치 성과형의 광고를 실시될 때 측정된 설치수 이상의 광고비의 지불을 요구하는 우려​​가 있습니다.

헤더 파일을 import

	#include "Cocos2dxFox.h"

성과 통지의 코드를 추가

	FoxPlugin::sendConversion("default");

sendConversion의 인수는 일반적으로 위와 같이 "default"라는 문자열을 입력하십시오. 기본적으로 표준으로 준비된 페이지가 표시되지만 링크URL을 F.O.X 관리 화면에서 임의로 설정할 수 있습니다.


특정 URL에 랑크시키고 싶은 경우나 앱에서 동적으로 URL을 생성하고자하는 경우에는 URL문자열을 설정하십시오.

	FoxPlugin::sendConversion("http://yourhost.com/yourpage.html");


sendConversion 메소드의 두 번째 인수에 광고주 단말 ID를 전달할 수 있습니다. 예를 들어 앱 시작시 UUID를 생성하고 초기기동의 성과와 연결하여 관리하고 싶은 경우 등에 사용할 수 있습니다.


	FoxPlugin::sendConversion("default", "your unique id");

> sendConversion는 기동 직후의 처리로써 구현될 필요가 있기 때문에 로그인 ID등의 유저 액션이 동반하는 값을 인수로 전달할 수 없습니다.