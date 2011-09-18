#import "D3EmuServer.h"
#import "D3EmuPacket.h"

#include <sys/socket.h>

@implementation D3EmuServer

@synthesize delegate;
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
    
    
    
    while (_alive) {
        [NSThread sleepForTimeInterval:3];
        D3EmuPacket *packet = [[D3EmuPacket alloc] init];
        [self performSelectorOnMainThread:@selector(logPacket:) withObject:packet waitUntilDone:YES];
        [packet release];
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