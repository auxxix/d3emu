#include "FriendsService.h"

#include <iostream>

namespace d3emu
{
	namespace Services
	{
		FriendsService::FriendsService(uint32_t _service_hash, uint8_t _service_id)
			: Service(_service_hash, _service_id) 
		{
		}

		PacketResponse *FriendsService::SubscribeToFriendsRequest(Client &client, PacketRequest &request_packet)
		{
			bnet::protocol::friends::SubscribeToFriendsResponse *response =
				new bnet::protocol::friends::SubscribeToFriendsResponse();

			response->set_max_friends(100);
			response->set_max_received_invitations(100);
			response->set_max_sent_invitations(100);

			PacketResponse *response_packet = new PacketResponse();
			response_packet->set_message(response);
			response_packet->mutable_header()->set_service_id(0xfe);
			response_packet->mutable_header()->set_request_id(request_packet.header().request_id());
        
			return response_packet;
		}

		PacketResponse *FriendsService::Request(Client &client, PacketRequest &request_packet)
		{
			PacketResponse *response_packet = 0;
        
			switch (request_packet.header().method_id())
			{
				case 0x01:
				{
					request_packet.set_message(new bnet::protocol::friends::SubscribeToFriendsRequest());
					if (request_packet.mutable_message()->ParseFromString(request_packet.message_data()))
						response_packet = this->SubscribeToFriendsRequest(client, request_packet);
					else
						request_packet.clear_message();
					break;
				}
			}
        
			return response_packet;
		}

		std::string FriendsService::Name() const
		{
			return std::string("d3emu.FriendsService");
		}
	}
}
