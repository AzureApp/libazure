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
    return [[ResultsHandler sharedInstance].searchObjects count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    SearchTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ID" forIndexPath:indexPath];
    if (cell == nil) {
        cell = [[SearchTableViewCell alloc] init];
    }
    if (handler.hasResults && indexPath.row < handler.addressCount) {
        SearchObject *obj = [handler searchObjectAtIndex:indexPath.row];
        
        cell.addressLabel.text = [NSString stringWithFormat:@"0x%lX", obj.address];
        cell.valueField.text = [obj toString];
    }
    return cell;
}

- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    if (indexPath.row == [handler.searchObjects count] - 1 && indexPath.row < handler.addressCount - 1)
    {
        int count = (handler.addressCount - indexPath.row < 100) ? handler.addressCount - indexPath.row : 100;
        [handler requestResultsFromStart:indexPath.row + 1 forCount:count];
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
    CGPoint buttonPosition = [textField convertPoint:CGPointZero toView:self.tableView];
    NSIndexPath *indexPath = [self.tableView indexPathForRowAtPoint:buttonPosition];
    
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    SearchObject *obj = [handler searchObjectAtIndex:indexPath.row];
    NSLog(@"address = %x", obj.address);
    [obj modifyData:textField.text];
    Message msg = [MessageHandler writeMessageForSearchObject:obj];
    [[MessageHandler sharedInstance] sendMessage:msg];
    return NO;
}

-(IBAction)toggleLock:(UIButton *)sender {
    sender.selected = !sender.selected;
    CGPoint buttonPosition = [sender convertPoint:CGPointZero toView:self.tableView];
    NSIndexPath *indexPath = [self.tableView indexPathForRowAtPoint:buttonPosition];
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    SearchObject *obj = [handler searchObjectAtIndex:indexPath.row];
    Message msg = [MessageHandler lockMessageForSearchObject:obj];
    [[MessageHandler sharedInstance] sendMessage:msg];
    NSLog(@"lock button pressed for row %d", indexPath.row);
}

@end
