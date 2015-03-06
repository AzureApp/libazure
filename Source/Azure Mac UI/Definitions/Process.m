//
//  Process.m
//  Azure Mac UI
//
//  Created by callum taylor on 02/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "Process.h"

@implementation Process

@synthesize name, pid;

- (id)init
{
    self = [super init];
    if (self) {
        name = @"Process-Placeholder";
        pid = -1;
    }
    return self;
}

@end
