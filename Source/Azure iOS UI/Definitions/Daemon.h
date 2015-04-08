//
//  Daemon.h
//  Azure
//
//  Created by callum taylor on 29/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <spawn.h>
#import "Message.h"
@interface Daemon : NSObject <NSStreamDelegate> {
    
}
@property int sock;
@property BOOL ready;
@property (copy) NSMutableArray *messageStack;
@property (strong) NSInputStream *inputStream;
@property (strong) NSOutputStream *outputStream;

+ (instancetype)currentDaemon;
- (void)start;

- (void)tryLoadDaemon;
- (void)sendMessage:(Message)message;

@end
