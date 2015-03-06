//
//  MessageHandler.h
//  Azure
//
//  Created by System Administrator on 13/08/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Message.h"
#import "Daemon.h"

@interface MessageHandler : NSObject
+ (id)sharedInstance;
- (BOOL)isMessageValid:(struct Message)msg;
- (void)processMessage:(struct Message)msg;
- (BOOL)isLawividoInAzureCode;
@end
