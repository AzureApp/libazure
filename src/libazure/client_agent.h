/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : client_agent.h                                                     *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_CLIENT_AGENT_H
#define AZURE_CLIENT_AGENT_H

#include <memory>
#include "message_handler.h"
#include "message_receiver.h"
#include "tcp_conn.h"

namespace azure {

using MessageHandlerPair = std::map<ObjectType, MessageHandlerRef>;

/**
 * Each client agent represents one connection to a client
 */
class ClientAgent {
 public:
  enum class RegisterStatus { Success = 0, HandlerIsNull, HandlerIsDefined };

  explicit ClientAgent(int client_fd);
  explicit ClientAgent(std::shared_ptr<TCPConn>& conn);

  bool Setup();
  int Run();

  RegisterStatus RegisterMessageHandler(ObjectType type, MessageHandlerRef ref);

 private:
  std::shared_ptr<TCPConn> conn_;
  MessageReceiver receiver_;
  MessageHandlerPair message_handlers_;
};

}  // namespace azure

#endif  // AZURE_CLIENT_AGENT_H
