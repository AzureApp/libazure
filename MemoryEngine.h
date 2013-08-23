//
//  MemoryEngine.h
//  azured
//
//  Created by Callum Taylor on 19/08/2013.
//
//

#ifndef __azured__MemoryEngine__
#define __azured__MemoryEngine__

#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <mach/mach.h>
#include <sys/sysctl.h>
#include <sys/types.h>
#include <vector>

using namespace std;
class MemoryEngine
{
public:
    vector<char *>runningProcesses;
    task_t port;
    MemoryEngine();
    ~MemoryEngine();
    
    pid_t GetProcessByName(const char * name);
    void GetPortForProcess(pid_t process);
    void Lock(uint address, int value);
    void Unlock(uint address);
    void Edit(uint address, int value);
    void KillProcess(const char *processName);
    kern_return_t WriteData(uint address, uint data);
    kern_return_t ReadData(vector<NumberEngine::ReadData > *data, uint address = 0x1000, uint endaddress = 0x7FFFFFF);


};
extern MemoryEngine *g_memengine;
#endif /* defined(__azured__MemoryEngine__) */
