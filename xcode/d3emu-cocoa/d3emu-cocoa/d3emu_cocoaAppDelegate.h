#import <Cocoa/Cocoa.h>

@interface Packet : NSObject {
}

- (NSInteger)length;

@end

@interface d3emu_cocoaAppDelegate : NSObject <NSApplicationDelegate,
    NSOutlineViewDelegate, NSOutlineViewDataSource> {
    NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;
@property (nonatomic, retain) IBOutlet NSOutlineView *consoleOutlineView;
@property (nonatomic, retain) IBOutlet NSTableColumn *consoleTypeColumn;
@property (nonatomic, retain) IBOutlet NSTableColumn *consoleLengthColumn;

@property (nonatomic, retain) NSMutableArray *consoleItemsArray;

- (void)logPacket:(Packet *)packet;

@end
