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

#include <gflags/gflags.h>
#include <linenoise.h>

#include <data_objects/meta_object.h>
#include <data_objects/search_object.h>
#include <daemon.h>
#include <logging.h>

DEFINE_bool(daemon, true, "Run azure as a daemon");

namespace azure {

extern "C" int msgpack_main(int argc, char **argv) {
    msgpack::sbuffer buffer;

    SearchObject so(0x12345678);
    msgpack::pack(buffer, so);

    msgpack::object_handle oh = msgpack::unpack(buffer.data(), buffer.size());

    msgpack::object obj = oh.get();
    MetaObject dataObj = obj.convert();

    std::cout << "magic: 0x" << std::hex << dataObj.magic << " type: " << dataObj.type << std::endl;

    SearchObject so2 = obj.convert();
    std::cout << "magic: 0x" << std::hex << dataObj.magic << " type: " << so2.type << " address: 0x" << std::hex << so2.addr << " " << std::endl;
}

extern "C" int main(int argc, char **argv) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_daemon) {
        AZLog("Starting azure in daemon mode");
        Daemon daemon(argc, argv);
        return daemon.Run();
    } else {
        AZLog("Starting azure in command-line mode");
        char *line;
        while((line = linenoise("azure> ")) != NULL) {
          printf("You wrote: %s\n", line);
          linenoiseFree(line); /* Or just free(line) if you use libc malloc. */
            if (!strcmp(line, "quit")) break;
        }
    }

    msgpack_main(argc, argv);
}

}
