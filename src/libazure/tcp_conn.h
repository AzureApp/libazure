/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : tcp_conn.h                                                         *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef AZURE_TCP_CONN_H
#define AZURE_TCP_CONN_H

#include <stdint.h>
#include <sys/types.h>

namespace azure {

class TCPConn {
 public:
  TCPConn(int sock);
  ~TCPConn();

  bool IsConnected() const;
  int DataAvailable() const;
  int8_t ReadChar() const;
  uint8_t ReadUChar() const;
  int16_t ReadShort() const;
  uint16_t ReadUShort() const;
  int32_t ReadInt() const;
  uint32_t ReadUInt() const;
  int64_t ReadLong() const;
  uint64_t ReadULong() const;
  ssize_t ReadBuf(void *buf, size_t size) const;

  int8_t PeekChar() const;
  uint8_t PeekUChar() const;
  int16_t PeekShort() const;
  uint16_t PeekUShort() const;
  int32_t PeekInt() const;
  uint32_t PeekUInt() const;
  int64_t PeekLong() const;
  uint64_t PeekULong() const;
  ssize_t PeekBuf(void *buf, size_t size) const;

  void WriteChar(int8_t c);
  void WriteUChar(uint8_t c);
  void WriteShort(int16_t s);
  void WriteUShort(uint16_t s);
  void WriteInt(int32_t i);
  void WriteUInt(uint32_t i);
  void WriteLong(int64_t l);
  void WriteULong(uint64_t l);
  ssize_t WriteBuf(void *buf, size_t size);

  template <typename T>
  T Read();
  template <typename T>
  T Peek();
  template <typename T>
  void Write(T val);

  int sock() const { return sock_; }

 private:
  int sock_;
};

template <typename T>
T TCPConn::Read() {
  T temp;
  ReadBuf(&temp, sizeof(T));
  return temp;
}

template <typename T>
T TCPConn::Peek() {
  T temp;
  PeekBuf(&temp, sizeof(T));
  return temp;
}

template <typename T>
void TCPConn::Write(T val) {
  WriteBuf(&val, sizeof(T));
}

}  // namespace azure

#endif  // AZURE_TCP_CONN_H
