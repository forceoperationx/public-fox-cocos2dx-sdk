#import <UIKit/UIKit.h>
#import <objc/runtime.h>
#import <CYZFox/CYZFox.h>

#define DEBUG 1

#if DEBUG
#define CYZLog(...) NSLog(__VA_ARGS__)
#else
#define CYZLog(...)
#endif

@implementation UIApplication (CYZFox)

void fox_swizzle(Class origClass, SEL originalSelector, Class swizzledClass, SEL swizzledSelector) {

    Method originalMethod = class_getInstanceMethod(origClass, originalSelector);
    if (originalMethod) {
        Method swizzledMethod = class_getInstanceMethod(swizzledClass, swizzledSelector);

        if (!class_getInstanceMethod(origClass, swizzledSelector)) {
            CYZLog(@"add method %@ to class %@", NSStringFromSelector(swizzledSelector), NSStringFromClass(origClass));
            class_addMethod(origClass, swizzledSelector,
                            method_getImplementation(swizzledMethod),
                            method_getTypeEncoding(swizzledMethod));
        }

        CYZLog(@"exchange method %@ of class %@", NSStringFromSelector(originalSelector), NSStringFromClass(origClass));
        Method swizzledMethodInOrigClass = class_getInstanceMethod(origClass, swizzledSelector);
        method_exchangeImplementations(originalMethod, swizzledMethodInOrigClass);
    }
}

+(void) load {
    CYZLog(@"load swizzling");
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        fox_swizzle([self class], @selector(setDelegate:),[self class], @selector(fox_setDelegate:));
    });
}

-(void) fox_setDelegate:(id<UIApplicationDelegate>) delegate {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        Class delegateClass = [delegate class];

        // swizzle application:openURL:sourceApplication:annotation:
        SEL ori_openURLSourceApplication = @selector(application:openURL:sourceApplication:annotation:);
        SEL swiz_openURLSourceApplication = @selector(fox_application:openURL:sourceApplication:annotation:);

        // swizzle application:openURL:options:
        SEL ori_openURLOptions = @selector(application:openURL:options:);
        SEL swiz_openURLOptions = @selector(fox_application:openURL:options:);

        // should add empty application:openURL:sourceApplication:annotation:
        if (!class_getInstanceMethod(delegateClass, ori_openURLSourceApplication)
            && !class_getInstanceMethod(delegateClass, ori_openURLOptions)) {
            CYZLog(@"not found either %@ or %@", NSStringFromSelector(ori_openURLSourceApplication), NSStringFromSelector(ori_openURLOptions));

            SEL swiz_empty_openURLSourceApplication = @selector(fox_empty_application:openURL:sourceApplication:annotation:);
            Method emptyMethod = class_getInstanceMethod([self class], swiz_empty_openURLSourceApplication);
            CYZLog(@"add empty method %@", NSStringFromSelector(ori_openURLSourceApplication));
            class_addMethod(delegateClass, ori_openURLSourceApplication,
                            method_getImplementation(emptyMethod),
                            method_getTypeEncoding(emptyMethod));
        }

        fox_swizzle(delegateClass, ori_openURLSourceApplication, [self class], swiz_openURLSourceApplication);
        fox_swizzle(delegateClass, ori_openURLOptions, [self class], swiz_openURLOptions);
    });

    [self fox_setDelegate:delegate];
}

-(BOOL) fox_application:(UIApplication *) application openURL:(nonnull NSURL *) url sourceApplication:(nullable NSString *) sourceApplication annotation:(nonnull id) annotation {
    CYZLog(@"fox swizzed method: application:openURL:sourceApplication:annotation:");
    [CYZFox handleOpenURL:url];
    return [self fox_application:application openURL:url sourceApplication:sourceApplication annotation:annotation];
}

-(BOOL)fox_application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary<NSString *,id> *)options {
    CYZLog(@"fox swizzed method: application:openURL:options:");
    [CYZFox handleOpenURL:url];
    return [self fox_application:app openURL:url options:options];
}

-(BOOL) fox_empty_application:(UIApplication *) application openURL:(nonnull NSURL *) url sourceApplication:(nullable NSString *) sourceApplication annotation:(nonnull id) annotation {
    CYZLog(@"fox empty method: application:openURL:sourceApplication:annotation:");
    return YES;
}

@end
