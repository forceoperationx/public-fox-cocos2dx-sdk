// F.O.X SDK
// CYZCCFox.h
//
// Created by T.Hiraga
//
#ifndef __CYZCCFox_H_
#define __CYZCCFox_H_

#include "CYZCCFoxTypes.h"
#include "CYZCCFoxEvent.h"
#include "external/json/document.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "Android/FoxNativeTrackListener.h"
#endif

namespace fox {

    struct CYZCCFoxConfig {
        int appId_ios = 0;
        const char* salt_ios = nullptr;
        const char* appKey_ios = nullptr;
        bool webViewTrackingEnabled_ios;

        int appId_android = 0;
        const char* salt_android = nullptr;
        const char* appKey_android = nullptr;

        const char* foxServerURL = nullptr;
        const char* analyticsServerURL = nullptr;
        bool debugMode = 0;
    };

    struct CYZCCFoxTrackOption {
        bool optout;
        const char* redirectURL;
        const char* buid;
        CYZCCFoxInstallCallbackFunc onInstallComplete;
    };

    class CYZCCFox {
    public:
        static void init(CYZCCFoxConfig config);
        static void trackInstall();
        static void trackInstall(CYZCCFoxTrackOption option);
        static void trackSession();
        static void trackEvent(CYZCCFoxEvent* event);

        static bool isConversionCompleted();
        static bool getUserInfo(rapidjson::Document& userInfo);
        static void setUserInfo(rapidjson::Document& userInfo);

        static void trackEventByBrowser(const char* redirectURL);

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    private:
        static FoxNativeTrackListener* foxTracklistener;
#endif
    };
}
#endif
