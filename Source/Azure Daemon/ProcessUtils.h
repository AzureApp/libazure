//
//  ProcessUtils.h
//  Azure Mac V3
//
//  Created by callum taylor on 17/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#ifndef __Azure_Mac_V3__ProcessUtils__
#define __Azure_Mac_V3__ProcessUtils__

#include "TargetConditionals.h"

#include <vector>
#include <mach/mach.h>

#ifndef TARGET_OS_IPHONE
#include <mach/mach_vm.h>
#endif

#include <errno.h>
#include <unistd.h>
#include <sys/sysctl.h>
#include <assert.h>
#include <sys/types.h>
#include <pwd.h>

#ifndef TARGET_OS_IPHONE
#include <libproc.h>
#else
#include <sys/param.h>
#endif 

#include "Message.h"

#pragma mark Process

#ifdef __LP64__ // 64 bit functions
#define vm_region_basic_info_data_xx_t vm_region_basic_info_data_64_t
#define vm_region_info_xx_t vm_region_info_64_t
#define vm_region_xx vm_region_64
#define VM_REGION_BASIC_INFO_XX VM_REGION_BASIC_INFO_64
#define VM_REGION_BASIC_INFO_COUNT_XX VM_REGION_BASIC_INFO_COUNT_64
#define VM_REGION_SUBMAP_INFO_COUNT_XX VM_REGION_SUBMAP_INFO_COUNT_64
#define vm_region_submap_info_xx vm_region_submap_info_64
#define vm_region_recurse_xx vm_region_recurse_64
#else // 32 bit functions
#define vm_region_basic_info_data_xx_t vm_region_basic_info_data_t
#define vm_region_info_xx_t vm_region_info_t
#define vm_region_xx vm_region
#define VM_REGION_BASIC_INFO_XX VM_REGION_BASIC_INFO
#define VM_REGION_BASIC_INFO_COUNT_XX VM_REGION_BASIC_INFO_COUNT
#define VM_REGION_SUBMAP_INFO_COUNT_XX VM_REGION_SUBMAP_INFO_COUNT
#define vm_region_submap_info_xx vm_region_submap_info
#define vm_region_recurse_xx vm_region_recurse
#endif

extern "C" int proc_pidpath(int,void*,uint32_t);

class Process {
public:
    pid_t pid;
    char name[512];
    char path[512];
    task_t task;
    
    struct Region {
        vm_address_t start;
        size_t size;
    };
    
    Process();
    Process(pid_t pid);
    Process(const char* name);
    Process(msg_process *);
    ~Process();
    
    AZ_STATUS ReadMemory(vm_address_t address, char *output, size_t size);
    AZ_STATUS WriteMemory(vm_address_t address, char *input, size_t size);
    std::vector<Region> GetRegions();
    std::vector<Region> GetRegions(vm_prot_t options);

};

#pragma mark ProcessUtils

namespace ProcessUtils {
    
    std::vector<Process> GetAllProcesses();
    
    pid_t GetPidForName(const char *name);
    const char *GetNameFromPid(pid_t pid);
    const char *GetPathForProcess(pid_t pid);
    const char *GetPathForProcess(const char *name);
    const char *GetNameFromPath(const char *path);

    bool ProcessExists(pid_t pid);
    bool ProcessExists(const char* name);
    
    AZ_STATUS TryAttach(Process *);
    std::vector<Process::Region> GetRegions(Process *);
    std::vector<Process::Region> GetRegions(Process *,vm_prot_t options);
    AZ_STATUS ReadMemory(Process *, vm_address_t address, char *output, size_t size);
    AZ_STATUS WriteMemory(Process *, vm_address_t address, char *input, size_t size);

} // ProcessUtils

#endif /* defined(__Azure_Mac_V3__ProcessUtils__) */
