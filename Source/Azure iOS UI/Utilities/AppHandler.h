//
//  AppHandler.h
//  Azure
//
//  Created by callum taylor on 16/02/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <mach/mach.h>
#import <mach/mach_host.h>
#import <sys/sysctl.h>
#import <dlfcn.h>
#import <sys/param.h>
#import "App.h"

extern int proc_pidpath(int,void*,uint32_t);

@interface AppHandler : NSObject

@property (nonatomic, strong) App *currentApp;

+ (instancetype)sharedInstance;
- (NSArray *)allRunningApps;
- (void)refreshRunningApps;
+ (UIImage *)appIconForBundleID:(NSString *)bundleID;
@end


