//
//  Azure.cpp
//  Azure
//
//  Created by callum taylor on 09/08/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "Azure.h"

const char* concat(const char *s1, const char *s2)
{
    char *result = (char*)malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


Azure::Azure()
{
    azureDaemon = new DaemonUtils::Daemon();
}

Azure::~Azure()
{
    delete azureDaemon;
}

Azure* Azure::GetInstance()
{
    static Azure *instance = NULL;
    if(!instance)
    {
        instance = new Azure();
    }
    return instance;
}

kern_return_t Azure::Start()
{
    if (azureDaemon) {
        azureDaemon->Start();
        return KERN_SUCCESS;
    }
    return KERN_FAILURE;
}

kern_return_t Azure::Tick()
{
    kern_return_t status = KERN_SUCCESS;
    while (status == KERN_SUCCESS)
    {
        Message msg;
        status = azureDaemon->ReceivedMessage(msg);
        if (status != KERN_SUCCESS) {
            AZLog("daemon failed with error %d\n", status);
            return status;
        }
        azureDaemon->SendMessageReceiveSuccess();
        status = Messaging::ProcessMessage(msg);
        if (status != KERN_SUCCESS) {
            AZLog("Messaging failed with error %d\n", status);
            return status;
        }
        status = azureDaemon->SendMessage(msg);
    }
    return status;
}

void Azure::AttachToProcess(Process *proc)
{
    kern_return_t status = ProcessUtils::TryAttach(proc);
    if (status == KERN_SUCCESS)
    {
        MemoryManager *manager = MemoryManager::GetInstance();
        manager->AttachToProcess(proc);
    }
    else
    {
        AZLog("could not attach to process: [%s-%d]", proc->name, proc->pid);
    }
}

void Azure::WriteToLog(const char *fmt, ...)
{
#ifdef DEBUG
    openlog("azure", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
    char str[1000];
    
    va_list arg;
    va_start(arg, fmt);
    vsprintf(str, fmt, arg);
    va_end(arg);
    
    syslog(LOG_INFO, str);
    closelog();
#else
    if (!strstr(fmt, "\n")) {
        fmt = concat(fmt, "\n");
    }
    const char *logger = "[Azure Daemon] ";
    char result[256];
    
    strcpy(result, logger);
    strcat(result, fmt);
    
    va_list arg;
    FILE *log_file = fopen(AZ_LOG_LOC, "a+");

    va_start(arg, fmt);
    vfprintf(log_file, fmt, arg);
    va_end(arg);
    
    fclose(log_file);
    return;
#endif
}

Daemon* Azure::CurrentDaemon()
{
    return azureDaemon;
}
