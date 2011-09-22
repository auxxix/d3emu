#include "ChannelInvitationService.h"

#include <iostream>

namespace d3emu
{
	namespace services
	{
		ChannelInvitationService::ChannelInvitationService(uint32_t _service_hash, uint8_t _service_id)
			: Service(_service_hash, _service_id) 
		{
		}

		net::PacketResponse *ChannelInvitationService::SubscribeRequest(Client &client, net::PacketRequest &request_packet)
		{
			bnet::protocol::channel_invitation::SubscribeResponse *response =
				new bnet::protocol::channel_invitation::SubscribeResponse();

			net::PacketResponse *response_packet = new net::PacketResponse();
			response_packet->set_message(response);
			response_packet->mutable_header()->set_service_id(0xfe);
			response_packet->mutable_header()->set_request_id(request_packet.header().request_id());
    
			return response_packet;
		}

		net::PacketResponse *ChannelInvitationService::Request(Client &client, net::PacketRequest &request_packet)
		{
			net::PacketResponse *response_packet = 0;
    
			switch (request_packet.header().method_id())
			{
				case 0x01:
				{
					request_packet.set_message(new bnet::protocol::channel_invitation::SubscribeRequest());
					if (request_packet.mutable_message()->ParseFromString(request_packet.message_data()))
						response_packet = this->SubscribeRequest(client, request_packet);
					else
						request_packet.clear_message();
					break;
				}
			}
    
			return response_packet;
		}

		std::string ChannelInvitationService::Name() const
		{
			return std::string("d3emu.ChannelInvitationService");
		}
	}
}