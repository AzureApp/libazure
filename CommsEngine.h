//
//  CommsEngine.h
//  azured
//
//  Created by Callum Taylor on 19/08/2013.
//
//

#ifndef __azured__CommsEngine__
#define __azured__CommsEngine__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <vector>

using namespace std;

class CommsEngine
{
public:
    enum InitErrors
    {
        NoError = 0,
        SocketFailed,
        HostFailed
    };

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    
    char writebuffer[1024];
    char readbuffer[1024];
    
    int Init();
    ~CommsEngine();
    
    void SendMessage(const char *message);
    const char *ReadMessage();
    void ProcessMessage(const char * message);
    void ConnectionKeepAlive(/*args?*/);

    
};

#endif /* defined(__azured__CommsEngine__) */


