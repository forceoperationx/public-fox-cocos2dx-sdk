// F.O.X SDK
// CYZCCFoxEvent.h
//
// Created by T.Hiraga
//
#ifndef __CYZCCFoxEVENT_H_
#define __CYZCCFoxEVENT_H_

#include "cocos2d.h"
#include "external/json/document.h"

using namespace rapidjson;

namespace fox {

    class CYZCCFoxEvent {
    public:
        uint const ltvId;
        const char* buid = nullptr;
        std::map<const char*, const char*> extraInfo;
        const char* const eventName = nullptr;
        uint value = 0;
        const char* orderId = nullptr;
        const char* sku = nullptr;
        const char* itemName = nullptr;
        double price;
        uint quantity = 1;
        const char* currency = nullptr;
        Document* eventInfo = nullptr;

        CYZCCFoxEvent(const char* eventName): eventName(eventName),ltvId(0){};
        CYZCCFoxEvent(const char* eventName, uint ltvId): eventName(eventName),ltvId(ltvId){};
        void addParam(const char* key, const char* value);

        static CYZCCFoxEvent* makePurchaseEvent(
                                             const char* const eventName,
                                             uint const ltvId,
                                             double price,
                                             const char* currency
                                             );
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
        const char* getExtraInfoStr();
        const char* getEventInfoStr();
#endif
    };
}
#endif
