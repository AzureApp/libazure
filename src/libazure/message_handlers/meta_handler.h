/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : meta_handler.h                                                     *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_META_HANDLER_H
#define AZURE_META_HANDLER_H

#include <memory>
#include "data_objects/meta_object.h"
#include "message_handler.h"

namespace azure {

class MetaHandler : public MessageHandler {
 public:
  MetaHandler(const ClientAgent *agent) : MessageHandler(agent) {}

  int HandleMessage(const MessageHandle &object_handle) override;
};

}  // namespace azure

#endif  // AZURE_META_HANDLER_H
