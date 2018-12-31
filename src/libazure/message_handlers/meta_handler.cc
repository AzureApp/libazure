/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : meta_handler.cc                                                    *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include "meta_handler.h"
#include <logging.h>

namespace azure {

int MetaHandler::HandleMessage(const MetaObjectRef &obj) {
  AZLog("Meta handler called");
  return 0;
}

}  // namespace azure
