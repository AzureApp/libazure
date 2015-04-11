//
//  ContainerViewController.h
//  Azure
//
//  Created by callum taylor on 05/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SearchTableViewController.h"
#import "SearchStatusViewController.h"

@interface ContainerViewController : UIViewController

@property (strong, nonatomic) NSString *currentSegueIdentifier;
@property (strong, nonatomic) SearchTableViewController *secondViewController;
@property (strong, nonatomic) SearchStatusViewController *firstViewController;
@property BOOL showProgress;
@property int results;

- (void)swapViewControllers;
@end
