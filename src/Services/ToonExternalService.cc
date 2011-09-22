#include "ToonExternalService.h"
#include "../bnet/OnlineService.pb.h"

#include <iostream>

namespace d3emu
{
	namespace services
	{
		ToonExternalService::ToonExternalService(uint32_t _service_hash, uint8_t _service_id)
			: Service(_service_hash, _service_id) 
		{
		}
    
		net::PacketResponse *ToonExternalService::ToonListRequest(Client &client, net::PacketRequest &request_packet)
		{
			bnet::protocol::toon::external::ToonListResponse *response =
				new bnet::protocol::toon::external::ToonListResponse();
        
			net::PacketResponse *response_packet = new net::PacketResponse();
			response_packet->set_message(response);
			response_packet->mutable_header()->set_service_id(0xfe);
			response_packet->mutable_header()->set_request_id(request_packet.header().request_id());
        
			return response_packet;
		}
    
		net::PacketResponse *ToonExternalService::CreateToonRequest(Client &client, net::PacketRequest &request_packet)
		{
			bnet::protocol::toon::external::CreateToonResponse *response =
				new bnet::protocol::toon::external::CreateToonResponse();
        
			/*
			// http://pastebin.com/ULfdcMba
			D3::OnlineService::HeroCreateParams params;
			params.ParseFromString(request.attribute(0).value().message_value());
            
			std::cout << params.GetTypeName() << ":" << std::endl
				<< params.DebugString() << std::endl;
			*/
        
			response->mutable_toon()->set_low(2L);
			response->mutable_toon()->set_high(0x300016200004433L);
        
			net::PacketResponse *response_packet = new net::PacketResponse();
			response_packet->set_message(response);
			response_packet->mutable_header()->set_service_id(0xfe);
			response_packet->mutable_header()->set_request_id(request_packet.header().request_id());
        
			return response_packet;
		}
    
		net::PacketResponse *ToonExternalService::Request(Client &client, net::PacketRequest &request_packet)
		{
			net::PacketResponse *response_packet = 0;

			switch (request_packet.header().method_id())
			{
				case 0x01:
				{
					request_packet.set_message(new bnet::protocol::toon::external::ToonListRequest());
					if (request_packet.message()->ParseFromString(request_packet.message_data()))
						response_packet = this->ToonListRequest(client, request_packet);
					else
						request_packet.clear_message();
					break;
				}
                
				case 0x03:
				{
					request_packet.set_message(new bnet::protocol::toon::external::CreateToonRequest());
					if (request_packet.message()->ParseFromString(request_packet.message_data()))
						response_packet = this->CreateToonRequest(client, request_packet);
					else
						request_packet.clear_message();
					break;
				}
			}
        
			return response_packet;
		}
    
		std::string ToonExternalService::Name() const
		{
			return std::string("d3emu.ToonListService");
		}
	}
}