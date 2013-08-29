//
//  MemoryEngine.cpp
//  azured
//
//  Created by Callum Taylor on 19/08/2013.
//
//

#include "Combined.h"
MemoryEngine *g_memengine = NULL;

MemoryEngine::MemoryEngine()
{
    g_memengine = this;
}

MemoryEngine::~MemoryEngine()
{
    
}


pid_t MemoryEngine::GetProcessByName(const char *name)
{
    int pid = 0;
    
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
            return 0;
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
                    const char * processName = process[i].kp_proc.p_comm;
                    
                    if (strcmp(name, processName) == 0)
                    {
                        pid = process[i].kp_proc.p_pid;
                    }
                }
                
                free(process);
            }
        }
    }
    return pid;
}

void MemoryEngine::GetPortForProcess(pid_t process)
{
    kern_return_t err = task_for_pid(mach_task_self(), process, &port);
    if(err != KERN_SUCCESS)
    {
        string error = "Azure error: failed to obtain port from process ";
        error += (const char*)process;
        error += " mach error: ";
        error += mach_error_string(err);
        error += "\n";
        
        g_azure->WriteToLog(error.c_str());
    }
}

kern_return_t MemoryEngine::WriteData(uint address, uint data)
{
    vm_protect(mach_task_self(), address, sizeof(data) / 4, false, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_COPY);
    kern_return_t err = vm_write(port, address, data, sizeof(data));
    if(err != KERN_SUCCESS)
    {
        string error = "Azure error: failed to write ";
        error += (const char*)data;
        error += " at address ";
        error += (const char*)address;
        error += " mach error: ";
        error += mach_error_string(err);
        error += "\n";
        g_azure->WriteToLog(error.c_str());
    }
    vm_protect(mach_task_self(), address, sizeof(data) / 4, false, VM_PROT_READ | VM_PROT_EXECUTE);
    return err;
}



kern_return_t MemoryEngine::ReadData(uint data[], uint addr)
{
    if(port == (int)NULL || port == 0 || data == NULL)
    {
        string s = "Azure error: incorrect port (" ;
        s += (const char*)port;
        s += ")\n";
        g_azure->WriteToLog(s.c_str());
        return KERN_FAILURE;
     }
                           
    vm_size_t readsize = 0; // holds the read amount of memory, not needed here	
	kern_return_t err; // something to deal with errors
   
    int localData[settings->chunksize];
    err = vm_protect(mach_task_self(), addr, sizeof(localData) / 4, false, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_COPY);
    //^ make memory readable
    err = vm_read_overwrite(port, addr, sizeof(localData) / 4, (vm_address_t)&localData, &readsize);
    //^ read the memory into that data array
        if ( err != KERN_SUCCESS) 
        {
            string s = "Azure error: vm_read failed \n" ;
            g_azure->WriteToLog(s.c_str());
            return KERN_FAILURE;
        }
    
        /*for (int j = 0; j < readsize / 4; j++)
        {
            NumberEngine::ReadData tempdata;
            tempdata.address = i+(j*sizeof(localData[j]));
            tempdata.value = localData[j];
            data->push_back(tempdata);
        }*/
    err = vm_protect(mach_task_self(), addr, sizeof(localData) / 4,false, VM_PROT_READ | VM_PROT_EXECUTE);
    
    return err;
}

void MemoryEngine::Lock(uint address, int value)
{
    
}
void MemoryEngine::Unlock(uint address)
{
    
}
void MemoryEngine::Edit(uint address, int value)
{
    
}
void MemoryEngine::KillProcess(const char *processName)
{
    
}
