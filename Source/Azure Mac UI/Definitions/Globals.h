//
//  Globals.h
//  Azure Mac UI
//
//  Created by callum taylor on 03/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GlobalController.h"
#import "ProcessListTableController.h"
#import "ResultsTableController.h"
#import "ResultsHandler.h"
#import "ProcessManager.h"
#import "Preferences.h"
#import "Daemon.h"

@interface Globals : NSObject {
    GlobalController *controller;
    ProcessListTableController *processController;
    ComponentController *componentController;
    ResultsTableController *resultsController;
    Preferences *userPreferences;
    Daemon *daemon;
    Process *currentProcess;
}

@property (nonatomic, retain) GlobalController *controller;
@property (nonatomic, retain) ProcessListTableController *processController;
@property (nonatomic, retain) ComponentController *componentController;
@property (nonatomic, retain) ResultsTableController *resultsController;
@property (nonatomic, retain) Preferences *userPreferences;
@property (nonatomic, retain) Daemon *daemon;
@property (nonatomic, retain) Process *currentProcess;

+ (id)sharedInstance;
- (void)start;
- (void)refreshContents;
- (void)selectedProcess:(Process *)process;

@end
