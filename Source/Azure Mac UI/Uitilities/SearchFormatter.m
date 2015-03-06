//
//  SearchFormatter.m
//  Azure Mac UI
//
//  Created by callum taylor on 05/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "SearchFormatter.h"

@implementation SearchFormatter

- (BOOL)isPartialStringValid:(NSString *)partialString newEditingString:(NSString *__autoreleasing *)newString errorDescription:(NSString *__autoreleasing *)error {
    if([partialString length] < 6) return YES;
    NSBeep();
    return NO;
}

@end
