/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : flags.h                                                            *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_FLAGS_H
#define AZURE_FLAGS_H

#include <type_traits>

namespace azure {

#define CREATE_FLAG(Name, Enum)        \
  using Name = Flags<Enum>;            \
  Name operator|(Enum lhs, Enum rhs) { \
    using flag = Name;                 \
    return flag(lhs) | flag(rhs);      \
  }

template <typename Enum>
class Flags {
  static_assert(std::is_enum<Enum>::value, "Type is not an enum");
  using type = std::underlying_type_t<Enum>;
  using Flag = Flags<Enum>;

 public:
  Flags(Enum value) : enum_(value) {}
  explicit Flags(type value) : enum_(static_cast<Enum>(value)) {}

  Flag operator|(Flag other) const {
    return static_cast<Enum>(static_cast<type>(*this) |
                             static_cast<type>(other));
  }
  Flag operator|(Enum other) const { return *this | Flag(other); }
  Flag operator|(type other) const { return *this | Flag(other); }

  Flag& operator|=(Flag rhs) {
    *this = *this | rhs;
    return *this;
  }
  Flag& operator|=(type rhs) {
    *this = *this | Flag(rhs);
    return *this;
  }

  Flag operator&(Flag other) const {
    return static_cast<Enum>(static_cast<type>(*this) &
                             static_cast<type>(other));
  }
  Flag operator&(Enum other) const { return *this & Flag(other); }
  Flag operator&(type other) const { return *this & Flag(other); }

  Flag& operator&=(Flag rhs) {
    *this = *this & rhs;
    return *this;
  }
  Flag& operator&=(type rhs) {
    *this = *this & Flag(rhs);
    return *this;
  }

  Flag operator^(Flag other) const {
    return static_cast<Enum>(static_cast<type>(*this) ^
                             static_cast<type>(other));
  }
  Flag operator^(Enum other) const { return *this ^ Flag(other); }
  Flag operator^(type other) const { return *this ^ Flag(other); }

  Flag& operator^=(Flag rhs) {
    *this = *this ^ rhs;
    return *this;
  }
  Flag& operator^=(type rhs) {
    *this = *this ^ Flag(rhs);
    return *this;
  }

  Flag operator~() { return Flag(~static_cast<type>(enum_)); }
  bool operator!() const { return static_cast<type>(enum_) == 0; }
  explicit operator bool() const { return static_cast<type>(enum_) == 0; }
  explicit operator type() const { return value(); }

  type value() const { return static_cast<type>(enum_); }

 private:
  Enum enum_;
};

}  // namespace azure

#endif