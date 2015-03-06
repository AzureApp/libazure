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
    
public:
    Daemon();
    
    void Start();
    int Tick();
    
    int Connect();
    
    void OnLostConnection();
    void OnNewConnection(int);
    bool IsConnected();
    
    void SendMessage(Message &);
    void ReceiveMessage();

};
}

#endif /* defined(__Azure_Mac_V3__DaemonUtils__) */
