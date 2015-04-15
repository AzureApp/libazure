//
//  SearchTableViewController.h
//  Azure
//
//  Created by callum taylor on 03/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SearchTableViewCell.h"
#import "ResultsHandler.h"
#import "NSString+HexAdditions.h"

@interface SearchTableViewController : UITableViewController <UITableViewDataSource, UITableViewDelegate, UITextFieldDelegate>
-(IBAction)toggleLock:(UIButton*)sender;
@end
