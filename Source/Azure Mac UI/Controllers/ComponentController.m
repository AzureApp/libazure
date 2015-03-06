//
//  ComponentController.m
//  Azure Mac UI
//
//  Created by callum taylor on 05/07/2014.
//  Copyright (c) 2014 iOSCheaters. All rights reserved.
//

#import "ComponentController.h"
#import "Globals.h"

@implementation ComponentController

@synthesize searchControl, searchField, searchSettings, currentProcessName, resultCount, settingsView;
@synthesize settingsMatrix, settingsResultField, settingsStartField, settingsEndField;


- (void)awakeFromNib {
    Preferences *prefs = [[Globals sharedInstance] userPreferences];
    settingsResultField.stringValue = [NSString stringWithFormat:@"%ld",prefs.numberOfResults];
    settingsStartField.stringValue = [NSString stringWithFormat:@"0x%lX",prefs.startAddress];
    settingsEndField.stringValue = [NSString stringWithFormat:@"0x%lX",prefs.endAddress];
}


- (IBAction)showSettings:(id)sender {
    static bool pressed = false;
    if(!pressed)
    {
        [[self settingsView] showRelativeToRect:[sender bounds] ofView:sender preferredEdge:NSMaxYEdge];
        pressed = true;
    }
    else
    {
        [[self settingsView] close];
        pressed = false;
    }
}

- (IBAction)showLog:(id)sender {
    NSWindowController * wc=[[NSWindowController alloc] initWithWindowNibName:@"Log"];
    [[wc window] makeKeyAndOrderFront:self];
    [wc showWindow:self];
}

- (IBAction)changeFilter:(id)sender {
    GlobalController *controller = [[Globals sharedInstance] controller];
    NSInteger value = [searchControl selectedSegment];
    switch (value) {
        case 0:
        {
            controller.searchType = e_Integer;
            break;
        }
        case 1:
        {
            controller.searchType = e_Float;
            break;
        }
        case 2:
        {
            controller.searchType = e_String;
            break;
        }
        case 3:
        {
            controller.searchType = e_Hex;
            break;
        }
        default:
        {
            @throw @"An error has occured";
            break;
        }
    }
    [searchField setStringValue:@""];
    ResultsTableController *results = [[Globals sharedInstance] resultsController];
    [results refreshResults];
    
}

- (void)controlTextDidChange:(NSNotification *)obj {
    bool identUsed = false; // used to tell if a . in float and x in hex is used
    
    NSTextField *textfield = [obj object];
    GlobalController *controller = [[Globals sharedInstance] controller];
    NSCharacterSet *charSet;
    
    if ([[textfield identifier] isEqualToString:@"searchField"])
    {
        switch (controller->searchType)
        {
            case e_Integer:
            {
                charSet = [NSCharacterSet characterSetWithCharactersInString:@"0123456789-"];
                break;
            }
            case e_Float:
            {
                charSet = [NSCharacterSet characterSetWithCharactersInString:@"0123456789.-"];
                break;
            }
            case e_Hex:
            {
                charSet = [NSCharacterSet characterSetWithCharactersInString:@"0123456789aAbBcCdDeEfFxX"];
                break;
            }
            default:
            {
                return;
            }
        }
    }
    else if ([[textfield identifier] rangeOfString:@"Address"].location != NSNotFound)
    {
        charSet = [NSCharacterSet characterSetWithCharactersInString:@"0123456789aAbBcCdDeEfFxX"];
    }
    else
    {
        return;
    }
    char *stringResult = malloc([textfield.stringValue length]);
    
    int cpt = 0;
    for (int i = 0; i < [textfield.stringValue length]; i++)
    {
        unichar c = [textfield.stringValue characterAtIndex:i];
        
        if ([charSet characterIsMember:c])
        {
            if (!(identUsed && (c == '.' || c == 'x' || c == 'X')))
            {
                stringResult[cpt] = c;
                if (c == '.' || c == 'x' || c == 'X') identUsed = true;
            }
            cpt++;
        }
    }
    stringResult[cpt] = '\0';
    textfield.stringValue = [NSString stringWithUTF8String:stringResult];
    free(stringResult);
}

- (IBAction)editSettings:(id)sender {
    Preferences *preferences = [[Globals sharedInstance] userPreferences];
    if ([sender isKindOfClass:[NSMatrix class]])
    {
        NSMatrix *matrix = sender;
        NSButtonCell *cell = [matrix selectedCell];
        if ([[cell title] isEqualToString:@"UI Processes"])
        {
            preferences.allProcesses = NO;
        }
        if ([[cell title] isEqualToString:@"All Processes"])
        {
            preferences.allProcesses = YES;

        }
    }
    else if ([sender isKindOfClass:[NSTextField class]])
    {
        NSTextField *field = sender;
        if ([[field identifier] isEqualToString:@"numberOfResults"])
        {
            unsigned val;
            NSScanner *scanner = [NSScanner scannerWithString:[field stringValue]];
            [scanner scanHexInt:&val];
            preferences.numberOfResults = val;
        }
        if ([[field identifier] isEqualToString:@"startAddress"])
        {
            unsigned val;
            NSScanner *scanner = [NSScanner scannerWithString:[field stringValue]];
            [scanner scanHexInt:&val];
            preferences.startAddress = val;
        }
        if ([[field identifier] isEqualToString:@"endAddress"])
        {
            unsigned val;
            NSScanner *scanner = [NSScanner scannerWithString:[field stringValue]];
            [scanner scanHexInt:&val];
            preferences.endAddress = val;
        }
    }
    [preferences synchronize];
    [[Globals sharedInstance] refreshContents];
}

- (IBAction)search:(id)sender {
    Daemon *daemon = [[Globals sharedInstance] daemon];
    GlobalController *controller = [[Globals sharedInstance] controller];
   
    void *data = NULL;
    long size = 0;
    
    switch (controller.searchType)
    {
        case e_Integer:
        {
            long val = [searchField integerValue];
            size = sizeof(long);
            data = malloc(size);
            memcpy(data, &val, size);
            break;
        }
            
        case e_Float:
        {
            float val = [searchField floatValue];
            size = sizeof(float);
            data = malloc(size);
            memcpy(data, &val, size);
            break;
        }
        case e_Hex:
        {
            return;
        }
        case e_String:
        {
            const char *val = [[searchField stringValue] UTF8String];
            data = malloc(strlen(val));
            memcpy(data, val, strlen(val));
            size = strlen(val);
            break;
        }
    }
    ResultsHandler *handler = [ResultsHandler sharedInstance];
    handler.value = data;
    handler.valueSize = size;
    
    enum MessageType type = NewSearch;
    if (handler.hasResults) type = IterateSearch;
    struct msg_header header;
    header.messageSize = size;
    header.type = type;
    header.shouldPop = true;
    
    struct Message msg;
    msg.header = header;
    msg.message = data;
    [daemon sendMessage:msg];
}

- (IBAction)clear:(id)sender {
    
}
@end