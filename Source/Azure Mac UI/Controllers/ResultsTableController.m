//
//  ResultsTableController.m
//  Azure Mac UI
//
//  Created by callum taylor on 02/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "ResultsTableController.h"
#import "Globals.h"

@implementation ResultsTableController



- (id)init
{
    self = [super init];
    if (self) {
       
    }
    return self;
}

- (void)refreshResults {
    [resultsView reloadData];
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return [[ResultsHandler sharedInstance] addressCount];
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    GlobalController *controller = [[Globals sharedInstance] controller];
    ResultsHandler *results = [ResultsHandler sharedInstance];
    if (results.addressCount == 0) return nil;
    if([[tableColumn identifier] isEqualToString:@"address"])
    {
        return [NSString stringWithFormat:@"0x%lX", results.addresses[row]];
    }
    switch(controller->searchType)
    {
        case e_Integer:
        {
            return [NSNumber numberWithInt:*(int*)results.value];
        }
        case e_Float:
        {
            return [NSNumber numberWithFloat:*(float*)results.value];
        }
        case e_Hex:
        {
            return @"TODO";
        }
        case e_String:
        {
            return [NSString stringWithUTF8String:results.value];
        }
    }
}

//- (NSView *)tableView:(NSTableView *)tableView viewForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
//    ResultsHandler *results = [ResultsHandler sharedInstance];
//    GlobalController *controller = [[Globals sharedInstance] controller];
//    
//    NSTextField *ret = nil;
//    
//    if ([tableColumn.identifier isEqualToString:@"address"])
//    {
//        ret = [tableView makeViewWithIdentifier:@"Address" owner:self];
//        
//        if (ret == nil) {
//            ret = [[NSTextField alloc] initWithFrame:CGRectMake(0, 0, 274, 17)];
//            ret.identifier = @"Address";
//        }
//        ret.stringValue = [NSString stringWithFormat:@"0x%lX", results.addresses[row]];
//    }
//    else
//    {
//        ret = [tableView makeViewWithIdentifier:@"Value" owner:self];
//        
//        if (ret == nil) {
//            ret = [[NSTextField alloc] initWithFrame:CGRectMake(0, 0, 274, 17)];
//            ret.identifier = @"Value";
//        }
//        switch(controller->searchType)
//        {
//            case e_Integer:
//            {
//                ret.stringValue = [NSString stringWithFormat:@"%d", *(int*)results.value];
//            }
//            case e_Float:
//            {
//                ret.stringValue = [NSString stringWithFormat:@"%.2f", *(float*)results.value];
//            }
//            case e_Hex:
//            {
//                ret.stringValue = @"TODO";
//            }
//            case e_String:
//            {
//                ret.stringValue = [NSString stringWithUTF8String:results.value];
//            }
//        }
//    }
//    return ret;
//}

- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    
   }

@end
