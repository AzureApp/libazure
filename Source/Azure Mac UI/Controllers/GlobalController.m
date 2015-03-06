//
//  GlobalController.m
//  Azure Mac UI
//
//  Created by callum taylor on 02/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "GlobalController.h"
#import "Globals.h"

@implementation GlobalController
@synthesize searchComponentsEnabled, settingsPanel, searchType;

- (void)awakeFromNib {
    searchType = e_Integer;
    searchComponentsEnabled = NO;
}

- (void)enableSearchComponents {
    [componentController.searchControl setEnabled:YES];
    [componentController.searchControl setSelectedSegment:0];
    [componentController.searchField setEnabled:YES];
    [componentController.currentProcessName setStringValue:[NSString stringWithFormat:@"Current process: %@", [[Globals sharedInstance] currentProcess].name]];
    searchComponentsEnabled = YES;
}

- (void)disableSearchComponents {
    
}

@end
