//
//  DataObject.cpp
//  Azure
//
//  Created by callum taylor on 07/02/2014.
//
//

#include "DataObject.h"


DataObject::DataObject(void* data, size_t dataCnt)
{
    _data = malloc(dataCnt);
    memcpy(_data, data, dataCnt);
}

DataObject::~DataObject()
{
    free(_data);
}

void* DataObject::data()
{
    return _data;
}


SearchObject::SearchObject(SearchType type, void* data, size_t dataCnt) : DataObject(data, dataCnt)
{
    _type = type;
}

WriteObject::WriteObject(uint address, void* data, size_t dataCnt) : DataObject(data, dataCnt)
{
    _address = address;
}
