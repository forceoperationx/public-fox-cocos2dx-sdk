## (옵션)관리화면에서 등록한 번들 버전에 따른 처리의 배분

F.O.X 관리 화면에 등록되어있는 버전과 실행중의 앱의 버전과 일치하는지 여부에 따라 처리를 배분 할 수 있습니다. 이 기능을 이용하면, 예를 들어 릴리스 중과 테스트중인 버전의 처리의 배분을 F.O.X를 이용하여 제어, 테스트중 인 것만 특정 처리를 실행 하는것이 가능합니다.
이 기능의 구현은 필수는 아닙니다.

또한 F.O.X에서 사용하는 번들 버전은 CFBundleShortVersionString에 해당하는 값입니다.


번들 버전에 따른 처리의 배분을 하려면 checkVersionWithDelegate() 메소드를 이용합니다. 버전체크의 문의를 F.O.X 서버에 대해 행하여, 결과를 수신하면 didLoadVersion()가 호출됩니다. delegate메소드 didLoadVersion()를 구현해 주십시오.
didLoadVersion()의 호출시에 관리화면에 등록한 번들버전이 실행중인 앱의 버전과 일치하는지 여부의 판정 결과를 인수로 전달합니다. 일치 한 경우에는 "YES", 일치하지 않은 경우에는 "NO"를 반환합니다.


이하, 본 기능의 구현 예입니다.
checkVersionWithDelegate() 메서드를 호출하여 서버에 질의를 하고 있습니다.

```c#
FoxPlugin.setListenerGameObject(this.gameObject.name);
FoxPlugin.checkVersionWithDelegate();
```

delegate메소드인 didLoadVersion()를 구현합니다.

```c#
public void didLoadVersion(string result)
{
	// 일치하지 않는 경우(예를 들어 테스트중인 버전)의 처리의 설명.
	if (result=="NO") {
		....
	}
}
```

>이 메소드에 의한 F.O.X 서버에 대한 질문은 부하 경감을 위한 1클라이언트에서 각 버전마다 5회까지로 제한됩니다. 5회를 초과하면 서버에 쿼리하지 않고 didLoadVersion()이 호출되지 않습니다. 번들버전을 업데이트하여 다시 5회를 상한으로 서버에 요청이 이루어집니다.