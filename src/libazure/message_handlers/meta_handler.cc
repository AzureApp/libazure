//
// Created by satori on 25/10/2017.
//

#include <logging.h>
#include "meta_handler.h"

namespace azure {

int MetaHandler::HandleMessage(const MetaObjectRef &obj) {
    AZLog("Meta handler called");
    return 0;
}

}