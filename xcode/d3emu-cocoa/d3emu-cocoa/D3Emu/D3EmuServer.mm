#include <Services/Service.h>
#include <Services/BaseService.h>
#include <Services/AuthenticationService.h>
#include <Services/ChannelInvitationService.h>
#include <Services/UserManagerService.h>
#include <Services/GameMasterService.h>
#include <Services/FollowersService.h>
#include <Services/FriendsService.h>
#include <Services/PresenceService.h>
#include <Services/StorageService.h>
#include <Services/ToonExternalService.h>

#import "D3EmuServer.h"
#import "D3EmuPacket.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

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
    
    struct sockaddr hints;
    struct sockaddr *res;
    
    
    
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