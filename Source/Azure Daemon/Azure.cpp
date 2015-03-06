//
//  Azure.cpp
//  Azure
//
//  Created by callum taylor on 09/08/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "Azure.h"

char* concat(char *s1, char *s2)
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
    // TODO
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

kern_return_t Azure::Tick()
{
    Messaging *msgs = Messaging::GetInstance();
    kern_return_t status = KERN_SUCCESS;
    while (status == KERN_SUCCESS)
    {
        status = azureDaemon->Tick();
        status = msgs->Tick();
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
    const char *logger = "[Azure Daemon] ";
    char result[256];
    
    strcpy(result, logger);
    strcat(result, fmt);
    
    va_list arg;
    /* Check if the message should be logged */
//    if (!azureSettings || azureSettings->debug != true)
//    {
//        return;
//    }
    FILE *log_file = fopen(AZ_LOG_LOC, "a+");
    /* Write the message */
    va_start(arg, fmt);
    vfprintf(log_file, fmt, arg);
    va_end(arg);
    fclose(log_file);
    return;
}

Daemon* Azure::CurrentDaemon()
{
    return azureDaemon;
}