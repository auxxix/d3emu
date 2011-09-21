#ifndef D3EMU_USERMANAGERSERVICE_H
#define D3EMU_USERMANAGERSERVICE_H

#include "Service.h"
#include "service/user_manager/user_manager.pb.h"

namespace d3emu
{
	namespace Services
	{
		class UserManagerService : public Service
		{
		public:
			UserManagerService(uint32_t _service_hash, uint8_t _service_id);
			Net::PacketResponse *Request(Client &client, Net::PacketRequest &request_packet);
			std::string Name() const;

		private:
			Net::PacketResponse *SubscribeToUserManagerRequest(Client &client, Net::PacketRequest &request_packet);
		};
	}
}

#endif