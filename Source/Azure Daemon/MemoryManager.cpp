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
    savedAddresses = new ::AddressList();
    savedDataList = new ::DataList();
}

MemoryManager::~MemoryManager()
{
    delete savedAddresses;
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

void MemoryManager::DetachFromProcess()
{
    delete this->currentProcess;
}

AddressList *MemoryManager::Results() const
{
    return savedAddresses;
}

DataList *MemoryManager::DataList() const
{
    return savedDataList;
}

AZ_STATUS MemoryManager::Find(void *data, size_t dataCnt)
{
    AZLog("data size: %d", dataCnt);
    this->initialDataSize = dataCnt;
    AZ_STATUS status = AZ_SUCCESS;
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
            return status;
        }
        
        for (int i = 0; (i+dataCnt) < region.size; i+=4) // i += dataTypeSize
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
    *savedAddresses = results;
    return status;
}

AZ_STATUS MemoryManager::Iterate(void *data, size_t dataCnt, AddressList *addresses)
{
    AZ_STATUS status = AZ_SUCCESS;
    AddressList results;
    if (addresses->size() <= 0)
    {
        AZLog("no saved addresses");
        return status;
    }
    
    for (auto it = addresses->begin(); it != addresses->end(); ++it)
    {
        char *temp = (char*)malloc(dataCnt);
        status = currentProcess->ReadMemory(*it, temp, dataCnt);
        if (status == AZ_SUCCESS)
        {
            if(!memcmp(temp, data, dataCnt))
            {
                results.push_back(*it);
            }
        }
        else
        {
            AZLog("An error occured while iterating saved values: %s", mach_error_string(status));
        }
        free(temp);
    }
    *savedAddresses = results;
    return status;
}

AZ_STATUS MemoryManager::FetchUpdatedResults()
{
    ::DataList dataList;
    AZ_STATUS status = AZ_SUCCESS;
    std::vector<vm_address_t> results;
    if (savedAddresses->size() <= 0)
    {
        AZLog("no saved addresses");
        return status;
    }
    
    for (auto it = savedAddresses->begin(); it != savedAddresses->end(); ++it)
    {
        char *temp = (char*)malloc(initialDataSize);
        status = currentProcess->ReadMemory(*it, temp, initialDataSize);
        if (status == AZ_SUCCESS)
        {
            DataItem *item = new DataItem;
            memcpy(item, temp, initialDataSize);
            dataList.push_back(*item);
        }
        else
        {
            AZLog("An error occured while fetching current values: %s", mach_error_string(status));
        }
        free(temp);
    }
    *savedDataList = dataList;
    return status;
}

void MemoryManager::ResetResults()
{
    savedAddresses->clear();
    savedDataList->clear();
}
