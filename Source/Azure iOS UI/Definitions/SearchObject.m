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

- (BOOL)isStringSearch {
    return (self.asString != nil);
}

- (BOOL)isNumberSearch {
    return (self.asNumber != nil);
}

- (BOOL)isDecimalNumberSearch {
    return (self.asDecimalNumber != nil);
}

- (BOOL)isBytes {
    return (self.asBytes != nil);
}

@end
