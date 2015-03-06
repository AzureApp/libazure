//
//  Settings.h
//  Azure Mac V3
//
//  Created by callum taylor on 17/06/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#ifndef __Azure_Mac_V3__Settings__
#define __Azure_Mac_V3__Settings__

#include <iostream>
#include <string>

using namespace std;


class Settings {
public:
    static int GetPrefInt(string key);
    static bool GetPrefBool(string key);
    static float GetPrefFloat(string key);
    
    class settings_proxy {
    public:
        string _key;
        settings_proxy(string key) : _key(key)
        {
            
        }
        
        operator int() {
            return Settings::GetPrefInt(_key);
        }
        
        operator bool() {
            return Settings::GetPrefBool(_key);
        }
        
        operator float() {
            return Settings::GetPrefFloat(_key);
        }
    };

    
    settings_proxy operator[] (std::string key) {
        settings_proxy proxy = settings_proxy(key);
        return proxy;
    }
};



#endif /* defined(__Azure_Mac_V3__Settings__) */
