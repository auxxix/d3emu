#ifndef D3EMU_AUTHENTICATIONSERVICE_H
#define D3EMU_AUTHENTICATIONSERVICE_H

#include "Service.h"
#include "service/authentication/authentication.pb.h"

namespace d3emu
{
	namespace services
	{
		class AuthenticationService : public Service
		{
		public:
			AuthenticationService(uint32_t _service_hash, uint8_t _service_id);
			net::PacketResponse *Request(Client &client, net::PacketRequest &request_packet);
			std::string Name() const;

		private:
			// 0x01
			net::PacketResponse *LogonRequest(Client &client, net::PacketRequest &request_packet);
		};
	}
}

#endif