/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : tcp_conn.cc                                                         *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include "tcp_conn.h"
#include "logging.h"

namespace azure {

TCPConn::TCPConn(int sock) : sock_(sock) {

}

TCPConn::~TCPConn() {
    close(sock_);
}

bool TCPConn::IsConnected() {
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(sock_, &rfd);
    timeval tv = { 0 };
    select(sock_+1, &rfd, 0, 0, &tv);
    if (!FD_ISSET(sock_, &rfd))
        return false;
    int n = 0;
    ioctl(sock_, FIONREAD, &n);
    return n == 0;
}

bool TCPConn::RunLoop() {
    char data[6];
    strcpy(data, "ping\n");
    if (send(sock_, data, sizeof(data), 0) != 6) {
        AZLogE("Failed to send data. Closing socket");
        return false;
    }
    char buf[256];
    recv(sock_, buf, 256, 0);
    AZLog("Received data: %s", buf);
}

}