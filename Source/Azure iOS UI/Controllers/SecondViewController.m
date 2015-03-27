//
//  SecondViewController.m
//  Azure iOS
//
//  Created by callum taylor on 21/11/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "SecondViewController.h"

@interface SecondViewController ()

@end

@implementation SecondViewController

@synthesize processNavigationBar;
- (void)viewDidLoad {
    [super viewDidLoad];
    UIBarButtonItem *refreshButton = [[UIBarButtonItem alloc]
                                      initWithBarButtonSystemItem:UIBarButtonSystemItemRefresh
                                      target:self
                                      action:@selector(refresh:)];
    refreshButton.tintColor = [UIColor whiteColor];
    
    UIBarButtonItem *listButton = [[UIBarButtonItem alloc] initWithImage:[UIImage imageNamed:@"list"] style:UIBarButtonItemStylePlain target:self action:nil];
                                   
    listButton.tintColor = [UIColor whiteColor];
    
    UINavigationItem *item = [[UINavigationItem alloc] initWithTitle:@"Processes"];
    item.rightBarButtonItems = @[refreshButton/*, listButton*/];
    [processNavigationBar pushNavigationItem:item animated:NO];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)refresh:(id)sender {
    [[NSNotificationCenter defaultCenter]
     postNotificationName:@"RefreshProcesses"
     object:self];
}

@end
