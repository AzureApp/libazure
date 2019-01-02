/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : daemon.cc                                                          *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "daemon.h"
#include <functional>
#include "client_agent.h"
#include "logging.h"

namespace azure {

Daemon::Daemon(std::string ip, short port) : server_(ip, port) {}

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

}  // namespace azure
