//
//  CYZCCFox.m
//  EarthWarrior3D
//
//  Created by 呉 維 on 2016/06/13.
//
//
#import <CYZFox/CYZFox.h>

#include "CYZCCFox.h"
#include "CYZCCFoxIOSUtility.mm"

using namespace rapidjson;
using namespace fox;

void CYZCCFox::init(CYZCCFoxConfig config) {
    CYZFoxConfig* foxConfig = [CYZFoxConfig configWithAppId:config.appId_ios salt:CYZCCFoxStringFromUTF8String(config.salt_ios) appKey:CYZCCFoxStringFromUTF8String(config.appKey_ios)];

    if (config.foxServerURL) {
        [foxConfig setFoxServerURL:CYZCCFoxStringFromUTF8String(config.foxServerURL)];
    }
    if (config.analyticsServerURL) {
        [foxConfig setAnalyticsServerURL:CYZCCFoxStringFromUTF8String(config.analyticsServerURL)];
    }
    if (config.debugMode) {
        [foxConfig enableDebugMode];
    }
    if (config.webViewTrackingEnabled_ios) {
        [foxConfig enableWebViewTracking];
    }

    [foxConfig activate];
}

void CYZCCFox::trackInstall() {
    [CYZFox trackInstall];
}

void CYZCCFox::trackInstall(CYZCCFoxTrackOption option) {
    CYZFoxTrackOption* foxOption = [CYZFoxTrackOption new];
    foxOption.redirectURL = CYZCCFoxStringFromUTF8String(option.redirectURL);
    foxOption.buid = CYZCCFoxStringFromUTF8String(option.buid);
    foxOption.optout = option.optout;
    if (option.onInstallComplete) {
        foxOption.trackingCompletionHandler = ^{
            option.onInstallComplete();
        };
    }

    [CYZFox trackInstallWithOption:foxOption];
}

void CYZCCFox::trackSession() {
    [CYZFox trackSession];
}

void CYZCCFox::trackEvent(CYZCCFoxEvent* event) {
    CYZFoxEvent* foxEvent = [[CYZFoxEvent alloc]initWithEventName:CYZCCFoxStringFromUTF8String(event->eventName) ltvId:event->ltvId];
    foxEvent.buid = CYZCCFoxStringFromUTF8String(event->buid);

    // set extraInfo: get NSDictionary from std::map
    for (auto elem : event->extraInfo) {
        [foxEvent addExtraValue:CYZCCFoxStringFromUTF8String(elem.second)
                         forKey:CYZCCFoxStringFromUTF8String(elem.first)];
    }

    foxEvent.value = event->value;
    foxEvent.orderId = CYZCCFoxStringFromUTF8String(event->orderId);
    foxEvent.sku = CYZCCFoxStringFromUTF8String(event->sku);
    foxEvent.itemName = CYZCCFoxStringFromUTF8String(event->itemName);
    foxEvent.price = event->price;
    foxEvent.quantity = event->quantity;
    foxEvent.currency = CYZCCFoxStringFromUTF8String(event->currency);
    if (event->eventInfo) {
        foxEvent.eventInfo = CYZCCFoxDocumentToDictionary(event->eventInfo);
    }

    [CYZFox trackEvent:foxEvent];
}

bool CYZCCFox::isConversionCompleted() {
    return [CYZFox isConversionCompleted];
}

bool CYZCCFox::getUserInfo(rapidjson::Document& doc) {
    NSDictionary* userInfo = [CYZFox getUserInfo];
    if (userInfo) {
        return CYZCCFoxDictionaryToDocument(userInfo, doc);
    }
    return false;
}

void CYZCCFox::setUserInfo(rapidjson::Document& doc) {
    rapidjson::Document* docPtr = &doc;
    NSDictionary* userInfo = CYZCCFoxDocumentToDictionary(docPtr);
    if (userInfo) {
        [CYZFox setUserInfo:userInfo];
    }
}

void CYZCCFox::trackEventByBrowser(const char* redirectURL) {
    [CYZFox trackEventByBrowser:CYZCCFoxStringFromUTF8String(redirectURL)];
}
