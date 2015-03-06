//
//  SearchTableViewCell.m
//  Azure
//
//  Created by callum taylor on 28/11/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "SearchTableViewCell.h"

@implementation SearchTableViewCell
@synthesize lockedButton, addressLabel, valueField;
- (void)awakeFromNib {
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (UIEdgeInsets)layoutMargins
{
    return UIEdgeInsetsZero;
}

@end
