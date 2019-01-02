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

namespace azure {

class ClientAgent;
class MetaObject;

class MessageHandler {
 public:
  MessageHandler(const ClientAgent *agent) : agent_(agent) {}

  virtual int HandleMessage(const MetaObjectRef &obj) {}

 private:
  const ClientAgent *agent_;
};

using MessageHandlerRef = std::unique_ptr<MessageHandler>;

}  // namespace azure

#endif  // AZURE_MESSAGE_HANDLER_H
