#ifndef D3EMU_FRIENDSSERVICE
#define D3EMU_FRIENDSSERVICE

#include "Service.h"
#include "service/friends/definition/friends.pb.h"

namespace d3emu
{
	namespace Services
	{
		class FriendsService : public Service
		{
		public:
			FriendsService(uint32_t _service_hash, uint8_t _service_id);
			PacketResponse *Request(Client &client, PacketRequest &request_packet);
			std::string Name() const;

		private:
			PacketResponse *SubscribeToFriendsRequest(Client &client, PacketRequest &request_packet);
		};
	}
}

#endif
