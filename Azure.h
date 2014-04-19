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
#include <unistd.h>
//#include <thread>
#include <pthread.h>
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/xpath.h>
#include <libxml2/libxml/xmlstring.h>
#include "MemoryManager.h"
#include "ProcessInfo.h"
#include "DataObject.h"
#include "Messaging.h"

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

#define AZStub "az# "

using namespace std;

#define AZLog(fmt, ...) Azure::WriteToLog(fmt, ##__VA_ARGS__) //for logging

struct GlobalSettings  //to do, change to a dictionary/tuple?
{
    unsigned long long start_addr;
    unsigned long long end_addr;
    uint chunk_size;
    bool debug;
    bool fileWrite;
    bool listOnly;
    bool systemApps;
    //create "attach stack"
    
};

enum HelpTopics 
{ //so unnecessarily unnecessy 
    e_main = 0,
    e_attach,
    e_search,
    e_write,
    e_lock,
    e_list,
    e_credits
};

class Azure
{
public:
    static GlobalSettings *azureSettings;
    static Azure *az_Instance;
    static Azure* instance();
    Azure();
    ~Azure();
    
    static void WriteToLog(const char* fmt, ...);
    
    void GetPreferences();
    int SetPreferences(GlobalSettings settings);
    int MainLoop();
    static void PrintHelp(HelpTopics topic);
    
};

#endif /* defined(__azure_mac_tests__Azure__) */
