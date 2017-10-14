/**
 ******************************************************************************
 * Azure : Open Source iOS Memory Editor                                      *
 * File : daemon_main.cc                                                      *
 ******************************************************************************
 * Copyright 2017 Satori. All rights reserved.                                *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <iostream>
#include <vector>

#include "tcp_server.h"

#include "data_objects/data_object.h"
#include "data_objects/search_object.h"

namespace azure {

extern "C" int main(int argc, char **argv) {
    TCPServer srv("127.0.0.1", 1248);
    srv.Setup();
    srv.Run();
}

extern "C" int msgpack_main(int argc, char **argv) {
    msgpack::sbuffer buffer;

    SearchObject so(0x12345678);
    msgpack::pack(buffer, so);

    msgpack::object_handle oh = msgpack::unpack(buffer.data(), buffer.size());

    msgpack::object obj = oh.get();
    DataObject dataObj = obj.convert();

    std::cout << "type: " << dataObj.type << std::endl;

    SearchObject so2 = obj.convert();
    std::cout << "type: " << so2.type << " address: 0x" << std::hex << so2.addr << " " << std::endl;
}

}
