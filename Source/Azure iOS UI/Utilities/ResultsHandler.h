//
//  ResultsHandler.h
//  Azure
//
//  Created by callum taylor on 02/01/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Message.h"
#import "Daemon.h"
#import "MessageHandler.h"

enum SearchType {
    Int,
    Float,
    Hex,
    String
};

@interface ResultsHandler : NSObject

+(instancetype)sharedInstance;
- (void)beginSearch;
- (void)onResultsReceived;
- (BOOL)hasResults;

@property enum SearchType currentSearchType;
@property (strong) NSArray *savedAddresses; // strong to copy?
@property int addressCount;
@property (strong) SearchObject *currentSearchObject;

@end
