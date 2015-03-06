//
//  ProcessUtils.h
//  Azure Mac UI
//
//  Created by callum taylor on 12/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Process.h"
#import "Globals.h"

#include <stdio.h>
#include <mach/mach.h>
#include <mach/mach_vm.h>
#include <errno.h>
#include <sys/sysctl.h>
#include <assert.h>
#include <sys/types.h>
#include <pwd.h>
#include <libproc.h>

@interface ProcessUtils : NSObject

+ (NSArray *)allProcesses;
+ (NSArray *)uiProcesses;
@end
