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

AZ_STATUS MemoryManager::AttachToProcess(Process *proc)
{
    if(proc->pid > 0)
    {
        this->currentProcess = proc;
        AZ_STATUS status = ProcessUtils::TryAttach(proc);
        if(status != AZ_SUCCESS)
        {
            AZLog("an error occured when attaching to process [%s-%d]: %s", proc->name, proc->pid, mach_error_string(status));
        }
        return status;
    }
    this->currentProcess = NULL;
    return AZ_FAILURE;
}

std::vector<vm_address_t> MemoryManager::Results()
{
    return savedAddresses;
}

std::vector<vm_address_t> MemoryManager::Find(void *data, size_t dataCnt)
{
    std::vector<vm_address_t> results;
    
    std::vector<Process::Region> regions = currentProcess->GetRegions(VM_PROT_READ | VM_PROT_WRITE);
    
    for (auto it = regions.begin(); it != regions.end(); ++it)
    {
        Process::Region region = *it;
        char *buffer = new char[region.size];
        
        AZ_STATUS status = currentProcess->ReadMemory(region.start, buffer, region.size);
        if(status != AZ_SUCCESS)
        {
            AZLog("read error: %s\n region size: 0x%llx\n", mach_error_string(status), region.size);
            return results;
        }
        
        for (int i = 0; (i+dataCnt) < region.size; i+=4) // i += dataTypeSize
        {
            if (!memcmp(data, buffer+i, dataCnt))
            {
                AZLog("found at 0x%x", region.start+i);
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
        AZ_STATUS status = currentProcess->ReadMemory(*it, temp, dataCnt);
        if (!status)
        {
            if(!memcmp(temp, data, dataCnt))
            {
                results.push_back(*it);
            }
        }
        else
        {
            AZLog("An error occured while iterating saved values");
        }
        free(temp);
    }
    savedAddresses = results;
    return results;
}


