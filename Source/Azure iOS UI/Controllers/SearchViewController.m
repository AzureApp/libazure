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

@synthesize resultsView, line, settingsButton, searchType;

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    UIBezierPath *shadowPath = [UIBezierPath bezierPathWithRect:line.bounds];
//    line.layer.masksToBounds = NO;
//    line.layer.shadowColor = [UIColor blackColor].CGColor;
//    line.layer.shadowRadius = 5.0f;
//    line.layer.shadowOffset = CGSizeMake(0.0f, 0.5f);
//    line.layer.shadowOpacity = 0.5f;
//    line.layer.shadowPath = shadowPath.CGPath;
    //resultsView.layer.shadowPath = [UIBezierPath bezierPathWithRect:line.bounds].CGPath;
    //[line setNeedsLayout];

}

- (void)viewDidAppear:(BOOL)animated {
    
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys: [UIFont fontWithName:@"Titillium-Bold" size:14], NSFontAttributeName, nil];
    [searchType setTitleTextAttributes:attributes forState:UIControlStateNormal];
}

- (IBAction)switchTest:(id)sender {
    [self.containerViewController swapViewControllers];
}

- (IBAction)onSearchTypeChanged:(UISegmentedControl *)sender {
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

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    [textField resignFirstResponder];
    NSString *contents = [textField text];
    NSLog(@"%@", contents);
    
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
    return NO;
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
