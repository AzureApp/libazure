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

}

}