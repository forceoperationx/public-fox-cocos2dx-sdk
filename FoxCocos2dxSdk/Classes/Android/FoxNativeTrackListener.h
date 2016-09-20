// F.O.X SDK
// FoxNativeTrackListener.h
//
// Created by T.Hiraga
//
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#ifndef __FoxNativeTrackListener_H__
#define __FoxNativeTrackListener_H__

#include <functional>
#include "../CYZCCFoxTypes.h"

using namespace fox;

class FoxNativeTrackListener
{
public:
    // FoxNativeTrackListener(CYZCCFoxOption option);
    FoxNativeTrackListener(CYZCCFoxInstallCallbackFunc onInstallCompleteCallback);

    void onInstallComplete();

private:
    // CYZCCFoxOption option;
    CYZCCFoxInstallCallbackFunc onInstallCompleteCallback;
};

#endif
#endif
