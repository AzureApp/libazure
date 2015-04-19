//
//  SettingsTableViewCell.h
//  Azure
//
//  Created by callum taylor on 16/04/2015.
//  Copyright (c) 2015 iOSCheaters. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AlignSettingsTableViewCell : UITableViewCell

@property (nonatomic, strong) IBOutlet UILabel *settingsLabel;
@property (nonatomic, strong) IBOutlet UISegmentedControl *settingsControl;

@end

@interface MaxResultsSettingsTableViewCell : UITableViewCell

@property (nonatomic, strong) IBOutlet UILabel *settingsLabel;
@property (nonatomic, strong) IBOutlet UITextField *settingsControl;

@end

@interface RegionSettingsTableViewCell : UITableViewCell

@property (nonatomic, strong) IBOutlet UILabel *settingsLabel;
@property (nonatomic, strong) IBOutlet UISegmentedControl *settingsControl;

@end
