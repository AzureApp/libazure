/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : tcp_server.h                                                        *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */
#ifndef AZURE_TCP_SERVER_H
#define AZURE_TCP_SERVER_H

#include <string>

class TCPServer {
public:
    TCPServer(std::string address, short port);
    int Run();
private:
    std::string address_;
    short port_;
};


#endif //AZURE_TCP_SERVER_H
