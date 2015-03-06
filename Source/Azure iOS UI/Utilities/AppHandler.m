//
//  AppHandler.m
//  Azure
//
//  Created by callum taylor on 16/02/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import "AppHandler.h"

@interface AppHandler()
- (NSString *)pathForPID:(int)pid;
- (NSString *)bundleForPath:(NSString *)path;
@end

@implementation AppHandler

+ (id)sharedInstance {
    static id inst = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        inst = [[AppHandler alloc] init];
    });
    return inst;
}

- (NSArray *)allRunningApps {
    int mib[4] = {CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0};
    size_t miblen = 4;
    
    size_t size;
    int st = sysctl(mib, miblen, NULL, &size, NULL, 0);
    
    struct kinfo_proc * process = NULL;
    struct kinfo_proc * newprocess = NULL;
    
    do {
        
        size += size / 10;
        newprocess = realloc(process, size);
        
        if (!newprocess){
            
            if (process){
                free(process);
            }
            
            return nil;
        }
        
        process = newprocess;
        st = sysctl(mib, miblen, process, &size, NULL, 0);
        
    } while (st == -1 && errno == ENOMEM);
    
    if (st == 0) {
        
        if (size % sizeof(struct kinfo_proc) == 0){
            int nprocess = size / sizeof(struct kinfo_proc);
            
            if (nprocess) {
                NSMutableArray * array = [[NSMutableArray alloc] init];
                for (int i = nprocess - 1; i >= 0; i--) {
                    int pid = process[i].kp_proc.p_pid;
                    const char *name = [[self pathForPID:pid] lastPathComponent].UTF8String;
                    
                    if (name == NULL) name = process[i].kp_proc.p_comm;
                    
                    App *app = [[App alloc] init];
                    
                    if ([[self pathForPID:pid] rangeOfString:@".app"].location == NSNotFound) continue;
                
                    app.name = [NSString stringWithUTF8String:name];
                    app.path = [self pathForPID:pid];
                    app.pid = pid;
                    app.bundleID = [self bundleForPath:[self pathForPID:pid]];
                    
                    [array addObject:app];
                    
                }
                free(process);
                return array;
            }
        }
    }
    
    return nil;
}

- (NSString *)pathForPID:(int)pid {
    int mib[3] = {CTL_KERN, KERN_ARGMAX, 0};
    
    size_t argmaxsize = sizeof(size_t);
    size_t size;
    
    int ret = sysctl(mib, 2, &size, &argmaxsize, NULL, 0);
    
    if (ret != 0) {
        return NULL;
    }
    
    // Then we can get the path information we actually want
    mib[1] = KERN_PROCARGS2;
    mib[2] = (int)pid;
    
    char *procargv = (char *)malloc(size);
    
    ret = sysctl(mib, 3, procargv, &size, NULL, 0);
    
    if (ret != 0) {
        free(procargv);
        
        return NULL;
    }
    char *path = procargv + sizeof(int);
    NSString *str = [NSString stringWithUTF8String:path];
    free(procargv);
    
    return str;
}

- (void)refreshRunningApps {
    // NO OP
}

- (NSString *)bundleForPath:(NSString *)path {
    NSString *folderPath = [path stringByDeletingLastPathComponent];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSString *infoPath = [NSString stringWithFormat:@"%@/Info.plist", folderPath];
    if ([fileManager fileExistsAtPath:infoPath])
    {
        NSDictionary *appDict = [NSDictionary dictionaryWithContentsOfFile:infoPath];
        return appDict[@"CFBundleIdentifier"];
    }
    return [NSString new];
}

+ (UIImage *)appIconForBundleID:(NSString *)bundleID {
    void *sbserv = dlopen("/System/Library/PrivateFrameworks/SpringBoardServices.framework/SpringBoardServices", RTLD_LAZY);
    NSData* (*SBSCopyIconImagePNGDataForDisplayIdentifier)(NSString *bundleid) = dlsym(sbserv, "SBSCopyIconImagePNGDataForDisplayIdentifier");
    
    UIImage *icon = nil;
    NSData *iconData = SBSCopyIconImagePNGDataForDisplayIdentifier(bundleID);
    if (iconData != nil) {
        icon = [UIImage imageWithData:iconData];
        
    }
    else {
        if ((UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad))
            icon = [[UIImage alloc] initWithContentsOfFile:@"/System/Library/PrivateFrameworks/MobileIcons.framework/DefaultIcon-76.png"];
        else
            icon = [[UIImage alloc] initWithContentsOfFile:@"/System/Library/PrivateFrameworks/MobileIcons.framework/DefaultIcon-40.png"];
    }
    dlclose(sbserv);
    return icon;
}

@end
