#import "D3EmuServer.h"

@implementation D3EmuServer

@synthesize host;
@synthesize port;

- (void)setHost:(NSString *)theHost
{
    if (!_socket) {
        [theHost retain];
        [host release];
        host = theHost;
    }
}

- (void)setPort:(NSString *)thePort
{
    if (!_socket) {
        [thePort retain];
        [port release];
        port = thePort;
    }
}

- (id)initWithHost:(NSString *)theHost port:(NSString *)thePort
{
    self = [super init];
    if (self) {
        host = [theHost retain];
        port = [thePort retain];
    }
    return self;
}

- (void)run
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    NSLog(@"Running server.");
    while (_alive) {
        
    }
    [pool release];
}

- (void)stop
{
    _alive = NO;
}

- (void)dealloc
{
    self.host = nil;
    self.port = nil;
    
    [super dealloc];
}

@end