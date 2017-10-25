/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : daemon.h                                                            *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_DAEMON_H
#define AZURE_DAEMON_H

#include <string>
#include "tcp_server.h"

namespace azure {

class Daemon {
public:
    Daemon(int argc, char **argv);
    Daemon(int argc, char **argv, std::string ip, short port);
    ~Daemon();

    int Run();

    void SpawnAgent(int client_fd);
private:
    int argc_;
    char **argv_;

    TCPServer server_;
};

}

#endif //AZURE_DAEMON_H
