//
//  AboutViewController.m
//  Azure
//
//  Created by callum taylor on 18/04/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import "AboutViewController.h"

@implementation AboutViewController
- (void)viewDidLayoutSubviews {
    [self.aboutView setContentOffset:CGPointZero animated:NO];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    switch (indexPath.row) {
        case 0: {
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://razzland.com"]];
            break;
        }
        case 1: {
            if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"tweetbot:"]]) {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[@"tweetbot:///user_profile/" stringByAppendingString:@"Razzilient"]]];
                
            } else if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"twitterrific:"]]) {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[@"twitterrific://user?screen_name=" stringByAppendingString:@"Razzilient"]]];
                
            } else if ([[UIApplication sharedApplication] canOpenURL:[NSURL URLWithString:@"twitter:"]]) {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[@"twitter://user?screen_name=" stringByAppendingString:@"Razzilient"]]];
            } else {
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[@"https://mobile.twitter.com/" stringByAppendingString:@"Razzilient"]]];
            }
            break;
        }
        case 2: {
            [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://ioscheaters.com"]];
            break;
        }
    }
}
@end
