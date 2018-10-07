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

namespace azure {

class ClientAgent;
class MetaObject;

class MessageHandler {
public:
    MessageHandler(ClientAgent *agent) : agent_(agent) {}

    virtual int HandleMessage(const MetaObjectRef &obj) {}
private:
    ClientAgent *agent_;
};

using MessageHandlerRef = std::unique_ptr<MessageHandler>;

}

#endif //AZURE_MESSAGE_HANDLER_H
