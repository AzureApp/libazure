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

class Settings {
public:
    
    Settings();
    ~Settings();
    
    void LoadSettings();
    
    static int GetPrefInt(const char* key);
    static float GetPrefFloat(const char* key);
    static bool GetPrefBool(const char* key);
    
    __attribute__((noinline))
    bool reloadSettings();
    
    class settings_proxy {
    public:
        char* key;
        
        union Value {
            int asInt;
            bool asBool;
            float asFloat;
        } value;
        
        enum ValueType {
            Int,
            Bool,
            Float
        } valueType;
        
        settings_proxy(const char* _key) {
            key = (char*)malloc(strlen(_key));
            strcpy(key, _key);
        }
        
        settings_proxy(int val) {
            value.asInt = val;
            valueType = Int;
        }
        
        settings_proxy(float val) {
            value.asFloat = val;
            valueType = Float;
        }
        
        settings_proxy(bool val) {
            value.asBool = val;
            valueType = Bool;
        }
        
        
        __attribute__((noinline))
        operator int() {
            return Settings::GetPrefInt(key);
        }
        
        __attribute__((noinline))
        operator float() {
            return Settings::GetPrefFloat(key);
        }
        
        __attribute__((noinline))
        operator bool() {
            return Settings::GetPrefBool(key);
        }

        void set(bool value);
        void set(int value);
        void set(float value);
        
        __attribute__((noinline))
        ~settings_proxy() {
            if (key != NULL)
                free(key);
        }
    };
    __attribute__((noinline))
    settings_proxy operator[] (const char* key) {
        settings_proxy proxy(key);
        return proxy;
    }
};

#endif /* defined(__Azure_Mac_V3__Settings__) */
