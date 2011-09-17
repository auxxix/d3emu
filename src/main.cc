#ifdef _WIN32
    #include <ws2tcpip.h>
    #include <WinSock2.h>
    #include <BaseTsd.h> // SSIZE_T

    typedef SSIZE_T ssize_t;

    #define close(s) closesocket(x)

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

#include "lib/rpc/rpc.pb.h"
#include "lib/rpc/connection.pb.h"
#include "service/authentication/authentication.pb.h"
#include "service/toon/toon.pb.h"
#include "service/toon/toon_external.pb.h"
#include "service/exchange/exchange.pb.h"
#include "service/user_manager/user_manager.pb.h"
#include "service/friends/definition/friends.pb.h"
#include "service/channel_invitation/definition/channel_invitation.pb.h"
#include "service/game_master/game_master.pb.h"
#include "service/followers/definition/followers.pb.h"
#include "service/presence/presence.pb.h"
#include "service/storage/storage.pb.h"

#include "OnlineService.pb.h"

#include "Client.h"

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

/*
ERROR_3005 | Awaiting response
*/

namespace d3emu
{
    // 0x4124C31B bnet.protocol.toon.external.*

    class ToonExternalService : public Service
    {
    public:
        ToonExternalService(uint32_t _service_hash, uint8_t _service_id);
        void Request(const char *packet, int packet_length);
        std::string Name() const;
        
    private:
        // 0x01
        void ToonListRequest(bnet::protocol::toon::external::ToonListRequest &request);
        
        // 0x02
        void SelectToonRequest(bnet::protocol::toon::external::SelectToonRequest &request);
        
        // 0x03
        void CreateToonRequest(bnet::protocol::toon::external::CreateToonRequest &request);
    };

    ToonExternalService::ToonExternalService(uint32_t _service_hash, uint8_t _service_id)
        : Service(_service_hash, _service_id) 
    {
    }

    void ToonExternalService::ToonListRequest(bnet::protocol::toon::external::ToonListRequest &request)
    {
        std::cout << request.GetTypeName() << ":" << std::endl << request.DebugString() << std::endl;
        
        bnet::protocol::toon::external::ToonListResponse response;
        
        unsigned char header[5] = { 0xfe, 0x00, this->current_packet()[2], 0x00, response.ByteSize() };
        std::string built_response = response.SerializeAsString();
        built_response.insert(built_response.begin(), header, header + 5);
        
        std::cout << response.GetTypeName() << ":" << std::endl << response.DebugString() << std::endl;
        send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
    }
    
    void ToonExternalService::CreateToonRequest(bnet::protocol::toon::external::CreateToonRequest &request)
    {
        std::cout << request.GetTypeName() << ":" << std::endl << request.DebugString() << std::endl;
        
        
        bnet::protocol::toon::external::CreateToonResponse response;
        
        for (int i = 0; i < request.attribute_size(); i++)
        {
            // http://pastebin.com/ULfdcMba
            D3::OnlineService::HeroCreateParams params;
            params.ParseFromString(request.attribute(i).value().message_value());
            
            std::cout << params.GetTypeName() << ":" << std::endl
                << params.DebugString() << std::endl;
            
            response.mutable_toon()->set_low(234);
            response.mutable_toon()->set_high(234234);
        }
        
        unsigned char header[5] = { 0xfe, 0x00, this->current_packet()[2], 0x00, response.ByteSize() };
        std::string built_response = response.SerializeAsString();
        built_response.insert(built_response.begin(), header, header + 5);
        
        std::cout << response.GetTypeName() << ":" << std::endl << response.DebugString() << std::endl;
        send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
    }

    void ToonExternalService::Request(const char *packet, int packet_length)
    {
        this->set_current_packet(packet, packet_length);

        switch ((uint8_t)packet[1])
        {
            case 0x01:
            {
                bnet::protocol::toon::external::ToonListRequest request;
                if (request.ParseFromArray(&packet[6], packet[5]))
                    this->ToonListRequest(request);
                break;
            }
                
            case 0x03:
            {
                bnet::protocol::toon::external::CreateToonRequest request;
                if (request.ParseFromArray(&packet[6], packet[5]))
                    this->CreateToonRequest(request);
                break;
            }
        }
    }

    std::string ToonExternalService::Name() const
    {
        return std::string("d3emu::ToonListService");
    }

}

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
						d3emu::Client client;
						client.set_socket(client_socket);
						service->Request(&client, packet, packet_len);
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
