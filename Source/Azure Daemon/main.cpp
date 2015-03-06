//
//  main.cpp
//  Azure Mac V3
//
//  Created by callum taylor on 17/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <mach-o/dyld.h>
#include "ProcessUtils.h"
#include "Settings.h"
#include "Azure.h"
#include "MemoryManager.h"
#include "DaemonUtils.h"

unsigned char fucklaw[12] {0x12, 0xFF, 0x3B, 0xD2, 0x3E, 0x28, 0xAF, 0x9C, 0x72, 0x0F, 0xB0, 0x00};
const char *magic = "law sucks";
Settings azureSettings;

using namespace DaemonUtils;
int main(int argc, const char **argv)
{
    Azure *az = Azure::GetInstance();
    az->Tick();
    
    
    //    Azure *main = Azure::GetInstance();
    //    main->Tick();
    
    //    AzureEngine *azureEngine = AzureEngine::GetInstance();
    //    
    //    Process self = Process(argv[1]);
    //    magic = atoi(argv[2]);
    //    azureEngine->AttachToProcess(&self);
    //    azureEngine->Find(&magic, sizeof(magic));
    
    
    //    char word[4];
    //    kern_return_t status = self.ReadMemory((vm_address_t)_dyld_get_image_header(0), word, 4);
    //    printf("%s\n", mach_error_string(status));
    //    int *value = (int*)word;
    //    printf("0x%X\n", *value);
    //    printf("pid: %d\nname: %s\npath: %s\ntask: %d\n ---------\n", self.pid, self.name, self.path, self.task);
    //    Settings azureSettings;
    //    int chunksz = azureSettings["kChunk"];
    //    bool system = azureSettings["kSystem"];
    //
    //    printf("%d\n, %d\n", chunksz, system);
    //    vector<Process> processes = ProcessUtils::GetAllProcesses();
    //    for(vector<Process>::iterator it = processes.begin(); it != processes.end(); ++it)
    //    {
    //        self = *it;
    //        printf("pid: %d\nname: %s\npath: %s\ntask: %d\n ---------\n", self.pid, self.name, self.path, self.task);
    //    }
}

