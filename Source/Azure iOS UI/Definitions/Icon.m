//
//  Icon.m
//  Azure
//
//  Created by callum taylor on 06/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "Icon.h"

@implementation Icon

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        UIView *insetView = [[UIView alloc] initWithFrame:CGRectInset(self.bounds, self.bounds.size.width/8, self.bounds.size.height/8)];
        [self.contentView addSubview:insetView];
        
        self.layer.rasterizationScale = [[UIScreen mainScreen] scale];
        self.layer.shouldRasterize = YES;
        
        self.iconView = ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) ?
                           [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 92, 92)] :
                           [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 48, 48)];
        self.iconView.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleHeight;
        self.iconView.center = CGPointMake(CGRectGetMidX(insetView.bounds), CGRectGetMidY(insetView.bounds));
        
        float dim = MIN(self.iconView.bounds.size.width, self.iconView.bounds.size.height);
        float offset = ([UIDevice currentDevice].userInterfaceIdiom == UIUserInterfaceIdiomPad) ? 70 : 40;
        self.label = [[UILabel alloc] initWithFrame:CGRectMake(0, 100, 80, 40)];
        self.label.center = CGPointMake(CGRectGetMidX(self.iconView.frame), CGRectGetMidY(self.iconView.frame)+offset);
        self.label.textAlignment = NSTextAlignmentCenter;
        self.label.numberOfLines = 3;
        self.label.lineBreakMode = NSLineBreakByWordWrapping;
        self.label.clipsToBounds = YES;
        self.label.font = [UIFont fontWithName:@"Titillium" size:dim/6];
        
        [insetView addSubview:self.iconView];
        [insetView addSubview:self.label];
        // INSERT ICON DELETE BUTTON SNIPPET HERE
        
    }
    return self;
}

@end
