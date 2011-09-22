#ifndef D3EMU_GAMEMASTERSERVICE_H
#define D3EMU_GAMEMASTERSERVICE_H

#include "service.h"
#include "service/game_master/game_master.pb.h"

namespace d3emu
{
	namespace services
	{
		class GameMasterService : public Service
		{
		public:
			GameMasterService(uint32_t _service_hash, uint8_t _service_id);
			net::PacketResponse *Request(Client &client, net::PacketRequest &request_packet);
			std::string Name() const;

		private:
			// 0x02
			net::PacketResponse *ListFactoriesRequest(Client &client, net::PacketRequest &request_packet);
		};
	}
}
#endif