//
//  SearchObject.h
//  Azure
//
//  Created by callum taylor on 03/01/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SearchObject : NSObject

@property (strong) NSString *asString;
@property (strong) NSNumber *asNumber;
@property (strong) NSDecimalNumber *asDecimalNumber;
@property (strong) NSData *asBytes;

+ (instancetype)searchWithString:(NSString *)string;
+ (instancetype)searchWithNumber:(NSNumber *)number;
+ (instancetype)searchWithDecimalNumber:(NSDecimalNumber *)number;
+ (instancetype)searchWithBytes:(NSData *)bytes;

- (BOOL)isStringSearch;
- (BOOL)isNumberSearch;
- (BOOL)isDecimalNumberSearch;
- (BOOL)isByteSearch;

- (NSInteger)getSearchSize;
- (void*)getRawData;

- (NSString *)toString;
@end
