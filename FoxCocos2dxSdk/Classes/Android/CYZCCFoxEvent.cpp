// F.O.X SDK
// CYZCCFoxEvent.cpp
//
// Created by T.Hiraga
//
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <stdio.h>
#include <string>
#include "../CYZCCFoxEvent.h"
#include "util/CYZCCFoxUtil.h"

using namespace fox;

void CYZCCFoxEvent::addParam(const char* k, const char* v)
{
  this->extraInfo[k] = v;
}

/**
 * map to char
 */
const char* CYZCCFoxEvent::getExtraInfoStr()
{
  CCLOG("CYZCCFoxEvent - getExtraInfoStr1");
  if (this->extraInfo.size() == 0) return nullptr;
  CCLOG("CYZCCFoxEvent - getExtraInfoStr2");
  return CYZCCFoxUtil::map2char(this->extraInfo);
}

/**
 * rapidJson to char
 */
const char* CYZCCFoxEvent::getEventInfoStr()
{
  CCLOG("CYZCCFoxEvent - getEventInfoStr1");
  if (this->eventInfo == nullptr) {
    CCLOG("CYZCCFoxEvent - eventInfo is null");
  }
  if (this->eventInfo == nullptr || this->eventInfo->HasParseError() || !this->eventInfo->IsObject()) {
    return nullptr;
  }
  CCLOG("CYZCCFoxEvent - getEventInfoStr2");
  return CYZCCFoxUtil::json2char(this->eventInfo);
}

CYZCCFoxEvent* CYZCCFoxEvent::makePurchaseEvent(
                                    const char* mEventName,
                                    uint const mLtvId,
                                    double mPrice,
                                    const char* mCurrency)
{
  CYZCCFoxEvent* e = new CYZCCFoxEvent(mEventName, mLtvId);
  e->price = mPrice;
  e->currency = mCurrency;
  return e;
}
#endif
