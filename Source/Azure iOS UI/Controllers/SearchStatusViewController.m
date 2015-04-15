//
//  SearchStatusViewController.m
//  Azure
//
//  Created by callum taylor on 05/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "SearchStatusViewController.h"
#import "ContainerViewController.h"

static float count = 0;

@interface SearchStatusViewController ()

- (void)showDefaultUI;
- (void)showProgressUI;
- (void)showResults;

- (void)progressUpdate;
@end

@implementation SearchStatusViewController

@synthesize resultsButton, resultsLabel;

- (id)initWithCoder:(NSCoder *)aDecoder {
    return [super initWithCoder:aDecoder];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    resultsButton.layer.borderWidth = 1;
    resultsButton.layer.borderColor = [UIColor colorWithRed:49/255.0f green:192/255.0f blue:190/255.0f alpha:1.0].CGColor;
    resultsButton.layer.cornerRadius = 6;
    [resultsButton addTarget:self action:@selector(showResults) forControlEvents:UIControlEventTouchUpInside];
    self.progressView.numberOfSegments = 4;
    self.progressView.primaryColor = [UIColor colorWithRed:49/255.0f green:192/255.0f blue:190/255.0f alpha:1.0];
    self.progressView.segmentShape = M13ProgressViewSegmentedBarSegmentShapeCircle;
    [self.view addSubview:self.progressView];
    if (self.showProgress)
        [self showProgressUI];
    else
        [self showDefaultUI];
}

- (void)initProgress {
    resultsButton.hidden = YES;
    resultsLabel.text = @"Searching...";
    self.progressView.hidden = NO;
    count = 0;
    [self.progressView setProgress:count animated:NO];
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        [self performSelector:@selector(progressUpdate) withObject:nil afterDelay:0.1];
    });
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)showDefaultUI {
    self.progressView.hidden = YES;
    if ([[ResultsHandler sharedInstance] hasResults]) {
        resultsLabel.text = [NSString stringWithFormat:@"%d Results", [[ResultsHandler sharedInstance] addressCount]];
        resultsButton.hidden = NO;
    }
    else {
        resultsLabel.text = @"No Results";
        resultsButton.hidden = YES;
    }
}

- (void)showProgressUI {
    [self initProgress];
    self.progressView.hidden = NO;
}

- (void)showResults {
    [[ResultsHandler sharedInstance] requestResultsFromStart:0 forCount:100];
    [self showProgressUI];
    resultsLabel.text = @"Loading Results...";
}

- (void)progressUpdate {
    if (self.showProgress) {
        float amount = 0.25;
        float total = count+amount;
        if (count+amount > 1.25) {
            total = 0;
            count = 0;
            [self.progressView setProgress:count animated:NO];
            [self performSelector:@selector(progressUpdate) withObject:nil];
        }
        else {
            [self.progressView setProgress:total animated:YES];
            count += amount;
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.33 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
                [self progressUpdate];
            });
        }
    }
    else {
        count = 0;
        [self.progressView setProgress:count animated:NO];
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.33 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
            [self progressUpdate];
        });
    }
}

@end
