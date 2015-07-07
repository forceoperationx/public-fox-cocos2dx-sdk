## SDK 설정의 상세

SDK의 동작에 필요한 설정을 plist에 추가합니다. 「AppAdForce.plist」라는 명칭의 속성 목록 파일을 프로젝트의 임의의 위치에 생성하고 다음의 키와 값을 입력하십시오.

임의의 장소에 오른쪽 클릭 → 「New File...」을 선택

![SDK설정01](./img01.png)

「Property List」를 선택

![SDK설정02](./img02.png)

「AppAdForce.plist」라는 명칭으로 변경, Create 버튼을 클릭합니다.

![SDK설정03](./img03.png)

만든 속성 목록 파일을 선택합니다. 오른쪽 클릭 메뉴를 열고 「Add Row」를 선택

![SDK설정04](./img04.png)

각 key와 value를 설정

![SDK설정05](./img05.png)

설정한 key와 value는 아래와 같습니다.

<table>
<tr>
  <th>Key</th>
  <th>Type</th>
  <th>Value</th>
</tr>
<tr>
  <td>APP_ID</td>
  <td>String</td>
  <td>Force Operation X 관리자가 연락합니다. 그 값을 입력하십시오.</td>
</tr>
<tr>
  <td>SERVER_URL</td>
  <td>String</td>
  <td>Force Operation X 관리자가 연락합니다. 그 값을 입력하십시오.</td>
</tr>
<tr>
  <td>APP_SALT</td>
  <td>String</td>
  <td>Force Operation X 관리자가 연락합니다. 그 값을 입력하십시오.</td>
</tr>
<tr>
  <td>APP_OPTIONS</td>
  <td>String</td>
  <td>아무것도 입력하지 마시고 빈문자의 상태로 해 주십시오.</td>
</tr>
<tr>
  <td>CONVERSION_MODE</td>
  <td>String</td>
  <td>1</td>
</tr>
<tr>
  <td>ANALYTICS_APP_KEY</td>
  <td>String</td>
  <td>Force Operation X 관리자가 연락합니다. 그 값을 입력하십시오.<br />액세스 해석을 이용하지 않으면 설정은 필요 없습니다.</td>
</tr>
</table>

[AppAdForce.plist 샘플](./AppAdForce.plist)