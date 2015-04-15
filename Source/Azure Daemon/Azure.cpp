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
    azureDaemon = new Daemon();
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

AZ_STATUS Azure::Start()
{
    if (azureDaemon) {
        AZ_STATUS status = azureDaemon->Start();
        return status;
    }
    AZLog("daemon not initialized");
    return AZ_FAILURE;
}

AZ_STATUS Azure::Tick()
{
    MemoryManager *manager = MemoryManager::GetInstance();
    AZ_STATUS status = AZ_SUCCESS;
    while (status == AZ_SUCCESS)
    {
        if (azureDaemon->HasDataAvailable())
        {
            Message msg;
            status = azureDaemon->ReceivedMessage(msg);
            if (status != AZ_SUCCESS) {
                AZLog("daemon failed with error %d\n", status);
                AZLog("trying to restart daemon");
                manager->DetachFromProcess();
                if ((status = azureDaemon->Start())) {
                    AZLog("fatal, cannot restart daemon");
                    return status;
                }
            }
            azureDaemon->SendMessageReceiveSuccess();
            
            status = Messaging::ProcessMessage(msg);
            if (status != AZ_SUCCESS) {
                AZLog("Messaging failed with error %d\n", status);
                return status;
            }
            
            status = azureDaemon->SendMessage(msg);
            if (status != AZ_SUCCESS) {
                AZLog("daemon failed with error %d\n", status);
                AZLog("trying to restart daemon");
                if ((status = azureDaemon->Start())) {
                    AZLog("fatal, cannot restart daemon");
                    return status;
                }
            }
        }
        if (manager->LockedResults()->size() > 0) {
            for (DataObject it : *manager->LockedResults())
            {
                manager->Write(it);
            }
        }
    }
    return status;
}

void Azure::AttachToProcess(Process *proc)
{
    AZ_STATUS status = ProcessUtils::TryAttach(proc);
    if (status == AZ_SUCCESS)
    {
        MemoryManager *manager = MemoryManager::GetInstance();
        manager->AttachToProcess(proc);
    }
    else
    {
        AZLog("could not attach to process: [%s-%d]", proc->name, proc->pid);
    }
}

void Azure::DetachFromProcess()
{
    MemoryManager *manager = MemoryManager::GetInstance();
    manager->DetachFromProcess();
}

void Azure::WriteToLog(const char *fmt, ...)
{
#ifdef DEBUG
    openlog("azure", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_USER);
    char str[1000];
    
    va_list arg1;
    va_start(arg1, fmt);
    vsprintf(str, fmt, arg1);
    
    syslog(LOG_INFO, str);
    
    va_end(arg1);
    closelog();
#endif
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
    vprintf(fmt, arg);
    va_end(arg);
    
    fclose(log_file);
    return;
}

Daemon* Azure::CurrentDaemon() const
{
    return azureDaemon;
}
