//
// Created by satori on 25/10/2017.
//

#ifndef AZURE_META_HANDLER_H
#define AZURE_META_HANDLER_H

#include <memory>
#include "data_objects/meta_object.h"
#include "message_handler.h"

namespace azure {

class MetaHandler : public MessageHandler {
public:
    MetaHandler(ClientAgent *agent) : MessageHandler(agent) {}

    int HandleMessage(const MetaObject &obj) override;
};

}

#endif //AZURE_META_HANDLER_H
