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

class MemoryManager {
public:
    
    MemoryManager();
    ~MemoryManager();
    
    static MemoryManager *GetInstance();
    static MemoryManager *manager;
    
    kern_return_t AttachToProcess(Process *);
    
    std::vector<vm_address_t> Results();
    
    std::vector<vm_address_t> Find(void* data, size_t dataCnt);
    std::vector<vm_address_t> Iterate(void *data, size_t dataCnt, std::vector<vm_address_t> addresses);
    
    kern_return_t Write(vm_address_t addr, void* data, size_t dataCnt);
private:
    Process *currentProcess;
    std::vector<vm_address_t> savedAddresses;
};

#endif /* defined(__Azure_Mac_V3__AzureEngine__) */
