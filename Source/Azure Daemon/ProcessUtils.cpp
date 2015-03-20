//
//  ProcessUtils.cpp
//  Azure Mac V3
//
//  Created by callum taylor on 17/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "ProcessUtils.h"
#include "Azure.h"

using namespace ProcessUtils;
using namespace std;

#pragma mark Process

Process::Process():
pid(-1), name(""), path(""), task(-1)
{
    
}

Process::Process(pid_t pid) : Process()
{
    if(ProcessExists(pid))
    {
        this->pid = pid;
        strcpy(this->name, GetNameFromPid(pid));
        strcpy(this->path, GetPathForProcess(pid));
        TryAttach(this);
    }
    else
    {
        AZLog("no matching process for %d", pid);
    }
}

Process::Process(const char *name) : Process()
{
    name = GetNameFromPath(name);
    if(ProcessExists(name))
    {
        strcpy(this->name, name);
        this->pid = GetPidForName(name);
        strcpy(this->path, GetPathForProcess(name));
        TryAttach(this);
    }
    else
    {
        AZLog("no matching process for %s", name);
    }
}

Process::Process(msg_process *processData) : Process()
{
    if (ProcessExists(processData->pid))
    {
        this->pid = processData->pid;
        strcpy(this->name, GetNameFromPid(this->pid));
        strcpy(this->path, GetPathForProcess(processData->pid));
        TryAttach(this);
    }
    else if (ProcessExists(processData->name))
    {
        this->pid = GetPidForName(processData->name);
        strcpy(this->name, processData->name);
        strcpy(this->path, GetPathForProcess(processData->name));
        TryAttach(this);
    }
    else
    {
        AZLog("no matching process for %s-%d", processData->name, processData->pid);
    }
}

Process::~Process()
{
    
}

vector<Process::Region> Process::GetRegions()
{
    return ProcessUtils::GetRegions(this, VM_PROT_ALL);
}

vector<Process::Region> Process::GetRegions(vm_prot_t options)
{
    return ProcessUtils::GetRegions(this, options);
}

kern_return_t Process::ReadMemory(vm_address_t address, char *output, size_t size)
{
    return ProcessUtils::ReadMemory(this, address, output, size);
}

kern_return_t Process::WriteMemory(vm_address_t address, char *input, size_t size)
{
    return ProcessUtils::WriteMemory(this, address, input, size);
}

#pragma mark ProcessUtils

vector<Process> ProcessUtils::GetAllProcesses()
{
    vector<Process> local;
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    u_int miblen = 4;
    
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
            return local;
        }
        
        process = newprocess;
        st = sysctl(mib, miblen, process, &size, NULL, 0);
        
    } while (st == -1 && errno == ENOMEM);
    
    if (st == 0)
    {
        
        if (size % sizeof(struct kinfo_proc) == 0)
        {
            long nprocess = size / sizeof(struct kinfo_proc);
            
            if (nprocess)
            {
                for (long i = nprocess - 1; i >= 0; i--)
                {
                    /*struct passwd *user = getpwuid(process[i].kp_eproc.e_ucred.cr_uid);
                     const char * name = user->pw_name;*/
                    
                    pid_t pid = process[i].kp_proc.p_pid;
                    char nameBuffer[64];
                    const char *pathBuffer = ProcessUtils::GetPathForProcess(pid);
                    AZLog("path is: %s", pathBuffer);
                    if (pathBuffer)
                    {
                        long position = strlen(pathBuffer);
                        
                        while(position >= 0 && pathBuffer[position] != '/')
                        {
                            position--;
                        }
                        
                        if (isalpha(*(pathBuffer+position+1)))
                        {
                            strcpy(nameBuffer, pathBuffer + position + 1);
                        }
                    }
                    // Create a new Process object
                    {
                        Process temp;
                    
                        if (nameBuffer) strcpy(temp.name, nameBuffer);
                        if (pathBuffer) strcpy(temp.path, pathBuffer);
                        temp.pid = process[i].kp_proc.p_pid;
                        
                        local.push_back(temp);
                    }
                    
                }
            }
            free(process);
        }
    }
    return local;
}

pid_t ProcessUtils::GetPidForName(const char *name)
{
    vector<Process> processes = GetAllProcesses();
    for(vector<Process>::iterator it = processes.begin(); it != processes.end(); ++it)
    {
        Process proc = *it;
        if(!strcmp(proc.name, name))
        {
            return proc.pid;
        }
    }
    return -1; // error
}

const char *ProcessUtils::GetNameFromPid(pid_t pid)
{
    char *local = new char[128];
    vector<Process> processes = GetAllProcesses();
    for(vector<Process>::iterator it = processes.begin(); it != processes.end(); ++it)
    {
        Process proc = *it;
        if(proc.pid == pid)
        {
            strcpy(local, proc.name);
            return local;
        }
    }
    return NULL; // error
}

