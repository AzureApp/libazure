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
                int count = *(int*)msg.message;
                
                results.addressCount = count;
                [results onResultsReceived];
                daemon.ready = YES;
                return;
            }
            
            case Values:
            {
                ResultsHandler *results = [ResultsHandler sharedInstance];
                DataObject *data = msg.message;
                int objCount = msg.header.messageSize/sizeof(DataObject);
                NSMutableArray *arr = (results.searchObjects.count > 0) ? [results.searchObjects mutableCopy] : [NSMutableArray new];
                for (int i = 0; i < objCount; i++)
                {
                    SearchObject *obj = [SearchObject objectFromDataObject:data[i]];
                    [arr addObject:obj];
                }
                results.searchObjects = [NSArray arrayWithArray:arr];
                NSLog(@"results size: %d", results.searchObjects.count);
                free(data);
                [results onValuesReceived];
                
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
        NSLog(@"Sending message of type %s [size %d]", enumToName(msg.header.type), msg.header.messageSize);
        return [[Daemon currentDaemon] sendMessage:msg];
    }
}

+ (Message)attachMessageForApp:(App *)app {
    size_t size = sizeof(struct msg_process);
    Message msg;
    msg.header.magic = MSG_MAGIC;
    msg.header.messageSize = size;
    msg.header.shouldPop = YES;
    msg.header.type = Attach;
    
    struct msg_process *procData = malloc(sizeof(struct msg_process));
    procData->pid = app.pid;
    
    msg.message = procData;
    
    return msg;
}

+ (Message)searchMessageForSearchObject:(SearchObject *)obj {
    DataObject data;
    memcpy(data.data, [obj getRawData], [obj getSearchSize]);
    NSLog(@"%p", data.data);
    data.dataLen = (int)[obj getSearchSize];
    if ([obj isNumberSearch]) data.dataType = Int;
    if ([obj isDecimalNumberSearch]) data.dataType = Float;
    if ([obj isByteSearch]) data.dataType = Hex;
    if ([obj isStringSearch]) data.dataType = String;
    
    SearchSettings *settings = malloc(sizeof(SearchSettings));
    settings->fuzzySearch = NO;
    settings->searchObj = data;
    
    Message msg;
    msg.header.magic = MSG_MAGIC;
    msg.header.messageSize = sizeof(SearchSettings);
    msg.header.shouldPop = YES;
    
    if ([[ResultsHandler sharedInstance] hasResults]) {
        msg.header.type = IterateSearch;
    }
    else {
        msg.header.type = NewSearch;
    }
    
    msg.message = settings;
    return msg;
}

+ (Message)writeMessageForSearchObject:(SearchObject *)obj {
    DataObject *data = malloc(sizeof(DataObject));
    memcpy(data->data, [obj getRawData], [obj getSearchSize]);
    data->dataLen = (int)[obj getSearchSize];
    if ([obj isNumberSearch]) data->dataType = Int;
    if ([obj isDecimalNumberSearch]) data->dataType = Float;
    if ([obj isByteSearch]) data->dataType = Hex;
    if ([obj isStringSearch]) data->dataType = String;
    data->address = obj.address;
    
    Message msg;
    msg.header = header_default;
    msg.header.type = Edit;
    msg.header.messageSize = sizeof(DataObject);
    msg.message = data;
    
    return msg;
}

+ (Message)lockMessageForSearchObject:(SearchObject *)obj {
    DataObject *data = malloc(sizeof(DataObject));
    memcpy(data->data, [obj getRawData], [obj getSearchSize]);
    data->dataLen = (int)[obj getSearchSize];
    if ([obj isNumberSearch]) data->dataType = Int;
    if ([obj isDecimalNumberSearch]) data->dataType = Float;
    if ([obj isByteSearch]) data->dataType = Hex;
    if ([obj isStringSearch]) data->dataType = String;
    data->address = obj.address;
    
    Message msg;
    msg.header = header_default;
    msg.header.type = Lock;
    msg.header.messageSize = sizeof(DataObject);
    msg.message = data;
    
    return msg;
}

- (BOOL)isLawividoInAzureCode {
    return YES;
}

@end
