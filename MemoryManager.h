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
namespace azure
{
    
    struct Region
    {
        uint start;
        uint size;
    };
    struct ReadData
    {
        uint data;
        vector<vm_address_t> addresses;
    };
    
    class MemoryManager
    {
    public:
        task_t currentTask;
        vector<Region> regions;
        ReadData *searchData;
        
        MemoryManager(task_t task);
        kern_return_t GetRegions();
        kern_return_t BeginSearch(uint bytes, size_t size);
        kern_return_t IterateSearch(uint newval);
        kern_return_t WriteAddress(uint addr, uint data); //to do: support all data types
        
        void FindData_Test(long long data);
    };
}
#endif /* defined(__azure_mac_tests__MemoryManager__) */
