/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : tcp_server.cc                                                      *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "tcp_server.h"
#include <arpa/inet.h>
#include <unistd.h>
#include "logging.h"
#include "tcp_conn.h"

namespace azure {

TCPServer::TCPServer(const std::string &address, short port)
    : address_(address), port_(port) {}

TCPServer::~TCPServer() {
  close(sock_);
  AZLog("Socket %d terminated", sock_);
}

bool TCPServer::Setup() {
  AZLog("Creating listen server at %s:%d", address_.c_str(), port_);

  sock_ = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in address;
  // memset(&address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(port_);
  address.sin_addr.s_addr = inet_addr(address_.c_str());

  int optval = 1;
  setsockopt(sock_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);
  signal(SIGPIPE, SIG_IGN);

  int result = ::bind(sock_, (struct sockaddr *)&address, sizeof(address));
  if (result != 0) {
    AZLogE("%s: bind() failed", strerror(errno));
    return false;
  }
  result = listen(sock_, 10);
  if (result != 0) {
    AZLogE("listen() failed: %s", strerror(errno));
    return false;
  }

  return true;
}

std::shared_ptr<TCPConn> TCPServer::AwaitConnection(int timeout_ms) {
  fd_set read_set;
  FD_ZERO(&read_set);
  FD_SET(sock_, &read_set);

  struct timeval *timeout = nullptr;
  if (timeout_ms > 0) {
    timeout = new struct timeval;
    timeout->tv_sec = timeout_ms / 1000;
    timeout->tv_usec = (timeout_ms % 1000) * 1000;
  } else {
    AZLog("Awaiting client");
  }

  int res = select(sock_ + 1, &read_set, NULL, NULL, timeout);

  delete timeout;
  // socket has a connection
  if (res > 0) {
    int client_sock = accept(sock_, 0, 0);
    if (client_sock < 0) {
      AZLogE("Client accept() failed %s [sock: %d]", strerror(errno), sock_);
      throw std::runtime_error("accept() failed");
    }

    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    int res = getpeername(client_sock, (struct sockaddr *)&addr, &addr_size);

    if (res == 0) {
      char *client_ip = new char[20];
      strncpy(client_ip, inet_ntoa(addr.sin_addr), 20);

      AZLog("Client connected [%s:%d]", client_ip, addr.sin_port);

    } else {
      AZLogW("Falied to get peer info for new connection");
    }
    return std::make_shared<TCPConn>(client_sock);
  }
  return nullptr;
}

}  // namespace azure
