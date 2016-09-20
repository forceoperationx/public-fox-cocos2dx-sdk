// F.O.X SDK
// FoxNativeTrackListener.cpp
//
// Created by T.Hiraga
//
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "FoxNativeTrackListener.h"
#include "cocos2d.h"

FoxNativeTrackListener::FoxNativeTrackListener(CYZCCFoxInstallCallbackFunc onInstallCompleteCallback)
{
  this->onInstallCompleteCallback = onInstallCompleteCallback;
}

void FoxNativeTrackListener::onInstallComplete()
{
  if (this->onInstallCompleteCallback) this->onInstallCompleteCallback();
}
#endif
