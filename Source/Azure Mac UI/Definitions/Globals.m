//
//  Globals.m
//  Azure Mac UI
//
//  Created by callum taylor on 03/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "Globals.h"

@implementation Globals

@synthesize controller, processController, componentController, resultsController, userPreferences, daemon, currentProcess;

- (id)init
{
    self = [super init];
    if (self) {
        controller = [[GlobalController alloc] init];
        processController = [[ProcessListTableController alloc] init];
        userPreferences = [[Preferences alloc] init];
        daemon = [[Daemon alloc] init];
    }
    return self;
}

+ (id)sharedInstance {
    static id inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = [[Globals alloc] init];
    });
    return inst;
}

- (void)start {
    processController.processes = [NSMutableArray arrayWithArray:[ProcessUtils allProcesses]];
    [daemon start];
}

- (void)refreshContents {
    processController.processes = [NSMutableArray arrayWithArray:[ProcessUtils allProcesses]];
    [processController.processList reloadData];
}

- (void)selectedProcess:(Process *)process {
    if (daemon.ready)
    {
        ResultsHandler *handler = [ResultsHandler sharedInstance];
        ResultsTableController *resultsTable = [self resultsController];
        
        if (handler.addresses) free(handler.addresses);
        if (handler.value) free(handler.value);
        handler.hasResults = NO;
        handler.value = NULL;
        handler.addressCount = 0;
        [resultsTable refreshResults];
        
        handler.valueSize = 0;
        struct msg_header header;
        header = header_default;
        header.type = Attach;
        header.shouldPop = YES;
        header.messageSize = sizeof(struct msg_process);
        
        struct msg_process *procData = malloc(sizeof(struct msg_process));
        procData->pid = process.pid;
        // strcpy(procData->name, [[process name] UTF8String]);
        
        struct Message msg;
        msg.header = header;
        msg.message = procData;
        [daemon sendMessage:msg];
        currentProcess = process;
        [[self controller] enableSearchComponents];
    }
}

@end
