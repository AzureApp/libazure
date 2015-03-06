//
//  SearchTableViewCell.h
//  Azure
//
//  Created by callum taylor on 28/11/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SearchTableViewCell : UITableViewCell

@property (nonatomic) IBOutlet UIButton *lockedButton;
@property (nonatomic) IBOutlet UILabel *addressLabel;
@property (nonatomic) IBOutlet UITextField *valueField;

+ (id)initWithAddress:(NSInteger)address andValue:(NSInteger)value; // to do: all data types (string, hext etc), locking

@end
