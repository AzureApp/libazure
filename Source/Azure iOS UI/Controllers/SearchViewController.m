//
//  FirstViewController.m
//  Azure iOS
//
//  Created by callum taylor on 21/11/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "UINavigationController+M13ProgressViewBar.h"
#import "SearchViewController.h"
#import "ContainerViewController.h"
#import "ResultsHandler.h"
#import "AppHandler.h"

@interface SearchViewController ()
@property (nonatomic, weak) ContainerViewController *containerViewController;
@end

@implementation SearchViewController

@synthesize processButton, line, settingsButton, searchType, searchNavigationBar, searchField;

- (void)viewDidLoad {
    [super viewDidLoad];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onResultsReceived)
                                                 name:@"ReceivedResults"
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(onValuesReceived)
                                                 name:@"ReceivedValues"
                                               object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(retrieveUpdatedValues)
                                                 name:@"RetrieveUpdatedValues"
                                               object:nil];
    NSLog(@"children : %@", self.childViewControllers);
}

- (void)viewDidAppear:(BOOL)animated {
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys: [UIFont fontWithName:@"Titillium-Bold" size:14], NSFontAttributeName, nil];
    [searchType setTitleTextAttributes:attributes forState:UIControlStateNormal];
    NSString *name = ([[AppHandler sharedInstance] currentApp]) ? [[AppHandler sharedInstance] currentApp].name : @"None";
    [processButton setTitle:[NSString stringWithFormat:@"Current Process: %@",name] forState:UIControlStateNormal];
    if (![[AppHandler sharedInstance] currentApp]) {
        searchField.enabled = NO;
        searchType.enabled = NO;
    }
    else {
        searchField.enabled = YES;
        searchType.enabled = YES;
    }
}

- (void)onResultsReceived {
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    int count = (handler.addressCount < 100) ? handler.addressCount : 100;
    self.containerViewController.firstViewController.showProgress = NO;
    if (count < 100 && count > 0 && [self.containerViewController.currentSegueIdentifier isEqualToString:@"embedFirst"]) {
        [[ResultsHandler sharedInstance] requestResultsFromStart:0 forCount:count];
    }
    else {
        [self.containerViewController.firstViewController showDefaultUI];
    }
    [self.containerViewController.secondViewController.tableView reloadData];
}

- (void)onValuesReceived {
    [self.containerViewController.secondViewController.tableView reloadData];
    if ([self.containerViewController.currentSegueIdentifier isEqualToString:@"embedFirst"]) {
        [self switchContainer];
    }
}

- (void)retrieveUpdatedValues {
    if ([self.containerViewController.currentSegueIdentifier isEqualToString:@"embedSecond"]) {        
        ResultsHandler *handler = [ResultsHandler sharedInstance];
        if ([handler hasResults]) {
            handler.searchObjects = nil;
            Message msg;
            msg.header = header_default;
            msg.header.type = Values;
            msg.header.messageSize = sizeof(msg_values);
            msg_values *vals = malloc(sizeof(msg_values));
            vals->start = 0;
            vals->count = 100;
            
            msg.message = vals;
            [[MessageHandler sharedInstance] sendMessage:msg];
        }
    }
}

- (void)switchContainer {
    self.containerViewController.results = [ResultsHandler sharedInstance].addressCount;
    [self.containerViewController swapViewControllers];
}

- (IBAction)onSearchTypeChanged:(UISegmentedControl *)sender {
    [searchField setText:@""];
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    handler.currentSearchType = (int)sender.selectedSegmentIndex;
    NSLog(@"%d", handler.currentSearchType);
}

- (IBAction)processSeleced:(id)sender {
    UIActionSheet *popup = [[UIActionSheet alloc] initWithTitle:@"Process Options" delegate:self
                                              cancelButtonTitle:@"Close" destructiveButtonTitle:nil
                                              otherButtonTitles:@"Detach From Process", nil];
    SEL selector = NSSelectorFromString(@"_alertController");
    if ([popup respondsToSelector:selector]) {
        UIAlertController *alertController = [popup valueForKey:@"_alertController"];
        if ([alertController isKindOfClass:[UIAlertController class]]) {
            alertController.view.tintColor = [UIColor colorWithRed:49/255.0f green:192/255.0f blue:190/255.0f alpha:1.0];
        }
    }
    else {
        for (UIView *subview in popup.subviews) {
            if ([subview isKindOfClass:[UIButton class]]) {
                UIButton *button = (UIButton *)subview;
                [button setTitleColor:[UIColor colorWithRed:49/255.0f green:192/255.0f blue:190/255.0f alpha:1.0] forState:UIControlStateNormal];
            }
        }
    }
    [popup showInView:[UIApplication sharedApplication].keyWindow];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString:@"embedContainer"]) {
        self.containerViewController = segue.destinationViewController;
    }
}

- (BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string  {
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    NSString *chars;
    switch (handler.currentSearchType) {
        case Int: {
            chars = @"0123456789";
            break;
        }
        case Float: {
            chars = @"0123456789.";
            break;
        }
        case Hex: {
            chars = @"0123456789ABCDEFabcdefxX ";
            break;
        }
        case String: {
            return YES;
        }
    }
    NSString *newString = [textField.text stringByReplacingCharactersInRange:range withString:string];
    NSArray  *arrayOfString = [newString componentsSeparatedByString:@"."];
    
    if ([arrayOfString count] > 2 ) {
        return NO;
    }
    NSCharacterSet *cs = [[NSCharacterSet characterSetWithCharactersInString:chars] invertedSet];
    
    NSString *filtered = [[string componentsSeparatedByCharactersInSet:cs] componentsJoinedByString:@""];
    return [string isEqualToString:filtered];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    NSString *contents = [textField text];
    NSLog(@"test %@", contents);
    
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    switch (handler.currentSearchType) {
            
        case Int: {
            NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
            [f setNumberStyle:NSNumberFormatterDecimalStyle];
            NSNumber *num = [f numberFromString:contents];
            [handler setCurrentSearchObject:[SearchObject searchWithNumber:num]];
            break;
        }
        case Float: {
            NSDecimalNumber *num = [NSDecimalNumber decimalNumberWithString:contents];
            [handler setCurrentSearchObject:[SearchObject searchWithDecimalNumber:num]];
            break;
        }
        case Hex: {
            NSData *data = [contents dataFromHexString];
            [handler setCurrentSearchObject:[SearchObject searchWithBytes:data]];
            break;
        }
        case String: {
            [handler setCurrentSearchObject:[SearchObject searchWithString:contents]];
            break;
        }
    }
    if ([self.containerViewController.currentSegueIdentifier isEqualToString:@"embedSecond"]) {
        [self switchContainer];
    }
    if ([handler hasResults]) {
        UITableView *resultsView = self.containerViewController.secondViewController.tableView;
        [resultsView setContentOffset:CGPointZero animated:YES];
    }
    handler.searchObjects = nil;
    self.containerViewController.firstViewController.showProgress = YES;
    [self.containerViewController.firstViewController showProgressUI];
    [[ResultsHandler sharedInstance] beginSearch];
    return NO;
}

- (UIBarPosition)positionForBar:(id<UIBarPositioning>)bar {
    return UIBarPositionTopAttached;
}

- (void)actionSheet:(UIActionSheet *)popup clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 0) {
        Message msg;
        msg.header = header_default;
        msg.header.type = Detach;
        
        [[MessageHandler sharedInstance] sendMessage:msg];
    }
}

@end
