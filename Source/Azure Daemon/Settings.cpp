//
//  Settings.cpp
//  Azure Mac V3
//
//  Created by callum taylor on 17/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#include "Settings.h"
//#include "Azure.h"

extern "C" {
#include <Foundation/Foundation.h>
}
NSDictionary *prefs;

Settings::Settings() = default;
Settings::~Settings() = default;

void Settings::LoadSettings()
{
    prefs = [NSDictionary dictionaryWithContentsOfFile:@"/var/mobile/Documents/azureSettings.plist"];
}


int Settings::GetPrefInt(const char* key)
{
    return [[prefs objectForKey:[NSString stringWithUTF8String:key]] intValue];
}

float Settings::GetPrefFloat(const char* key)
{
    return [[prefs objectForKey:[NSString stringWithUTF8String:key]] floatValue];
}

bool Settings::GetPrefBool(const char* key)
{
    return [[prefs objectForKey:[NSString stringWithUTF8String:key]] boolValue];
}
