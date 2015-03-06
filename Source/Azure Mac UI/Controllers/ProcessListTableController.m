//
//  ProcessListTableController.m
//  Azure Mac UI
//
//  Created by callum taylor on 02/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "ProcessListTableController.h"
#import "Process.h"
#import "Globals.h"
#import "AzureAppDelegate.h"

@implementation ProcessListTableController

@synthesize processes, processList;
 
- (id)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return [processes count];
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    Process *process = [processes objectAtIndex:row];
    NSString *identifier = [tableColumn identifier];
    return [process valueForKey:identifier];
}

- (BOOL)tableView:(NSTableView *)tableView shouldSelectRow:(NSInteger)row {
    Process *process = [processes objectAtIndex:row];
//    [[NSNotificationCenter defaultCenter] postNotificationName:@"SelectedProcess" object:process];
    Globals *globals = [Globals sharedInstance];
    [globals selectedProcess:process];
    return YES;
}

@end
