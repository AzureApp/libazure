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
#include <msgpack.hpp>
#include <sstream>
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

  template <typename T>
  bool SendObject(const T& object) const {
    static_assert(std::is_base_of<MetaObject, T>::value,
                  "T is not a data object");

    msgpack::sbuffer buf;

    msgpack::pack(buf, object);

    size_t size = buf.size();

    std::stringstream ss;
    azure::hex_dump(buf.data(), size, ss);

    AZLogD("Sent data to client:\n %s", ss.str().c_str());

    return SendData(buf.data(), size);
  }

  const std::shared_ptr<TCPConn>& conn() const { return conn_; }
  const MessageReceiver& message_receiver() const { return receiver_; }

 private:
  bool SendData(void* data, size_t size) const;

  std::shared_ptr<TCPConn> conn_;
  MessageReceiver receiver_;
  MessageHandlerPair message_handlers_;
};

}  // namespace azure

#endif  // AZURE_CLIENT_AGENT_H
