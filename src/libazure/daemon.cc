/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : daemon.cc                                                          *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <functional>
#include "logging.h"
#include "daemon.h"
#include "client_agent.h"

namespace azure {

Daemon::Daemon(int argc, char **argv, std::string ip, short port)
        : argc_(argc), argv_(argv), server_(ip, port) {

}

Daemon::~Daemon() {
    // TODO: 
}

int Daemon::Run() {
    if (!server_.Setup()) {
        AZLogW("Could not set up TCP server");
        return 255;
    }
    return server_.AwaitConnections(ClientAgent::SpawnAgent);
}

}
