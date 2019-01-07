/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : message_receiver.h                                                 *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_MESSAGE_RECEIVER_H
#define AZURE_MESSAGE_RECEIVER_H

#include "data_objects/meta_object.h"
#include "logging.h"
#include "message_handle.h"
#include "tcp_conn.h"

namespace azure {

using MetaObjectRef = std::unique_ptr<MetaObject>;

const int base_size = 128;  // read 128 bytes from buffer by default

class MessageReceiver {
 public:
  MessageReceiver(TCPConn *conn);
  MessageHandle NextMessage();

 private:
  TCPConn *conn_;
  msgpack::unpacker unpacker_;
};

}  // namespace azure

#endif  // AZURE_MESSAGE_HANDLER_H
