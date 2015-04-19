//
//  SettingsViewController.m
//  Azure
//
//  Created by callum taylor on 29/11/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "SettingsViewController.h"
#import "AzureSettings.h"
#import <mach/mach.h>

@interface SettingsViewController ()

@end

@implementation SettingsViewController


- (IBAction)unwindSettings:(id)sender {
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end
