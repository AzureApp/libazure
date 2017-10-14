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
#include <unistd.h>
#include <thread>
#include "tcp_server.h"
#include "tcp_conn.h"
#include "logging.h"

namespace azure {

TCPServer::TCPServer(std::string address, short port)
        : address_(address), port_(port) {

}

TCPServer::~TCPServer() {
    close(sock_);
    AZLog("Socket %d terminated", sock_);
}

bool TCPServer::Setup() {
    AZLog("Creating listen server at %s:%d", address_.c_str(), port_);

    sock_ = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    //memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port_);
    inet_pton(AF_INET, address_.c_str(), &address.sin_addr);

    int optval = 1;
    setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
    setsockopt(sock_, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof optval);

    int result = ::bind(sock_, (struct sockaddr *) &address, sizeof(address));
    if (result != 0) {
        AZLogE("%s: bind() failed", strerror(errno));
        return result;
    }
    result = listen(sock_, 10);
    if (result != 0) {
        AZLogE("listen() failed: %s", strerror(errno));
        return result;
    }

    return result;
}

bool TCPServer::Run() {
    while (true) {
        AZLog("Awaiting client");
        int client_sock = accept(sock_, 0, 0);
        if (client_sock < 0) {
            return false; // error
        }

        std::thread([client_sock]() {
            AZLog("Client connected. Spawned client thread");

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