/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : message_handle.h                                                   *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_MESSAGE_HANDLE_H
#define AZURE_MESSAGE_HANDLE_H

#include <msgpack.hpp>
#include "data_objects/meta_object.h"
#include "logging.h"

namespace azure {
/**
 * A handle encapsulating an ACP data object
 * Used to find the type of an object at runtime
 */
class MessageHandle {
 public:
  MessageHandle(msgpack::object object) : object_(object) {}

  ObjectType type() const {
    MetaObject temp = object_.as<MetaObject>();
    return temp.type;
  }

  bool is_valid() const {
    try {
      MetaObject temp = object_.as<MetaObject>();
    } catch (msgpack::type_error e) {
      return false;
    }
    return true;
  }

  template <typename T>
  T as() const {
    static_assert(std::is_base_of<MetaObject, T>::value,
                  "T is not an ACP object");
    try {
      T obj = object_.as<T>();
      return obj;
    } catch (msgpack::type_error e) {
      AZLogE("Received invalid ACP object");
      exit(1);  // TODO: more graceful here (or try and recover)
    }
  }

  operator bool() const { return is_valid(); }

 private:
  msgpack::object object_;
};

}  // namespace azure

#endif