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
    return az->Tick();
}

