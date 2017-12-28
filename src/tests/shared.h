#ifndef __SHARED__
#define __SHARED__

#include <iostream>

#include "data_objects/meta_object.h"
#include "../libazure/data_objects/search_object.h"

//struct Result {
//  uintptr_t address;
//  std::vector<unsigned char> value;
//  MSGPACK_DEFINE(address, value);
//};
//
//struct ResultObject : azure::MetaObject {
//  std::vector<Result> results;
//  ResultObject() {}
//  ResultObject(std::vector<Result> results) : results(results) {
//
//  }
//
//  MSGPACK_DEFINE(magic, type, results);
//};
//
//static ResultObject RecvObject(int fd) {
//    std::size_t const try_read_size = 100;
//
//    msgpack::unpacker unp;
//
//    unp.reserve_buffer(try_read_size);
//    std::size_t actual_read_size = recv(fd, unp.buffer(), try_read_size, 0);
//
//    // tell msgpack::unpacker actual consumed size.
//    unp.buffer_consumed(actual_read_size);
//
//    msgpack::object_handle result;
//    unp.next(result);
//    return result.get().convert();
////        // Message pack data loop
////        while(unp.next(result)) {
////            msgpack::object obj(result.get());
////            // Use obj
////        }
////        // All complete msgpack message is proccessed at this point,
////        // then continue to read addtional message.
//}
//
//static void SendObject(int fd, ResultObject &obj) {
//    msgpack::sbuffer buffer;
//    msgpack::pack(buffer, obj);
//
//    send(fd, buffer.data(), buffer.size(), 0);
//}

//static void PrintDataObject(const ResultObject &obj) {
//    PrintDataObject(static_cast<azure::MetaObject>(obj));
//    for (const Result &result : obj.results) {
//      std::cout << "address: 0x" << std::hex << result.address << " data: [";
//      for (int i = 0; i < result.value.size() - 1; i++) {
//        std::cout << std::hex << (int)result.value[i] << ", ";
//      }
//      std::cout << (int)result.value.back() << "]" << std::endl;
//    }
//}

static void SendDataObject(int fd, const azure::MetaObject &obj) {
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
