//
//  ProcessCollectionViewController.h
//  Azure
//
//  Created by callum taylor on 06/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Icon.h"
#import "AppHandler.h"
#import "MessageHandler.h"

@interface ProcessCollectionViewController : UICollectionViewController
@property (nonatomic, strong) UINavigationController *passedController;
@property (copy) NSArray *runningApps;
@end
