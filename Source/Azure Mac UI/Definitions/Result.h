//
//  Result.h
//  Azure Mac UI
//
//  Created by callum taylor on 02/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>

enum ResultType {
    e_Integer,
    e_Float,
    e_String,
    e_Hex
};

@interface Result : NSObject {
@public
    vm_address_t address;
    enum ResultType type;
    void* value;
    size_t valueCnt;
}

+ (Result *)resultWithAddress:(vm_address_t)address andInt:(int)result;
+ (Result *)resultWithAddress:(vm_address_t)address andFloat:(float)result;
+ (Result *)resultWithAddress:(vm_address_t)address andDouble:(double)result;
+ (Result *)resultWithAddress:(vm_address_t)address andHex:(char *)result ofSize:(long)size;
+ (Result *)resultWithAddress:(vm_address_t)address andString:(const char *)result;

@property vm_address_t address;
@property void* value;

@end
