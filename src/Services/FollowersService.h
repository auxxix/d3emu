#ifndef D3EMU_FOLLOWERSSERVICE_H
#define D3EMU_FOLLOWERSSERVICE_H

#include "Service.h"
#include "service/followers/definition/followers.pb.h"

namespace d3emu
{
	namespace Services
	{
		class FollowersService : public Service
		{
		public:
			FollowersService(uint32_t _service_hash, uint8_t _service_id);
			Net::PacketResponse *Request(Client &client, Net::PacketRequest &request_packet);
			std::string Name() const;

		private:
			// 0x01
			Net::PacketResponse *SubscribeToFollowersRequest(Client &client, Net::PacketRequest &request_packet);
		};
	}
}

#endif