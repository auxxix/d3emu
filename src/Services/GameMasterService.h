#ifndef D3EMU_GAMEMASTERSERVICE_H
#define D3EMU_GAMEMASTERSERVICE_H

#include "Service.h"
#include "service/game_master/game_master.pb.h"

namespace d3emu
{
	namespace Services
	{
		class GameMasterService : public Service
		{
		public:
			GameMasterService(uint32_t _service_hash, uint8_t _service_id);
			Net::PacketResponse *Request(Client &client, Net::PacketRequest &request_packet);
			std::string Name() const;

		private:
			// 0x02
			Net::PacketResponse *ListFactoriesRequest(Client &client, Net::PacketRequest &request_packet);
		};
	}
}
#endif