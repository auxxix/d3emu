#include "FollowersService.h"

#include <iostream>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#endif

namespace d3emu
{

FollowersService::FollowersService(uint32_t _service_hash, uint8_t _service_id)
	: Service(_service_hash, _service_id) 
{
}

void FollowersService::SubscribeToFollowersRequest(bnet::protocol::followers::SubscribeToFollowersRequest &request)
{
	std::cout << request.GetTypeName() << ":" << std::endl
		<< request.DebugString() << std::endl;

	bnet::protocol::followers::SubscribeToFollowersResponse response;
	/*
	bnet::protocol::followers::FollowedUser *followed_user =
		response.mutable_followed_users()->Add();
	followed_user->mutable_id()->set_high(24903242);
	followed_user->mutable_id()->set_low(239292);
	*/
	unsigned char header[5] = { 0xfe, 0x00, this->current_packet()[2], 0x00, response.ByteSize() };
	std::string built_response = response.SerializeAsString();
	built_response.insert(built_response.begin(), header, header + 5);

	/*
	printf("<-- (Hex): ");
	for (size_t i = 0; i < built_response.length(); i++)
	{
		printf("%02X ", built_response[i] & 0xff);
	}
	printf("\n");
	*/

	std::cout << response.GetTypeName() << ":"
		<< std::endl << response.DebugString() << std::endl;
	send(this->client()->socket(), built_response.c_str(), built_response.length(), 0);
}

void FollowersService::Request(const char *packet, int packet_length)
{
	this->set_current_packet(packet, packet_length);

	switch ((uint8_t)packet[1])
	{
		case 0x01:
		{
			bnet::protocol::followers::SubscribeToFollowersRequest request;
			if (request.ParseFromArray(&packet[6], packet[5]))
				this->SubscribeToFollowersRequest(request);
			break;
		}
	}
}

std::string FollowersService::Name() const
{
	return std::string("d3emu::FollowersService");
}

}