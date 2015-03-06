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

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source



- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return 50;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    SearchTableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ID" forIndexPath:indexPath];
    if (cell == nil) {
        cell = [[SearchTableViewCell alloc] init];
    }
    return cell;
}

-(IBAction)toggleLock:(UIButton*)sender
{
    sender.selected = !sender.selected;
    CGPoint buttonPosition = [sender convertPoint:CGPointZero toView:self.tableView];
    NSIndexPath *indexPath = [self.tableView indexPathForRowAtPoint:buttonPosition];
    
    NSLog(@"lock button pressed for row %d", indexPath.row);
}
    
- (void)tableView:(UITableView *)tableView willDisplayCell:(SearchTableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath {
//    CALayer *buttonLeftBorder = [CALayer layer];
//    CALayer *buttonRightBorder = [CALayer layer];
//    CALayer *addressBorder = [CALayer layer];
//    CALayer *valueBorder = [CALayer layer];
//    
//    buttonLeftBorder.backgroundColor = [[UIColor colorWithRed:49/255.0f green:192/255.0f blue:190/255.0f alpha:1.0] CGColor];
//    buttonRightBorder.backgroundColor = [[UIColor colorWithRed:49/255.0f green:192/255.0f blue:190/255.0f alpha:1.0] CGColor];
//    
//    
//    addressBorder.backgroundColor = [[UIColor colorWithRed:49/255.0f green:192/255.0f blue:190/255.0f alpha:1.0] CGColor];
//    valueBorder.backgroundColor = [[UIColor colorWithRed:49/255.0f green:192/255.0f blue:190/255.0f alpha:1.0] CGColor];
//    
//    //    buttonLeftBorder.frame = CGRectMake(-5, CGRectGetMinY(cell.lockedButton.frame)-4, 2.0f, CGRectGetHeight(cell.lockedButton.frame)+2);
//    //    [cell.lockedButton.layer addSublayer:buttonLeftBorder];
//    
//    buttonRightBorder.frame = CGRectMake(38, 0, 0.5f, CGRectGetHeight(cell.frame)+1);
//    [cell.lockedButton.layer addSublayer:buttonRightBorder];
//    
//    valueBorder.frame = CGRectMake(-5, CGRectGetMinY(cell.valueField.frame), 2.0f, CGRectGetHeight(cell.valueField.frame)+10);
//    [cell.valueField.layer addSublayer:valueBorder];
    
    
    cell.addressLabel.text = [NSString stringWithFormat:@"0x%X", indexPath.row * 10000000];
    cell.valueField.text = [NSString stringWithFormat:@"%ld", random()];
}
/*
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:<#@"reuseIdentifier"#> forIndexPath:indexPath];
    
    // Configure the cell...
    
    return cell;
}
*/

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:@[indexPath] withRowAnimation:UITableViewRowAnimationFade];
    } else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
