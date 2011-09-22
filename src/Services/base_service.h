#ifndef D3EMU_BASESERVICE_H
#define D3EMU_BASESERVICE_H

#include "Service.h"
#include "lib/rpc/connection.pb.h"

namespace d3emu
{
	namespace services
	{
		class BaseService : public Service
		{
		public:
			BaseService(uint32_t _service_hash, uint8_t _service_id);
        
			net::PacketResponse *Request(Client &client, net::PacketRequest &request_packet);
        
			std::string Name() const;

		private:
			net::PacketResponse *ConnectRequest(Client &client, net::PacketRequest &request_packet);
			net::PacketResponse *BindRequest(Client &client, net::PacketRequest &request_packet);
		};
	}
}

#endif
