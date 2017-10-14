/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : tcp_server.cc                                                       *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <arpa/inet.h>
#include <thread>
#include <memory>
#include "tcp_server.h"
#include "tcp_conn.h"

namespace azure {

bool TCPServer::Setup() {
    sock_ = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    //memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = port_;
    address.sin_addr.s_addr = INADDR_ANY;

    int optval = 1;
    setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
    setsockopt(sock_, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof optval);

    int result = ::bind(sock_, (struct sockaddr *) &address, sizeof(address));
    if (result != 0) {
        perror("bind() failed");
        return result;
    }
    result = listen(sock_, 10);
    if (result != 0) {
        //AZLog("listen() failed: %s", strerror(errno));
        return result;
    }

    return result;
}

bool TCPServer::Run() {
    while (true) {
        int client_sock = accept(sock_, 0, 0);
        if (client_sock < 0) {
            return false; // error
        }

        std::thread([client_sock]() {
            TCPConn conn(client_sock);
            while (conn.IsConnected()) {
                if (!conn.RunLoop()) {
                    break;
                }
            }
        }).detach();
    }
}

}