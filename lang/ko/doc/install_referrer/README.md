## 여러 INSTALL_REFERRER receiver를 공존시키는 경우의 설정

"com.android.vending.INSTALL_REFERRER"에 대한 receiver클래스는 하나만 정의할수 있습니다.

F.O.X 이외의 SDK등 이미 "com.android.vending.INSTALL_REFERRER"에 대한 receiver클래스가 정의되어있는 경우, F.O.X SDK를 제공하고 있는 receiver클래스에서 다른 receiver클래스를 호출하여 공존시키는것이 가능합니다.

### 두개의 INSTALL_REFERRER receiver를 공존시키는 경우

AndroidManifest.xml을 편집하고 아래 설정을 추가하십시오.

```xml
<!-- receiver 클래스는 F.O.X SDK의 클래스를 지정합니다 -->
<receiver
  android:name="jp.appAdForce.android.InstallReceiver"
  android:exported="true">
  <intent-filter>
    <action android:name="com.android.vending.INSTALL_REFERRER" />
  </intent-filter>
</receiver>

<!-- F.O.X SDK에서 호출하고 싶은 다른 receiver클래스 정보를 meta-data로써 설명합니다 -->
<meta-data
  android:name="APPADFORCE_FORWARD_RECEIVER"
  android:value="com.example.InstallReceiver" />
```

### 세 이상의 INSTALL_REFERRER receiver를 공존시키는 경우

세 개 이상의 receiver를 통합할때는 하나의 축이되는 receiver클래스를 정의하고 그 클래스 내에서 직렬로 각 receiver를 호출하도록 합니다.

아래에 구현 예를 기재합니다.

* MyReceiver 클래스(클래스명은 아무거나 하셔도 상관하지 않습니다)

```java
public class MyReceiver extends BroadcastReceiver {
  // F.O.X INSTALL_REFERRER receiver
   jp.appAdForce.android.InstallReceiver foxReceiver;

   // F.O.X이외의 INSTALL_REFERRER receiver
   jp.co.android.sample.InstallReceiver thirdPartyReceiver;
   jp.co.android.sample.InstallReceiver2 thirdPartyReceiver2;

   public MyReceiver() {
      foxReceiver = new jp.appAdForce.android.InstallReceiver();
      thirdPartyReceiver = new jp.co.android.sample.InstallReceiver();
      thirdPartyReceiver2 = jp.co.android.sample.InstallReceiver2();
   }
   @Override
   public void onReceive(Context context, Intent intent){
       foxReceiver.onReceive(context, intent);

       thirdPartyReceiver.onReceive(context, intent);

       thirdPartyReceiver2.onReceive(context, intent);
   }
}
```

* AndroidManifest.xml

```xml
<receiver
       android:name="jp.co.sample.android.receiver.MyReceiver"
       android:exported="true" >
       <intent-filter>
            <action android:name="com.android.vending.INSTALL_REFERRER" />
       </intent-filter>
</receiver>
```