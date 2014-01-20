//
//  Azure.h
//  azure-mac-tests
//
//  Created by Callum Taylor on 23/12/2013.
//  Copyright (c) 2013 Callum Taylor. All rights reserved.
//

#ifndef __azure_mac_tests__Azure__
#define __azure_mac_tests__Azure__

#include <iostream>
#include <cstdio>
#include <sys/types.h>
namespace azure
{
    struct GlobalSettings
    {
        unsigned long long start_addr;
        unsigned long long end_addr;
        uint chunk_size;
        bool debug;
        bool fileWrite;
    };
    
    class Azure
    {
    public:
        
        GlobalSettings *azureSettings;
        Azure();
        ~Azure();
        
        void WriteToLog(const char* msg);
        int GetPreferences();
    };
}
#endif /* defined(__azure_mac_tests__Azure__) */
