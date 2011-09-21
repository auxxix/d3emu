#include "FollowersService.h"

#include <iostream>

namespace d3emu
{
	namespace Services
	{
		FollowersService::FollowersService(uint32_t _service_hash, uint8_t _service_id)
			: Service(_service_hash, _service_id) 
		{
		}

		Net::PacketResponse *FollowersService::SubscribeToFollowersRequest(Client &client, Net::PacketRequest &request_packet)
		{
			bnet::protocol::followers::SubscribeToFollowersResponse *response =
				new bnet::protocol::followers::SubscribeToFollowersResponse();
			/*
			bnet::protocol::followers::FollowedUser *followed_user =
				response.mutable_followed_users()->Add();
			followed_user->mutable_id()->set_high(24903242);
			followed_user->mutable_id()->set_low(239292);
			*/
			Net::PacketResponse *response_packet = new Net::PacketResponse();
			response_packet->set_message(response);
			response_packet->mutable_header()->set_service_id(0xfe);
			response_packet->mutable_header()->set_request_id(request_packet.header().request_id());
        
			return response_packet;
		}

		Net::PacketResponse *FollowersService::Request(Client &client, Net::PacketRequest &request_packet)
		{
			Net::PacketResponse *response_packet = 0;
        
			switch (request_packet.header().method_id())
			{
				case 0x01:
				{
					request_packet.set_message(new bnet::protocol::followers::SubscribeToFollowersRequest());
					if (request_packet.mutable_message()->ParseFromString(request_packet.message_data()))
						response_packet = this->SubscribeToFollowersRequest(client, request_packet);
					else
						request_packet.clear_message();
					break;
				}
			}
        
			return response_packet;
		}

		std::string FollowersService::Name() const
		{
			return std::string("d3emu.FollowersService");
		}
	}
}