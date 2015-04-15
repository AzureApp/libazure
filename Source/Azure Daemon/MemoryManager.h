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

struct DataObject {
    enum SearchType {
        Int,
        Float,
        Hex,
        String,
    } dataType;
    
    vm_address_t address;
    int dataLen;
    char data[16];
    
    bool operator==(DataObject& other) const;
    bool operator!=(DataObject& other) const;
    bool operator>(DataObject& other) const;
    bool operator<(DataObject& other) const;
};

struct SearchSettings {
    bool fuzzySearch;
    
    enum FuzzySettings {
        FuzzyNew,
        FuzzyGreater,
        FuzzySmaller,
        FuzzyExact,
        FuzzyNotEqual
    } fuzzySettings;
    
    DataObject searchObj;
    
    bool Match(DataObject raw);
};

typedef std::vector<DataObject> ResultsList;

class MemoryManager {
public:
    
    MemoryManager();
    ~MemoryManager();
    
    static MemoryManager *GetInstance();
    static MemoryManager *manager;
    
    AZ_STATUS AttachToProcess(Process *);
    void DetachFromProcess();
    
    ResultsList *Results() const;
    int DataSize() const { return this->initialDataSize; }
    
    AZ_STATUS Find(SearchSettings& settings);
    AZ_STATUS Iterate(SearchSettings& settings);
    AZ_STATUS FetchUpdatedResults(int start, int count);
    
    AZ_STATUS Write(vm_address_t addr, DataObject obj); // TODO
    void ResetResults();
private:
    Process *currentProcess;
    int initialDataSize;
    ResultsList *savedResults;
};

#endif /* defined(__Azure_Mac_V3__AzureEngine__) */
