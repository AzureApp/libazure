//
//  AzureSettings.h
//  Azure
//
//  Created by callum taylor on 16/04/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AzureSettings : NSObject

@property (nonatomic, strong) NSMutableDictionary *userDict;
+ (instancetype)userSettings;

@end
