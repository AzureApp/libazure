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

@synthesize currentSearchType;

+ (id)sharedInstance {
    static id inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = [[ResultsHandler alloc] init];
    });
    return inst;
}

- (void)beginSearch {
    // TODO: send daemon message
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
        else if ([obj isBytes]) {
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
