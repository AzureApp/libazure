/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : data_object.h                                                       *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_DATA_OBJECT_H
#define AZURE_DATA_OBJECT_H

#include <msgpack.hpp>

#define AZ_MAGIC 0xABAD1DEA

namespace azure {

/**
 * Base DataObject type used to define the type of the object
 */
struct MetaObject {
    enum Type {
        Meta,
        Search
    };

    MetaObject() {}
    MetaObject(Type type) : type(type) {}
    uint32_t magic = AZ_MAGIC;
    Type type;

    MSGPACK_DEFINE(magic, type);
};

using MetaObjectRef = std::unique_ptr<MetaObject>;

}

MSGPACK_ADD_ENUM(azure::MetaObject::Type);

#include "search_object.h"

#endif //AZURE_DATA_OBJECT_H
