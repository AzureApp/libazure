//
//  Result.m
//  Azure Mac UI
//
//  Created by callum taylor on 02/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "Result.h"

@implementation Result

@synthesize address, value;

- (id)init
{
    self = [super init];
    if (self) {
        address = 0x1337;
        type = e_Integer;
        value = malloc(4);
        *(int*)value = 0;
    }
    return self;
}

+ (Result *)resultWithAddress:(vm_address_t)address andInt:(int)result {
    Result *temp = [[Result alloc] init];
    free([temp value]);
    temp->value = malloc(sizeof(int));
    *(int*)temp->value = result;
    temp->address = address;
    temp->valueCnt = sizeof(int);
    temp->type = e_Integer;
    return temp;
}

+ (Result *)resultWithAddress:(vm_address_t)address andDouble:(double)result {
    Result *temp = [[Result alloc] init];
    free([temp value]);
    temp->value = malloc(sizeof(double));
    *(double*)temp->value = result;
    temp->address = address;
    temp->valueCnt = sizeof(double);
    temp->type = e_Float;
    return temp;
}

+ (Result *)resultWithAddress:(vm_address_t)address andFloat:(float)result {
    Result *temp = [[Result alloc] init];
    free([temp value]);
    temp->value = malloc(sizeof(float));
    *(float*)temp->value = result;
    temp->address = address;
    temp->valueCnt = sizeof(float);
    temp->type = e_Float;
    return temp;
}

+ (Result *)resultWithAddress:(vm_address_t)address andHex:(char *)result ofSize:(long)size {
    Result *temp = [[Result alloc] init];
    free([temp value]);
    temp->value = malloc(size);
    memcpy(temp->value, result, size);
    temp->address = address;
    temp->valueCnt = size;
    temp->type = e_Hex;
    return temp;
}

+ (Result *)resultWithAddress:(vm_address_t)address andString:(const char*)result {
    Result *temp = [[Result alloc] init];
    long size = strlen(result);
    free([temp value]);
    temp->value = malloc(size);
    memcpy(temp->value, result, size);
    temp->address = address;
    temp->valueCnt = size;
    temp->type = e_String;
    return temp;
}

@end