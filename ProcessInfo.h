//
//  AZProcessInfo.h
//  AZHooker
//
//  Created by Callum Taylor on 28/11/2013.
//
//



#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <mach/mach.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <pwd.h>
#include <vector>

using namespace std;

namespace azure
{
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
        
        ProcessInfo();
        int GetAllProcesses();
        pid_t GetProcessByName(const char* name);
        const char* GetNameFromProcess(pid_t process);
        int AttachToProcess(Process& process);
        
    };
    
    
}
