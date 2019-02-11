/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : message_receiver.cc                                                *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "message_receiver.h"
#include "logging.h"

namespace azure {

MessageReceiver::MessageReceiver(std::shared_ptr<TCPConn> conn) : conn_(conn) {}

MessageHandle MessageReceiver::NextMessage() {
  msgpack::object_handle result;
  unpacker_.reserve_buffer(base_size);

  size_t actual_read_size;
  while ((actual_read_size = conn_->ReadBuf(unpacker_.buffer(), base_size)) >
         0) {
    // tell msgpack::unpacker actual consumed size.
    unpacker_.buffer_consumed(actual_read_size);

    if (unpacker_.next(result)) {
      break;
    }
  }
  return MessageHandle(std::move(result));
}

}  // namespace azure
