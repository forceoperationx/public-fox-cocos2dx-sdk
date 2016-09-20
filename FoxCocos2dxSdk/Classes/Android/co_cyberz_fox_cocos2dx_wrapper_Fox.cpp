// F.O.X SDK
// co_cyberz_fox_cocos2dx_wrapper_Fox.cpp
//
// Created by T.Hiraga
//
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <jni.h>
#include "co_cyberz_fox_cocos2dx_wrapper_Fox.h"
#include "FoxNativeTrackListener.h"
#include "../CYZCCFox.h"

using namespace cocos2d;

JNIEXPORT void JNICALL Java_co_cyberz_fox_cocos2dx_wrapper_Fox_onCompleted
  (JNIEnv * env, jobject thiz, jlong delegate) {
    FoxNativeTrackListener* listener = reinterpret_cast<FoxNativeTrackListener*>(delegate);
    if (listener != nullptr) listener->onInstallComplete();
}
#endif
