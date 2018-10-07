/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : azure_info_object.h                                                *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_AZURE_INFO_OBJECT_H
#define AZURE_AZURE_INFO_OBJECT_H

#include "meta_object.h"

/**
 * ACP (Azure Communication Protocol) version, lets clients know which version of ACP
 * this host uses for compatibility reasons
 */
#define ACP_VERSION "1.0.0";

namespace azure {

    struct AzureInfoObject : MetaObject {
        AzureInfoObject() {}

        std::string acp_version;

    };
} // namespace azure


#endif //AZURE_AZURE_INFO_OBJECT_H
