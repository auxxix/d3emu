#include "FriendsService.h"

#include <iostream>

namespace d3emu
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
        response_packet->mutable_header()->set_method_id(request_packet.header().method_id());
        response_packet->mutable_header()->set_request_id(request_packet.header().request_id());
        
        return response_packet;
    }

    PacketResponse *FriendsService::Request(const char *packet, int packet_length)
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
        return std::string("d3emu.FriendsService");
    }
}
