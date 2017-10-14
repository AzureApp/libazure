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

namespace azure {

class TCPServer {
public:
    TCPServer(std::string address, short port)
            : address_(address), port_(htons(port)) {};

    bool Setup();

    bool Run();

private:
    std::string address_;
    short port_;
    int sock_;
};

}

#endif //AZURE_TCP_SERVER_H
