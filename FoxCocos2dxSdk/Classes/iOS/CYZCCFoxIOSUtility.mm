#import <Foundation/Foundation.h>
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

using namespace rapidjson;

static NSString* CYZCCFoxStringFromUTF8String(const char *bytes) {
    if (bytes) {
        return @(bytes);
    } else {
        return nil;
    }
}

static NSDictionary* CYZCCFoxDocumentToDictionary(Document*& doc) {
    StringBuffer strBuf;
    Writer<StringBuffer> writer(strBuf);
    doc->Accept(writer);
    NSString* jsonStr = CYZCCFoxStringFromUTF8String(strBuf.GetString());

    if (jsonStr && jsonStr.length > 0) {
        NSError* err = nil;
        NSDictionary* dict = [NSJSONSerialization JSONObjectWithData:[jsonStr dataUsingEncoding:NSUTF8StringEncoding]  options:0 error:&err];
        if (err) {
            NSLog(@"json write err!! : %@", err);
        }
        return dict;
    }
    return nil;
}

static bool CYZCCFoxDictionaryToDocument(NSDictionary* dict, Document& doc) {
    if (dict) {
        NSError* err = nil;
        NSData* jsonData = [NSJSONSerialization dataWithJSONObject:dict options:0 error:&err];
        if (err) {
            NSLog(@"json read err: %@", err);
        }
        if(jsonData) {
            NSString* objcStr = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
            const char* cJsonStr = [objcStr UTF8String];
            if (doc.Parse<ParseFlag::kParseDefaultFlags>(cJsonStr).HasParseError()) {
                NSLog(@"json parse error!! : %s for %@", doc.GetParseError(), objcStr);
            } else {
                return true;
            }
        }
    }
    return false;
}
