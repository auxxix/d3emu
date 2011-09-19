#ifdef _WIN32
    #include <ws2tcpip.h>
    #include <WinSock2.h>
    #include <BaseTsd.h> // SSIZE_T

    typedef SSIZE_T ssize_t;

    #define close(s) closesocket(s)

#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netdb.h>
#endif

#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <iomanip>

#include <time.h>
#include <stdint.h>

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

#include "Net/Packet.h"

int StartServer(const char *ip, const char *port);
void StopServer(int s);

int main(int argc, char **argv)
{
	srand((unsigned int)time(0));

#ifdef _WIN32
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2,0), &WSAData);
#endif
    
	int s = StartServer("127.0.0.1", "6543");
	if (s <= 0)
	{
		std::cout << "Invalid socket." << std::endl;
		exit(0);
	}
    else
    {
        std::cout << "Server listening on 127.0.0.1:6543" << std::endl;
    }

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

	while (true)
	{
		int client_socket = accept(s, NULL, NULL);
		char buf[1024] = { 0 };
		int len = 0;

		while (true)
		{
            ssize_t recvd = recv(client_socket, &buf[len], 1024 - len, 0);

			if (recvd > 0)
			{
				len += recvd;

				// std::cout << "Received " << len << " bytes of data. " << std::endl;

				// Parse all complete packets
				while (len >= 6 && buf[5] <= (len - 6))
				{
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
					if (!service)
					{
						std::cout << "Couldn't find service handler for service id '" 
							<< std::hex << ((unsigned int)packet[0] & 0xff) << "'" << std::endl;
						std::cout << "--> (Hex)[" << (unsigned int)packet_len << "]:" << std::endl;
						for (int i = 0; i < packet_len; i++)
						{
							// Output hex
							printf("%02X ", packet[i] & 0xff);
						}
						printf("\n");
					}
					else
					{
                        /*
                        std::cout << "--> (Hex)[" << (unsigned int)packet_len << "]:" << std::endl;
						for (int i = 0; i < packet_len; i++)
						{
							// Output hex
							printf("%02X ", packet[i] & 0xff);
						}
						printf("\n");
                        */
						d3emu::Client client;
						client.set_socket(client_socket);
                        
                        d3emu::PacketRequest request_packet(packet, packet_len);
                        d3emu::PacketResponse *response_packet = service->Request(client, request_packet);
                        
                        if (response_packet)
                        {
                            std::cout << response_packet->message()->GetTypeName() << std::endl
                                << response_packet->message()->DebugString() << std::endl;
                            
                            std::string built_response = response_packet->SerializeAsString();
                            for (int i = 0; i < built_response.length(); i++)
                            {
                                // Output hex
                                printf("%02X ", built_response[i] & 0xff);
                            }
                            printf("\n");
                            
                            send(client_socket, built_response.c_str(), built_response.length(), 0);
                        }
                        else
                        {
                            std::cout << "No handler found for service_id: " <<
                                (uint32_t)request_packet.header().service_id() 
                                << " method_id: " << (uint32_t)request_packet.header().method_id() << std::endl;
                        }
					}

					delete[] packet;

					char temp[1024];
					len -= packet_len;
					memcpy(temp, &buf[packet_len], len);
					memcpy(buf, temp, len);
				}
			}
			else
			{
				std::cout << "Client disconnected." << std::endl;
				break;
			}
		}

		close(client_socket);
	}

#ifdef _WIN32
	WSACleanup();
#endif
    
	return 0;
}

int StartServer(const char *ip, const char *port)
{
	struct addrinfo hints;
	struct addrinfo *res;

	memset(&hints, 0, sizeof hints);

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo(ip, port, &hints, &res);

	int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (bind(s, res->ai_addr, res->ai_addrlen))
	{
		std::cout << "Couldn't bind." << std::endl;
	}

	listen(s, SOMAXCONN);

	freeaddrinfo(res);

	return s;
}

void StopServer(int s)
{
	close(s);
}
