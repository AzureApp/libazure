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

MetaObjectRef MessageReceiver::NextMessage() {
    msgpack::object_handle result;
    if (unpacker_.next(result)) {
        return LoadMessage(result);
    } else {
        unpacker_.reserve_buffer(base_size);
        std::size_t actual_read_size = conn_->ReadBuf(unpacker_.buffer(), base_size);

        // tell msgpack::unpacker actual consumed size.
        unpacker_.buffer_consumed(actual_read_size);

        return NextMessage();
    }
}

MetaObjectRef MessageReceiver::LoadMessage(msgpack::object_handle &handle) {
    MetaObject temp = handle.get().convert();

    switch (temp.type) {
        case ObjectType::Meta: {
            return std::unique_ptr<MetaObject>(new MetaObject(handle.get().as<MetaObject>()));
            break;
        }
    }

}

}
