//
//  MemoryManager.cpp
//  Azure Mac V3
//
//  Created by callum taylor on 17/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "MemoryManager.h"
#include "Azure.h"
MemoryManager* MemoryManager::manager = NULL;

MemoryManager::MemoryManager():
currentProcess(0)
{

}

MemoryManager* MemoryManager::GetInstance()
{
    if(!manager)
    {
        manager = new MemoryManager();
    }
    return manager;
}

kern_return_t MemoryManager::AttachToProcess(Process *proc)
{
    if(proc->pid > 0)
    {
        this->currentProcess = proc;
        kern_return_t status = ProcessUtils::TryAttach(proc);
        if(status != KERN_SUCCESS)
        {
            AZLog("an error occured when attaching to process [%s-%d]: %s", proc->name, proc->pid, mach_error_string(status));
        }
        return status;
    }
    this->currentProcess = NULL;
    return KERN_FAILURE;
}

std::vector<vm_address_t> MemoryManager::Results()
{
    return savedAddresses;
}

std::vector<vm_address_t> MemoryManager::Find(void *data, size_t dataCnt)
{
    std::vector<vm_address_t> results;
    
    std::vector<Process::Region> regions = currentProcess->GetRegions(VM_PROT_READ | VM_PROT_WRITE);
    
    for(auto it = regions.begin(); it != regions.end(); ++it)
    {
        Process::Region region = *it;
        long long readsz = region.size;
        char *buffer = new char[readsz];
        
        kern_return_t status = currentProcess->ReadMemory(region.start, buffer, readsz);
        if(status != KERN_SUCCESS)
        {
            AZLog("read error: %s\n region size: 0x%llx\n", mach_error_string(status), region.size);
            return results;
        }
        
        for (int i = 0; (i+dataCnt) < readsz; i+=4) // i += dataTypeSize
        {
            if (!memcmp(data, buffer+i, dataCnt))
            {
               results.push_back(region.start+i);
            }
        }
        delete buffer;
    }
    if (results.size() > 10000000) {
        results.resize(10000000); // change me later
    }
    savedAddresses = results;
    return results;
}

std::vector<vm_address_t> MemoryManager::Iterate(void *data, size_t dataCnt, std::vector<vm_address_t> addresses)
{
    std::vector<vm_address_t> results;
    if (addresses.size() <= 0)
    {
        AZLog("no saved addresses");
        return results;
    }
    
    for (auto it = addresses.begin(); it != addresses.end(); ++it)
    {
        char *temp = (char*)malloc(dataCnt);
        currentProcess->ReadMemory(*it, temp, dataCnt);
        if(!memcmp(temp, data, dataCnt))
        {
            results.push_back(*it);
        }
        free(temp);
    }
    savedAddresses = results;
    return results;
}


