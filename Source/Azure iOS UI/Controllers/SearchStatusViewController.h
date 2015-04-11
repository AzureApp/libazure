//
//  SearchStatusViewController.h
//  Azure
//
//  Created by callum taylor on 05/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "M13ProgressViewSegmentedBar.h"
#import "ResultsHandler.h"

@interface SearchStatusViewController : UIViewController

@property (nonatomic, retain) IBOutlet M13ProgressViewSegmentedBar *progressView;
@property (nonatomic, retain) IBOutlet UILabel *resultsLabel;
@property (nonatomic, retain) IBOutlet UIButton *resultsButton;
@property BOOL showProgress;

- (void)initProgress;

- (void)showDefaultUI;
- (void)showProgressUI;

@end
