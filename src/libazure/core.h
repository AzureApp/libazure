/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : core.h                                                             *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_CORE_H
#define AZURE_CORE_H

#include <grpc++/grpc++.h>
#include <memory>
#include <string>
#include <vector>

namespace azure {

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Service;
using grpc::Status;

constexpr uint16_t AZ_DEFAULT_PORT = 1248;

class Core {
 public:
  explicit Core(const std::string& host, uint16_t port = AZ_DEFAULT_PORT);

  void AddService(Service* service);
  void Run();

  const std::string& host() const { return host_; }
  uint16_t port() const { return port_; }

 private:
  std::string host_;
  uint16_t port_;
  ServerBuilder builder_;
  std::unique_ptr<Server> server_;
};

}  // namespace azure

#endif