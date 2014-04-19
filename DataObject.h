//
//  SearchObject.h
//  Azure
//
//  Created by callum taylor on 07/02/2014.
//
//

#ifndef __Azure__SearchObject__
#define __Azure__SearchObject__

#include <iostream>
#include <sys/types.h>



enum SearchType
{
    IntegerSearch,
    FloatSearch,
    HexDataSearch,
    StringSearch
};

class DataObject
{ // I don't even...
public:
    void* data();
    int _dataCnt;
    DataObject(void* data, size_t dataCnt);
    ~DataObject();
    
private:
    void* _data;
};


class SearchObject : public DataObject
{
public:
    SearchType _type;
    SearchObject(SearchType type, void* data, size_t dataCnt);
};


class WriteObject : public DataObject
{
public:
    uint _address;
    WriteObject(uint address, void* data, size_t dataCnt);
};

#endif /* defined(__Azure__SearchObject__) */