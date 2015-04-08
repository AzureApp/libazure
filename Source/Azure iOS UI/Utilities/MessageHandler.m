//
//  MessageHandler.m
//  Azure
//
//  Created by callum taylor on 29/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//
#undef MSG_MAGIC
#import "MessageHandler.h"
#import "ResultsHandler.h"

@implementation MessageHandler

+ (id)sharedInstance {
    static id inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = [[MessageHandler alloc] init];
    });
    return inst;
}

- (BOOL)isMessageValid:(Message)msg {
    NSLog(@"msg type: %s msg size: %ld", enumToName(msg.header.type), msg.header.messageSize);
    if (msg.header.magic != MSG_MAGIC) return false;
    if(enumToName(msg.header.type))
    {
        NSLog(@"valid message");
        return true;
    }
    return false;
}

- (void)processMessage:(Message)msg {
    if ([self isMessageValid:msg])
    {
        Daemon *daemon = [Daemon currentDaemon];
        NSLog(@"Message received: type: %s", enumToName(msg.header.type));
        switch (msg.header.type)
        {
            default:
            {
                return;
            }
            case StatusOK:
            {
                NSLog(@"daemon ok");
                daemon.ready = YES;
                return;
            }
                
            case StatusErr:
            {
                daemon.ready = YES;
                // process error
                return;
            }
                
            case Results:
            {
                ResultsHandler *results = [ResultsHandler sharedInstance];
                vm_offset_t *addresses = msg.message;
                NSMutableArray *arr = [[NSMutableArray alloc] init];
                int addressCount = msg.header.messageSize/sizeof(vm_address_t);
                NSLog(@"address count = %d", addressCount);
                for (int i = 0; i < addressCount; i++)
                {
                    [arr addObject:[NSNumber numberWithInt:addresses[i]]];
                }
                results.savedAddresses = [NSArray arrayWithArray:arr];
                results.addressCount = addressCount;
                [results onResultsReceived];
                
                daemon.ready = YES;
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
        }
    }
    else
    {
        // alert and log
    }
}

- (void)sendMessage:(Message)msg {
    if (messageIsValid(msg)) {
        NSLog(@"Sending message of type %s", enumToName(msg.header.type));
        return [[Daemon currentDaemon] sendMessage:msg];
    }
}

+ (Message)attachMessageForApp:(App *)app {
    Message msg;
    msg.header.magic = MSG_MAGIC;
    msg.header.messageSize = sizeof(struct msg_process);
    msg.header.shouldPop = YES;
    msg.header.type = Attach;
    
    struct msg_process *procData = malloc(sizeof(struct msg_process));
    procData->pid = app.pid;
    
    msg.message = procData;
    
    return msg;
}

+ (Message)searchMessageForSearchObject:(SearchObject *)obj {
    Message msg;
    msg.header.magic = MSG_MAGIC;
    msg.header.messageSize = obj.getSearchSize;
    msg.header.shouldPop = YES;
    msg.header.type = NewSearch;
    
    msg.message = [obj getRawData];
    
    return msg;
}

- (BOOL)isLawividoInAzureCode {
    return YES;
}

@end
