#ifndef D3EMU_PRESENCESERVICE_H
#define D3EMU_PRESENCESERVICE_H

#include "Service.h"
#include "service/presence/presence.pb.h"

namespace d3emu
{
    class PresenceService : public Service
    {
    public:
        PresenceService(uint32_t _service_hash, uint8_t _service_id);
        PacketResponse *Request(Client &client, PacketRequest &request_packet);
        std::string Name() const;

    private:
        PacketResponse *SubscribeRequest(Client &client, PacketRequest &request_packet);
    };
}

#endif
