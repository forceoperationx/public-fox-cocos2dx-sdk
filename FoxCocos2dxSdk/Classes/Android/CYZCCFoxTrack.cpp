// F.O.X SDK
// CYZCCFox.cpp
//
// Created by T.Hiraga
//
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "../CYZCCFox.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include <string>
#include <string.h>
#include "FoxNativeTrackListener.h"
#include "util/CYZCCFoxUtil.h"

using namespace cocos2d;
using namespace rapidjson;

namespace fox {

  void CYZCCFox::init(CYZCCFoxConfig config) {

    jobject ctx = CYZCCFoxUtil::getContext();
    JniMethodInfo minfo;
    bool exists = JniHelper::getStaticMethodInfo(
                                                  minfo,
                                                  "co.cyberz/fox/support/cocos2dx/Fox",
                                                  "init",
                                                  "(Landroid/content/Context;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V"
                                                );
    if (exists) {
      int appId = config.appId_android;
      jstring appKey = minfo.env->NewStringUTF(config.appKey_android);
      jstring appSalt = minfo.env->NewStringUTF(config.salt_android);
      jstring foxServerURL = minfo.env->NewStringUTF(config.foxServerURL);
      jstring analyticsServerURL = minfo.env->NewStringUTF(config.analyticsServerURL);
      jboolean isDebug = (jboolean)config.debugMode;
      minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, ctx, appId, appKey, appSalt, foxServerURL, analyticsServerURL, isDebug);
    }
  }

  void CYZCCFox::trackInstall() {
    JniMethodInfo minfo;
    bool exists = JniHelper::getStaticMethodInfo(
                                                  minfo,
                                                  "co.cyberz/fox/support/cocos2dx/Fox",
                                                  "trackInstall",
                                                  "()V"
                                                );
    if (exists) {
      minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
  }


  FoxNativeTrackListener* CYZCCFox::foxTracklistener;

  void CYZCCFox::trackInstall(CYZCCFoxTrackOption option) {
    JniMethodInfo minfo;
    bool exists = JniHelper::getStaticMethodInfo(
                                                  minfo,
                                                  "co.cyberz/fox/support/cocos2dx/Fox",
                                                  "trackInstall",
                                                  "(Ljava/lang/String;Ljava/lang/String;ZJ)V"
                                                );
    if (exists) {
      jstring redirectUrl = minfo.env->NewStringUTF(option.redirectURL);
      jstring buid = minfo.env->NewStringUTF(option.buid);
      jboolean isOptOut = (jboolean)option.optout;
      CYZCCFox::foxTracklistener = new FoxNativeTrackListener(option.onInstallComplete);
      jlong test = (jlong)(unsigned long long) CYZCCFox::foxTracklistener;
      minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, redirectUrl, buid, isOptOut, test);
    }
  }

  void CYZCCFox::trackSession() {
    JniMethodInfo minfo;
    bool exists = JniHelper::getStaticMethodInfo(
                                                  minfo,
                                                  "co.cyberz/fox/support/cocos2dx/Fox",
                                                  "trackSession",
                                                  "()V"
                                                );
    if (exists) {
      minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID);
    }
  }

  /**
   *
   */
  void CYZCCFox::trackEvent(CYZCCFoxEvent* event) {
    if (event == nullptr) return;
    JNIEnv *env = JniHelper::getEnv();
    int ltvId = event->ltvId;
    jstring buid = env->NewStringUTF(event->buid);
    jdouble price = (jdouble) event->price;
    jstring sku = env->NewStringUTF(event->sku);
    jstring currency = env->NewStringUTF(event->currency);
    jstring eventName = env->NewStringUTF(event->eventName);
    int value = event->value;
    jstring orderId = env->NewStringUTF(event->orderId);
    jstring itemName = env->NewStringUTF(event->itemName);
    int quantity = event->quantity;
    const char* cEventInfo = event->getEventInfoStr();
    jstring eventInfo = env->NewStringUTF(cEventInfo);
    const char* cExtraInfo = event->getExtraInfoStr();
    jstring extraInfo = env->NewStringUTF(cExtraInfo);

    JniMethodInfo minfo;
    std::string args;
    args.append("(")
        .append("I")                  // ltvId
        .append("Ljava/lang/String;") // buid
        .append("D")                  // price
        .append("Ljava/lang/String;") // sku
        .append("Ljava/lang/String;") // currency
        .append("Ljava/lang/String;") // eventName
        .append("I")                  // value
        .append("Ljava/lang/String;") // orderId
        .append("Ljava/lang/String;") // itemName
        .append("I")                  // quantity
        .append("Ljava/lang/String;") // eventInfo
        .append("Ljava/lang/String;") // extraInfo
        .append(")V");

    bool exists = JniHelper::getStaticMethodInfo(
                                                  minfo,
                                                  "co.cyberz/fox/support/cocos2dx/Fox",
                                                  "trackEvent",
                                                  args.c_str()
                                                );
    if (exists) {
      CCLOG("CYZCCFox - getExtraInfoStr3");
      minfo.env->CallStaticVoidMethod(minfo.classID,
                                      minfo.methodID,
                                      ltvId,
                                      buid,
                                      price,
                                      sku,
                                      currency,
                                      eventName,
                                      value,
                                      orderId,
                                      itemName,
                                      quantity,
                                      eventInfo,
                                      extraInfo);
    }
  }

  /**
   *
   */
  void CYZCCFox::trackEventByBrowser(const char* url) {
    JniMethodInfo minfo;
    bool exists = JniHelper::getStaticMethodInfo(
                                                  minfo,
                                                  "co.cyberz/fox/support/cocos2dx/Fox",
                                                  "trackEventByBrowser",
                                                  "(Ljava/lang/String;)V"
                                                );
    if (exists) {
      jstring jUrl = minfo.env->NewStringUTF(url);
      minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, jUrl);
    }
  }

  bool CYZCCFox::isConversionCompleted() {
    JniMethodInfo minfo;
    bool exists = JniHelper::getStaticMethodInfo(
                                                  minfo,
                                                  "co.cyberz/fox/support/cocos2dx/Fox",
                                                  "isConversionCompleted",
                                                  "()Z"
                                                );
    if (exists) {
      return minfo.env->CallStaticBooleanMethod(minfo.classID, minfo.methodID);
    }
  }

  bool CYZCCFox::getUserInfo(rapidjson::Document& userInfo) {
    JniMethodInfo minfo;
    bool exists = JniHelper::getStaticMethodInfo(
                                                  minfo,
                                                  "co.cyberz/fox/support/cocos2dx/Fox",
                                                  "getUserInfo",
                                                  "()Ljava/lang/String;"
                                                );
    if (exists) {
      jstring jUserInfoStr = (jstring) minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
      const char* cUserInfo = minfo.env->GetStringUTFChars(jUserInfoStr, nullptr);
      if (!userInfo.Parse(cUserInfo).HasParseError()) {
        return true;
      }
    }
    return false;
  }

  void CYZCCFox::setUserInfo(rapidjson::Document& userInfo) {
    rapidjson::Document* docPtr = &userInfo;
    const char* cUserInfo = CYZCCFoxUtil::json2char(docPtr);
    JniMethodInfo minfo;
    bool exists = JniHelper::getStaticMethodInfo(
                                                  minfo,
                                                  "co.cyberz/fox/support/cocos2dx/Fox",
                                                  "setUserInfo",
                                                  "(Ljava/lang/String;)V"
                                                );
    if (exists && cUserInfo != nullptr) {
      jstring userInfoStr = minfo.env->NewStringUTF(cUserInfo);
      minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, userInfoStr);
    }
  }

}
#endif
