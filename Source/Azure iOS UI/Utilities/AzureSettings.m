//
//  AzureSettings.m
//  Azure
//
//  Created by callum taylor on 16/04/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import "AzureSettings.h"
#define SETTINGS_PATH  [[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0] stringByAppendingPathComponent:@"azureSettings.plist"]
@implementation AzureSettings

@synthesize userDict;

+ (instancetype)userSettings {
    static AzureSettings *inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = [[AzureSettings alloc] init];
    });
    if (![[NSFileManager defaultManager] fileExistsAtPath:SETTINGS_PATH]) {
        inst.userDict = [NSMutableDictionary dictionaryWithObjects:@[@4, @1000000, @(1|2)] forKeys:@[@"kAlignment", @"kMaxResults", @"kRegions"]];
    }
    else {
        inst.userDict = [NSMutableDictionary dictionaryWithContentsOfFile:SETTINGS_PATH];
    }
    return inst;
}

- (void)setValue:(id)value forKey:(NSString *)key {
    NSLog(SETTINGS_PATH);
    [userDict setObject:value forKey:key];
    [userDict writeToFile:SETTINGS_PATH atomically:YES];
}

@end
