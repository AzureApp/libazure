//
//  FirstViewController.m
//  Azure iOS
//
//  Created by callum taylor on 21/11/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "SearchViewController.h"
#import "ContainerViewController.h"
#import "ResultsHandler.h"

@interface SearchViewController ()
@property (nonatomic, weak) ContainerViewController *containerViewController;
@end

@interface NSString (HexAdditions)
- (NSData *)dataFromHexString;
@end

@implementation SearchViewController

@synthesize resultsView, line, settingsButton, searchType, searchNavigationBar, searchField;

- (void)viewDidLoad {
    [super viewDidLoad];
    [[NSNotificationCenter defaultCenter] addObserver:self
        selector:@selector(onResultsReceived)
        name:@"ReceivedResults"
        object:nil];

}

- (void)viewDidAppear:(BOOL)animated {
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys: [UIFont fontWithName:@"Titillium-Bold" size:14], NSFontAttributeName, nil];
    [searchType setTitleTextAttributes:attributes forState:UIControlStateNormal];
}

- (void)onRseultsReceived {
    if (![[ResultsHandler sharedInstance] hasResults]) {
        [self switchContainer:nil];
    }
}

- (void)switchContainer:(id)sender {
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
