//
//  DaemonUtils.h
//  Azure Mac V3
//
//  Created by callum taylor on 14/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#ifndef __Azure_Mac_V3__DaemonUtils__
#define __Azure_Mac_V3__DaemonUtils__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>

#include "Message.h"
#include "Messaging.h"


namespace DaemonUtils {
    
class Daemon {
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
    bool serverReady;
    
    void OnLostConnection();
    
public:
    static Daemon CurrentDaemon();
    Daemon();
    ~Daemon();
    
    void Start();
    
    kern_return_t ReceivedMessage(Message&);
    kern_return_t SendMessage(Message&);
    
    void SendMessageReceiveSuccess();
};
} // DaemonUtils

#endif /* defined(__Azure_Mac_V3__DaemonUtils__) */
