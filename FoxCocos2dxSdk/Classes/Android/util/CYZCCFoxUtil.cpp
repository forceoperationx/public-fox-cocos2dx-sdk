// F.O.X SDK
// CYZCCFox.cpp
//
// Created by T.Hiraga
//
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "cocos2d.h"
#include "CYZCCFoxUtil.h"
#include <jni.h>
#include "external/json/rapidjson.h"
#include "external/json/stringbuffer.h"
#include "external/json/writer.h"

using namespace cocos2d;
using namespace std;
using namespace rapidjson;
using namespace fox;

    /**
     * コンテキスト取得
     */
    jobject CYZCCFoxUtil::getContext() {
        JniMethodInfo t;
        JniHelper::getStaticMethodInfo(t, "org/cocos2dx/lib/Cocos2dxActivity", "getContext", "()Landroid/content/Context;");
        jobject ctx = t.env->CallStaticObjectMethod(t.classID, t.methodID);
        return ctx;
    }

    /**
     * クラスインスタンスの取得
     * className クラスパス
     * paramCode 引数
     * ... パラメータ群
     *
     * classInfo.classID : パスから生成したjclass
     * classInfo.classObj : 呼び出したクラスのインスタンス(コンストラクタ呼び出し)
     */
    bool CYZCCFoxUtil::getClassInstance(ClassInfo &classInfo,
                                  const char* className,
                                  const char* paramCode,
                                  ...) {
        JNIEnv *env = JniHelper::getEnv();
        if (!env) return false;
        jstring _jstrClassName = env->NewStringUTF(className);
        jclass jClass = (jclass) env->CallObjectMethod(cocos2d::JniHelper::classloader,
                                                   cocos2d::JniHelper::loadclassMethod_methodID,
                                                   _jstrClassName);
        if (nullptr == jClass) return false;

        jmethodID jClassCnstrctr = env->GetMethodID(jClass, "<init>", paramCode);
        if (! jClassCnstrctr) return false;

        va_list args;
        va_start(args, paramCode);
        jobject jClassObj = env->NewObjectV(jClass, jClassCnstrctr, args);
        va_end(args);
        if (nullptr == jClassObj) return false;

        classInfo.classID = jClass;
        classInfo.classObj = jClassObj;
        env->DeleteLocalRef(_jstrClassName);

        return true;
    }

    /**
     * mapをcharに変換
     * m map
     */
    const char* CYZCCFoxUtil::map2char(map<const char*, const char*> m) {
      const char* extraInfoStr = nullptr;
      if (m.size() == 0) return extraInfoStr;
      for(auto itr = m.begin(); itr != m.end(); ++itr) {
        std::string key(itr->first);
        std::string val(itr->second);
        if (extraInfoStr != nullptr && 0 < strlen(extraInfoStr)) {
          std::string tmp(extraInfoStr);
          extraInfoStr = (tmp + "&" + key + "=" + val).c_str();
        } else {
          extraInfoStr = (key + "=" + val).c_str();
        }
      }
      return extraInfoStr;
    }

    /**
     * rapidjsonをcharに変換
     * doc RapidJsonオブジェクト
     */
    const char* CYZCCFoxUtil::json2char(Document*& doc) {
      if (doc->HasParseError() || !doc->IsObject()) {
        return nullptr;
      }
      StringBuffer sb;
      Writer<StringBuffer> writer(sb);
      doc->Accept(writer);
      return sb.GetString();
    }
#endif
