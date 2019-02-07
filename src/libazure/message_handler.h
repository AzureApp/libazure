/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : message_handler.h                                                  *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_MESSAGE_HANDLER_H
#define AZURE_MESSAGE_HANDLER_H

#include <memory>
#include "data_objects/meta_object.h"
#include "message_handle.h"

namespace azure {

class ClientAgent;
class MetaObject;

class MessageHandler {
 public:
  enum MessageResult { Success = 0, InvalidObject, LogicFail };

  MessageHandler(const ClientAgent *agent) : agent_(agent) {}

  virtual int HandleMessage(const MessageHandle &object_handle) {
    throw std::runtime_error("virtual base HandleMessage() called directly");
  }

 private:
  const ClientAgent *agent_;
};

using MessageHandlerRef = std::unique_ptr<MessageHandler>;

}  // namespace azure

#endif  // AZURE_MESSAGE_HANDLER_H
