#include "D3EmuPacket.h"
#include "D3EmuServer.h"

#import <Cocoa/Cocoa.h>

@interface d3emu_cocoaAppDelegate : NSObject <NSApplicationDelegate,
    NSOutlineViewDelegate, NSOutlineViewDataSource, D3EmuServerDelegate> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;
@property (nonatomic, retain) IBOutlet NSOutlineView *consoleOutlineView;
@property (nonatomic, retain) IBOutlet NSTableColumn *consoleTypeColumn;
@property (nonatomic, retain) IBOutlet NSTableColumn *consoleLengthColumn;

@property (nonatomic, retain) NSMutableArray *consoleItemsArray;

@property (nonatomic, retain) D3EmuServer *server;
@property (nonatomic, retain) NSThread *serverThread;

- (void)logPacket:(D3EmuPacket *)packet;

@end
