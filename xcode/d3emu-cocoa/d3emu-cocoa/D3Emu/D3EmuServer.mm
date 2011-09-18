#include "Services/Service.h"
#include "Services/BaseService.h"
#include "Services/AuthenticationService.h"
#include "Services/ChannelInvitationService.h"
#include "Services/UserManagerService.h"
#include "Services/GameMasterService.h"
#include "Services/FollowersService.h"
#include "Services/FriendsService.h"
#include "Services/PresenceService.h"
#include "Services/StorageService.h"
#include "Services/ToonExternalService.h"

#import "D3EmuServer.h"
#import "D3EmuPacket.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>

#include <iostream>

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
    _alive = YES;
    
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    struct addrinfo hints;
	struct addrinfo *res;
    
	memset(&hints, 0, sizeof hints);
    
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
    
	getaddrinfo([self.host UTF8String], [self.port UTF8String], &hints, &res);
    
	int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
	if (bind(s, res->ai_addr, res->ai_addrlen)) {
        NSLog(@"Couldn't bind socket.");
	}
    
	listen(s, SOMAXCONN);
    
	freeaddrinfo(res);
    
    d3emu::BoundServicesManager service_manager;
    
	service_manager.Bind(new d3emu::AuthenticationService(0x0DECFC01, 0));
	service_manager.Bind(new d3emu::ChannelInvitationService(0x83040608, 0));
	service_manager.Bind(new d3emu::UserManagerService(0x3E19268A, 0));
	service_manager.Bind(new d3emu::GameMasterService(0x810CB195, 0));
	service_manager.Bind(new d3emu::ToonExternalService(0x4124C31B, 0));
	service_manager.Bind(new d3emu::FollowersService(0xE5A11099, 0));
	service_manager.Bind(new d3emu::FriendsService(0xA3DDB1BD, 0));
	service_manager.Bind(new d3emu::PresenceService(0xFA0796FF, 0));
	service_manager.Bind(new d3emu::StorageService(0xDA6E4BB9, 0));
    
    while (_alive) {
		int client_socket = accept(s, NULL, NULL);
		char buf[1024] = { 0 };
		int len = 0;
        
		while (_alive) {
            ssize_t recvd = recv(client_socket, &buf[len], 1024 - len, 0);
            
			if (recvd > 0) {
				len += recvd;
                
				// std::cout << "Received " << len << " bytes of data. " << std::endl;
                
				// Parse all complete packets
				while (len >= 6 && buf[5] <= (len - 6) && _alive) {
					int packet_len = buf[5] + 6;
                    
					char *packet = new char[packet_len];
					memcpy(packet, buf, packet_len);
					/*
                     std::cout << "--> (Hex)[" << (unsigned int)packet_len << "]:" << std::endl;
                     for (int i = 0; i < packet_len; i++)
                     {
                     // Output hex
                     printf("%02X ", packet[i] & 0xff);
                     }
                     printf("\n");
                     */
                    
					d3emu::Service *service = service_manager.bound_service(packet[0]);
					if (!service) {
						printf("Couldn't find service handler for service id '%02X':\n--> (Hex)[%d]:",
                              ((unsigned int)packet[0] & 0xff), (unsigned int)packet_len);

						for (int i = 0; i < packet_len; i++)
						{
							// Output hex
							printf("%02X ", packet[i] & 0xff);
						}
						printf("\n");
					}
					else {
                        // If our delegate doesn't respond, we'll still want to handle the packet
                        BOOL handle = YES;
                        
                        if ([self.delegate respondsToSelector:@selector(server:didReceivePacket:length:)]) {
                            handle = [self.delegate server:self didReceivePacket:packet length:packet_len];
                        }
                        
                        if (handle) {
                            d3emu::Client client;
                            client.set_socket(client_socket);
                            service->Request(&client, packet, packet_len);
                        }
					}
                    
					delete[] packet;
                    
					char temp[1024];
					len -= packet_len;
					memcpy(temp, &buf[packet_len], len);
					memcpy(buf, temp, len);
				}
			}
			else {
				printf("Client disconnected.");
				break;
			}
		}
        
		close(client_socket);
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