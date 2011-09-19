#ifndef D3EMU_BASESERVICE_H
#define D3EMU_BASESERVICE_H

#include "Service.h"
#include "lib/rpc/connection.pb.h"

namespace d3emu
{
    class BaseService : public Service
    {
    public:
        BaseService(uint32_t _service_hash, uint8_t _service_id);
        
        PacketResponse *Request(Client &client, PacketRequest &request_packet);
        
        std::string Name() const;

    private:
        PacketResponse *ConnectRequest(Client &client, PacketRequest &request_packet);
        PacketResponse *BindRequest(Client &client, PacketRequest &request_packet);
    };
}

#endif
