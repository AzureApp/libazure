//
//  ResultsHandler.m
//  Azure
//
//  Created by callum taylor on 02/01/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import "ResultsHandler.h"

@interface ResultsHandler ()
- (void)rawData:(char *)data ofSize:(size_t *)size fromSearchObject:(SearchObject *)obj;
@end

@implementation ResultsHandler

@synthesize currentSearchType, currentSearchObject, savedAddresses, addressCount, searchObjects;

+ (id)sharedInstance {
    static id inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = [[ResultsHandler alloc] init];
    });
    return inst;
}

- (void)beginSearch {
    Message msg = [MessageHandler searchMessageForSearchObject:currentSearchObject];
    [[MessageHandler sharedInstance] sendMessage:msg];
}

- (void)onResultsReceived {
    [[NSNotificationCenter defaultCenter]
         postNotificationName:@"ReceivedResults"
         object:nil];
}

- (void)onValuesReceived {
    [[NSNotificationCenter defaultCenter]
        postNotificationName:@"ReceivedValues"
        object:nil];
}

- (BOOL)hasResults {
    return (addressCount > 0);
}

- (SearchObject *)searchObjectAtIndex:(NSInteger)index {
    if (searchObjects.count > 0) {
        return [searchObjects objectAtIndex:index];
    }
    return currentSearchObject;
}

- (void)rawData:(char *)data ofSize:(size_t *)size fromSearchObject:(SearchObject *)obj {
    if (data != NULL) {
        if ([obj isNumberSearch]) {
            int num = [obj.asNumber integerValue];
            memcpy(data, &num, sizeof(int));
            *size = sizeof(int);
        }
        else if ([obj isDecimalNumberSearch]) {
            float num = [obj.asDecimalNumber floatValue];
            memcpy(data, &num, sizeof(int));
            *size = sizeof(float);
        }
        else if ([obj isStringSearch]) {
            const char *chr = [obj.asString UTF8String];
            memcpy(data, chr, [obj.asString length]); // TODO: adjust for terminating byte
            *size = [obj.asString length];
        }
        else if ([obj isByteSearch]) {
            const void *bytes = [obj.asBytes bytes];
            memcpy(data, bytes, [obj.asBytes length]);
            *size = [obj.asBytes length];
        }
    }
    else { // NULL pointer received
        //AZLog
    }
}

@end
