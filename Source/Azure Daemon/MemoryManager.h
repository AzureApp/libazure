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

typedef std::vector<vm_address_t> AddressList;

class MemoryManager {
public:
    
    MemoryManager();
    ~MemoryManager();
    
    static MemoryManager *GetInstance();
    static MemoryManager *manager;
    
    AZ_STATUS AttachToProcess(Process *);
    
    AddressList *Results();
    
    AZ_STATUS Find(void* data, size_t dataCnt);
    AZ_STATUS Iterate(void *data, size_t dataCnt, AddressList *addresses);
    
    AZ_STATUS Write(vm_address_t addr, void* data, size_t dataCnt);
    void ResetResults();
private:
    Process *currentProcess;
    AddressList *savedAddresses;
};

#endif /* defined(__Azure_Mac_V3__AzureEngine__) */
