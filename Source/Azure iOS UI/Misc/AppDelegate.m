//
//  AppDelegate.m
//  Azure iOS
//
//  Created by callum taylor on 21/11/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "AppDelegate.h"
#import "Daemon.h"
#import "AppHandler.h"
#import "MessageHandler.h"
#import "ResultsHandler.h"

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    [[UINavigationBar appearance] setBarTintColor:[UIColor colorWithRed:49/255.0f green:192/255.0f blue:190/255.0f alpha:1.0]];
    [[UINavigationBar appearance] setTranslucent:YES];
    [[UITabBar appearance] setTintColor:[UIColor colorWithRed:49/255.0f green:192/255.0f blue:190/255.0f alpha:1.0]];
    //[application setStatusBarStyle:UIStatusBarStyleLightContent];
    Daemon *daemon = [Daemon currentDaemon]; // move to an - [Azure init] func?
    [daemon start];
    
    NSLog(@"%@",[[AppHandler sharedInstance] allRunningApps]);
    //exit(0);
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    [[NSNotificationCenter defaultCenter]
     postNotificationName:@"RetrieveUpdatedValues"
     object:nil];
}

- (void)applicationDidBecomeActive:(UIApplication *)application {

}

- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
