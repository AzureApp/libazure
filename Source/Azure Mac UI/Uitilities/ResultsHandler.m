//
//  ResultsHandler.m
//  Azure
//
//  Created by callum taylor on 15/08/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "ResultsHandler.h"

@implementation ResultsHandler

@synthesize addresses, addressCount, hasResults, value, valueSize;

- (id)init
{
    self = [super init];
    if (self) {
        self.addresses = NULL;
        self.addressCount = 0;
        self.value = NULL;
        self.hasResults = NO;
        self.valueSize = 0;
    }
    return self;
}

+ (id)sharedInstance {
    static id inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = [[ResultsHandler alloc] init];
    });
    return inst;
}

- (void)clear {
    //free(addresses);
}

@end
