//
//  Process.h
//  Azure Mac UI
//
//  Created by callum taylor on 02/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Process : NSObject {
    NSString *name;
    pid_t pid;
}

@property (copy) NSString *name;
@property pid_t pid;

@end
