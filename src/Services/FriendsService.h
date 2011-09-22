#ifndef D3EMU_FRIENDSSERVICE
#define D3EMU_FRIENDSSERVICE

#include "Service.h"
#include "service/friends/definition/friends.pb.h"

namespace d3emu
{
	namespace services
	{
		class FriendsService : public Service
		{
		public:
			FriendsService(uint32_t _service_hash, uint8_t _service_id);
			net::PacketResponse *Request(Client &client, net::PacketRequest &request_packet);
			std::string Name() const;

		private:
			net::PacketResponse *SubscribeToFriendsRequest(Client &client, net::PacketRequest &request_packet);
		};
	}
}

#endif
