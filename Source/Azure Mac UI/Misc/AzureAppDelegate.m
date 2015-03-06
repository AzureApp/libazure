//
//  AppDelegate.m
//  Azure Mac UI
//
//  Created by callum taylor on 30/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "AzureAppDelegate.h"

@implementation AppDelegate

@synthesize controller, processController, componentController, resultsController;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
}

- (void)awakeFromNib {
    Globals *main = [Globals sharedInstance];
    [main setController:controller];
    [main setProcessController:processController];
    [main setComponentController:componentController];
    [main setResultsController:resultsController];
    [main start];
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)application {
    return YES;
}

- (IBAction)exit:(id)sender {
    
}

@end
