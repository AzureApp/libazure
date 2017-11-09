/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : daemon.cc                                                            *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
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

    virtual int HandleMessage(const MetaObject &obj) {}
private:
    ClientAgent *agent_;
};

}

#endif //AZURE_MESSAGE_HANDLER_H
