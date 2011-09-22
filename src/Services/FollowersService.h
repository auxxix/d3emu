#ifndef D3EMU_FOLLOWERSSERVICE_H
#define D3EMU_FOLLOWERSSERVICE_H

#include "Service.h"
#include "service/followers/definition/followers.pb.h"

namespace d3emu
{
	namespace services
	{
		class FollowersService : public Service
		{
		public:
			FollowersService(uint32_t _service_hash, uint8_t _service_id);
			net::PacketResponse *Request(Client &client, net::PacketRequest &request_packet);
			std::string Name() const;

		private:
			// 0x01
			net::PacketResponse *SubscribeToFollowersRequest(Client &client, net::PacketRequest &request_packet);
		};
	}
}

#endif