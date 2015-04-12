//
//  AzureEngine.h
//  Azure Mac V3
//
//  Created by callum taylor on 17/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#ifndef __Azure_Mac_V3__AzureEngine__
#define __Azure_Mac_V3__AzureEngine__

#include <iostream>
#include <vector>
#include "ProcessUtils.h"


typedef void* DataItem;

typedef std::vector<vm_address_t> AddressList;
typedef std::vector<DataItem> DataList;

class MemoryManager {
public:
    
    MemoryManager();
    ~MemoryManager();
    
    static MemoryManager *GetInstance();
    static MemoryManager *manager;
    
    AZ_STATUS AttachToProcess(Process *);
    void DetachFromProcess();
    
    AddressList *Results() const;
    DataList *DataList() const;
    int DataSize() const { return this->initialDataSize; }
    
    AZ_STATUS Find(void* data, size_t dataCnt);
    AZ_STATUS Iterate(void *data, size_t dataCnt, AddressList *addresses);
    AZ_STATUS FetchUpdatedResults();
    
    AZ_STATUS Write(vm_address_t addr, void* data, size_t dataCnt);
    void ResetResults();
private:
    Process *currentProcess;
    int initialDataSize;
    ::AddressList *savedAddresses;
    ::DataList *savedDataList;
};

#endif /* defined(__Azure_Mac_V3__AzureEngine__) */
