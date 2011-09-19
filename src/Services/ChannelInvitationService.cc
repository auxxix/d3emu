#include "ChannelInvitationService.h"

#include <iostream>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <sys/socket.h>
#endif

namespace d3emu
{

ChannelInvitationService::ChannelInvitationService(uint32_t _service_hash, uint8_t _service_id)
	: Service(_service_hash, _service_id) 
{
}

PacketResponse *ChannelInvitationService::SubscribeRequest(Client &client, PacketRequest &request_packet)
{
	bnet::protocol::channel_invitation::SubscribeResponse response =
        new bnet::protocol::channel_invitation::SubscribeResponse();

	
    return 
}

void ChannelInvitationService::Request(const char *packet, int packet_length)
{
	this->set_current_packet(packet, packet_length);

	switch ((uint8_t)packet[1])
	{
		case 0x01:
		{
			bnet::protocol::channel_invitation::SubscribeRequest request;
			if (request.ParseFromArray(&packet[6], packet[5]))
				this->SubscribeRequest(request);
			break;
		}
	}
}

std::string ChannelInvitationService::Name() const
{
	return std::string("d3emu::ChannelInvitationService");
}

}