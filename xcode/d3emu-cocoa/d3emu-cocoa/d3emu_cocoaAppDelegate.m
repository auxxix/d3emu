#import "D3EmuServer.h"

#import "d3emu_cocoaAppDelegate.h"

@implementation d3emu_cocoaAppDelegate

@synthesize window;
@synthesize consoleOutlineView;
@synthesize consoleTypeColumn;
@synthesize consoleLengthColumn;
@synthesize consoleItemsArray;
@synthesize server;
@synthesize serverThread;

#pragma mark - D3EmuServerDelegate

- (BOOL)server:(D3EmuServer *)server didReceivePacket:(const char *)packet length:(int)length
{
    D3EmuPacket *thePacket = [[D3EmuPacket alloc] init];
    // Note that we receive this in the server's thread
    [self performSelector:@selector(logPacket:) onThread:[NSThread mainThread]
               withObject:thePacket waitUntilDone:YES];
    [thePacket release];
    
    return YES;
}


- (void)logPacket:(D3EmuPacket *)packet
{
    [self.consoleItemsArray addObject:packet];
    
    [self.consoleOutlineView beginUpdates];
    NSIndexSet *indexSet = [[NSIndexSet alloc] initWithIndex:[self.consoleItemsArray count] - 1];
    [self.consoleOutlineView insertItemsAtIndexes:indexSet
                                         inParent:nil withAnimation:NSTableViewAnimationSlideDown];
    [indexSet release];
    [self.consoleOutlineView endUpdates];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    NSMutableArray *array = [[NSMutableArray alloc] init];
    self.consoleItemsArray = array;
    [array release];
    
    D3EmuServer *theServer = [[D3EmuServer alloc] initWithHost:@"127.0.0.1" port:@"6543"];
    self.server = theServer;
    self.server.delegate = self;
    [NSThread detachNewThreadSelector:@selector(run) toTarget:self.server withObject:nil];
    [theServer release];
}

#pragma mark - NSOutlineViewDelegate

#pragma mark - NSOutlineViewDataSource

- (NSInteger)outlineView:(NSOutlineView *)outlineView numberOfChildrenOfItem:(id)item
{
    NSInteger children = 0;
    
    if (!item) {
        children = [self.consoleItemsArray count];
    }
    else {
        children = 1;
    }
    
    return children;
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item
{
    return YES;
}

- (id)outlineView:(NSOutlineView *)outlineView child:(NSInteger)index ofItem:(id)item
{
    id child = nil;
    if (!item) {
        child = [self.consoleItemsArray objectAtIndex:index];
    }
    return child;
}

- (id)outlineView:(NSOutlineView *)outlineView objectValueForTableColumn:(NSTableColumn *)tableColumn byItem:(id)item
{
    id columnItem = nil;
    
    if (tableColumn == self.consoleTypeColumn) {
        columnItem = [item className];
    }
    else if (tableColumn == self.consoleLengthColumn) {
        columnItem = [NSString stringWithFormat:@"%d", [item length]];
    }
    
    return columnItem;
}

@end
