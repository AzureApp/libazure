//
//  AZProcessInfo.h
//  AZHooker
//
//  Created by Callum Taylor on 28/11/2013.
//
//

#ifndef __ProcessInfo__
#define __ProcessInfo__

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <mach/mach.h>
#include <sys/sysctl.h>
#include <assert.h>
#include <sys/types.h>
#include <pwd.h>
#include <vector>
#include "MemoryManager.h"

using namespace std;


struct Process
{
    pid_t pid;
    mach_port_t port;
    char* processName = new char[30];
    char* path = new char[100];
};

class ProcessInfo
{
public:
    
    vector<Process> *processes;
    Process currentProcess;
    static ProcessInfo *az_Pinfo;
    
    ProcessInfo();
    int GetAllProcesses();
    static ProcessInfo* instance();
    
    pid_t GetProcessByName(const char* name);
    const char* GetNameFromProcess(pid_t process);
    int AttachToProcess(Process& process);
    
};

#endif
