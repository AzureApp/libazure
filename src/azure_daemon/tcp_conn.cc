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
#include "tcp_conn.h"

namespace azure {

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
    // unused
}

}