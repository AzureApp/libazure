//
//  SearchView.m
//  Azure
//
//  Created by callum taylor on 21/11/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "SearchView.h"

@implementation SearchView


- (id)initWithFrame:(CGRect)frameRect {
    NSArray *array = [[NSBundle mainBundle] loadNibNamed:@"SearchView" owner:self options:nil];
    NSLog(@"%@", array);
    SearchView *v = [array firstObject];
    v.bounds = frameRect;
//    v.center = CGPointMake(frameRect.size.width/2, frameRect.size.height/2);
//    UISegmentedControl *control = [[UISegmentedControl alloc] initWithItems:@[@"yolo", @"swag"]];
//    control.frame = frameRect;
//    [control setTranslatesAutoresizingMaskIntoConstraints:NO];
//    
//    [v addSubview:control];
//    [v addConstraint:[NSLayoutConstraint constraintWithItem:control
//                                                          attribute:NSLayoutAttributeWidth
//                                                          relatedBy:NSLayoutRelationEqual
//                                                             toItem:v
//                                                          attribute:NSLayoutAttributeWidth
//                                                         multiplier:0.8
//                                                           constant:0]];
//
//    [v addConstraint:[NSLayoutConstraint constraintWithItem:control
//                                                          attribute:NSLayoutAttributeCenterX
//                                                          relatedBy:NSLayoutRelationEqual
//                                                             toItem:v
//                                                          attribute:NSLayoutAttributeCenterX
//                                                         multiplier:1.0
//                                                           constant:0.0]];
//    [v addConstraint:[NSLayoutConstraint constraintWithItem:control
//                                                          attribute:NSLayoutAttributeCenterY
//                                                          relatedBy:NSLayoutRelationEqual
//                                                             toItem:v
//                                                          attribute:NSLayoutAttributeCenterY
//                                                         multiplier:0.2
//                                                           constant:0.0]];
    return v;
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
