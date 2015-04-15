//
//  MemoryManager.cpp
//  Azure Mac V3
//
//  Created by callum taylor on 17/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "MemoryManager.h"
#include "Azure.h"


#pragma mark DataObject

bool DataObject::operator==(DataObject& other) const {
    switch (other.dataType) {
        case Int:    return *(int*)data == *(int*)other.data;
        case Float:  return *(float*)data == *(float*)other.data;
        case Hex:    return !memcmp(data, other.data, dataLen);
        case String: return !memcmp(data, other.data, dataLen);
        default:     return false;
    }
}

bool DataObject::operator!=(DataObject& other) const {
    switch (other.dataType) {
        case Int:    return *(int*)data != *(int*)other.data;
        case Float:  return *(float*)data != *(float*)other.data;
        case Hex:    return memcmp(data, other.data, dataLen);
        case String: return memcmp(data, other.data, dataLen);
        default:     return false;
    }
}

bool DataObject::operator>(DataObject& other) const {
    switch (other.dataType) {
        case Int:    return *(int*)data > *(int*)other.data;
        case Float:  return *(float*)data > *(float*)other.data;
        case Hex:    return false; // can't do arithmetic on hex and string types
        case String: return false;
        default: return false;
    }
}
bool DataObject::operator<(DataObject& other) const {
    switch (other.dataType) {
        case Int:    return *(int*)data < *(int*)other.data;
        case Float:  return *(float*)data < *(float*)other.data;
        case Hex:    return false; // can't do arithmetic on hex and string types
        case String: return false;
        default: return false;
    }
}

#pragma mark SearchSettings

bool SearchSettings::Match(DataObject raw)
{
    if (fuzzySearch) {
        switch (fuzzySettings) {
            case FuzzyNew:      return true;
            case FuzzyExact:    return searchObj == raw;
            case FuzzyNotEqual: return searchObj != raw;
            case FuzzyGreater:  return searchObj > raw;
            case FuzzySmaller:  return searchObj < raw;
        }
    }
    return searchObj == raw;
}

#pragma mark MemoryManager

MemoryManager::MemoryManager()
: currentProcess(0)
{
    savedResults = new ResultsList();
    lockedResults = new ResultsList();
}

MemoryManager::~MemoryManager()
{
    delete savedResults;
    delete lockedResults;
}

MemoryManager* MemoryManager::GetInstance()
{
    static MemoryManager *manager = NULL;
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
    this->ResetResults();
}

ResultsList *MemoryManager::Results() const
{
    return savedResults;
}

ResultsList *MemoryManager::LockedResults() const
{
    return lockedResults;
}

AZ_STATUS MemoryManager::Find(SearchSettings& settings)
{
    DataObject obj = settings.searchObj;
    AZLog("data size: %d", obj.dataLen);
    this->initialDataSize = obj.dataLen;
    
    AZ_STATUS status = AZ_SUCCESS;
    ResultsList results = ResultsList();
    
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

        for (int i = 0; (i+obj.dataLen) < region.size; i+=4) // i += dataTypeSize
        {
            DataObject temp = obj;
            memcpy(temp.data, buffer+i, temp.dataLen);
            
            if (settings.Match(temp)) {
                temp.address = region.start+i;
                results.push_back(temp);
            }
        }
        
        delete buffer;
    }
    *savedResults = results;
    return status;
}

AZ_STATUS MemoryManager::Iterate(SearchSettings& settings)
{
    DataObject obj = settings.searchObj;
    
    AZ_STATUS status = AZ_SUCCESS;
    ResultsList newResults;
    if (savedResults->size() <= 0)
    {
        AZLog("no saved addresses");
        return status;
    }
    
    for (auto it = savedResults->begin(); it != savedResults->end(); ++it)
    {
        DataObject temp = obj;
        status = currentProcess->ReadMemory(it->address, temp.data, obj.dataLen);
        if (status == AZ_SUCCESS)
        {
            if (settings.Match(temp)) {
                temp.address = it->address;
                newResults.push_back(temp);
            }
        }
        else
        {
            AZLog("An error occured while iterating saved values: %s", mach_error_string(status));
        }
    }
    savedResults->clear();
    *savedResults=newResults;
    return status;
}

AZ_STATUS MemoryManager::FetchUpdatedResults(int start, int count)
{
    AZ_STATUS status = AZ_SUCCESS;
    for (auto it = savedResults->begin()+start; it != savedResults->begin()+start+count; ++it)
    {
        DataObject temp;
        temp.dataLen = initialDataSize;
        
        status = currentProcess->ReadMemory(it->address, temp.data, temp.dataLen);
        if (status == AZ_SUCCESS)
        {
            memcpy(it->data, temp.data, temp.dataLen);
        }
    }
    return status;
}

AZ_STATUS MemoryManager::Write(DataObject obj)
{
    return currentProcess->WriteMemory(obj.address, obj.data, obj.dataLen);
}

AZ_STATUS MemoryManager::Lock(DataObject obj)
{
    lockedResults->push_back(obj);
    return AZ_SUCCESS;
}

void MemoryManager::ResetResults()
{
    savedResults->clear();
    lockedResults->clear();
}
