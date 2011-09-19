#include "PresenceService.h"
#include "service/presence/presence.pb.h"
#include <iostream>

namespace d3emu
{
    PresenceService::PresenceService(uint32_t _service_hash, uint8_t _service_id)
        : Service(_service_hash, _service_id) 
    {
    }

    PacketResponse *PresenceService::Request(Client &client, PacketRequest &request_packet)
    {
        PacketResponse *response_packet = 0;
        
        switch (request_packet.header().method_id()) 
        {
            case 0x01:
            {
                request_packet.set_message(new bnet::protocol::presence::SubscribeRequest());
                if (request_packet.mutable_message()->ParseFromString(request_packet.message_data()))
                    response_packet = this->SubscribeRequest(client, request_packet);
                else
                    request_packet.clear_message();
                break;
            }
        }
        
        return response_packet;
    }
    
    PacketResponse *PresenceService::SubscribeRequest(Client &client, PacketRequest &request_packet)
    {
        PacketResponse *response_packet = new PacketResponse();
        response_packet->mutable_header()->set_service_id(0xfe);
        response_packet->mutable_header()->set_method_id(request_packet.header().method_id());
        response_packet->mutable_header()->set_request_id(request_packet.header().request_id());
        
        return response_packet;
    }

    std::string PresenceService::Name() const
    {
        return std::string("d3emu.PresenceService");
    }
}
