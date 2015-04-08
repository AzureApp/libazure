//
//  FirstViewController.h
//  Azure iOS
//
//  Created by callum taylor on 21/11/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SearchView.h"
#import "SearchTableViewCell.h"


@interface SearchViewController : UIViewController <UITextFieldDelegate, UIBarPositioningDelegate>

@property (nonatomic, strong) IBOutlet UITableView *resultsView;
@property (nonatomic, strong) IBOutlet UIView *line;
@property (nonatomic, strong) IBOutlet UIButton *settingsButton;
@property (nonatomic, strong) IBOutlet UISegmentedControl *searchType;
@property (nonatomic, strong) UINavigationController *passedController;
@property (nonatomic, strong) IBOutlet UINavigationBar *searchNavigationBar;
@property (nonatomic, strong) IBOutlet UITextField *searchField;

- (void)switchContainer:(id)sender;
- (void)onRseultsReceived;
- (IBAction)onSearchTypeChanged:(id)sender;
@end

