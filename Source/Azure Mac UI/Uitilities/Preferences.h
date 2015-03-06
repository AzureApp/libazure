//
//  Preferences.h
//  Azure Mac UI
//
//  Created by callum taylor on 13/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Preferences : NSObject {
    BOOL allProcesses;
    size_t numberOfResults;
    size_t startAddress;
    size_t endAddress;
}

@property BOOL allProcesses;
@property size_t numberOfResults;
@property size_t startAddress;
@property size_t endAddress;

- (void)synchronize;

@end
