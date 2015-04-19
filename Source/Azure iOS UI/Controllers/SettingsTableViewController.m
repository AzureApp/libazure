//
//  SettingsTableViewController.m
//  Azure
//
//  Created by callum taylor on 18/04/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import "SettingsTableViewController.h"
#import "AzureSettings.h"
#import "MessageHandler.h"
#import <mach/mach.h>

int protection[3] = { VM_PROT_READ, VM_PROT_READ | VM_PROT_WRITE, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXECUTE };

@implementation SettingsTableViewController

- (IBAction)changeSettings:(id)sender {
    AzureSettings *settings = [AzureSettings userSettings];
    if ([sender isKindOfClass:[UISegmentedControl class]]) {
        UISegmentedControl *control = sender;
        if (control.tag == 0) { // alignment
            NSString *str = [control titleForSegmentAtIndex:control.selectedSegmentIndex];
            NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
            f.numberStyle = NSNumberFormatterDecimalStyle;
            NSNumber *myNumber = [f numberFromString:str];
            [settings setValue:myNumber forKey:@"kAlignment"];
        }
        if (control.tag == 2) {
            int index = (int)control.selectedSegmentIndex;
            [settings setValue:[NSNumber numberWithInt:protection[index]] forKey:@"kRegions"];
        }
    }
    else if ([sender isKindOfClass:[UITextField class]]) {
        UITextField *control = sender;
        if (control.tag == 1) {
            UITextField *control = sender;
            NSString *str = control.text;
            NSNumberFormatter *f = [[NSNumberFormatter alloc] init];
            f.numberStyle = NSNumberFormatterDecimalStyle;
            NSNumber *myNumber = [f numberFromString:str];
            [settings setValue:myNumber forKey:@"kMaxResults"];
        }
    }
    Message msg;
    msg.header = header_default;
    msg.header.type = Prefs;
    [[MessageHandler sharedInstance] sendMessage:msg];
}


@end
