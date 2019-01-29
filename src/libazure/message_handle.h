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
  MessageHandle(msgpack::object_handle handle)
      : object_handle_(std::move(handle)) {}

  ObjectType type() const {
    MetaObject temp = object_handle_.get().as<MetaObject>();
    return temp.type;
  }

  bool is_valid() const {
    try {
      MetaObject temp = object_handle_.get().as<MetaObject>();
      return temp.magic == AZ_MAGIC;
    } catch (msgpack::type_error e) {
      return false;
    }
  }

  template <typename T>
  T as() const {
    static_assert(std::is_base_of<MetaObject, T>::value,
                  "T is not an ACP object");
    try {
      T obj = object_handle_.get().as<T>();
      return obj;
    } catch (msgpack::type_error e) {
      AZLogE("Failed to decode ACP object");
      raise(SIGTRAP);  // exit(1);  // TODO: more graceful here (or try and
                       // recover)
    }
  }

  operator bool() const { return is_valid(); }

 private:
  msgpack::object_handle object_handle_;
};

}  // namespace azure

#endif