#import <Cocoa/Cocoa.h>

#include "D3EmuPacket.h"

@interface d3emu_cocoaAppDelegate : NSObject <NSApplicationDelegate,
    NSOutlineViewDelegate, NSOutlineViewDataSource> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;
@property (nonatomic, retain) IBOutlet NSOutlineView *consoleOutlineView;
@property (nonatomic, retain) IBOutlet NSTableColumn *consoleTypeColumn;
@property (nonatomic, retain) IBOutlet NSTableColumn *consoleLengthColumn;

@property (nonatomic, retain) NSMutableArray *consoleItemsArray;

- (void)logPacket:(D3EmuPacket *)packet;

@end
