//
//  AboutViewController.h
//  Azure
//
//  Created by callum taylor on 18/04/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AboutViewController : UITableViewController <UITableViewDataSource, UITableViewDelegate>
@property (nonatomic, strong) IBOutlet UITextView *aboutView;
@end
