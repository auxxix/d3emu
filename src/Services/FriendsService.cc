#include "FriendsService.h"

#include <iostream>

#ifdef _WIN32
	#include <WinSock2.h>
#else
    #include <sys/socket.h>
#endif

namespace d3emu
{

FriendsService::FriendsService(uint32_t _service_hash, uint8_t _service_id)
	: Service(_service_hash, _service_id) 
{
}

void FriendsService::SubscribeToFriendsRequest(bnet::protocol::friends::SubscribeToFriendsRequest &request)
{
	std::cout << request.GetTypeName() << ":" << std::endl << request.DebugString() << std::endl;

	bnet::protocol::friends::SubscribeToFriendsResponse response;

	response.set_max_friends(100);
	response.set_max_received_invitations(100);
	response.set_max_sent_invitations(100);

	unsigned char header[5] = { 0xfe, 0x00, this->current_packet()[2], 0x00, response.ByteSize() };
	std::string built_response = response.SerializeAsString();
	built_response.insert(built_response.begin(), header, header + 5);

	std::cout << response.GetTypeName() << ":" << std::endl << response.DebugString() << std::endl;
	send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
}

void FriendsService::Request(const char *packet, int packet_length)
{
	this->set_current_packet(packet, packet_length);

	switch ((uint8_t)packet[1])
	{
		case 0x01:
		{
			bnet::protocol::friends::SubscribeToFriendsRequest request;
			if (request.ParseFromArray(&packet[6], packet[5]))
				this->SubscribeToFriendsRequest(request);
			break;
		}
	}
}

std::string FriendsService::Name() const
{
	return std::string("d3emu::FriendsService");
}

}
