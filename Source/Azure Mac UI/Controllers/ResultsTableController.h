//
//  ResultsTableController.h
//  Azure Mac UI
//
//  Created by callum taylor on 02/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Result.h"


@interface ResultsTableController : NSObject <NSTableViewDataSource, NSTableViewDelegate> {
    IBOutlet NSTableView *resultsView;
}
@property (copy) NSMutableArray *resultsArr;
- (void)refreshResults;
@end
