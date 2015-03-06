//
//  DaemonUtils.h
//  Azure
//
//  Created by callum taylor on 02/08/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Message.h"


@interface Daemon : NSObject <NSStreamDelegate> {
    int sock;
    bool ready;
    NSMutableArray *messageStack;
@private
    NSInputStream *inputStream;
    NSOutputStream *outputStream;

}
@property (assign) int sock;
@property (assign) bool ready;
@property (copy) NSMutableArray *messageStack;
@property (nonatomic, retain) NSInputStream *inputStream;
@property (nonatomic, retain) NSOutputStream *outputStream;

+ (instancetype)currentDaemon;

- (void)start;

- (void)sendMessage:(struct Message)message;
- (void)receiveMessage:(struct Message)message;

@end
