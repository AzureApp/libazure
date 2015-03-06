//
//  DaemonUtils.m
//  Azure
//
//  Created by callum taylor on 02/08/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "Daemon.h"
#import "MessageHandler.h"

@implementation Daemon

@synthesize sock, ready, messageStack, inputStream, outputStream;

+ (instancetype)currentDaemon {
    static id inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = [[Daemon alloc] init];
        [inst start];
    });
    return inst;
}

- (void)start {
    CFReadStreamRef readStream;
    CFWriteStreamRef writeStream;
    CFStreamCreatePairWithSocketToHost(NULL,(CFStringRef)@"localhost",1248 ,&readStream ,&writeStream);
    
    inputStream = (__bridge NSInputStream *)readStream;
    outputStream = (__bridge NSOutputStream *)writeStream;
    
    [inputStream setDelegate:self];
    [outputStream setDelegate:self];
    
    [inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    
    [inputStream open];
    [outputStream open];
    
    self.ready = YES;
}

- (void)sendMessage:(struct Message)message {
    long chunk_size = 64;
    if (self.ready) {
        if ([outputStream hasSpaceAvailable]) {
            unsigned char *data = (unsigned char*)message.message;
            struct msg_header header = message.header;
            [outputStream write:(unsigned char*)&header maxLength:sizeof(struct msg_header)];
            
            long msg_size = message.header.messageSize;
            if (msg_size > 0) {
                long write_size = 0;
                
                while (write_size <= msg_size) {
                    if ((write_size + chunk_size) > msg_size)
                    {
                        chunk_size = msg_size - write_size;
                        if (chunk_size == 0) break;
                    }
                    write_size += [outputStream write:data+write_size maxLength:chunk_size];
                }
            }
        }
        self.ready = NO;
    }
    else {
        NSAlert *alert = [[NSAlert alloc] init];
        [alert setMessageText: @"Azure is currently busy"];
        [alert runModal];
    }
}

- (void)receiveMessage:(struct Message)message {
    NSLog(@"\nmsg type: %s\nmsg size: %ld\n", enumToName(message.header.type), message.header.messageSize);
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
            if (stream == inputStream)
            {
                while ([inputStream hasBytesAvailable])
                {
                    long chunk_size = 64;
                    struct msg_header header;
                    long bytes = [inputStream read:(unsigned char*)&header maxLength:sizeof(struct msg_header)];
                    MessageHandler *handler = [MessageHandler sharedInstance];
                    if ([handler isMessageValid:*(struct Message*)&header])
                    {
                        if (bytes > 0)
                        {
                            long msg_size = header.messageSize;
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
                                    long bytes = [inputStream read:data+read_size maxLength:chunk_size];
                                    if (bytes == -1)
                                    {
                                        // error
                                        return;
                                    }
                                    read_size += bytes;
                                }
                            }
                            struct Message msg;
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
                    }
                }
            }
            break;
        }
		case NSStreamEventErrorOccurred:
        {
			NSLog(@"%@",stream.streamError);
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
@end
