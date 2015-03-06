//
//  SettingsViewController.m
//  Azure
//
//  Created by callum taylor on 29/11/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "SettingsViewController.h"

@interface SettingsViewController ()

@end

@implementation SettingsViewController
@synthesize myBar;
- (void)viewDidLoad {
    [super viewDidLoad];
    self.modalPresentationStyle = UIModalPresentationFormSheet;
    }

-(void)dismiss {
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillLayoutSubviews {
    //[super viewWillAppear:animated];
    myBar = [[UINavigationBar alloc] initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 40)];
    UINavigationItem *navItem = [[UINavigationItem alloc] initWithTitle:@"Settings"];
    [myBar setTitleTextAttributes:@{NSForegroundColorAttributeName:[UIColor whiteColor]}];
    
    UIBarButtonItem *myButton = [[UIBarButtonItem alloc] initWithTitle:@"Done" style:UIBarButtonItemStyleDone target:self action:@selector(dismiss)];
    
    myButton.tintColor = [UIColor whiteColor];
    [navItem setLeftBarButtonItem:myButton];
    
    [myBar setTranslucent:YES];
    self.edgesForExtendedLayout = UIRectEdgeNone;
    [myBar pushNavigationItem:navItem animated:NO];
    [self.view addSubview:myBar];

}

- (BOOL) prefersStatusBarHidden {
    return YES;
}


//- (void)view
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
