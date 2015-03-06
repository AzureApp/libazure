//
//  ProcessCollectionViewFlowLayout.m
//  Azure
//
//  Created by callum taylor on 06/12/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "ProcessCollectionViewFlowLayout.h"

@implementation ProcessCollectionViewFlowLayout

- (id)initWithCoder:(NSCoder *)aDecoder {
    if ((self = [super initWithCoder:aDecoder])) {
        self.itemSize = CGSizeMake(CGRectGetWidth([UIScreen mainScreen].bounds)/4, CGRectGetWidth([UIScreen mainScreen].bounds)/4);
        self.minimumInteritemSpacing = 0;
        self.minimumLineSpacing = 0;
        self.scrollDirection = UICollectionViewScrollDirectionHorizontal;
        self.sectionInset = UIEdgeInsetsMake(0, 0, 32, 32);
    }
    return self;
}

@end
