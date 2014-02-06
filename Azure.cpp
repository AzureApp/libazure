//
//  Azure.cpp
//  azure-mac-tests
//
//  Created by Callum Taylor on 23/12/2013.
//  Copyright (c) 2013 Callum Taylor. All rights reserved.
//

#include "Azure.h"

using namespace azure;

Azure* Azure::az_Instance = NULL;
Azure::Azure()
{
    azureSettings = new struct GlobalSettings();
    this->GetPreferences();
}

Azure* Azure::GetInstance()
{
    if(!az_Instance)
    {
        az_Instance = new Azure();
    }
    return az_Instance;
}

void Azure::WriteToLog(const char *msg)
{
    if(!azureSettings || azureSettings->debug != true)
        return;
    FILE *az_file = fopen("/var/mobile/Azure/log.txt", "w+");
    fprintf(az_file, msg);
    fclose(az_file);
}

int Azure::GetPreferences()
{
    return 0; // to do
}

/* TO DO: Tidy this up */
int Azure::SetPreferences(GlobalSettings& prefs)
{
    if(prefs.start_addr <= -1)
        this->azureSettings->start_addr = prefs.start_addr;
    if(prefs.end_addr <= -1)
        this->azureSettings->end_addr = prefs.end_addr;
    if(prefs.chunk_size <= 0)
        this->azureSettings->chunk_size = prefs.chunk_size;
    this->azureSettings->debug = prefs.debug;
    this->azureSettings->fileWrite = prefs.fileWrite;
    this->azureSettings->listOnly = prefs.listOnly;
    return 0;
        
}

int Azure::MainLoop()
{
    
}

Azure::~Azure()
{
    delete azureSettings;
}