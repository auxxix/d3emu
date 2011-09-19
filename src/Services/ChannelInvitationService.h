#ifndef D3EMU_CHANNELINVITATIONSERVICE_H
#define D3EMU_CHANNELINVITATIONSERVICE_H

#include "Service.h"
#include "service/channel_invitation/definition/channel_invitation.pb.h"

namespace d3emu
{
    class ChannelInvitationService : public Service
    {
    public:
        ChannelInvitationService(uint32_t _service_hash, uint8_t _service_id);
        PacketResponse *Request(Client &client, PacketRequest &request_packet);
        std::string Name() const;

    private:
        // 0x01
        PacketResponse *SubscribeRequest(Client &client, PacketRequest &request_packet);
    };
}

#endif