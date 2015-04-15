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

@interface NSString (HexAdditions)
- (NSData *)dataFromHexString;
@end

@implementation SearchViewController

@synthesize processLabel, line, settingsButton, searchType, searchNavigationBar, searchField;

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
    NSLog(@"children : %@", self.childViewControllers);
}

- (void)viewDidAppear:(BOOL)animated {
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys: [UIFont fontWithName:@"Titillium-Bold" size:14], NSFontAttributeName, nil];
    [searchType setTitleTextAttributes:attributes forState:UIControlStateNormal];
    processLabel.text = [NSString stringWithFormat:@"Current Process: %@", [[AppHandler sharedInstance] currentApp].name];
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

- (void)switchContainer {
    self.containerViewController.results = [ResultsHandler sharedInstance].addressCount;
    [self.containerViewController swapViewControllers];
}

- (IBAction)onSearchTypeChanged:(UISegmentedControl *)sender {
    [searchField setText:@""];
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    handler.currentSearchType = sender.selectedSegmentIndex;
    NSLog(@"%d", handler.currentSearchType);
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
    else {
        handler.searchObjects = nil;
        handler.addressCount = 0;
    }
    self.containerViewController.firstViewController.showProgress = YES;
    [self.containerViewController.firstViewController showProgressUI];
    [[ResultsHandler sharedInstance] beginSearch];
    return NO;
}

- (UIBarPosition)positionForBar:(id<UIBarPositioning>)bar {
    return UIBarPositionTopAttached;
}
    
@end

@implementation NSString (HexAdditions)

- (NSData *)dataFromHexString {
    const char *chars = [self UTF8String];
    int i = 0, len = self.length;
    
    NSMutableData *data = [NSMutableData dataWithCapacity:len / 2];
    char byteChars[3] = {'\0','\0','\0'};
    unsigned long wholeByte;
    
    while (i < len) {
        byteChars[0] = chars[i++];
        byteChars[1] = chars[i++];
        wholeByte = strtoul(byteChars, NULL, 16);
        [data appendBytes:&wholeByte length:1];
    }
    
    return data;
}

@end
