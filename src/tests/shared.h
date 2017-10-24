#ifndef __SHARED__
#define __SHARED__

#include <iostream>

#include "data_objects/meta_object.h"
#include "../libazure/data_objects/search_object.h"

static azure::SearchObject RecvObject(int fd) {
    std::size_t const try_read_size = 100;

    msgpack::unpacker unp;

    unp.reserve_buffer(try_read_size);
    std::size_t actual_read_size = recv(fd, unp.buffer(), try_read_size, 0);

    // tell msgpack::unpacker actual consumed size.
    unp.buffer_consumed(actual_read_size);

    msgpack::object_handle result;
    unp.next(result);
    return result.get().convert();
//        // Message pack data loop
//        while(unp.next(result)) {
//            msgpack::object obj(result.get());
//            // Use obj
//        }
//        // All complete msgpack message is proccessed at this point,
//        // then continue to read addtional message.
}

static void SendObject(int fd, azure::SearchObject &obj) {
    msgpack::sbuffer buffer;
    msgpack::pack(buffer, obj);

    send(fd, buffer.data(), buffer.size(), 0);
}

static void PrintDataObject(const azure::MetaObject &obj) {
    std::cout << "magic: 0x" << std::hex << obj.magic << " type: " << obj.type << std::endl;
}

static void PrintDataObject(const azure::SearchObject &obj) {
    std::cout << "magic: 0x" << std::hex << obj.magic << " type: " << obj.type << " address: 0x" << std::hex << obj.addr
              << " " << std::endl;
}

#endif
