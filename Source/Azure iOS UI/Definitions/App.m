//
//  App.m
//  Azure
//
//  Created by callum taylor on 16/02/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import "App.h"

@implementation App

- (id)description {
    return [NSString stringWithFormat:@"Name: %@, Path: %@, PID: %d", self.name, self.path, self.pid];
}
@end
