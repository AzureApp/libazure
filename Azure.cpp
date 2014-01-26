//
//  Azure.cpp
//  azure-mac-tests
//
//  Created by Callum Taylor on 23/12/2013.
//  Copyright (c) 2013 Callum Taylor. All rights reserved.
//

#include "Azure.h"

using namespace azure;


Azure::Azure()
{
    azureSettings = new struct GlobalSettings();
    this->GetPreferences();
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

Azure::~Azure()
{
    delete azureSettings;
}