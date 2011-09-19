#ifndef D3EMU_GAMEMASTERSERVICE_H
#define D3EMU_GAMEMASTERSERVICE_H

#include "Service.h"
#include "service/game_master/game_master.pb.h"

namespace d3emu
{
    class GameMasterService : public Service
    {
    public:
        GameMasterService(uint32_t _service_hash, uint8_t _service_id);
        PacketResponse *Request(Client &client, PacketRequest &request_packet);
        std::string Name() const;

    private:
        // 0x02
        PacketResponse *ListFactoriesRequest(Client &client, PacketRequest &request_packet);
    };
}

#endif