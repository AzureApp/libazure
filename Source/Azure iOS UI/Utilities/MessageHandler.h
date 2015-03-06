//
//  MessageHandler.h
//  Azure
//
//  Created by callum taylor on 29/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Message.h"
#import "Daemon.h"
#import "ResultsHandler.h"
#import "App.h"

@interface MessageHandler : NSObject

+ (id)sharedInstance;
- (BOOL)isMessageValid:(struct Message)msg;
- (void)processMessage:(struct Message)msg;
- (void)sendMessage:(struct Message)msg;

+ (struct Message)attachMessageForApp:(App *)app;

- (BOOL)isLawividoInAzureCode;
@end