const char *ProcessUtils::GetPathForProcess(pid_t pid)
{
    char *buf = (char*)malloc(MAXPATHLEN*4);
    int ret = proc_pidpath(pid, buf, MAXPATHLEN*4);
    if (ret == 0) {
        perror("proc_pidpath returned error");
    }
    return buf;
}

const char *ProcessUtils::GetPathForProcess(const char *name) {
    pid_t pid = GetPidForName(name);
    
    char *buf = (char*)malloc(MAXPATHLEN*4);
    int ret = proc_pidpath(pid, buf, MAXPATHLEN*4);
    if (ret == 0) {
        perror("proc_pidpath returned error");
    }
    return buf;
}

const char *ProcessUtils::GetNameFromPath(const char *path)
{
    bool slashFound = false;
    long position = strlen(path);
    for(int i = 0; i < position; i++)
    {
        if(path[i] == '/') slashFound = true;
    }
    
    if(slashFound)
    {
        while(position >= 0 && path[position] != '/')
        {
            position--;
        }
        
        path += position + 1;
    }
    return path;
}

bool ProcessUtils::ProcessExists(pid_t pid)
{
    vector<Process> processes = GetAllProcesses();
    for(vector<Process>::iterator it = processes.begin(); it != processes.end(); ++it)
    {
        Process proc = *it;
        if(proc.pid == pid)
        {
            return true;
        }
    }
    return false;
}

bool ProcessUtils::ProcessExists(const char* name)
{
    if (name == NULL) return false;
    
    long position = strlen(name);
    
    while(position >= 0 && name[position] != '/')
    {
        position--;
    }
    if (isalpha(*(name+position+1)))
    {
        name = name + position + 1;
    }

    vector<Process> processes = GetAllProcesses();
    
    for(vector<Process>::iterator it = processes.begin(); it != processes.end(); ++it)
    {
        Process proc = *it;
        if(!strcmp(proc.name, name))
        {
            return true;
        }
    }
    return false;
}

kern_return_t ProcessUtils::TryAttach(Process *proc)
{
    kern_return_t status = KERN_SUCCESS;
    if(proc->pid < 0)
    {
        if(ProcessExists(proc->name))
        {
            proc->pid = GetPidForName(proc->name);
        }
    }
    if(proc->name == NULL)
    {
        if(ProcessExists(proc->pid))
        {
            strcpy(proc->name, GetNameFromPid(proc->pid));
        }
    }
    if(proc->pid == getpid())
    {
        proc->task = mach_task_self();
        return status;
    }
    status = task_for_pid(mach_task_self(), proc->pid, &proc->task);
    return status;
}

vector<Process::Region> ProcessUtils::GetRegions(Process *proc)
{
    return GetRegions(proc, VM_PROT_ALL);
}

vector<Process::Region> ProcessUtils::GetRegions(Process *proc, vm_prot_t options)
{
    vector<Process::Region> regions;
    
    kern_return_t status = KERN_SUCCESS;
    vm_address_t address = 0x0;
    
    if(!proc->task)
    {
        status = TryAttach(proc);
        if(status != KERN_SUCCESS)
        {
            // error
            return regions;
        }
    }
    
    while (status == KERN_SUCCESS)
    {
        vm_size_t vmsize;
        vm_region_basic_info_data_xx_t info;
        mach_msg_type_number_t info_count = VM_REGION_BASIC_INFO_COUNT_64;
        memory_object_name_t object;
        
        status = vm_region_xx(proc->task, &address, &vmsize, VM_REGION_BASIC_INFO, (vm_region_info_64_t)&info, &info_count, &object);
        
        if((info.protection == options) && (status == KERN_SUCCESS)) //remember to change vm_prot_default back
        {
            Process::Region temp = {address, vmsize};
            regions.push_back(temp);
        }
        address+=vmsize;
    }
    return regions;
}

kern_return_t ProcessUtils::ReadMemory(Process *proc, vm_address_t address, char *output, size_t size)
{
    kern_return_t status = KERN_SUCCESS;
    if(proc->task <= 0)
    {
        status = TryAttach(proc);
        if(status != KERN_SUCCESS)
        {
            // error
            return status;
        }
    }
    vm_size_t sz;
    status = vm_read_overwrite(proc->task, address, size, (vm_address_t)output, &sz);
    if(status != KERN_SUCCESS)
    {
        // error
        return status;
    }
    
    return status;
}

kern_return_t ProcessUtils::WriteMemory(Process *proc, vm_address_t address, char *input, size_t size)
{
    kern_return_t status = KERN_SUCCESS;
    if(!proc->task)
    {
        status = TryAttach(proc);
        if(status != KERN_SUCCESS)
        {
            // error
            return status;
        }
    }
    
    status = vm_write(proc->task, address, (vm_address_t)input, size);
    if(status != KERN_SUCCESS)
    {
        // error
        return status;
    }
    
    return status;
}
