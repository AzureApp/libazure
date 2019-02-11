/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : tcp_server.h                                                       *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_TCP_SERVER_H
#define AZURE_TCP_SERVER_H

#include <functional>
#include <memory>
#include <string>
#include "delegate.h"
#include "tcp_conn.h"

namespace azure {

using ConnectionCallback = std::function<void(int)>;

class TCPServer {
 public:
  TCPServer(const std::string& address, short port);
  ~TCPServer();

  bool Setup();
  std::shared_ptr<TCPConn> AwaitConnection(int timeout_ms = -1);

  const std::string& address() const { return address_; }
  short port() const { return port_; }
  int sock() const { return sock_; }

 private:
  std::string address_;
  short port_;
  int sock_;
};

}  // namespace azure

#endif  // AZURE_TCP_SERVER_H
