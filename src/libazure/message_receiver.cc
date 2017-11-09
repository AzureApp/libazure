/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : message_handler.cc                                                  *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "message_receiver.h"

namespace azure {

MessageReceiver::MessageReceiver(TCPConn *conn) : conn_(conn) {

}

MetaObject MessageReceiver::NextMessage() {
    msgpack::object_handle result;
    if (unpacker_.next(result)) {
        return result.get().convert(); 
    } else {
        unpacker_.reserve_buffer(base_size);
        std::size_t actual_read_size = conn_->ReadBuf(unpacker_.buffer(), base_size);

        // tell msgpack::unpacker actual consumed size.
        unpacker_.buffer_consumed(actual_read_size);

        return NextMessage();
    }
}

}
