## sendLtvConversion 상세

sendLtvConversion 메소드를 이용하여 광고 유입별의 과금 금액 및 가입 횟수 등을 측정 할 수 있습니다. 측정을 위해 임의의 지점에 LTV 성과통신을 하는 코드를 추가합니다.

소스 편집은 성과가 오른 후에 실행되는 스크립트 처리를 설명합니다. 예를 들어 회원 가입이나 앱 내 과금 후 과금측에서는 등록·과금 처리 실행 후 콜백내에 LTV 측정 처리를 설명합니다.

성과가 앱 내부에서 발생하는 경우 성과 처리부에 아래와 같이 설명합니다.

헤더 파일을 import

```cpp
	#include "Cocos2dxFox.h"
```

성과 통지 코드를 추가

```cpp
	FoxPlugin::sendLtv(성과 지점 ID);
```

> 성과 지점 ID (필수) : 관리자가 연락합니다. 그 값을 입력하십시오.
※ Android Cocos2dx SDK v2.10.4g 이전 해외판/글로벌 버전 SDK (버전끝이 u 또는 g)에서 SDK를 업데이트하려면 반드시 「v2.10.4g 이전의 업데이트 지침」의 단계를 추가 하십시오.


앱 내부의 성과에 광고주 단말 ID (회원 ID 등)를 포함 할 수 있으며 이를 기준으로 한 성과 측정을 할 수 있습니다. LTV 성과에 광고주 단말 ID를 부여하려면 다음과 같이 설명합니다.

```cpp
	FoxPlugin::sendLtv(성과 지점 ID, "광고주 단말 ID");
```

> 성과 지점 ID(필수) : 관리자가 연락합니다. 그 값을 입력하십시오.
광고주 단말 ID(옵션) : 광고주가 관리하는 고유 식별자(회원 ID등)입니다.
지정할수 있는 값은 64자 이내의 영숫자입니다.


앱 내 에서 측정시에는 매개 변수를 옵션으로 설정하는 것이 가능합니다.

```cpp
	FoxPlugin::addParameter("매개 변수명", "값");
```

지정할 수있는 매개 변수는 다음과 같습니다.

|매개 변수명|개요|
|:------|:------|
|CC_LTV_PARAM_SKU|Stock Keeping Unit(상품 관리 코드)<br>(영숫자 32문자까지)<br>상품의 재고 관리를 할 때 사용하십시오|
|CC_LTV_PARAM_PRICE|Price<br>(정수값 일본 엔)<br>매출액을 관리하는데 사용하십시오.|
|CC_LTV_PARAM_CURRENCY|Currency<br>(반각 영문자 3자의 통화 코드)<br>통화별로 과금액을 집계 할 때 사용합니다.<br>통화가 설정되어 있지 않은 경우 Price를 JPY (일본 엔)로 처리합니다.|
|임의로 매개 변수를 추가하는 것도 가능합니다.|FoxPlugin::addParameter("매개변수 명", "값");<br>※1 동일한 매개 변수 이름을 작성하는 경우는 후자가 활성화됩니다. <br> ※ 2 밑줄( "_")를 매개 변수 이름 앞에 넣지마십시오. <br> ※ 3 영숫자 이외는 사용할 수 없습니다.|

CC_LTV_PARAM_CURRENCY은[ISO 4217](http://ja.wikipedia.org/wiki/ISO_4217)에서 정의된 통화 코드를 지정하십시오.

설정 예 :

```cpp
FoxPlugin::addParameter(CC_LTV_PARAM_SKU, “ABC1234”);
FoxPlugin::addParameter(CC_LTV_PARAM_PRICE, “2000”);
FoxPlugin::addParameter(“my_param”, “ABC”);
FoxPlugin::sendLtv(70, “Taro”);
```

	---
[TOP](../../README.md)
