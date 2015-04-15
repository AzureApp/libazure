//
//  SearchObject.h
//  Azure
//
//  Created by callum taylor on 03/01/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <mach/mach.h>

enum SearchType {
    Int,
    Float,
    Hex,
    String
};

struct DataObject {
    enum SearchType dataType;
    
    vm_address_t address;
    int dataLen;
    char data[16];
};

@interface SearchObject : NSObject

@property vm_address_t address;
@property (strong) NSString *asString;
@property (strong) NSNumber *asNumber;
@property (strong) NSDecimalNumber *asDecimalNumber;
@property (strong) NSData *asBytes;

+ (instancetype)searchWithString:(NSString *)string;
+ (instancetype)searchWithNumber:(NSNumber *)number;
+ (instancetype)searchWithDecimalNumber:(NSDecimalNumber *)number;
+ (instancetype)searchWithBytes:(NSData *)bytes;
+ (instancetype)objectFromDataObject:(struct DataObject)obj;

- (BOOL)isStringSearch;
- (BOOL)isNumberSearch;
- (BOOL)isDecimalNumberSearch;
- (BOOL)isByteSearch;

- (NSInteger)getSearchSize;
- (void*)getRawData;

- (NSString *)toString;
@end
