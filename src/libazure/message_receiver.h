/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : message_handler.h                                                   *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_MESSAGE_RECEIVER_H
#define AZURE_MESSAGE_RECEIVER_H

#include <tcp_conn.h>
#include "data_objects/meta_object.h"

namespace azure {

const int base_size = 128; // read 128 bytes from buffer by default

class MessageReceiver {
public:
    MessageReceiver(TCPConn *conn);

    MetaObjectRef NextMessage();
private:
    TCPConn *conn_;
    msgpack::unpacker unpacker_;
};

}

#endif //AZURE_MESSAGE_HANDLER_H
