//
//  Daemon.m
//  Azure
//
//  Created by callum taylor on 29/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "Daemon.h"
#import "MessageHandler.h"

#define AZLog NSLog //makeshift 
@implementation Daemon

+ (instancetype)currentDaemon {
    static id inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = [[Daemon alloc] init];
    });
    return inst;
}

- (void)start {
    CFReadStreamRef readStream;
    CFWriteStreamRef writeStream;
    
    CFStreamCreatePairWithSocketToHost(NULL,(CFStringRef)@"localhost", DAEMON_PORT, &readStream, &writeStream);
    
    self.inputStream = (__bridge NSInputStream *)readStream;
    self.outputStream = (__bridge NSOutputStream *)writeStream;
    
    [self.inputStream setDelegate:self];
    [self.outputStream setDelegate:self];
    dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0);
    dispatch_async(queue, ^ {
        [self.inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        [self.outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        
        [self.inputStream open];
        [self.outputStream open];
        // here: start the loop
        [[NSRunLoop currentRunLoop] run];
        // note: all code below this line won't be executed, because the above method NEVER returns.
    });
    
    self.ready = YES;
    
    AZLog(@"daemon started\n");
}


- (void)sendMessage:(Message)message {
    long chunk_size = CHUNK_SIZE;
    if (self.ready) {
        if ([self.outputStream hasSpaceAvailable]) {
            unsigned char *data = (unsigned char*)message.message;
            struct msg_header header = message.header;
            [self.outputStream write:(unsigned char*)&header maxLength:sizeof(struct msg_header)];
            
            long msg_size = message.header.messageSize;
            if (msg_size > 0) {
                long write_size = 0;
                
                while (write_size <= msg_size) {
                    if ((write_size + chunk_size) > msg_size)
                    {
                        chunk_size = msg_size - write_size;
                        if (chunk_size == 0) break;
                    }
                    write_size += [self.outputStream write:data+write_size maxLength:chunk_size];
                }
            }
        }
        self.ready = NO;
    }
    else {
        // azure is doing something
        AZLog(@"Azure busy");
    }
}

- (void)receiveMessage:(Message)message {
    NSLog(@"received message of type %s (size %ld)", enumToName(message.header.type), message.header.messageSize);
    MessageHandler *handler = [MessageHandler sharedInstance];
    [handler processMessage:message];
}

#pragma mark NSStreamDelegate

- (void)stream:(NSStream *)stream handleEvent:(NSStreamEvent)streamEvent {
    
    switch (streamEvent)
    {
        case NSStreamEventOpenCompleted:
        {
            NSLog(@"Stream opened");
            break;
        }
        case NSStreamEventHasBytesAvailable:
        {
            if (stream == self.inputStream)
            {
                while ([self.inputStream hasBytesAvailable])
                {
                    long chunk_size = CHUNK_SIZE;
                    struct msg_header header;
                    long bytes = [self.inputStream read:(unsigned char*)&header maxLength:sizeof(struct msg_header)];
                    MessageHandler *handler = [MessageHandler sharedInstance];
                    if ([handler isMessageValid:*(Message*)&header])
                    {
                        if (bytes > 0)
                        {
                            long msg_size = header.messageSize;
                            NSLog(@"msg size = %ld", msg_size);
                            unsigned char *data = NULL;
                            if (msg_size > 0) {
                                long read_size = 0;
                                data = (unsigned char*)malloc(msg_size);
                                
                                while (read_size <= msg_size)
                                {
                                    if ((read_size + chunk_size) > msg_size)
                                    {
                                        chunk_size = msg_size - read_size;
                                        if (chunk_size == 0) break;
                                    }
                                    long bytes = [self.inputStream read:data+read_size maxLength:chunk_size];
                                    if (bytes == -1)
                                    {
                                        // error
                                        return;
                                    }
                                    read_size += bytes;
                                }
                            }
                            Message msg;
                            msg.header = header;
                            msg.message = malloc(msg_size);
                            memcpy(msg.message, data, msg_size);
                            free(data);
                            [self receiveMessage:msg];
                        }
                    }
                    else
                    {
                        NSLog(@"u dun goofd razz");
                        [self.inputStream close];
                        [self.outputStream close];
                    }
                }
            }
            break;
        }
        case NSStreamEventErrorOccurred:
        {
            // daemon not running
            [self tryLoadDaemon];
            break;
        }
        case NSStreamEventEndEncountered:
            break;
        case NSStreamEventHasSpaceAvailable:
            break;
        case NSStreamEventNone:
            break;
    }
}

- (void)tryLoadDaemon {
    pid_t newPid;
    char *argV[] = {"launchctl", "load /Library/LaunchDaemons/azure.daemon.plist", 0};
    int status = posix_spawn(&newPid, "launchctl", NULL, NULL, argV, NULL);
    if (status)
    {
        NSLog(@"Failed to load daemon");
    }
}
@end
