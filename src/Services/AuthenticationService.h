#ifndef D3EMU_AUTHENTICATIONSERVICE_H
#define D3EMU_AUTHENTICATIONSERVICE_H

#include "Service.h"
#include "service/authentication/authentication.pb.h"

namespace d3emu
{
	namespace Services
	{
		class AuthenticationService : public Service
		{
		public:
			AuthenticationService(uint32_t _service_hash, uint8_t _service_id);
			PacketResponse *Request(Client &client, PacketRequest &request_packet);
			std::string Name() const;

		private:
			// 0x01
			PacketResponse *LogonRequest(Client &client, PacketRequest &request_packet);
		};
	}
}

#endif