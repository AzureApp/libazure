//
//  SearchTableViewController.m
//  Azure
//
//  Created by callum taylor on 03/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "SearchTableViewController.h"

@interface SearchTableViewController ()

@end

@implementation SearchTableViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.tableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

- (CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return 44;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [[ResultsHandler sharedInstance] addressCount];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    SearchTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ID" forIndexPath:indexPath];
    if (cell == nil) {
        cell = [[SearchTableViewCell alloc] init];
    }
    return cell;
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(SearchTableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    if (handler.hasResults) {
        int addr = [[[handler savedAddresses] objectAtIndex:indexPath.row] intValue];
        
        cell.addressLabel.text = [NSString stringWithFormat:@"0x%X", addr];
        cell.valueField.text = [[handler currentSearchObject] toString];
    }
}

-(IBAction)toggleLock:(UIButton*)sender {
    sender.selected = !sender.selected;
    CGPoint buttonPosition = [sender convertPoint:CGPointZero toView:self.tableView];
    NSIndexPath *indexPath = [self.tableView indexPathForRowAtPoint:buttonPosition];
    
    NSLog(@"lock button pressed for row %d", indexPath.row);
}

@end
