//
//  MessageHandler.m
//  Azure
//
//  Created by System Administrator on 13/08/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "MessageHandler.h"
#import "Globals.h"

@implementation MessageHandler


- (id)init {
    self = [super init];
    return self;
}

+ (id)sharedInstance {
    static id inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = [[MessageHandler alloc] init];
    });
    return inst;
}

- (BOOL)isMessageValid:(struct Message)msg {
    if (msg.header.magic != MSG_MAGIC) return false;
    if(enumToName(msg.header.type))
    {
        return true;
    }
    return false;
}

- (void)processMessage:(struct Message)msg {
    if ([self isMessageValid:msg])
    {
        Daemon *daemon = [Daemon currentDaemon];
        GlobalController *controller = [[Globals sharedInstance] controller];
        switch (msg.header.type) {
            default:
            {
                return;
            }
            case StatusOK:
            {
                daemon.ready = YES;
                return;
            }
                
            case StatusErr:
            {
                daemon.ready = YES;
                // process error
                return;
            }
                
            case Attach:
            case Detach:
            case NewSearch:
            case IterateSearch:
            case Edit:
            case Lock:
            {
                // alert and log (invalid message)
                return;
            }
                
            case Results:
            {
                vm_address_t *addresses = (vm_address_t*)msg.message;
                ComponentController *componentController = [[Globals sharedInstance] componentController];
                ResultsTableController *resultsController = [[Globals sharedInstance] resultsController];
                ResultsHandler *results = [ResultsHandler sharedInstance];
                [results clear];
                results.hasResults = YES;
                long count = msg.header.messageSize/sizeof(vm_address_t);
                
                results.addressCount = count;
                [componentController.resultCount setStringValue:[NSString stringWithFormat:@"%ld Results", count]];
                
                results.addresses = addresses;
                [resultsController refreshResults];
                daemon.ready = YES;
            }
        }
    }
    else
    {
        // alert and log invalid message
    }
}

- (BOOL)isLawividoInAzureCode {
    return YES;
}
@end
