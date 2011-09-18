#import "d3emu_cocoaAppDelegate.h"
#import "D3EmuServer.h"

@implementation d3emu_cocoaAppDelegate

@synthesize window;
@synthesize consoleOutlineView;
@synthesize consoleTypeColumn;
@synthesize consoleLengthColumn;
@synthesize consoleItemsArray;

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
    
    D3EmuServer *server = [[D3EmuServer alloc] initWithHost:@"127.0.0.1" port:@"6543"];
    [NSThread detachNewThreadSelector:@selector(run) toTarget:server withObject:nil];
    [server release];
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
