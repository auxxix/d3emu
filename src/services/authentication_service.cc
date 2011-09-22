#include "authentication_service.h"
#include <iostream>

namespace d3emu
{
	namespace services
	{
		AuthenticationService::AuthenticationService(uint32_t _service_hash, uint8_t _service_id)
			: Service(_service_hash, _service_id) 
		{
		}

		net::PacketResponse *AuthenticationService::LogonRequest(Client &client, net::PacketRequest &request_packet)
		{
			bnet::protocol::authentication::LogonResponse *response =
				new bnet::protocol::authentication::LogonResponse();

			response->mutable_account()->set_high(0x100000000000000L);
			response->mutable_account()->set_low(1L);
			response->mutable_game_account()->set_high(0x200006200004433L);
			response->mutable_game_account()->set_low(3L);

			net::PacketResponse *response_packet = new net::PacketResponse();
			response_packet->set_message(response);
			response_packet->mutable_header()->set_service_id(0xfe);
			response_packet->mutable_header()->set_request_id(request_packet.header().request_id());
        
			return response_packet;
		}

		net::PacketResponse *AuthenticationService::Request(Client &client, net::PacketRequest &request_packet)
		{
			net::PacketResponse *response_packet = 0;
        
			switch (request_packet.header().method_id())
			{
				case 0x01:
				{
					request_packet.set_message(new bnet::protocol::authentication::LogonRequest());
					if (request_packet.message()->ParseFromString(request_packet.message_data()))
						response_packet = this->LogonRequest(client, request_packet);
					else
						request_packet.clear_message();
					break;
				}
			}
        
			return response_packet;
		}

		std::string AuthenticationService::Name() const
		{
			return std::string("d3emu.AuthenticationService");
		}
	}
}