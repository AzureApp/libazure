//
//  ProcessUtils.m
//  Azure Mac UI
//
//  Created by callum taylor on 12/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "ProcessManager.h"

@implementation ProcessUtils

+ (NSArray *)allProcesses {
    
    NSMutableArray *local = [[NSMutableArray alloc] init];
    
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    u_int miblen = 4;
    
    size_t size;
    int st = sysctl(mib, miblen, NULL, &size, NULL, 0);
    
    struct kinfo_proc * process = NULL;
    struct kinfo_proc * newprocess = NULL;
    
    do {
        
        size += size / 10;
        newprocess = (struct kinfo_proc *)realloc(process, size);
        
        if (!newprocess)
        {
            if (process){
                free(process);
            }
            return local;
        }
        
        process = newprocess;
        st = sysctl(mib, miblen, process, &size, NULL, 0);
        
    } while (st == -1 && errno == ENOMEM);
    
    if (st == 0)
    {
        
        if (size % sizeof(struct kinfo_proc) == 0)
        {
            long nprocess = size / sizeof(struct kinfo_proc);
            
            if (nprocess)
            {
                for (long i = nprocess - 1; i >= 0; i--)
                {
                    /*struct passwd *user = getpwuid(process[i].kp_eproc.e_ucred.cr_uid);
                     const char * name = user->pw_name;*/
                    NSArray *uiProcesses = [ProcessUtils uiProcesses];
                    
                    Process *temp = [[Process alloc] init];
                    char pathBuffer[PROC_PIDPATHINFO_MAXSIZE];
                    proc_pidpath(process[i].kp_proc.p_pid, pathBuffer, sizeof(pathBuffer));
                    
                    char nameBuffer[256];
                    strcpy(nameBuffer, process[i].kp_proc.p_comm);
                    long position = strlen(pathBuffer);
                    while(position >= 0 && pathBuffer[position] != '/')
                    {
                        position--;
                    }
                    if (isalpha(*(pathBuffer+position+1)))
                    {
                        strcpy(nameBuffer, pathBuffer + position + 1);
                    }
                    
                    temp.pid = process[i].kp_proc.p_pid;
                    temp.name = [NSString stringWithUTF8String:nameBuffer];
                    
                    if (![[Globals sharedInstance] userPreferences].allProcesses)
                    {
                        for (NSNumber *process in uiProcesses)
                        {
                            pid_t pid = [process intValue];
                            if (pid == temp.pid)
                            {
                                if ([local containsObject:temp] || temp.pid == getpid()) continue;
                                [local addObject:temp];
                            }
                            
                        }
                        CFRelease((__bridge CFTypeRef)(uiProcesses));
                    }
                    else
                    {
                        if ([local containsObject:temp] || temp.pid == getpid()) continue;
                        [local addObject:temp];
                    }
                    
                }
            }
            
            free(process);
        }
    }
    return [NSArray arrayWithArray:local];
}

+ (NSArray *)uiProcesses {
    CFArrayRef  orderedwindows = CGWindowListCopyWindowInfo(kCGWindowListOptionAll, kCGNullWindowID);
    CFIndex count = CFArrayGetCount(orderedwindows);
    CFMutableArrayRef uiProcess = CFArrayCreateMutable(kCFAllocatorDefault , count,  &kCFTypeArrayCallBacks);
    for (CFIndex i = 0; i < count; i++)
    {
        if (orderedwindows)
        {
            CFDictionaryRef windowsdescription = (CFDictionaryRef)CFArrayGetValueAtIndex(orderedwindows, i);
            CFNumberRef windowownerpid  = (CFNumberRef)CFDictionaryGetValue (windowsdescription, CFSTR("kCGWindowOwnerPID"));
            CFArrayAppendValue(uiProcess, windowownerpid);
        }
    }
    CFRelease(orderedwindows);
    return (__bridge NSArray *)(uiProcess);
}

@end
