/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : core.cc                                                            *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "core.h"

namespace azure {

Core::Core(const std::string& host, uint16_t port) : host_(host), port_(port) {
  builder_.AddListeningPort(host + ":" + std::to_string(port),
                            grpc::InsecureServerCredentials());
}

void Core::AddService(Service* service) {
  builder_.RegisterService(service);
}

void Core::Run() {
  server_ = builder_.BuildAndStart();
  return server_->Wait();
}

}  // namespace azure