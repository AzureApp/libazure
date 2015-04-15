//
//  ProcessCollectionViewController.m
//  Azure
//
//  Created by callum taylor on 06/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "ProcessCollectionViewController.h"
#import "SearchViewController.h"
@interface ProcessCollectionViewController ()
- (void)refresh;
@end

@implementation ProcessCollectionViewController

@synthesize runningApps;

static NSString * const reuseIdentifier = @"Cell";

- (void)viewDidLoad {
    [super viewDidLoad];
    
    // Uncomment the following line to preserve selection between presentations
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Register cell classes
    [self.collectionView registerClass:[Icon class] forCellWithReuseIdentifier:reuseIdentifier];
    runningApps = [[AppHandler sharedInstance] allRunningApps];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(refresh)
                                                 name:@"RefreshProcesses"
                                               object:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)refresh {
    runningApps = [[AppHandler sharedInstance] allRunningApps];
    [self.collectionView reloadData];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

#pragma mark <UICollectionViewDataSource>

- (NSInteger)numberOfSectionsInCollectionView:(UICollectionView *)collectionView {
    return 1;
}


- (NSInteger)collectionView:(UICollectionView *)collectionView numberOfItemsInSection:(NSInteger)section {
    return [runningApps count];
}

- (UICollectionViewCell *)collectionView:(UICollectionView *)collectionView cellForItemAtIndexPath:(NSIndexPath *)indexPath {
  
    Icon *cell = [collectionView dequeueReusableCellWithReuseIdentifier:@"Cell" forIndexPath:indexPath];
    App *app = [runningApps objectAtIndex:indexPath.row];
    
    cell.label.text = app.name;
    cell.iconView.image = [AppHandler appIconForBundleID:app.bundleID];

    return cell;
}

- (void)collectionView:(UICollectionView *)collectionView didSelectItemAtIndexPath:(NSIndexPath *)indexPath
{
    [AppHandler sharedInstance].currentApp = [runningApps objectAtIndex:indexPath.row];
    [self.tabBarController setSelectedIndex:1];
    Message msg = [MessageHandler attachMessageForApp:[runningApps objectAtIndex:indexPath.row]];
    [[MessageHandler sharedInstance] sendMessage:msg];
}

@end
