//
//  SearchTableViewController.h
//  Azure
//
//  Created by callum taylor on 03/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SearchTableViewCell.h"
@interface SearchTableViewController : UITableViewController <UITableViewDataSource, UITableViewDelegate>

-(IBAction)toggleLock:(UIButton*)sender;
@end
