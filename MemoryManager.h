//
//  MemoryManager.h
//  azure-mac-tests
//
//  Created by Callum Taylor on 03/12/2013.
//  Copyright (c) 2013 Callum Taylor. All rights reserved.
//

#ifndef __azure_mac_tests__MemoryManager__
#define __azure_mac_tests__MemoryManager__

#include <iostream>
#include <sys/types.h>
#include <vector>
#include <mach/mach.h>
#include <stdio.h>
#include <pthread.h>
#include "DataObject.h"
#include "Azure.h"


using namespace std;

namespace Math
{
    template<typename T>
    static T Clamp(T value, T max, T min)
    {
        T result = value;
        if (value > max)
            result = max;
        if (value < min)
            result = min;
        return result;
        
    }
}

    struct Region
    {
        int start;
        int size;
    };
    struct ReadData
    {
        ReadData() : data(DataObject(NULL, 0)) {}
        DataObject data;
        vector<vm_address_t> addresses;
    };
    struct LockData //remove?
    {
        void* data; //change?
        int dataCnt;
        int address;
    };
    
    class MemoryManager
    {
    public:
        task_t currentTask;
        vector<Region> regions;
        vector<LockData> *lockData;
        ReadData *searchData;
        
        static MemoryManager* az_mem;
        static MemoryManager* instance();
        MemoryManager();
        ~MemoryManager();
        
        kern_return_t GetRegions();
        kern_return_t Search(SearchObject *);
        kern_return_t WriteData(WriteObject *);
        void Lock(WriteObject *);
        /* DEPRECEATED */
        kern_return_t BeginSearch(uint bytes, size_t size);
        kern_return_t IterateSearch(uint newval);
        kern_return_t WriteAddress(uint addr, uint data); //to do: support all data types
        
    };

#endif /* defined(__azure_mac_tests__MemoryManager__) */
