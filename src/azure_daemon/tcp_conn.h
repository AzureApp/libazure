/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : tcp_conn.h                                                          *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_TCP_CONN_H
#define AZURE_TCP_CONN_H

class TCPConn {
public:
    TCPConn(int socket_desc);

private:
    int socket_desc_;
};


#endif //AZURE_TCP_CONN_H
