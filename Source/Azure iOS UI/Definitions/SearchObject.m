//
//  SearchObject.m
//  Azure
//
//  Created by callum taylor on 03/01/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import "SearchObject.h"

@implementation SearchObject

+ (instancetype)searchWithString:(NSString *)string {
    SearchObject *obj = [[SearchObject alloc] init];
    obj.asString = string;
    return obj;
}

+ (instancetype)searchWithNumber:(NSNumber *)number {
    SearchObject *obj = [[SearchObject alloc] init];
    obj.asNumber = number;
    return obj;
}

+ (instancetype)searchWithDecimalNumber:(NSDecimalNumber *)number {
    SearchObject *obj = [[SearchObject alloc] init];
    obj.asDecimalNumber = number;
    return obj;
}

+ (instancetype)searchWithBytes:(NSData *)bytes {
    SearchObject *obj = [[SearchObject alloc] init];
    obj.asBytes = bytes;
    return obj;
}

+ (instancetype)objectFromDataObject:(struct DataObject)obj {
    SearchObject *so = [SearchObject new];
    switch (obj.dataType) {
        case Int: so.asNumber = [NSNumber numberWithInt:*(int*)obj.data];
        case Float: so.asDecimalNumber = [NSNumber numberWithFloat:*(float*)obj.data];
        case Hex: so.asBytes = [NSData dataWithBytes:obj.data length:obj.dataLen];
        case String: so.asString = [NSString stringWithUTF8String:obj.data];
    }
    so.address = obj.address;
    return so;
}

- (BOOL)isStringSearch {
    return (self.asString != nil);
}

- (BOOL)isNumberSearch {
    return (self.asNumber != nil);
}

- (BOOL)isDecimalNumberSearch {
    return (self.asDecimalNumber != nil);
}

- (BOOL)isByteSearch {
    return (self.asBytes != nil);
}

- (NSInteger)getSearchSize {
    if ([self isNumberSearch]) {
        return sizeof(int); // TODO: change to 1 byte, 2 bytes, 4 bytes ... etc
    }
    if ([self isDecimalNumberSearch]) {
        return sizeof(float); // TODO: change to float, double, quad ... etc
    }
    if ([self isByteSearch]) {
        return [[self asBytes] length];
    }
    if ([self isStringSearch]) {
        return [[self asString] length]; // may have to adjust for trailing byte
    }
    return 0;
}

- (void*)getRawData {
    NSInteger size = [self getSearchSize];
    void *data = malloc(size);
    
    if ([self isNumberSearch]) {
        int val = [[self asNumber] intValue];
        memcpy(data, &val, size); // TODO: change to 1 byte, 2 bytes, 4 bytes ... etc
    }
    else if ([self isDecimalNumberSearch]) {
    float val = [[self asDecimalNumber] floatValue];
        memcpy(data, &val, size); // TODO: change to 1 byte, 2 bytes, 4 bytes ... etc

    }
    else if ([self isByteSearch]) {
        const void *val = [[self asBytes] bytes];
        memcpy(data, val, size); // TODO: change to 1 byte, 2 bytes, 4 bytes ... etc
    }
    else if ([self isStringSearch]) {
        const char *val = [[self asString] UTF8String];
        memcpy(data, val, size);
    }
    return data;
}

- (NSString *)toString {
    if ([self isNumberSearch]) {
        return [NSString stringWithFormat:@"%d", [[self asNumber] intValue]];
    }
    if ([self isDecimalNumberSearch]) {
        return [NSString stringWithFormat:@"%f", [[self asDecimalNumber] floatValue]];
    }
    if ([self isByteSearch]) {
        NSData *data = [self asBytes];
        NSMutableString *hex = [NSMutableString new];
        char *byteData = malloc(data.length);
        memcpy(byteData, data.bytes, data.length);
        for (int i = 0; i < data.length; i++) {
            [hex appendFormat:@"%02x", byteData[i]];
        }
        free(byteData);
        return [NSString stringWithString:hex];
    }
    if ([self isStringSearch]) {
        return [self asString];
    }
    return [NSString new];
}

- (void)modifyData:(NSString *)data {
    if ([self isNumberSearch]) {
        NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
        [f setNumberStyle:NSNumberFormatterDecimalStyle];
        NSNumber *num = [f numberFromString:data];
        self.asNumber = num;
    }
    else if ([self isDecimalNumberSearch]) {
        NSDecimalNumber *num = [NSDecimalNumber decimalNumberWithString:data];
        self.asDecimalNumber = num;
    }
    else if ([self isByteSearch]) {
        NSData *byteData = [data dataFromHexString];
        self.asBytes = byteData;
    }
    else if ([self isStringSearch]) {
        self.asString = data;
    }
}

@end
