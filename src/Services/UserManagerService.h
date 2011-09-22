#ifndef D3EMU_USERMANAGERSERVICE_H
#define D3EMU_USERMANAGERSERVICE_H

#include "Service.h"
#include "service/user_manager/user_manager.pb.h"

namespace d3emu
{
	namespace services
	{
		class UserManagerService : public Service
		{
		public:
			UserManagerService(uint32_t _service_hash, uint8_t _service_id);
			net::PacketResponse *Request(Client &client, net::PacketRequest &request_packet);
			std::string Name() const;

		private:
			net::PacketResponse *SubscribeToUserManagerRequest(Client &client, net::PacketRequest &request_packet);
		};
	}
}

#endif