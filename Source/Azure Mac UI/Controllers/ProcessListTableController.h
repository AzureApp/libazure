//
//  ProcessListTableController.h
//  Azure Mac UI
//
//  Created by callum taylor on 02/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ProcessListTableController : NSObject <NSTableViewDelegate, NSTableViewDataSource> {
    IBOutlet NSTableView *processList;
    NSMutableArray *processes;
}
@property (nonatomic, retain) NSMutableArray *processes;
@property (nonatomic, retain) NSTableView *processList;
@end
