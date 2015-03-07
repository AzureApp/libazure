//
//  Azure.h
//  Azure
//
//  Created by callum taylor on 09/08/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#ifndef __Azure__Azure__
#define __Azure__Azure__

#include <iostream>
#include <syslog.h>
#include "MemoryManager.h"
#include "ProcessUtils.h"
#include "DaemonUtils.h"
#include "ObjCUtils.h"

#include "TargetConditionals.h"

#define AZLog(fmt, ...) Azure::WriteToLog(fmt, ##__VA_ARGS__)
char* concat(char *s1, char *s2);

#ifndef TARGET_OS_IPHONE
#define AZ_LOG_LOC "/opt/azure.log"
#else
#define AZ_LOG_LOC "/Applications/Azure.app/azure.log"
#endif

using namespace DaemonUtils;
using namespace ProcessUtils;

class Azure {
public:
    Azure();
    ~Azure();
    
    static Azure *GetInstance();
    
    kern_return_t Start();
    kern_return_t Tick();
    static void WriteToLog(const char *fmt, ...);
    void AttachToProcess(Process *);
    
    Daemon *CurrentDaemon();
    
private:
    Daemon *azureDaemon;
    Process *currentProcess;
};

#endif /* defined(__Azure__Azure__) */