#ifndef D3EMU_USERMANAGERSERVICE_H
#define D3EMU_USERMANAGERSERVICE_H

#include "Service.h"
#include "service/user_manager/user_manager.pb.h"

namespace d3emu
{
    class UserManagerService : public Service
    {
    public:
        UserManagerService(uint32_t _service_hash, uint8_t _service_id);
        PacketResponse *Request(Client &client, PacketRequest &request_packet);
        std::string Name() const;

    private:
        PacketResponse *SubscribeToUserManagerRequest(Client &client, PacketRequest &request_packet);
    };
}

#endif