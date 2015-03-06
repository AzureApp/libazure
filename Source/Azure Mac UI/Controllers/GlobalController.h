//
//  GlobalController.h
//  Azure Mac UI
//
//  Created by callum taylor on 02/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Process.h"
#import "ComponentController.h"
#import "Result.h"
#import "Daemon.h"

@interface GlobalController : NSObject {
    IBOutlet ComponentController *componentController;
    IBOutlet NSPanel *settingsPanel;
@public
    enum ResultType searchType;
}

@property (nonatomic, retain) NSPanel *settingsPanel;
@property BOOL searchComponentsEnabled;
@property enum ResultType searchType;

- (void)enableSearchComponents;
- (void)disableSearchComponents;


@end
