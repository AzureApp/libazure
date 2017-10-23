#ifndef __SHARED__
#define __SHARED__

#include <iostream>

#include "data_objects/meta_object.h"
#include "../libazure/data_objects/search_object.h"

static void PrintDataObject(const azure::DataObject &obj) {
    std::cout << "magic: 0x" << std::hex << obj.magic << " type: " << obj.type << std::endl;
}

static void PrintDataObject(const azure::SearchObject &obj) {
    std::cout << "magic: 0x" << std::hex << dataObj.magic << " type: " << so2.type << " address: 0x" << std::hex << so2.addr << " " << std::endl;
}

#endif
