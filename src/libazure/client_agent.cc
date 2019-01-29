/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : client_agent.cc                                                    *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "client_agent.h"
#include "data_objects/meta_object.h"
#include "logging.h"
#include "message_handle.h"
#include "message_handlers/meta_handler.h"

namespace azure {

using RegisterStatus = ClientAgent::RegisterStatus;

ClientAgent::ClientAgent(int client_fd) : conn_(client_fd), receiver_(&conn_) {
  // setup meta handler
  message_handlers_.emplace(ObjectType::Meta,
                            std::make_unique<MetaHandler>(this));
}

int ClientAgent::Run() {
  // TODO: change int return codes to proper errors
  while (true) {
    MessageHandle handle = receiver_.NextMessage();
    if (handle.is_valid()) {
      AZLogD("[client %d] Received message of type %s", conn_.sock(),
             object_type_to_string(handle.type()));

      const auto &handler = message_handlers_.find(handle.type())->second;
      int result = handler->HandleMessage(handle);
      if (result != 0) {
        return result;
      }
    } else {
      return 0;
    }
  }
}

RegisterStatus ClientAgent::RegisterMessageHandler(ObjectType type,
                                                   MessageHandlerRef ref) {
  // TODO: change int return codes to proper errors
  if (ref) {
    if (message_handlers_.find(type) == message_handlers_.end()) {
      message_handlers_.emplace(type, std::move(ref));

      return RegisterStatus::Success;
    }
    return RegisterStatus::HandlerIsDefined;
  }
  return RegisterStatus::HandlerIsNull;
}

}  // namespace azure
