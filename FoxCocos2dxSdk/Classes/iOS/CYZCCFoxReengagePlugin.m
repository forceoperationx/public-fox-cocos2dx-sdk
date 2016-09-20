//
//  FoxReengagePlugin.m
//  FoxSDK Cocos2d-x Plugin
//
//  Created by CyberZ
//  Copyright 2014 CyberZ, Inc. All rights reserved.
//

#import "CYZCCFoxReengagePlugin.h"
#import <objc/runtime.h>
#import <CYZFox/CYZFox.h>

@implementation UIApplication (CYZFoxReengagePlugin)

+(void)load
{
    NSLog(@"load CYZFoxReengagePlugin");
    method_exchangeImplementations(class_getInstanceMethod(self, @selector(setDelegate:)), class_getInstanceMethod(self, @selector(setFoxReengageDelegate:)));
    
}

BOOL foxReengageOpenURL(id self, SEL _cmd, id application, id url, id sourceApplication, id annotation) {

    if ([self respondsToSelector:@selector(application:reengageOpenURL:sourceApplication:annotation:)])
    {
		[self application:application reengageOpenURL:url sourceApplication:sourceApplication annotation:annotation];
	}

    [CYZFox handleOpenURL:url];
    return YES;
    
}

static void exchangeMethodImplementations(Class class, SEL oldMethod, SEL newMethod, IMP impl, const char * signature)
{
	Method method = nil;
	method = class_getInstanceMethod(class, oldMethod);
    
	if (method)
    {
		class_addMethod(class, newMethod, impl, signature);
		method_exchangeImplementations(class_getInstanceMethod(class, oldMethod), class_getInstanceMethod(class, newMethod));
	}
    else
    {
		class_addMethod(class, oldMethod, impl, signature);
	}
}

- (void) setFoxReengageDelegate:(id<UIApplicationDelegate>)delegate
{
    
	static Class delegateClass = nil;
    
	if(delegateClass == [delegate class])
	{
		[self setFoxReengageDelegate:delegate];
		return;
	}
    
	delegateClass = [delegate class];
    
	exchangeMethodImplementations(delegateClass, @selector(application:openURL:sourceApplication:annotation:),
                                  @selector(application:reengageOpenURL:sourceApplication:annotation:), (IMP)foxReengageOpenURL, "v@:::");
    
	[self setFoxReengageDelegate:delegate];
}

@end
