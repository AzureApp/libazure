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
#include <signal.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include "Message.h"
#include "Messaging.h"
    
class Daemon {
    int socket_desc , client_sock , c, port;
    struct sockaddr_in server , client;
    bool serverReady;
    
    void OnLostConnection();
    
public:
    Daemon();
    ~Daemon();
    
    AZ_STATUS Start();
    bool HasDataAvailable();
    void Close();
    
    AZ_STATUS ReceivedMessage(Message&);
    AZ_STATUS SendMessage(Message&);
    
    void SendMessageReceiveSuccess();
};

#endif /* defined(__Azure_Mac_V3__DaemonUtils__) */
