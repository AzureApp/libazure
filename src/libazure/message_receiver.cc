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

MessageReceiver::MessageReceiver(TCPConn *conn) : conn_(conn) {}

MessageHandle MessageReceiver::NextMessage() {
  msgpack::object_handle result;
  while (!unpacker_.next(result)) {
    unpacker_.reserve_buffer(base_size);
    size_t actual_read_size =
        (size_t)conn_->ReadBuf(unpacker_.buffer(), base_size);

    // tell msgpack::unpacker actual consumed size.
    unpacker_.buffer_consumed(actual_read_size);
  }
  return MessageHandle(result.get());
}

}  // namespace azure
