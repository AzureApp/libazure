//
//  Preferences.m
//  Azure Mac UI
//
//  Created by callum taylor on 13/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "Preferences.h"


@implementation Preferences

@synthesize allProcesses, numberOfResults, startAddress, endAddress;

- (id)init
{
    self = [super init];
    if (self) {
        allProcesses = NO;
        numberOfResults = [[[NSUserDefaults standardUserDefaults] objectForKey:@"numberOfResults"] longValue];
        startAddress = [[[NSUserDefaults standardUserDefaults] objectForKey:@"startAddress"] longValue];
        endAddress = [[[NSUserDefaults standardUserDefaults] objectForKey:@"endAddress"] longValue];
    }
    return self;
}

- (void)synchronize {
    [[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithLong:numberOfResults] forKey:@"numberOfResults"];
    [[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithLong:startAddress] forKey:@"startAddress"];
    [[NSUserDefaults standardUserDefaults] setObject:[NSNumber numberWithLong:endAddress] forKey:@"endAddress"];
    [[NSUserDefaults standardUserDefaults] synchronize];
}

@end
