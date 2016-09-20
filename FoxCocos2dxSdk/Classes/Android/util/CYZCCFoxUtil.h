// F.O.X SDK
// CYZCCFoxUtil.h
//
// Created by T.Hiraga
//
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "cocos2d.h"
#include <jni.h>
#include "external/json/document.h"

using namespace std;
using namespace rapidjson;

typedef struct ClassInfo_
{
    JNIEnv *    env;
    jclass      classID;
    jobject     classObj;
} ClassInfo;

namespace fox
{
  class CYZCCFoxUtil
  {
  public:
      static jobject getContext();
      static bool getClassInstance(ClassInfo &classInfo, const char* className, const char* paramCode, ...);
      static const char* map2char(map<const char*, const char*> m);
      static const char* json2char(Document*& doc);
  };
}
#endif
