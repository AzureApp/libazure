//
//  ProcessInfo.cpp
//  azured
//
//  Created by Callum Taylor on 26/12/2013.
//
//

#include "ProcessInfo.h"

using namespace azure;


ProcessInfo *ProcessInfo::az_Pinfo = NULL;
ProcessInfo::ProcessInfo()
{
    processes = new vector<Process>;
}

ProcessInfo* ProcessInfo::GetInstance()
{
    if(!az_Pinfo)
        az_Pinfo = new ProcessInfo();
    return az_Pinfo;
}
/*AZProcessInfo::GetInstance()
 {
 AZProcessInfo inst;
 return inst;
 }*/
int ProcessInfo::GetAllProcesses()
{
    bool testReady = true;
    
    
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    size_t miblen = 4;
    
    size_t size;
    int st = sysctl(mib, miblen, NULL, &size, NULL, 0);
    
    struct kinfo_proc * process = NULL;
    struct kinfo_proc * newprocess = NULL;
    
    do {
        
        size += size / 10;
        newprocess = (kinfo_proc *)realloc(process, size);
        
        if (!newprocess)
        {
            if (process){
                free(process);
            }
            return -1;
        }
        
        process = newprocess;
        st = sysctl(mib, miblen, process, &size, NULL, 0);
        
    } while (st == -1 && errno == ENOMEM);
    
    if (st == 0)
    {
        
        if (size % sizeof(struct kinfo_proc) == 0)
        {
            int nprocess = size / sizeof(struct kinfo_proc);
            
            if (nprocess)
            {
                for (int i = nprocess - 1; i >= 0; i--)
                {
                    /*struct passwd *user = getpwuid(process[i].kp_eproc.e_ucred.cr_uid);
                     const char * name = user->pw_name;*/
                    
                    struct Process temp;
                    
                    strcpy(temp.processName, process[i].kp_proc.p_comm);
                    temp.pid = process[i].kp_proc.p_pid;
                    
                    mib[0] = CTL_KERN;
                    mib[1] = KERN_ARGMAX;
                    mib[2] = 0;
                    
                    size_t argmaxsize = sizeof(size_t);
                    size_t size;
                    
                    sysctl(mib, 2, &size, &argmaxsize, NULL, 0);
                    
                    mib[1] = KERN_PROCARGS2;
                    mib[2] = process[i].kp_proc.p_pid;
                    
                    char *procargv = (char*)malloc(size);
                    
                    sysctl(mib, 3, procargv, &size, NULL, 0);
                    
                    strcpy(temp.path, procargv+sizeof(int));
                    
                    if(testReady && strstr(procargv+sizeof(int), "/var/mobile/Applications") != NULL)
                    {
                        temp.port = 0;
                        processes->push_back(temp);
                    }
                    else if(!testReady)
                    {
                        temp.port = 0;
                        processes->push_back(temp);
                    }
                    
                    
                }
                
                free(process);
            }
        }
    }
    return 0;
}


pid_t ProcessInfo::GetProcessByName(const char *name)
{
    return 0;
}

int ProcessInfo::AttachToProcess(Process& process)
{
    mach_port_t port;
    if(!task_for_pid(mach_task_self(), process.pid, &port))
    {
        //azure log
    }
    
    return 0;
}
