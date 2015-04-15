//
//  MessageHandler.h
//  Azure
//
//  Created by callum taylor on 29/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#undef MSG_MAGIC

#import "Message.h"
#import "Daemon.h"
#import "App.h"
#import "SearchObject.h"

struct SearchSettings {
    bool fuzzySearch;
    
    enum FuzzySettings {
        FuzzyNew,
        FuzzyGreater,
        FuzzySmaller,
        FuzzyExact,
        FuzzyNotEqual
    } fuzzySettings;
    
    struct DataObject searchObj;
};

typedef struct DataObject DataObject;
typedef struct SearchSettings SearchSettings;

@interface MessageHandler : NSObject

+ (id)sharedInstance;
- (BOOL)isMessageValid:(Message)msg;
- (void)processMessage:(Message)msg;
- (void)sendMessage:(Message)msg;

+ (Message)attachMessageForApp:(App *)app;
+ (Message)searchMessageForSearchObject:(SearchObject *)obj;

- (BOOL)isLawividoInAzureCode;
@end
