//
//  Settings.cpp
//  Azure Mac V3
//
//  Created by callum taylor on 17/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "Settings.h"


int Settings::GetPrefInt(string key)
{
    return 56;
}

bool Settings::GetPrefBool(string key)
{
    return false;
}

float Settings::GetPrefFloat(string key)
{
    return (float)GetPrefInt(key);
}