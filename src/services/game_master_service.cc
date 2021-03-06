#include "game_master_service.h"

#include <iostream>

namespace d3emu
{
	namespace services
	{
		GameMasterService::GameMasterService(uint32_t _service_hash, uint8_t _service_id)
			: Service(_service_hash, _service_id) 
		{
		}

		net::PacketResponse *GameMasterService::ListFactoriesRequest(Client &client, net::PacketRequest &request_packet)
		{
			bnet::protocol::game_master::ListFactoriesResponse *response =
				new bnet::protocol::game_master::ListFactoriesResponse();

			//response.set_total_results(1);

			net::PacketResponse *response_packet = new net::PacketResponse();
			response_packet->set_message(response);
			response_packet->mutable_header()->set_service_id(0xfe);
			response_packet->mutable_header()->set_request_id(request_packet.header().request_id());
        
			return response_packet;
		}

		net::PacketResponse *GameMasterService::Request(Client &client, net::PacketRequest &request_packet)
		{
			net::PacketResponse *response_packet = 0;
        
			switch (request_packet.header().method_id())
			{
				case 0x02:
				{
					request_packet.set_message(new bnet::protocol::game_master::ListFactoriesRequest());
					if (request_packet.mutable_message()->ParseFromString(request_packet.message_data()))
						response_packet = this->ListFactoriesRequest(client, request_packet);
					else
						request_packet.clear_message();
					break;
				}
			}
        
			return response_packet;
		}

		std::string GameMasterService::Name() const
		{
			return std::string("d3emu.GameMasterService");
		}
	}
}