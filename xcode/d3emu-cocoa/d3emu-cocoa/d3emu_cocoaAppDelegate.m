#import "d3emu_cocoaAppDelegate.h"

@implementation Packet

- (NSString *)description
{
    return [NSString stringWithFormat:@"%@ Length=0", [self className]];
}

- (NSInteger)length
{
    return 0;
}

@end

@implementation d3emu_cocoaAppDelegate

@synthesize window;
@synthesize consoleOutlineView;
@synthesize consoleTypeColumn;
@synthesize consoleLengthColumn;
@synthesize consoleItemsArray;

- (void)logPacket:(Packet *)packet
{
    [self.consoleItemsArray addObject:packet];
    
    [self.consoleOutlineView beginUpdates];
    NSIndexSet *indexSet = [[NSIndexSet alloc] initWithIndex:[self.consoleItemsArray count] - 1];
    [self.consoleOutlineView insertItemsAtIndexes:indexSet
                                         inParent:nil withAnimation:NSTableViewAnimationSlideDown];
    [indexSet release];
    [self.consoleOutlineView endUpdates];
}

- (void)server:(id)object
{
    //D3EmuServer *server = [[D3EmuServer alloc] init];
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSLog(@"Running server.");
    
    for (;;) {
        [NSThread sleepForTimeInterval:3];
        Packet *packet = [[Packet alloc] init];
        [self performSelectorOnMainThread:@selector(logPacket:) withObject:packet waitUntilDone:YES];
        [packet release];
    }
    [pool release];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    NSMutableArray *array = [[NSMutableArray alloc] init];
    self.consoleItemsArray = array;
    [array release];
    
    [NSThread detachNewThreadSelector:@selector(server:) toTarget:self withObject:nil];
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
