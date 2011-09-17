#ifndef D3EMU_GAMEMASTERSERVICE_H
#define D3EMU_GAMEMASTERSERVICE_H

#include <stdint.h>

#include "Service.h"

#include "service/game_master/game_master.pb.h"

namespace d3emu
{

// 0x810CB195 bnet.protocol.game_master.ListFactoriesRequest

class GameMasterService : public Service
{
public:
	GameMasterService(uint32_t _service_hash, uint8_t _service_id);
	void Request(const char *packet, int packet_length);
	std::string Name() const;

private:
	// 0x02
	void ListFactoriesRequest(bnet::protocol::game_master::ListFactoriesRequest &request);
};

}

#endif