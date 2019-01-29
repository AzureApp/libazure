/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : handshake_object.h                                                 *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_HANDSHAKE_OBJECT_H
#define AZURE_HANDSHAKE_OBJECT_H

#include <string>
#include "meta_object.h"

namespace azure {

enum class OperatingSystem { Windows, iOS, macOS, Android, Linux };

struct HandshakeObject : public MetaObject {
  HandshakeObject() : MetaObject(ObjectType::Handshake) {}
  std::string acp_version;
  OperatingSystem system;

  MSGPACK_DEFINE(magic, type, acp_version, system);
};

}  // namespace azure

MSGPACK_ADD_ENUM(azure::OperatingSystem);

#endif