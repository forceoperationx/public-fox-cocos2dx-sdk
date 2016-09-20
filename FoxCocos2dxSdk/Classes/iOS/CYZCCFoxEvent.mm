//
//  CYZCCFoxEvent.m
//  EarthWarrior3D
//
//  Created by 呉 維 on 2016/06/13.
//
//

#include "CYZCCFoxEvent.h"

using namespace fox;

CYZCCFoxEvent* CYZCCFoxEvent::makePurchaseEvent(const char* eventName,
                                          uint ltvId,
                                          double price,
                                          const char* currency
                                          ) {
    CYZCCFoxEvent* event =new CYZCCFoxEvent::CYZCCFoxEvent(eventName, ltvId);
    event->price = price;
    event->currency = currency;

    return event;
}

void CYZCCFoxEvent::addParam(const char *key, const char *value) {
    this->extraInfo.insert(std::map<const char*, const char*>::value_type(key, value));
}

