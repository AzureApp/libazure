
//
//  AppDelegate.h
//  Azure Mac UI
//
//  Created by callum taylor on 30/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GlobalController.h"
#import "Globals.h"
#import "ProcessListTableController.h"
#import "ResultsTableController.h"

@interface AppDelegate : NSObject <NSApplicationDelegate> {
    IBOutlet GlobalController *controller;
    IBOutlet ProcessListTableController *processController;
    IBOutlet ComponentController *componentController;
    IBOutlet ResultsTableController *resultsController;
}

@property (assign) IBOutlet NSWindow *window;
@property (nonatomic, retain) IBOutlet GlobalController *controller;
@property (nonatomic, retain) IBOutlet ProcessListTableController *processController;
@property (nonatomic, retain) IBOutlet ResultsTableController *resultsController;
@property (nonatomic, retain) IBOutlet ComponentController *componentController;

@end
