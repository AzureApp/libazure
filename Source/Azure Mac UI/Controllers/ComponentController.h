//
//  ComponentController.h
//  Azure Mac UI
//
//  Created by callum taylor on 05/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SettingsWindowController.h"


@interface ComponentController : NSObject <NSTextFieldDelegate> {
    IBOutlet NSSegmentedControl *searchControl;
    IBOutlet NSSearchField *searchField;
    IBOutlet NSButton *searchSettings;
    IBOutlet NSTextField *currentProcessName;
    IBOutlet NSTextField *resultCount;
    IBOutlet NSMatrix *settingsMatrix;
    IBOutlet NSTextField *settingsResultField;
    IBOutlet NSTextField *settingsStartField;
    IBOutlet NSTextField *settingsEndField;
}

@property (nonatomic, retain) IBOutlet NSSegmentedControl *searchControl;
@property (nonatomic, retain) IBOutlet NSSearchField *searchField;
@property (nonatomic, retain) IBOutlet NSButton *searchSettings;
@property (nonatomic, retain) IBOutlet NSTextField *currentProcessName;
@property (nonatomic, retain) IBOutlet NSTextField *resultCount;
@property (nonatomic, retain) IBOutlet NSMatrix *settingsMatrix;
@property (nonatomic, retain) IBOutlet NSTextField *settingsResultField;
@property (nonatomic, retain) IBOutlet NSTextField *settingsStartField;
@property (nonatomic, retain) IBOutlet NSTextField *settingsEndField;
@property (assign) IBOutlet NSPopover *settingsView;

- (IBAction)search:(id)sender;
- (IBAction)changeFilter:(id)sender;
- (IBAction)showSettings:(id)sender;
- (IBAction)editSettings:(id)sender;
- (IBAction)showLog:(id)sender;
- (IBAction)clear:(id)sender;
@end
