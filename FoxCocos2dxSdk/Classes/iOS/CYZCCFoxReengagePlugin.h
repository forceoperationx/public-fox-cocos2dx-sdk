//
//  FoxReengagePlugin.h
//  FoxSDK Cocos2d-x Plugin
//
//  Created by CyberZ
//  Copyright 2014 CyberZ, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UIApplication(SupressWarnings)

- (BOOL)application:(UIApplication *)application reengageOpenURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

@end
