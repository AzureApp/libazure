/**
 ******************************************************************************
 * Azure : Open Source Multi-Target Memory Editor                             *
 * File  : tcp_conn.cc                                                        *
 ******************************************************************************
 * Copyright 2018 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include "tcp_conn.h"
#include "logging.h"

namespace azure {

TCPConn::TCPConn(int sock) : sock_(sock) {

}

TCPConn::~TCPConn() {
    close(sock_);
}

bool TCPConn::IsConnected() const {
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(sock_, &rfd);
    timeval tv = {0};
    select(sock_ + 1, &rfd, 0, 0, &tv);
    if (!FD_ISSET(sock_, &rfd))
        return false;
    int n = 0;
    ioctl(sock_, FIONREAD, &n);
    return n == 0;
}

int TCPConn::DataAvailable() const {
    fd_set rfd;
    FD_ZERO(&rfd);
    FD_SET(sock_, &rfd);
    timeval tv = {0};
    select(sock_ + 1, &rfd, 0, 0, &tv);
    if (!FD_ISSET(sock_, &rfd))
        return false;
    int n = 0;
    ioctl(sock_, FIONREAD, &n);
    return n;
}

int8_t TCPConn::ReadChar() const {
    int8_t c;
    ReadBuf(&c, sizeof(c));
    return c;
}

uint8_t TCPConn::ReadUChar() const {
    uint8_t c;
    ReadBuf(&c, sizeof(c));
    return c;
}

int16_t TCPConn::ReadShort() const {
    int16_t s;
    ReadBuf(&s, sizeof(s));
    return s;
}

uint16_t TCPConn::ReadUShort() const {
    uint16_t s;
    ReadBuf(&s, sizeof(s));
    return s;
}

int32_t TCPConn::ReadInt() const {
    int32_t i;
    ReadBuf(&i, sizeof(i));
    return i;
}

uint32_t TCPConn::ReadUInt() const {
    uint32_t i;
    ReadBuf(&i, sizeof(i));
    return i;
}

int64_t TCPConn::ReadLong() const {
    int64_t l;
    ReadBuf(&l, sizeof(l));
    return l;
}

uint64_t TCPConn::ReadULong() const {
    uint64_t l;
    ReadBuf(&l, sizeof(l));
    return l;
}

ssize_t TCPConn::ReadBuf(void *buf, size_t size) const {
    return recv(sock_, buf, size, 0);
}

int8_t TCPConn::PeekChar() const {
    int8_t c;
    PeekBuf(&c, sizeof(c));
    return c;
}

uint8_t TCPConn::PeekUChar() const {
    uint8_t c;
    PeekBuf(&c, sizeof(c));
    return c;
}

int16_t TCPConn::PeekShort() const {
    short s;
    PeekBuf(&s, sizeof(s));
    return s;
}

uint16_t TCPConn::PeekUShort() const {
    uint16_t s;
    PeekBuf(&s, sizeof(s));
    return s;
}

int32_t TCPConn::PeekInt() const {
    int32_t i;
    PeekBuf(&i, sizeof(i));
    return i;
}

uint32_t TCPConn::PeekUInt() const {
    uint32_t i;
    PeekBuf(&i, sizeof(i));
    return i;
}

int64_t TCPConn::PeekLong() const {
    int64_t l;
    PeekBuf(&l, sizeof(l));
    return l;
}

uint64_t TCPConn::PeekULong() const {
    uint64_t l;
    PeekBuf(&l, sizeof(l));
    return l;
}

ssize_t TCPConn::PeekBuf(void *buf, size_t size) const {
    return recv(sock_, buf, size, MSG_PEEK);
}

void TCPConn::WriteChar(int8_t c) {
    WriteBuf(&c, sizeof(c));
}

void TCPConn::WriteUChar(uint8_t c) {
    WriteBuf(&c, sizeof(c));
}

void TCPConn::WriteShort(int16_t s) {
    WriteBuf(&s, sizeof(s));
}

void TCPConn::WriteUShort(uint16_t s) {
    WriteBuf(&s, sizeof(s));
}

void TCPConn::WriteInt(int32_t i) {
    WriteBuf(&i, sizeof(i));
}

void TCPConn::WriteUInt(uint32_t i) {
    WriteBuf(&i, sizeof(i));
}

void TCPConn::WriteLong(int64_t l) {
    WriteBuf(&l, sizeof(l));
}

void TCPConn::WriteULong(uint64_t l) {
    WriteBuf(&l, sizeof(l));
}

ssize_t TCPConn::WriteBuf(void *buf, size_t size) {
    return send(sock_, buf, size, 0);
}

}
