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

namespace azure {

class TCPConn {
public:
    TCPConn(int sock);
    ~TCPConn();

    bool IsConnected();

    bool RunLoop();

private:
    int sock_;
};

}

#endif //AZURE_TCP_CONN_H
