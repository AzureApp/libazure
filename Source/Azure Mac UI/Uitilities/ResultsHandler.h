//
//  ResultsHandler.h
//  Azure
//
//  Created by callum taylor on 15/08/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ResultsHandler : NSObject

@property vm_address_t *addresses;
@property size_t addressCount;
@property BOOL hasResults;
@property void *value;
@property size_t valueSize;

+ (id)sharedInstance;
- (void)clear;
@end
