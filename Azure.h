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

#define kRED  "\033[1;31m"
#define kGRN  "\033[1;32m"
#define kYEL  "\033[1;33m"
#define kBLU  "\033[1;34m"
#define kMAG  "\033[1;35m"
#define kCYN  "\033[1;36m"

#define kCLR "\033[1;0m"

#define AZGreet \
"\
++++++++++++++++++++++\n\
++Azure Alpha (v0.5)++\n\
++[--help for usage]++\n\
++++++++++++++++++++++\n"

#define AZStub "<Azure>"

namespace azure
{
    struct GlobalSettings  //to do, change to a dictionary/tuple
    {
        unsigned long long start_addr;
        unsigned long long end_addr;
        uint chunk_size;
        bool debug;
        bool fileWrite;
        bool listOnly;
        //create "attach stack"
        
    };
    
    class Azure
    {
    public:
        GlobalSettings *azureSettings;
        static Azure* GetInstance();
        Azure();
        ~Azure();
        static Azure *az_Instance;
        void WriteToLog(const char* msg);
        int GetPreferences();
        int SetPreferences(GlobalSettings& settings);
        int MainLoop();
    };
}
#endif /* defined(__azure_mac_tests__Azure__) */
